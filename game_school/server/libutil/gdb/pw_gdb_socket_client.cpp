#include "pw_gdb_socket_client.h"
#include "pw_gdb_socket_utils.h"
#include "pw_gdb_platform.h"

namespace gdb
{
	SocketClient::SocketClient()
		: m_bConnected(false)
	{
		this->Create();
	}

	int SocketClient::Connect( const char* ip,int port )
	{
		{
			int aio = 1;
			SocketUtils::Ioctl(m_nSocket,FIONBIO,&aio);
		}

		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		SocketUtils::InetAton(ip,&addr.sin_addr);

		return ::connect(m_nSocket,(sockaddr*)&addr,sizeof(addr));
	}

	int SocketClient::ConnectSync( const char* ip,int port )
	{
		{
			int aio = 0;
			SocketUtils::Ioctl(m_nSocket,FIONBIO,&aio);
		}
		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		SocketUtils::InetAton(ip,&addr.sin_addr);

		int result =  ::connect(m_nSocket,(sockaddr*)&addr,sizeof(addr));

		{
			int aio = 1;
			SocketUtils::Ioctl(m_nSocket,FIONBIO,&aio);
		}

		return result;
	}

	int SocketClient::OnDataOutgoing()
	{
		if(!m_bConnected)
		{
			m_bConnected = true;
			OnConnected();
		}
		return SocketConnection::OnDataOutgoing();
	}

	int SocketClient::OnConnected()
	{
		return 0;
	}

	int SocketClient::OnClose()
	{
		m_bConnected = false;
		return SocketConnection::OnClose();
	}

	void SocketClient::Create()
	{
		m_nSocket = ::socket(AF_INET,SOCK_STREAM,0);
		int valueTrue = 1;
		setsockopt(m_nSocket,SOL_SOCKET,SO_KEEPALIVE,(char*)&valueTrue,sizeof(valueTrue));
	}

}
