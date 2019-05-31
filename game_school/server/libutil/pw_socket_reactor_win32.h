#ifndef _pw_socket_reactor_win32_
#define _pw_socket_reactor_win32_

#ifdef _MSC_VER

#include "pw_socket_reactor.h"
#include "pw_platform.h"

namespace pwutils
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
		virtual int Add(SocketConnection* connection,int mask);
		virtual int Del(SocketConnection* connection);
		virtual int Mod(SocketConnection* connection,int mask);
	public:
		virtual int Update();
	protected:
		virtual int Del(SocketConnection* connection,int index);
		virtual int iUpdate(int start,int end);
	protected:
		int m_nMaxConnection;
		int m_nNumConnection;
		SocketConnection** m_pConnections;
		WSAEVENT* m_pEvents;
	};

	typedef SocketReactorImplWES SocketReactorDefaultImpl;
}

#endif

#endif // _pw_socket_reactor_win32_