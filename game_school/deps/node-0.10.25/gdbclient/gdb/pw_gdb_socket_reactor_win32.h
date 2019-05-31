#ifndef _pw_gdb_socket_reactor_win32_
#define _pw_gdb_socket_reactor_win32_

#ifdef _MSC_VER

#include "pw_gdb_socket_reactor.h"
#include "pw_gdb_platform.h"

namespace gdb
{
	class SocketReactorImplWES : public SocketReactor
	{
	public:
		SocketReactorImplWES(int maxSockets);
		virtual ~SocketReactorImplWES();
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
		virtual int Del(SocketBaseConnection* connection,int index);
		virtual int iUpdate(int start,int end);
	protected:
		int m_nMaxConnection;
		int m_nNumConnection;
		SocketBaseConnection** m_pConnections;
		WSAEVENT* m_pEvents;
	};

	typedef SocketReactorImplWES SocketReactorDefaultImpl;
}

#endif

#endif // _pw_socket_reactor_win32_