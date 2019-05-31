#include "gdb/pw_gdb_socket_utils.h"
#include "pw_web_socket_listener.h"
#include "sha1.h"
#include "base64.h"
#include <string.h>
#include <sstream>
#include <map>

namespace gdb
{
	WebsocketListener::WebsocketListener()
	{
		int valuetrue = 1;
		m_nSocket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		SocketUtils::Ioctl(m_nSocket,FIONBIO,&valuetrue);
	}

	int WebsocketListener::OnDataIncoming()
	{
		sockaddr_in addr = {0};
#ifdef __linux
		socklen_t addrlen = sizeof(sockaddr_in);
#else
		int addrlen = sizeof(sockaddr_in);
#endif
		int sock = ::accept(m_nSocket,(sockaddr*)&addr,&addrlen);
		if( sock != -1)
		{
			this->SetupSocket(sock);				
			this->OnAccept(sock,&addr);
		}
		return 0;
	}

	int WebsocketListener::OnClose()
	{
		return 0;
	}

	int WebsocketListener::OnAccept(int sock, sockaddr_in* addr)
	{
		return 0;
	}

	void WebsocketListener::SetupSocket(int sock)
	{
		linger s = {0};
		s.l_onoff = 1;
		setsockopt(sock,SOL_SOCKET,SO_LINGER,(char*)&s,sizeof(linger));

		int valuetrue = 1;
		setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,(char*)&valuetrue,sizeof(int));

		SocketUtils::Ioctl(sock,FIONBIO,&valuetrue);
	}

	int WebsocketListener::Bind(const char* ip, int port, bool reuseAddr /*= true*/)
	{
		if(reuseAddr)
		{
			int valuetrue = 1;
			setsockopt(m_nSocket,SOL_SOCKET,SO_REUSEADDR,(char*)&valuetrue,sizeof(int));
		}
		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = INADDR_ANY;
		if(ip != 0 && strlen(ip) > 0)
			addr.sin_addr.s_addr = ::inet_addr(ip);
		return ::bind(m_nSocket,(sockaddr*)&addr,sizeof(sockaddr_in));
	}

	int WebsocketListener::Listen(int backlog /*= 10*/)
	{
		return ::listen(m_nSocket,backlog);
	}

}
