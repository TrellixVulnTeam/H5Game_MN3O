#ifndef _pw_gdb_socket_reactor_select_
#define _pw_gdb_socket_reactor_select_

#include "pw_gdb_socket_reactor.h"
#include "pw_gdb_platform.h"

namespace gdb
{

	class SocketReactorImplSelect : SocketReactor
	{
	public:
		SocketReactorImplSelect(int maxSockets);
		virtual ~SocketReactorImplSelect();
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
		int Del( SocketBaseConnection* connection,int index );
	protected:
		int m_nMaxConnection;
		int m_nNumConnection;
		SocketBaseConnection** m_pConnections;
		int* m_pEvents;
	protected:
		void* m_fdsetRead;
		void* m_fdsetWrite;
		void* m_fdsetExcept;
	};
}

#endif // _pw_socket_reactor_select_
