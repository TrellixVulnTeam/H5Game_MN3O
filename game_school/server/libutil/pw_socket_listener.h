#ifndef _pw_socket_listener_
#define _pw_socket_listener_

#include "pw_platform.h"
#include "pw_socket_reactor.h"
#include "pw_socket_utils.h"

namespace pwutils
{
	
	template<class T = SocketConnectionThread<false> > class SocketListener : public T
	{
	public:
		SocketListener()
		{
			int valuetrue = 1;
			T::m_nSocket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
			pwutils::my_ioctl(T::m_nSocket,FIONBIO,&valuetrue);
		}
		virtual ~SocketListener()
		{
		}
	public:
		int Bind(const char* ip,int port,bool reuseAddr = true)
		{
			if(reuseAddr)
			{
				int valuetrue = 1;
				setsockopt(T::m_nSocket,SOL_SOCKET,SO_REUSEADDR,(char*)&valuetrue,sizeof(int));
			}
			sockaddr_in addr = {0};
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = INADDR_ANY;
			if(ip != 0 && strlen(ip) > 0)
				addr.sin_addr.s_addr = ::inet_addr(ip);
			return ::bind(T::m_nSocket,(sockaddr*)&addr,sizeof(sockaddr_in));
		}

		int Listen(int backlog = 10)
		{
			return ::listen(T::m_nSocket,backlog);
		}
	public:
		virtual int OnDataIncoming()
		{
			sockaddr_in addr = {0};
#ifdef __linux
			socklen_t addrlen = sizeof(sockaddr_in);
#else
			int addrlen = sizeof(sockaddr_in);
#endif
			int sock = ::accept(T::m_nSocket,(sockaddr*)&addr,&addrlen);
			if( sock != -1)
			{
				this->SetupSocket(sock);				
				this->OnAccept(sock,&addr);
			}
			return 0;
		}
		virtual int OnClose() { return 0; }
		virtual int OnAccept(int sock,sockaddr_in* addr) { return 0; }
	protected:
		void SetupSocket(int sock)
		{
			linger s = {0};
			s.l_onoff = 1;
			setsockopt(sock,SOL_SOCKET,SO_LINGER,(char*)&s,sizeof(linger));

			int valuetrue = 1;
			setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,(char*)&valuetrue,sizeof(int));

			pwutils::my_ioctl(sock,FIONBIO,&valuetrue);
		}
	};

	typedef SocketListener<> SocketListenerDefault;
}

#endif // _pw_socket_listener_
