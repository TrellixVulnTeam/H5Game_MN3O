#include "pw_gdb_client.h"
#include <iostream>
#include "pw_gdb_def.h"
#include "pw_gdb_socket_utils.h"

#ifndef _NODEJS_CLIENT
	#include "algorithm/pw_md5.h"
	#include "pw_time.h"
#else
	#include "pw_md5.h"
	#include "pw_gdb_time.h"
#endif

namespace gdb
{
	static int64 clib_time()
	{
		time_t result = 0;
		::time(&result);
		return result;
	}


	std::ostream& operator<<(std::ostream& s,const Client::Configure& conf)
	{
		s << " addr:" << conf.addr
			<< " port:" << conf.port
			<< " user:" << conf.user
			// << " pswd:" << conf.pswd
			<< " db:" << conf.dbname;

			return s;
	}

	// *******************************************************************

	Client::Request::Request()
		: requestId(0)
		, writer(&actualWriter)
	{

	}

	// *******************************************************************

	Client::Client()
		: m_mReactor(8)
		, m_nLastRequestId(0)
		, m_nLastReconnectTime(0)
		, m_nClientFlags(gdb::CLIENT_FLAGS_DEFAULT)
	{
#ifndef _NODEJS_CLIENT
		m_objLazyTimer.Startup(pwutils::time::Second(8));
#endif
	}

	int Client::Connect( const char* addr,int port )
	{
		m_nFlags = 0;

		m_mReader.Skip(m_mReader.Length());

		m_mConf.addr = addr;
		m_mConf.port = port;

		int r = gdb::SocketClient::ConnectSync(addr,port);
		if( r == 0 )
		{
			m_mReactor.Add(this,gdb::SocketReactor::MASK_DEFAULT);
		}
		return r;
	}

	int Client::Connect( const Configure& conf )
	{
		Configure tmpconf = conf;
		if(this->Connect(tmpconf.addr.c_str(),tmpconf.port) != 0)
			return -1;
		if(this->Authentication(tmpconf.user.c_str(),tmpconf.pswd.c_str()) != 0)
			return -2;
		if(this->SelectDatabase(tmpconf.dbname.c_str()) != 0)
			return -3;
		if(this->SetClientFlags(m_nClientFlags) != 0)
			return -4;

		std::cout << __FUNCTION__ << tmpconf << std::endl;
		return 0;
	}

	int Client::OnDataIncoming()
	{
		int r = gdb::SocketClient::OnDataIncoming();
		if( r < 0 )
			return r;

		gdb::ProtocolReader reader(&m_mReader);
		while(gdb::SProtocolPacket* packet = reader.Read())
		{
			if(!packet->IsTerminator())
				m_vPackets.push_back(packet);

			if(!packet->more || packet->IsTerminator())
			{
				r = this->HandlePackets(&m_vPackets[0],m_vPackets.size());
				this->m_vPackets.clear();
			}

			if(r < 0)
			{
				std::cerr << pwutils::time::str() << " " << __FUNCTION__ << " Closed" << std::endl;
				break;
			}
		}

		// 检查大小
		if(m_mReader.Length() > 4*1024*1024)
		{
			m_mReader.Skip(m_mReader.Length());
			m_mReader.Free(0);
			return -1;
		}

		return r;
	}

	int Client::OnClose()
	{
		std::cerr << pwutils::time::str() << " " << __FUNCTION__ << " " << m_mConf << std::endl;

		m_mReactor.Del(this);

		return gdb::SocketClient::OnClose();
	}

	int Client::HandlePackets(gdb::SProtocolPacket** packets,size_t count)
	{
		if(count <= 0)
			return -1;

		bool rebuildStream = true;
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		CollectionFuturesT::iterator iter = m_vFutures.find(ctx);
		if(iter != m_vFutures.end())
		{
			Future* f = iter->second;
			m_vFutures.erase(iter);

			rebuildStream = f->IsAllowRebuildStream();

			f->packets.clear();
			f->packets.reserve(count);
			for(size_t i = 0; i < count; ++i)
				f->packets.push_back(packets[i]);

			f->OnFinished();
			f->Destroy();
		}

		if(rebuildStream)
			this->m_mReader.RebuildStream();

		return 0;
	}

	int Client::CheckAndReconnect()
	{
		if(!IsConnected())
		{
			this->m_nLastReconnectTime = clib_time();
			int r = this->Reconnect();
			if( r < 0 )
			{
				std::cout << pwutils::time::str() << " " << __FUNCTION__ << " Failed:" << r << " info:" << m_mConf << std::endl;
				return r;
			}
			std::cout << pwutils::time::str() << " " << __FUNCTION__ << " Successful: " << m_mConf << std::endl;
		}
		return 0;
	}

	int Client::Update(int64 currTick)
	{
		if(currTick < 0)
			currTick = pwutils::time::get();

		m_mReactor.Update();

#ifndef _NODEJS_CLIENT
		if(m_objLazyTimer.IsPeriodExpired(currTick))
		{
			this->CheckExpiredFuture(currTick);
		}
#endif
		return 0;
	}

	int Client::OnConnected()
	{	
		return gdb::SocketClient::OnConnected();
	}

	void Client::CreateRequest( Request& req,int64 cmd )
	{
		req.cmd = cmd;
		req.requestId = MakeRequestId();

		req.Reset();
		req.writer.WriteI(cmd,true);
		req.writer.WriteI(req.requestId,true);
	}

	void Client::CommitRequest( Request& req,Response* res)
	{
		this->PushSendBuffer(&req.actualWriter);
		this->CommitSendBuffer();

		if(res != 0)
		{
			this->FlushSendBuffer();
			this->FetchResponse(req.requestId,res);
		}
	}


	void Client::FetchResponse( int64 requestId,Response* res )
	{
		this->FlushSendBuffer();

		int64 cst_timeout = pwutils::time::Msec(800000);

		res->packets.clear();

		StackFuture future;
		future._requestId = requestId;
		m_vFutures[future._requestId] = &future;

		gdb::ProtocolReader reader(&m_mReader);

		int64 starttime = pwutils::time::get();

		this->m_mReader.RebuildStream();

		while(!future.IsFinished() && !future.IsExpired() && this->IsConnected())
		{
			unsigned mask = this->WaitForReadable(GetSocket(),100);
			if(mask & _WAIT_READ)
			{
				if(this->OnDataIncoming() < 0)
				{
					m_bConnected = false;
					break;
				}
			}
			if(mask & _WAIT_CLOSE)
			{
				m_bConnected = false;
			}

			int64 curr = pwutils::time::get();
			int64 diff = curr - starttime;
			
			if(diff > cst_timeout)
			{
				std::cerr << pwutils::time::str() << " " << __FUNCTION__ << " timeout " << this->m_mConf << std::endl;
				break;
			}
		}

		// 确保删除(万一超时的话)
		m_vFutures.erase(future._requestId);

		res->packets = future.packets;
	}

	Client::Future* Client::ListenFuture( fnFutureCallback cb,void* context1,void* context2 )
	{
		Future* f = new Future();
		f->context1 = context1;
		f->context2 = context2;
		f->_callback = cb;
		f->_requestId = m_nLastRequestId;
		m_vFutures[f->_requestId] = f;
		return f;
	}

	int64 Client::MakeRequestId()
	{
		++m_nLastRequestId;
		return m_nLastRequestId;
	}

	int Client::Authentication( const char* user,const char* pswd )
	{
		m_mReactor.Update();

		m_mConf.user = user;
		m_mConf.pswd = pswd;

		std::string md5pswd = pwutils::Md5(pswd);

		Request req;
		Response res;
		CreateRequest(req,CMD_AUTHENTICATION);
		req.GetWriter()->WriteS(user,cst_string_auto_len,true);
		req.GetWriter()->WriteS(md5pswd.c_str(),cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::CreateDatabase( const char* dbname )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_CREATE_DATABASE);
		req.GetWriter()->WriteS(dbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::DeleteDatabase( const char* dbname )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_DELETE_DATABASE);
		req.GetWriter()->WriteS(dbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::SelectDatabase( const char* dbname )
	{
		m_mConf.dbname = dbname;

		Request req;
		Response res;
		CreateRequest(req,CMD_SELECT_DATABASE);
		req.GetWriter()->WriteS(dbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	void Client::CheckExpiredFuture(int64 currTick)
	{
		for(CollectionFuturesT::iterator iter = m_vFutures.begin(); iter != m_vFutures.end(); )
		{
			if(Future* f = iter->second)
			{
				if(f->_timeoutTick <= currTick)
				{
					iter = m_vFutures.erase(iter);
					f->OnExpired();
					f->Destroy();
					continue;
				}
			}
			++iter;
		}
	}

	int Client::ListDatabases( std::vector<std::string>& list )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_LIST_DATABASES);
		req.GetWriter()->WriteNil();
		CommitRequest(req,&res);

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < res.packets.size(); ++i)
		{
			list.push_back(std::string(res.packets[i]->data,res.packets[i]->size));
		}

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::Reconnect()
	{
		this->Close();
		this->Create();
		return this->Connect(m_mConf);
	}

	int Client::AddUser( const std::string& user,const std::string& pswd,bool sys )
	{
		std::string md5pswd = pwutils::Md5(pswd);

		Request req;
		Response res;
		CreateRequest(req,CMD_SYS_ADDUSER);
		req.GetWriter()->WriteS(user.c_str(),user.length(),true);
		req.GetWriter()->WriteS(md5pswd.c_str(),md5pswd.length(),true);
		req.GetWriter()->WriteI(sys ? 1 : 0);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();

	}

	int Client::ModUser( const std::string& user,const std::string& pswd,bool sys )
	{
		std::string md5pswd = pwutils::Md5(pswd);

		Request req;
		Response res;
		CreateRequest(req,CMD_SYS_MODUSER);
		req.GetWriter()->WriteS(user.c_str(),user.length(),true);
		req.GetWriter()->WriteS(md5pswd.c_str(),md5pswd.length(),true);
		req.GetWriter()->WriteI(sys ? 1 : 0);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::DelUser( const std::string& user )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_SYS_DELUSER);
		req.GetWriter()->WriteS(user.c_str(),user.length());
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::LoadDatabase( const char* dbname )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_LOAD_DATABASE);
		req.GetWriter()->WriteS(dbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::UnloadDatabase( const char* dbname )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_UNLOAD_DATABASE);
		req.GetWriter()->WriteS(dbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::CopyDatabase( const char* srcdbname,const char* dstdbname )
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_COPY_DATABASE);
		req.GetWriter()->WriteS(srcdbname,cst_string_auto_len,true);
		req.GetWriter()->WriteS(dstdbname,cst_string_auto_len);
		CommitRequest(req,&res);

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	int Client::SetClientFlags(int64 flags)
	{
		Request req;
		Response res;
		CreateRequest(req,CMD_CLIENT_FLAGS);
		req.GetWriter()->WriteI(flags);
		CommitRequest(req,&res);

		m_nClientFlags = flags;

		m_sLastError = res.GetErrorString();
		return (int)res.GetErrorCode();
	}

	// *********************************************************************************

	Client::Future::Future()
		: _requestId(0)
		, context1(0)
		, context2(0)
		, _finished(false)
		, _expired(false)
	{
		this->_timeoutTick = pwutils::time::get() + pwutils::time::Second(10);
	}

	Client::Future::~Future()
	{

	}

	void Client::Future::OnFinished()
	{
		this->_finished = true;

		if(this->_callback.valid())
			this->_callback(this,MODE_FINISHED);
	}

	void Client::Future::OnExpired()
	{
		this->_expired = true;

		if(this->_callback.valid())
			this->_callback(this,MODE_TIMEOUT);
	}

	void Client::Future::Destroy()
	{
		delete this;
	}

	bool Client::Future::IsAllowRebuildStream()
	{
		return true;
	}

	// *********************************************************************************

	void Client::StackFuture::Destroy()
	{
		
	}

	bool Client::StackFuture::IsAllowRebuildStream()
	{
		return false;
	}

	// *********************************************************************************

	int64 Client::Response::GetErrorCode()
	{
		if(packets.size() <= 0)
			return -1;
		return _checked_integer(&packets[0],packets.size(),PKT_INDEX_RET);
	}

	const char* Client::Response::GetErrorString()
	{
		if(packets.size() <= 0)
			return "NoResponse";
		return _checked_string(&packets[0],packets.size(),PKT_INDEX_ERR);
	}

	int64 Client::Response::CheckedInteger( size_t i )
	{
		return _checked_integer(&packets[0],packets.size(),i);
	}

	const char* Client::Response::CheckedString( size_t i )
	{
		return _checked_string(&packets[0],packets.size(),i);
	}

	double Client::Response::CheckedDecimal( size_t i )
	{
		return _checked_decimal(&packets[0],packets.size(),i);
	}

	void Client::Response::CheckedBuffer( size_t i,char** data,size_t* size )
	{
		_checked_buffer(&packets[0],packets.size(),i,data,size);
	}

	bool Client::Response::IsSuccessful()
	{
		return GetErrorCode() == FAILED_SUCCESSFUL;
	}

	bool Client::Response::IsSuccessfulButNoFound()
	{
		return GetErrorCode() == FAILED_NOFOUND;
	}

	SProtocolPacket* Client::Response::Get( size_t i )
	{
		if(i < packets.size())
			return packets[i];
		return 0;
	}

	void Client::Response::ToArray( std::vector<std::string>& array )
	{
		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < packets.size(); ++i)
		{
			array.push_back(std::string(packets[i]->data,packets[i]->size));
		}
	}

	void Client::Response::ToArray( std::vector<gdb::SProtocolPacket*>& array )
	{
		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < packets.size(); ++i)
		{
			array.push_back(packets[i]);
		}
	}

	// *********************************************************************************


}