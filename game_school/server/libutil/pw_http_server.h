#ifndef _pw_http_server_
#define _pw_http_server_

#include "pw_def.h"
#include "pw_http_protocol.h"
#include "pw_socket_listener.h"
#include "pw_socket_reactor.h"
#include "pw_socket_reactor_win32.h"
#include "pw_socket_reactor_linux.h"
#include "pw_runnable.h"

namespace pwutils
{

	/*
	 @class HttpServer
	 @author cbh
	 @date 2013/3/19 11:00:21
	 @file pw_http_server.h
	 @brief 无线程支持的httpserver,必须由其它线程调用Update
	*/
	class HttpServer : public SocketListenerDefault
	{
	public:
		class Connection : public SocketConnectionThread<true>
		{
		public:
			Connection(HttpServer* server,int sock,const sockaddr_in& addr);
			virtual ~Connection();
		public:
			virtual int OnDataIncoming(char* buf,int32 len);
			virtual int OnClose();
		public:
			int Send(HttpProtocol& response);
		public:
			inline bool IsClosed()
			{
				return m_bClosed;
			}
		protected:
			bool m_bClosed;
			HttpServer* m_pServer;
			sockaddr_in m_objSocketAddr;
			pwutils::HttpProtocol m_objRequest;
		};
	public:
		HttpServer();
	public:
		virtual int ListenAndServer(const char* ip,int port);
		virtual int Cleanup();
	public:
		virtual int Update();
	protected:
		virtual int HttpSvc(Connection* connection,HttpProtocol& request,HttpProtocol& response);
		virtual int OnAccept(int sock,sockaddr_in* addr);
	protected:
		SocketReactorDefaultImpl m_objReactor;
	};
	/*
	 @class HttpServer
	 @author cbh
	 @date 2013/3/11 10:10:46
	 @file pw_http_server.h
	 @brief 1个线程HttpServer(处理listener&connection)
	*/
	class HttpServerThread : public HttpServer, protected Runnable
	{
	public:
		HttpServerThread();
	public:
		virtual int ListenAndServer(const char* ip,int port);
		virtual int Cleanup();
	public:
		virtual int Update();
	protected:
		virtual int run();
	};

	/*
	 @class HttpServerMultiThread
	 @author cbh
	 @date 2013/3/11 10:10:34
	 @file pw_http_server.h
	 @brief 多线程HttpServer(1个线程处理listener,多个线程处理connection)
	*/
	class HttpServerMultiThread : public HttpServerThread
	{
	public:
		HttpServerMultiThread(int threadNum);
		virtual ~HttpServerMultiThread();
	public:
		virtual int ListenAndServer(const char* ip,int port);
		virtual int Cleanup();
	protected:
		virtual int OnAccept(int sock,sockaddr_in* addr);
	protected:
		class Worker : public Runnable
		{
		public:
			Worker() : m_objReactor(4096) { }
		public:
			void PostConnection(SocketConnection* connection)
			{
				m_vConnsPosted.push(connection);
			}
		protected:
			virtual int run();
		protected:
			typedef tbb::concurrent_queue<SocketConnection*> CollectionConnectionPostedT;
		protected:
			SocketReactorDefaultImpl m_objReactor;
			CollectionConnectionPostedT m_vConnsPosted;
		};
	protected:
		typedef std::vector<Worker*> CollectionWorkersT;
	protected:
		CollectionWorkersT m_vWorkers;
	};

	/*
	 @class HttpDispatcher
	 @author cbh
	 @date 2013/3/11 10:10:55
	 @file pw_http_server.h
	 @brief Http服务器Url分派
	*/
	class HttpDispatcher
	{
	public:
		typedef void (*pfnHttpSvc)(HttpServerThread::Connection* connection,HttpProtocol& request,HttpProtocol& response);
	public:
		int HandleUrl(const char* url,pfnHttpSvc pfn);
	public:
		int HandleRequest(HttpServerThread::Connection* connection, HttpProtocol& request,HttpProtocol& response);
	protected:
		typedef std_unordered_map<std::string,pfnHttpSvc> CollectionHandlersT;
	protected:
		CollectionHandlersT m_mapHandlers;
	};
}

#endif // _pw_http_server_