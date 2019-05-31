#include "pw_http_server.h"
#include "pw_time.h"
#include "pw_utils.h"

namespace pwutils
{
	HttpServer::Connection::Connection( HttpServer* server,int sock,const sockaddr_in& addr )
		: m_bClosed(false)
		, m_pServer(server)
		, m_objSocketAddr(addr)
	{
		m_nSocket = sock;
	}

	int HttpServer::Connection::OnClose()
	{
		m_bClosed = true;
		return 0;
	}

	int HttpServer::Connection::OnDataIncoming(char* buf,int32 len)
	{		
		int32 remaineLen = len;
		while(remaineLen > 0)
		{
			if(m_objRequest.Parse(&buf[len - remaineLen],remaineLen,&remaineLen))
			{
				try
				{
					pwutils::HttpProtocol response;
					if(m_pServer->HttpSvc(this,m_objRequest,response) < 0)
						return -1;
					m_objRequest.Clear();
					this->Send(response);
				}
				catch(...)
				{
					std::cout << __FUNCTION__ << " exception occured" << std::endl;
					return -1;
				}
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	HttpServer::Connection::~Connection()
	{
	}

	int HttpServer::Connection::Send( HttpProtocol& response )
	{
		if(response.GetLen() > 0)
		{
			return SocketConnectionThread<true>::Send(response.GetBuf(),response.GetLen());
		}
		return 0;
	}

	// --------------------------------------------------------------------------------------


	int HttpServer::HttpSvc( Connection* connection, HttpProtocol& request,HttpProtocol& response )
	{
		return 0;
	}

	int HttpServer::ListenAndServer( const char* ip,int port )
	{
		int result = this->Bind(ip,port);
		if( result == -1)
			return result;

		result = this->Listen(200);
		if( result == -1)
			return result;

		m_objReactor.Add(this,SocketReactor::MASK_ACCEPT);

		return 0;
	}

	int HttpServer::Cleanup()
	{
		return 0;
	}

	int HttpServer::OnAccept( int sock,sockaddr_in* addr )
	{
		Connection* conn = new Connection(this,sock,*addr);
		m_objReactor.Add(conn,SocketReactor::MASK_DEFAULT);
		return 0;
	}

	int HttpServer::Update()
	{
		return m_objReactor.Update();
	}

	HttpServer::HttpServer()
		: m_objReactor(4096)
	{

	}


	// --------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------

	HttpServerThread::HttpServerThread()
	{

	}

	int HttpServerThread::ListenAndServer( const char* ip,int port )
	{
		if(HttpServer::ListenAndServer(ip,port) == 0)
			return Runnable::Startup(1);
		return -1;
	}


	int HttpServerThread::Cleanup()
	{
		return Runnable::Cleanup();
	}

	int HttpServerThread::run()
	{
		while(!this->mClosed)
		{
			m_objReactor.Update();
			pwutils::time::sleep(10);
		}
		return 0;
	}

	int HttpServerThread::Update()
	{
		// ²»¸üÐÂ
		return 0;
	}

	int HttpDispatcher::HandleUrl( const char* url,pfnHttpSvc pfn )
	{
		m_mapHandlers[url] = pfn;
		return 0;
	}

	int HttpDispatcher::HandleRequest( HttpServerThread::Connection* connection,HttpProtocol& request,HttpProtocol& response )
	{
		std::string url(request.m_phUrl,HttpProtocol::GetHeaderValueLength(request.m_phUrl));
		CollectionHandlersT::iterator iter = m_mapHandlers.find(url);
		if(iter == m_mapHandlers.end())
		{
			response.WriteResponseHeader(404,"Not Found");
			response.WriteHeader(pwutils::HttpConsts::HEADER_CONNECTION,"close");
			response.WriteHeader(pwutils::HttpConsts::HEADER_CONTENT_LENGTH,0);
			response.WriteHeaderTerminator();
			return -1;
		}

		pfnHttpSvc fn = iter->second;
		fn(connection,request,response);
		return 0;
	}

	HttpServerMultiThread::HttpServerMultiThread( int threadNum )
	{
		m_vWorkers.resize(threadNum,NULL);
		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i] = new Worker();
		}
	}

	HttpServerMultiThread::~HttpServerMultiThread()
	{
		Cleanup();

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			_safe_delete(m_vWorkers[i]);
		}
		m_vWorkers.clear();
	}

	int HttpServerMultiThread::ListenAndServer( const char* ip,int port )
	{
		int result = HttpServerThread::ListenAndServer(ip,port);
		if( result != 0)
			return result;

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i]->Startup();
		}

		return result;
	}

	int HttpServerMultiThread::Cleanup()
	{
		int result = HttpServerThread::Cleanup();
		if( result != 0)
			return result;

		for(size_t i = 0; i < m_vWorkers.size(); ++i)
		{
			m_vWorkers[i]->Cleanup();
		}
		return result;
	}

	int HttpServerMultiThread::OnAccept( int sock,sockaddr_in* addr )
	{
		int32 r = pwutils::random(0,m_vWorkers.size());
		Connection* conn = new Connection(this,sock,*addr);
		m_vWorkers[r]->PostConnection(conn);
		return 0;
	}

	int HttpServerMultiThread::Worker::run()
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