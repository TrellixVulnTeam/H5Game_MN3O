#ifndef _pw_socket_reactor_linux_
#define _pw_socket_reactor_linux_

#ifdef __linux

#include "pw_socket_reactor.h"

namespace pwutils
{
	class SocketReactorImplEPOLL : public SocketReactor
	{
	public:
		SocketReactorImplEPOLL(int maxSockets);
		virtual ~SocketReactorImplEPOLL();
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
		int m_nEpoll;
		int m_nMaxSockets;
		struct epoll_event* m_pEvents;
	};

	typedef SocketReactorImplEPOLL SocketReactorDefaultImpl;
}

#endif 

#endif // _pw_socket_reactor_linux_



