#ifndef _pw_socket_reactor_select_
#define _pw_socket_reactor_select_

#include "pw_socket_reactor.h"

namespace pwutils
{

	class SocketReactorImplSelect : public SocketReactor
	{
	public:
		SocketReactorImplSelect(int maxSockets);
		virtual ~SocketReactorImplSelect();
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
		int Del( SocketConnection* connection,int index );
	protected:
		int m_nMaxConnection;
		int m_nNumConnection;
		SocketConnection** m_pConnections;
		int* m_pEvents;
	protected:
		void* m_fdsetRead;
		void* m_fdsetWrite;
		void* m_fdsetExcept;
	};
}

#endif // _pw_socket_reactor_select_
