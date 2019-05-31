#ifndef _pw_websocket_listener_
#define _pw_websocket_listener_

#include "gdb/pw_gdb_platform.h"
#include "gdb/pw_gdb_socket_base_connection.h"

namespace gdb
{
	class WebsocketListener : public SocketBaseConnection
	{
	public:
		WebsocketListener();
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

#endif // _pw_gdb_websocket_listener_
