#ifndef _pw_socket_client_
#define _pw_socket_client_

#include "pw_socket_reactor.h"

namespace pwutils
{
	class SocketClient : public SocketConnectionThread<false>
	{
	public:
		SocketClient();
		virtual ~SocketClient();
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
		void CreateSocket();
		int SetAsync(bool value);
	protected:
		bool m_bConnected;
	};


}

#endif // _pw_socket_client_