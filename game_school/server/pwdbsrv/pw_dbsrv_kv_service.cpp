#include "pw_dbsrv_kv_service.h"
#include "pw_rpc_names.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_utils.h"
#include "pw_ngs_def.h"
#include "pw_ngs_common.h"
#include "pw_utils.h"
#include "kvorm/pw_orm_reflection.h"
#include "kvorm/pw_orm_passporthuman.h"

#include "bson/bson.h"
#include "pw_kvorm_uuid_pool.h"
#include "pw_error_handler.h"

namespace pwdbsrv
{
	const std::string g_kvdb_uuid_meta("uuid");

	SImplKVDB::SImplKVDB()
		: m_bClosePerformed(false)
	{
		this->Initial();
		m_pAClient = new gdb::AsynchronousClient();
		m_pAClient->doref();

		this->m_objPingTimer.Startup(pwutils::time::Second(3));
		this->m_objTimer1Sec.Startup(pwutils::time::Second(1));
	}

	SImplKVDB::~SImplKVDB()
	{
		Cleanup();
		_safe_delete(m_pAClient);
	}

	int SImplKVDB::Initial()
	{
		InitialRpcs(this);

		return 0;
	}


	int SImplKVDB::Startup(const std::string& name, pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwdbsrv/database/host");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwdbsrv/database/port","3306").c_str());
		std::string user = params.GetValue("/pwdist/pwdbsrv/database/user");
		std::string pswd = params.GetValue("/pwdist/pwdbsrv/database/pswd");
		std::string db  = params.GetValue("/pwdist/pwdbsrv/database/name");

		if(m_pAClient->Connect(host.c_str(),port) != 0)
		{
			std::cout << "connect to db failed," << host << ":" << port << std::endl;
			return -1;
		}

		if(m_pAClient->Authentication(user.c_str(),pswd.c_str()) != 0)
		{
			std::cout << "auth failed,host:" << host << " port:" << port << std::endl;
			return -2;
		}

		m_pAClient->CreateDatabase(db.c_str());

		if(m_pAClient->SelectDatabase(db.c_str()) != 0)
		{
			std::cout << "select database failed,host:" << host << " port:" << port << std::endl;
			return -3;
		}

		m_pAClient->Update(this->GetFrameTime());
		
		this->InitialLookTables();

		return pwdist::Port::Startup(name,node);
	}

	int SImplKVDB::Cleanup()
	{
		return 0;
	}

	int SImplKVDB::InitialLookTables()
	{
		m_pAClient->Hvals((orm::Human::meta()));
		m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_initial_looktable));

		return 0;
	}

	void SImplKVDB::_dbcb_initial_looktable(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		GMDB_FOREACH_PACKETS(i,f)
		{
			char* data = NULL;
			size_t size = 0;
			f->CheckedBuffer(i,&data,&size);

			if(data != NULL || size > 0)
			{
				orm::Human info;
				info.from_bson(data,size);

				if(info.id > 0)
				{
					this->m_mHumanInfos[info.id] = info;
					this->m_mHumanNames[info.name.c_str()] = info.id;
				}
			}
		}
	}

	int SImplKVDB::OnThreadStarted()
	{
		return pwdist::Port::OnThreadStarted();
	}

	void SImplKVDB::_rpc_call_Hsetnx_incrid(const char* meta,pwdist::Chunk bson)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		pwutils::KvormBase* base = orm::createObject(bson.buf,bson.len);
		pwassert(base);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hincrby(g_kvdb_uuid_meta,meta);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_setnx_incrid_1));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsContext<pwutils::KvormBase>(base);
		ctx->AddDependsContext<std::string>(new std::string(meta));
	}

	void SImplKVDB::_dbcb_setnx_incrid_1(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		pwutils::KvormBase* base = f->GetDependsPointer<pwutils::KvormBase>(1);
		std::string& meta = *f->GetDependsPointer<std::string>(2);

		if(!f->IsSuccessful())
		{
			this->AsyncReturn(pid,-1);
			return ;
		}

		int64 newid = f->CheckedInteger(gdb::Client::PKT_INDEX_DATA0 + 0);
		int64 incrd = f->CheckedInteger(gdb::Client::PKT_INDEX_DATA0 + 1);

		mongo::BSONObj bsonobj;
		base->set_autoincr(newid);
		base->to_bson(bsonobj);

		std::string nkey = base->getkey();
		std::string nmeta = base->getmeta();

		m_pAClient->Hsetnx((nmeta),(nkey),std::string(bsonobj.objdata(),bsonobj.objsize()));
		
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_setnx_incrid_2));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<int64>(new int64(newid));
	}

	void SImplKVDB::_dbcb_setnx_incrid_2(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		int64 incrid = *f->GetDependsPointer<int64>(1);

		if(f->IsSuccessful())
		{
			this->AsyncReturn(pid,incrid);
		}
		else
		{
			this->AsyncReturn(pid,-1);
			gDebugStream(__FUNCTION__ << " caller=" << __FUNCTION__ << " failed,errr=" << f->GetErrorString());
		}
	}

	void SImplKVDB::_rpc_call_Hsetnx(const char* meta,const char* key,pwdist::Chunk bson)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

#ifdef _DEBUG
		{
			mongo::BSONObj obj(bson.buf);
			std::cout << __FUNCTION__ << " hsetnx " << meta << " " << key << " = " << obj.toString() << std::endl;
		}
#endif

		m_pAClient->Hsetnx((meta),(key),std::string(bson.buf,bson.len));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_return_result));
		ctx->AddDependsPointer<int64>(new int64(pid));

// #ifdef _DEBUG
		try
		{
			mongo::BSONObj bsonobj(bson.buf);
			std::string* callerinfo = new std::string(__FUNCTION__);
			callerinfo->append(" value=");
			callerinfo->append(bsonobj.toString());
			ctx->AddDependsPointer<std::string>(callerinfo);
		}
		catch(...)
		{
			ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
			gErrorStream(__FUNCTION__ << " exception not bson");
		}
// #else
//		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
//#endif
	}

	void SImplKVDB::_rpc_call_Hset(const char* meta,const char* key,pwdist::Chunk bson)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

// #ifdef _DEBUG
// 		{
// 			mongo::BSONObj obj(bson.buf);
// 			std::cout << __FUNCTION__ << " hset " << meta << " " << key << " = " << obj.toString() << std::endl;
// 		}
// #endif

		m_pAClient->Hset(meta,key,std::string(bson.buf,bson.len));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		std::string* callerinfo = new std::string(__FUNCTION__);
		callerinfo->append(" ");
		callerinfo->append(meta);
		callerinfo->append(" ");
		callerinfo->append(key);
		callerinfo->append(" ");
		callerinfo->append(this->GetSenderNode());
		callerinfo->append(" ");
		callerinfo->append(this->GetSenderPort());

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_return_result));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(callerinfo);
	}

	void SImplKVDB::_rpc_call_Hget(const char* meta,const char* key)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		m_pAClient->Hget((meta),(key));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_get));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
	}

	void SImplKVDB::_rpc_call_HgetByid(const char* meta,int64 id)
	{
		char buf[64] = "";
		pwutils::itoa(buf,id);
		this->_rpc_call_Hget(meta,buf);
	}

	void SImplKVDB::_rpc_call_Hdel(const char* meta,const char* key)
	{
		m_pAClient->Hdel((meta),(key));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		std::string caller(__FUNCTION__);
		caller.append("  ").append(meta).append("  ").append(key);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_report_error));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(caller));
	}

	void SImplKVDB::_rpc_call_MallocIncrid(const char* meta,int64 size)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		m_pAClient->Hincrby(g_kvdb_uuid_meta,meta,size);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_malloc_incrid));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
	}

	void SImplKVDB::_dbcb_malloc_incrid(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		if(f->IsSuccessful())
		{
			int64 newid = f->CheckedInteger(gdb::Client::PKT_INDEX_DATA0 + 0);
			int64 incrd = f->CheckedInteger(gdb::Client::PKT_INDEX_DATA0 + 1);

			this->AsyncReturn(pid,newid,incrd);
		}
		else
		{
			this->AsyncReturn(pid,0LL,0LL);
		}
	}

	void SImplKVDB::_rpc_call_Hvals( const char* hashmapName )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		m_pAClient->Hvals((hashmapName));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(hashmapName));
	}

	void SImplKVDB::_rpc_call_Hrange(const char* hashmapName,int64 start,int64 count)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		m_pAClient->Hrange(hashmapName,start,count);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(hashmapName));
	}

	void SImplKVDB::_rpc_call_Hall( const char* hashmapName )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		m_pAClient->Hall((hashmapName));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(hashmapName));
	}

	void SImplKVDB::_dbcb_return_is_successful(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		mongo::BSONArrayBuilder builder;

		GMDB_FOREACH_PACKETS(i,f)
		{
			gdb::SProtocolPacket* val = f->packets[i];
			if(val->size > 0)
			{
				mongo::BSONObj tmpobj(val->data);
				pwassertop(tmpobj.objsize() == val->size,continue);
				builder.append(tmpobj);
			}
		}

		mongo::BSONObj retobj = builder.obj();
		this->AsyncReturn(pid,pwdist::Chunk((char*)retobj.objdata(),retobj.objsize()));
	}

	int SImplKVDB::InternalUpdate()
	{
		if(m_pAClient != NULL)
		{
			m_pAClient->CheckAndReconnect();
			m_pAClient->Update(this->GetFrameTime());

			if(m_objPingTimer.IsPeriodExpired(GetFrameTime()))
				m_pAClient->Ping();
		}

		if(!m_bClosePerformed && m_objTimer1Sec.IsPeriodExpired(GetFrameTime()))
		{
			if(!m_pAClient->IsConnected())
			{
				pwngs::ctrlsrv::SImplStageMgrProxy prx(this);
				prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_dungeon,0);
				prx._rpc_call_ExitAfter(NULL,10);

				m_bClosePerformed = true;
			}
		}

		return pwdist::Port::InternalUpdate();
	}

	void SImplKVDB::_dbcb_get(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		if(f->IsSuccessful())
		{
			char* data = 0;
			size_t size = 0;
			f->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,&data,&size);

			if(data != NULL && size > 0)
			{
				this->AsyncReturn(pid,pwdist::Chunk(data,size));
				return ;
			}
		}
		this->AsyncReturn(pid,pwdist::Chunk());
	}

	void SImplKVDB::_dbcb_get_integer(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		int64 result = f->CheckedInteger(gdb::Client::PKT_INDEX_DATA0);
		this->AsyncReturn(pid,result);
	}

	void SImplKVDB::_dbcb_fetch(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		if(!f->IsSuccessful())
		{
			this->AsyncReturn(pid,pwdist::Chunk());
			return ;
		}

		GMDB_FOREACH_PACKETS(i,f)
		{
			char* data = NULL;
			size_t size = 0;
			f->CheckedBuffer(i,&data,&size);

			if(data != NULL || size > 0)
			{
				this->AsyncReturnEx(pid,false,pwdist::Chunk(data,size));
			}
		}
		// 返回一个空chunk表示结束
		this->AsyncReturnEx(pid,true,pwdist::Chunk());
	}

	void SImplKVDB::_dbcb_mget(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		mongo::BSONArrayBuilder builder;

		GMDB_FOREACH_PACKETS(i,f)
		{
			gdb::SProtocolPacket* pkt = f->packets[i];
			if(pkt->IsBuffer())
			{
				mongo::BSONObj obj(pkt->data);
				pwassert(obj.objsize() == pkt->size);
				builder.append(obj);
			}
			else
			{
				builder.appendNull();
			}
		}

		mongo::BSONObj obj = builder.obj();
		this->AsyncReturn(pid,pwdist::Chunk((char*)obj.objdata(),obj.objsize()));
	}

	// -------------------------------------------------------------

	void SImplKVDB::_rpc_call_Hmultiget( const char* meta,pwdist::Chunk multiKey )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		std::vector<std::string> keys;

		mongo::BSONObj objkey(multiKey.buf);
		pwassert(objkey.objsize() == multiKey.len);

		mongo::BSONObjIterator iter(objkey);
		while(iter.more())
		{
			std::string key;
			mongo::BSONElement be = iter.next();
			pwutils::bsonToCppVariable(key,be);
			keys.push_back(key);
		}

		if(keys.size() == 0)
		{
			mongo::BSONObj empty_obj;

			this->Return(pwdist::Chunk(empty_obj.objdata(),empty_obj.objsize()));
			return ;
		}

		m_pAClient->Hmultiget(meta,keys);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_mget));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Hmultidel(const char* meta,pwdist::Chunk multiKey)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		std::vector<std::string> keys;

		mongo::BSONObj objkey(multiKey.buf);
		pwassert(objkey.objsize() == multiKey.len);

		mongo::BSONObjIterator iter(objkey);
		while(iter.more())
		{
			mongo::BSONElement be = iter.next();
			std::string key;
			pwutils::bsonToCppVariable(key,be);
			keys.push_back(key);
		}

		m_pAClient->Hmultidel((meta),keys);
	}

	void SImplKVDB::_rpc_call_Hmultiset( const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		std::vector<std::string> keys;
		std::vector<std::string> vals;

		mongo::BSONObj objkey(multiKey.buf);
		mongo::BSONObj objval(multiVal.buf);
		pwassert(objkey.objsize() == multiKey.len);
		pwassert(objval.objsize() == multiVal.len);

		{
			mongo::BSONObjIterator iter(objkey);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				std::string key;
				pwutils::bsonToCppVariable(key,be);
				keys.push_back(key);
			}
		}

		{
			mongo::BSONObjIterator iter(objval);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				std::string key;
				pwutils::bsonToCppVariable(key,be);
				vals.push_back(key);
			}
		}

		pwassert(keys.size() > 0 && vals.size() > 0);

		m_pAClient->Hmultiset((meta),keys,vals);
	}

	void SImplKVDB::_rpc_call_HmultisetnxLoose(pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		std::vector<std::string> metas;
		std::vector<std::string> keys;
		std::vector<std::string> vals;

		mongo::BSONObj objmeta(multiMeta.buf);
		mongo::BSONObj objkey(multiKey.buf);
		mongo::BSONObj objval(multiVal.buf);
		pwassert(objmeta.objsize() == multiMeta.len);
		pwassert(objkey.objsize() == multiKey.len);
		pwassert(objval.objsize() == multiVal.len);

		{
			mongo::BSONObjIterator iter(objmeta);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				std::string value;
				pwutils::bsonToCppVariable(value,be);
				metas.push_back(value);
			}
		}

		{
			mongo::BSONObjIterator iter(objkey);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				std::string value;
				pwutils::bsonToCppVariable(value,be);
				keys.push_back(value);
			}
		}

		{
			mongo::BSONObjIterator iter(objval);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				std::string value;
				pwutils::bsonToCppVariable(value,be);
				vals.push_back(value);	
			}
		}

		pwassert(metas.size() == keys.size() && metas.size() == vals.size());

		m_pAClient->HmultisetnxLoose(metas,keys,vals);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_msetnxloose_result));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_dbcb_msetnxloose_result(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		if(f->IsSuccessful())
		{
			this->AsyncReturn(pid,0);
		}
		else
		{
			gDebugStream(__FUNCTION__ << " failed,errrcode=" << f->GetErrorString());
			this->AsyncReturn(pid,-1);
		}
	}


	void SImplKVDB::_dbcb_async_return_result(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		std::string& caller = *f->GetDependsPointer<std::string>(1);

		if(f->IsSuccessful())
		{
			this->AsyncReturn(pid,0);
		}
		else
		{
			gDebugStream(__FUNCTION__ << " caller=" << caller << " failed,errrcode=" << f->GetErrorString());
			this->AsyncReturn(pid,-1);
		}
	}

	void SImplKVDB::_dbcb_async_report_error(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);
		std::string& caller = *f->GetDependsPointer<std::string>(1);

		if(!f->IsSuccessful())
		{
			gDebugStream(__FUNCTION__ << " caller=" << caller << " failed,errrcode=" << f->GetErrorString());
			// pwassert(false && "_dbcb_async_report_error failed");
		}
	}

	void SImplKVDB::_rpc_call_HcrossallFetch( const char* meta )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hcrossall(meta,false);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_fetch));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_HvalsFetch( const char* meta )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hvals((meta));

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_fetch));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Exit()
	{
		std::cout << __FUNCTION__ << std::endl;

		pwngs::gClosed = true;

		pwutils::g_pUUIDPool->Sync();

		// exit(0);
	}

	void SImplKVDB::_rpc_call_Zset( const char* zsetname,const char* key,int64 value )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Zset(zsetname,key,value);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_report_error));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
	}

	void SImplKVDB::_rpc_call_Zdel( const char* zsetname,const char* key )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Zdel(zsetname,key);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_report_error));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
	}

	void SImplKVDB::_rpc_call_Zget( const char* zsetname,const char* key )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Zget(zsetname,key);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_get_integer));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Ztop( const char* zsetname,int64 limit )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Ztop(zsetname,limit);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_zset_values));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_ZRtop( const char* zsetname,int64 limit )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Zrtop(zsetname,limit);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_zset_values));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Zclear( const char* zsetname )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Zclear(zsetname);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_async_report_error));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(__FUNCTION__));
	}

	void SImplKVDB::_dbcb_return_zset_values( gdb::Client::Future* f,int mode )
	{
		/*pwassert(f != NULL && f->IsFinished());

		int64 pid = *f->GetDependsPointer<int64>(0);

		pwutils::KvormArray<orm::TmpZsetData> array;

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < f->packets.size(); i+=2)
		{
			gdb::SProtocolPacket* pkt = f->packets[i+0];

			orm::TmpZsetData data;
			data.key.set(pkt->data,pkt->size);
			data.score = f->packets[i+1]->AsInteger();
			array.push_back(data);
		}

		mongo::BSONObj obj;
		array.save(obj);

		this->AsyncReturn(pid,pwdist::Chunk((char*)obj.objdata(),obj.objsize()));*/
	}

	void SImplKVDB::_rpc_call_Hsize( const char* hashmapName )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hsize(hashmapName);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_get_integer));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Hclear(const char* hashmapName)
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());
		m_pAClient->Hclear(hashmapName);
	}

	void SImplKVDB::_rpc_call_HvalsIndexQueryInt( const char* meta,const char* field,int64 value )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hindexquery(meta,field,value);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_HvalsIndexQueryStr( const char* meta,const char* field,const char* value )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hindexquery(meta,field,value);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_HvalsIndexQueryRangeInt( const char* meta,const char* field,int64 start,int64 ended )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hindexqueryrange(meta,field,start,ended);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_HvalsIndexQueryRangeStr( const char* meta,const char* field,const char* start,const char* ended )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		m_pAClient->Hindexqueryrange(meta,field,start,ended);
		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
	}

	void SImplKVDB::_rpc_call_Hscan( const char* meta,const char* start,const char* pattern,int64 limit )
	{
		pwassert(this && m_pAClient && m_pAClient->IsConnected());

		std::string startkey(start);
		startkey.resize(startkey.length()+1,'\0');
		m_pAClient->Hscan(meta,pattern,startkey,limit);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		gdb::Client::Future* ctx = m_pAClient->ListenFuture(gdb::Client::fnFutureCallback(this,&SImplKVDB::_dbcb_return_is_successful));
		ctx->AddDependsPointer<int64>(new int64(pid));
		ctx->AddDependsPointer<std::string>(new std::string(meta));
	}


}

