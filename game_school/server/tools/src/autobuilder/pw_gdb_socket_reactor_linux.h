#ifndef _pw_gdb_socket_reactor_linux_
#define _pw_gdb_socket_reactor_linux_

#ifdef __linux

#include "pw_gdb_platform.h"
#include "pw_gdb_socket_reactor.h"

namespace gdb
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
		virtual int Add(SocketBaseConnection* connection,int mask);
		virtual int Del(SocketBaseConnection* connection);
		virtual int Mod(SocketBaseConnection* connection,int mask);
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



