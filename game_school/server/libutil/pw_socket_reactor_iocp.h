#ifndef _pw_socket_reactor_iocp_
#define _pw_socket_reactor_iocp_

#ifdef _MSC_VER

#include "pw_socket_reactor.h"
#include "pw_socket_listener.h"

namespace pwutils
{
	class IocpSocketConnectionContext;

	/*
	 @class IocpSocketConnection
	 @author cbh
	 @date 2013/3/26 14:48:56
	 @file pw_socket_reactor_iocp.h
	 @brief 支持iocp的socket connection
	*/
	class IocpSocketConnection : public SocketConnectionThread<false>
	{
	public:
		IocpSocketConnection();
	public:
		virtual int FlushSendBuffer();
	};

	/*
	 @class IocpSocketListener
	 @author cbh
	 @date 2013/3/26 14:48:44
	 @file pw_socket_reactor_iocp.h
	 @brief iocp监听对象
	*/
	class IocpSocketListener : public SocketListener<IocpSocketConnection>
	{
	public:
		virtual int OnDataIncoming();
	};

	/*
	@class SocketReactorImplIocp
	 @author cbh
	 @date 2013/3/26 14:48:33
	 @file pw_socket_reactor_iocp.h
	 @brief iocp反应器
	*/
	class SocketReactorImplIocp : public SocketReactor
	{
		friend class IocpSocketConnection;
		friend class IocpSocketConnectionContext;
	public:
		SocketReactorImplIocp(int unused);
		virtual ~SocketReactorImplIocp();
	public:
		virtual int Startup();
		virtual int Cleanup();
	public:
		virtual int Add(SocketConnection* connection,int mask);
		virtual int Del(SocketConnection* connection);
		virtual int Mod(SocketConnection* connection,int mask);
	public:
		virtual int Update();
	protected:
		int PostRecv(SocketConnection* connection);
		int PostAccept(SocketConnection* connection);
		int PostSend(SocketConnection* connection,char* buf,int32 len);
	protected:
		HANDLE m_hIocp;
	};

}

#endif

#endif // _pw_socket_reactor_iocp_