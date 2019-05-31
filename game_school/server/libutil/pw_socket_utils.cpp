#include "pw_socket_utils.h"
#include <stdio.h>
#include "pw_byte_order.h"
#include "pw_utils.h"

namespace pwutils
{
	bool is_socket_eagain()
	{
#ifdef __linux
		int e = errno;
		return (e == EAGAIN || e == EINTR);
#else
		int e = WSAGetLastError();
		return e == WSAEWOULDBLOCK;
#endif
	}

	char* _inet_ntoa(struct in_addr in)
	{
		return ::inet_ntoa(in);
	}

	unsigned long int inet_aton (const char * ip,bool to_host_order)
	{
		struct in_addr addr = {0};

		pwutils::inet_aton(ip,&addr);

		unsigned long result = addr.s_addr;

		if(to_host_order)
		{
			pwutils::Convert<unsigned long>::ToHostOrder(result);
		}
		return result;
	}

	int inet_aton( const char *ip, struct in_addr *addr )
	{
#ifdef __linux
		return ::inet_aton(ip,addr);
#else
		addr->S_un.S_addr = ::inet_addr(ip);
		return 0;
#endif
	}

	int my_ioctl( int s,long cmd,int *argp )
	{
#ifdef __linux
		return ::ioctl(s,cmd,argp);
#else
		return ioctlsocket(s,cmd,(u_long*)argp);
#endif
	}

#ifdef __linux
	bool resolve_host( const char* host,char* ip )
	{
		struct hostent *answer;
		char ipstr[16];

		answer = gethostbyname(host);
		if (answer == NULL)
			return false;
		inet_ntop(AF_INET, (answer->h_addr_list)[0], ip, 16);
		return true;
	}
#endif

#ifdef _MSC_VER
	bool resolve_host( const char* host,char* ip )
	{
		struct hostent *answer;

		answer = gethostbyname(host);
		if (answer == NULL)
			return false;
		char* ipstr = inet_ntoa(*(in_addr*)(answer->h_addr_list)[0]);
		if(ipstr == NULL)
			return false;
		strcpy(ip,ipstr);
		return true;
	}


#endif

	extern std::string get_sock_name( int sock,bool port )
	{
		std::string result;
		sockaddr_in addr = {0};
		socklen_t len = sizeof(addr);
		if(::getsockname(sock,(sockaddr*)&addr,&len) == 0)
		{
			result = _inet_ntoa(addr.sin_addr);
			if(port)
			{
				unsigned short _port = addr.sin_port;
				pwutils::Convert<unsigned short>::ToHostOrder(_port);
				result.append(":").append(pwutils::itoa2(_port));
			}
		}
		return result;
	}

	extern std::string get_peer_name( int sock,bool port )
	{
		std::string result;
		sockaddr_in addr = {0};
		socklen_t len = sizeof(addr);
		if(::getpeername(sock,(sockaddr*)&addr,&len) == 0)
		{
			result = _inet_ntoa(addr.sin_addr);
			if(port)
			{
				unsigned short _port = addr.sin_port;
				pwutils::Convert<unsigned short>::ToHostOrder(_port);
				result.append(":").append(pwutils::itoa2(_port));
			}
		}
		return result;
	}
}
