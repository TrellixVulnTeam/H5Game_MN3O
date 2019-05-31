
#include "pw_client_moniter.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_ngs_qlvh_log.h"
#include "pw_client_logger.h"
#include "pw_entrance_def.h"
#include "pw_byte_order.h"



namespace pwutils
{
	ClientLogServer::Connection::Connection( ClientLogServer* server,int sock,const sockaddr_in& addr )
		: m_bClosed(false)
		, m_pServer(server)
		, m_objSocketAddr(addr)
		, m_objPump(pwngs::entrance::cst_entrance_client_bufsize,pwngs::entrance::cst_entrance_client_bufsize)
	{
		m_nSocket = sock;
		m_objSendBuffer.initial(pwngs::entrance::cst_entrance_client_bufsize);
	}

	int ClientLogServer::Connection::OnClose()
	{
		m_bClosed = true;
		return 0;
	}

	int ClientLogServer::Connection::OnDataIncoming(char* buf,int32 len)
	{		
		char tmpbuf[cst_tmp_buf_size] = "";

		if(pwutils::strcmp(buf,unity_policy_request_fmt) == 0)
		{
			return this->Send(unity_policy_response_fmt,sizeof(unity_policy_response_fmt));
		}		

		m_objPump.Put(buf,len);

		while(m_objPump.Get(tmpbuf,cst_tmp_buf_size,true))
		{			
			pwutils::SPacketHeader* header = (pwutils::SPacketHeader*)tmpbuf;
			if(OnPacket(header) != 0)
			{
				return -1;
			}				
		}
		return 0;
	}

	int ClientLogServer::Connection::OnPacket( pwutils::SPacketHeader* header )
	{
		pwutils::Convert<int>::ToHostOrder( header->msgid);
		pwutils::Convert<int>::ToHostOrder( header->msglen);
		
		switch(header->msgid)
		{
			case msgid_client_attr:
			{
				MsgClientLog* msg = (MsgClientLog*)header;
				gMoniterStream(msg->szAttr);
			}
			break;
			case msgid_client_md5:
			{
				MsgClientMD5* msg = (MsgClientMD5*)header;
				gMoniterStream(msg->szMD5);
			}
			break;
		}
		return 0;
	}

	ClientLogServer::Connection::~Connection()
	{
	}

	int ClientLogServer::ListenAndServer( const char* ip,int port )
	{
		int result = this->Bind(ip,port);
		if( result == -1)
			return result;

		result = this->Listen(20);
		if( result == -1)
			return result;

		m_objReactor.Add(this,SocketReactor::MASK_ACCEPT);

		return 0;
	}

	int ClientLogServer::Cleanup()
	{
		return 0;
	}

	int ClientLogServer::OnAccept( int sock,sockaddr_in* addr )
	{
		Connection* conn = new Connection(this,sock,*addr);
		m_objReactor.Add(conn,SocketReactor::MASK_DEFAULT);
		return 0;
	}

	int ClientLogServer::Update()
	{
		return m_objReactor.Update();
	}

	ClientLogServer::ClientLogServer()
		: m_objReactor(4096)
	{

	}


	ClientLogServerThread::ClientLogServerThread()
	{

	}

	int ClientLogServerThread::ListenAndServer( const char* ip,int port )
	{
		if(ClientLogServer::ListenAndServer(ip,port) == 0)
			return Runnable::Startup(1);
		return -1;
	}


	int ClientLogServerThread::Cleanup()
	{
		return Runnable::Cleanup();
	}

	int ClientLogServerThread::run()
	{
		while(!this->mClosed)
		{
			m_objReactor.Update();
			pwutils::time::sleep(10);
		}
		return 0;
	}

	int ClientLogServerThread::Update()
	{
		return 0;
	}


	ClientLogServerMultiThread::ClientLogServerMultiThread( int threadNum )
	{
		m_vWorkers.resize(threadNum,NULL);
		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i] = new Worker();
		}
	}

	ClientLogServerMultiThread::~ClientLogServerMultiThread()
	{
		Cleanup();

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			_safe_delete(m_vWorkers[i]);
		}
		m_vWorkers.clear();
	}

	int ClientLogServerMultiThread::ListenAndServer( const char* ip,int port )
	{
		int result = ClientLogServerThread::ListenAndServer(ip,port);
		if( result != 0)
			return result;

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i]->Startup();
		}

		return result;
	}

	int ClientLogServerMultiThread::Cleanup()
	{
		int result = ClientLogServerThread::Cleanup();
		if( result != 0)
			return result;

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i]->Cleanup();
		}
		return result;
	}

	int ClientLogServerMultiThread::OnAccept( int sock,sockaddr_in* addr )
	{
		int32 r = pwutils::random(0,m_vWorkers.size());
		Connection* conn = new Connection(this,sock,*addr);
		m_vWorkers[r]->PostConnection(conn);
		return 0;
	}

	int ClientLogServerMultiThread::Worker::run()
	{
		while(!mClosed)
		{
			SocketConnection* connection = NULL;
			while(m_vConnsPosted.try_pop(connection))
			{
				m_objReactor.Add(connection,SocketReactor::MASK_DEFAULT);
			}
			m_objReactor.Update();
			pwutils::time::sleep(10);
		}

		SocketConnection* connection = NULL;
		while(m_vConnsPosted.try_pop(connection))
		{
			_safe_delete(connection);
		}
		return 0;
	}


}
