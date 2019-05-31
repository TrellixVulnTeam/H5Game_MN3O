#ifndef _pw_gdb_socket_client_
#define _pw_gdb_socket_client_

#include "pw_gdb_socket_connection.h"

namespace gdb
{
	class SocketClient : public SocketConnection
	{
	public:
		SocketClient();
	public:
		inline bool IsConnected()
		{
			return m_bConnected;
		}
	public:
		virtual int Connect( const char* ip,int port );
		virtual int ConnectSync( const char* ip,int port );
	public:
		virtual int OnClose();
		virtual int OnConnected();
		virtual int OnDataOutgoing();
	protected:
		void Create();
	protected:
		bool m_bConnected;
	};


}

#endif // _pw_socket_client_