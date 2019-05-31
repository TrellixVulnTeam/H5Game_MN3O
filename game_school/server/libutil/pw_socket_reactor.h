#ifndef _pw_socket_reactor_
#define _pw_socket_reactor_

#include "pw_def.h"
#include "pw_refcounted.h"
#include "pw_circle_buffer.h"

namespace pwutils
{
	class SocketConnectionContext : public pwutils::Refcounted<false>
	{
	public:
		SocketConnectionContext(){}
		virtual ~SocketConnectionContext() {}
	};

	class SocketConnection
	{
	public:
		SocketConnection(int sock = -1);
		virtual ~SocketConnection();
	public:
		virtual int GetSocket()
		{
			return m_nSocket;
		}
	public:
		virtual int OnDataIncoming();
		virtual int OnDataIncoming(char* buf,int32 len);
		virtual int OnDataOutgoing();
		virtual int OnClose() { return 0; }
	public:
		virtual int Send(const char* buf,int32 len);
		virtual int SendN(const char* buf,int32 len,int tryCount = -1);
		virtual int FlushSendBuffer();
	public:
		virtual int Close(bool justShutdown = false);
	public:
		virtual int doref() = 0;
		virtual int unref() = 0;
	public:
		static int RecvSync(int sock,char* buf,int32 len);
		static int RecvAsync(int sock,char* buf,int32 len);
		static int CloseSocket(int sock);
	public:
		inline SocketConnectionContext* GetInternalContext()
		{
			return m_pInternalContext;
		}

		inline void SetInternalContext(SocketConnectionContext* ctx)
		{
			if(m_pInternalContext)
				m_pInternalContext->unref();
			m_pInternalContext = ctx;
			if(m_pInternalContext)
				m_pInternalContext->doref();
		}
	protected:
		int m_nSocket;
		bool m_bWriteEnable;
		SocketConnectionContext* m_pInternalContext;
		pwutils::CircleBuffer m_objSendBuffer;
	};

	template<bool MultiThread> class SocketConnectionThread : public SocketConnection,private pwutils::Refcounted<MultiThread>
	{
	public:
		SocketConnectionThread(int sock = -1)
			: SocketConnection(sock)
		{
		}
	public:
		virtual int doref()
		{
			return pwutils::Refcounted<MultiThread>::doref();
		}
		virtual int unref()
		{
			return pwutils::Refcounted<MultiThread>::unref();
		}
	};

	typedef SocketConnectionThread<false> SocketConnectionST;
	typedef SocketConnectionThread<true> SocketConnectionMT;


	class SocketReactor
	{
	public:
		enum 
		{
			MASK_READ	= 0x0001,
			MASK_WRITE	= 0x0002,
			MASK_EXCEPT	= 0x0004,
			MASK_ACCEPT	= 0x0008,
			MASK_ET		= 0x0010,

			MASK_DEFAULT = MASK_READ | MASK_WRITE | MASK_EXCEPT | MASK_ET,
		};
	public:
		virtual ~SocketReactor(){}
	public:
		virtual int Startup() = 0;
		virtual int Cleanup() = 0;
	public:
		virtual int Add(SocketConnection* connection,int mask) = 0;
		virtual int Del(SocketConnection* connection) = 0;
		virtual int Mod(SocketConnection* connection,int mask) = 0;
	public:
		virtual int Update() = 0;
	};
}

#endif // _pw_socket_reactor_
