
#ifndef _PW_SOCKET_LOG_H
#define _PW_SOCKET_LOG_H

#include "pw_def.h"
#include "pw_socket_listener.h"
#include "pw_socket_reactor.h"
#include "pw_socket_reactor_win32.h"
#include "pw_socket_reactor_linux.h"
#include "pw_runnable.h"
#include "pw_socket_stream_pump.h"


namespace pwutils
{
	const char unity_policy_request_fmt[] = "<policy-file-request/>";

	const char unity_policy_response_fmt[] = "<?xml version=\"1.0\"?>\
											 <cross-domain-policy>\
											 <allow-access-from domain=\"*\" to-ports=\"*\" />\
											 </cross-domain-policy>";

	struct MsgClientLog : public pwutils::SPacketHeader
	{
		char szAttr[cst_tmp_buf_size];
	};

	struct MsgClientMD5 : public pwutils::SPacketHeader
	{
		char szMD5[cst_tmp_buf_size];
	};

	//玩家电脑配置属性
	const int msgid_client_attr = 1;
	//客户端md5
	const int msgid_client_md5	= 2;

	class ClientLogServer : public SocketListenerDefault
	{
	public:
		class Connection : public SocketConnectionThread<true>
		{
		public:
			Connection(ClientLogServer* server,int sock,const sockaddr_in& addr);
			virtual ~Connection();
		public:
			virtual int OnDataIncoming(char* buf,int32 len);
			virtual int OnClose();
		public:
			//virtual int Send(const char* buf,int32 len);
		public:
			inline bool IsClosed()
			{
				return m_bClosed;
			}
		public:
			int OnPacket(pwutils::SPacketHeader* header);
		protected:
			bool m_bClosed;
			ClientLogServer* m_pServer;
			sockaddr_in m_objSocketAddr;
			pwutils::SocketStreamPump m_objPump;
		};
	public:
		ClientLogServer();
	public:
		virtual int ListenAndServer(const char* ip,int port);
		virtual int Cleanup();
	public:
		virtual int Update();
	protected:
		virtual int OnAccept(int sock,sockaddr_in* addr);
	protected:
		SocketReactorDefaultImpl m_objReactor;
	};


	class ClientLogServerThread : public ClientLogServer, protected Runnable
	{
	public:
		ClientLogServerThread();
	public:
		virtual int ListenAndServer(const char* ip,int port);
		virtual int Cleanup();
	public:
		virtual int Update();
	protected:
		virtual int run();
	};


	class ClientLogServerMultiThread : public ClientLogServerThread
	{
	public:
		ClientLogServerMultiThread(int threadNum);
		virtual ~ClientLogServerMultiThread();
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
}

#endif // _PW_SOCKET_LOG_H