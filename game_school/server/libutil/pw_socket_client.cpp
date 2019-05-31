#include "pw_socket_client.h"
#include "pw_logger.h"
#include "pw_socket_utils.h"
#include "pw_platform.h"

namespace pwutils
{

	SocketClient::SocketClient()
		: m_bConnected(false)
	{
		CreateSocket();
	}

	void SocketClient::CreateSocket()
	{
		m_nSocket = ::socket(AF_INET,SOCK_STREAM,0);
		pwassert(m_nSocket > 0);

		int valueTrue = 1;
#ifndef __linux
		//		setsockopt(m_nSocket,SOL_SOCKET,SO_CONDITIONAL_ACCEPT,(char*)&valueTrue,sizeof(valueTrue));
#endif
		setsockopt(m_nSocket,SOL_SOCKET,SO_KEEPALIVE,(char*)&valueTrue,sizeof(valueTrue));
	}

	SocketClient::~SocketClient()
	{
	}

	int SocketClient::Connect( const char* ip,int port )
	{
		SetAsync(true);

		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		pwutils::inet_aton(ip,&addr.sin_addr);

		return ::connect(m_nSocket,(sockaddr*)&addr,sizeof(addr));
	}

	int SocketClient::ConnectSync( const char* ip,int port )
	{
		SetAsync(false);

		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		pwutils::inet_aton(ip,&addr.sin_addr);

		int result =  ::connect(m_nSocket,(sockaddr*)&addr,sizeof(addr));

		SetAsync(true);

		return result;
	}

	int SocketClient::OnClose()
	{
		m_bConnected = false;
		return SocketConnectionThread<false>::OnClose();
	}

	int SocketClient::OnConnected()
	{
		return 0;
	}


	int SocketClient::OnDataOutgoing()
	{
		if(!m_bConnected)
		{
			m_bConnected = true;
			this->OnConnected();
		}
		return SocketConnectionThread<false>::OnDataOutgoing();
	}

	int SocketClient::SetAsync( bool value )
	{
		int aio = value ? 1 : 0;
		return pwutils::my_ioctl(m_nSocket,FIONBIO,&aio);		
	}


}
