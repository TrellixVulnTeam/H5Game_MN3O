#ifndef _pw_gdb_socket_listener_
#define _pw_gdb_socket_listener_

#include "pw_gdb_platform.h"
#include "pw_gdb_socket_base_connection.h"

namespace gdb
{
	class SocketListener : public SocketBaseConnection
	{
	public:
		SocketListener();
	public:
		int Bind(const char* ip,int port,bool reuseAddr = true);
		int Listen(int backlog = 10);
	public:
		virtual int OnDataIncoming();
		virtual int OnClose();
		virtual int OnAccept(int sock,sockaddr_in* addr);
	protected:
		void SetupSocket(int sock);
	};
}

#endif // _pw_socket_listener_
