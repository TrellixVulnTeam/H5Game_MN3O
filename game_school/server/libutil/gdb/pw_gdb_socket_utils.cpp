#include "pw_gdb_socket_utils.h"
#include <stdio.h>

namespace gdb
{
	unsigned SocketUtils::GetLastError()
	{
#ifdef __linux
		switch(errno)
		{
		case EAGAIN:
			return ERROR_WOULDBLOCK;
		case EINTR:
			return ERROR_INTERRUPTED;
		}
#else
		switch(WSAGetLastError())
		{
		case WSAEWOULDBLOCK:
			return ERROR_WOULDBLOCK;
		}
#endif
		return ERROR_FAILED;
	}

	bool SocketUtils::IsSocketEagain()
	{
#ifdef __linux
		int e = errno;
		return (e == EAGAIN || e == EINTR);
#else
		int e = WSAGetLastError();
		return e == WSAEWOULDBLOCK;
#endif
	}

	char* SocketUtils::InetNtoa(struct in_addr in)
	{
		return ::inet_ntoa(in);
	}

	int SocketUtils::InetAton( const char *ip, struct in_addr *addr )
	{
#ifdef __linux
		return ::inet_aton(ip,addr);
#else
		addr->S_un.S_addr = ::inet_addr(ip);
		return 0;
#endif
	}

	int SocketUtils::Ioctl( int s,long cmd,int *argp )
	{
#ifdef __linux
		return ::ioctl(s,cmd,argp);
#else
		return ioctlsocket(s,cmd,(u_long*)argp);
#endif
	}

#ifdef __linux
	bool SocketUtils::ResolveHost( const char* host,char* ip )
	{
		struct hostent *answer;
		char ipstr[16];

		answer = gethostbyname(host);
		if (answer == NULL)
			return false;
		inet_ntop(AF_INET, (answer->h_addr_list)[0], ip, 16);
		return true;
	}
#else
	bool SocketUtils::ResolveHost( const char* host,char* ip )
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

	int SocketUtils::RecvSynco( int sock,char* buf,int len )
	{
		return ::recv(sock,buf,len,0);
	}

	int SocketUtils::RecvAsync( int sock,char* buf,int len )
	{
#ifdef __linux
		return ::recv(sock,buf,len,MSG_DONTWAIT);
#else
		return ::recv(sock,buf,len,0);
#endif
	}

	int SocketUtils::RecvUntilError( int sock,char* buf,int len )
	{
		int total_bytes = 0;

		while(len > 0)
		{
			int bytes = RecvAsync(sock,buf,len);

			if( bytes <=  0)
			{
				int lasterror = GetLastError();

				// 缓冲区已空
				if( lasterror == ERROR_WOULDBLOCK)
					break;

				// 调用中断,再来一次
				if( lasterror == ERROR_INTERRUPTED)
					continue;

				// 错误,关闭socket
				return -1;
			}
				
			buf += bytes;
			len -= bytes;
			total_bytes += bytes;
		}
		return total_bytes;
	}

	int SocketUtils::Close( int sock )
	{
#ifdef __linux
		return ::close(sock);
#else
		return ::closesocket(sock);
#endif
	}

	int SocketUtils::Shutdown( int sock )
	{
#ifdef __linux
		return ::shutdown(sock,SHUT_RDWR);
#else
		return ::shutdown(sock,0xff);
#endif
	}

	int SocketUtils::SendAsync( int sock,const char* buf,int len )
	{
#ifdef _MSC_VER
		return ::send(sock,buf,len,0);
#else
		return ::send(sock,buf,len,MSG_DONTWAIT);
#endif
	}

	int SocketUtils::SendAsyncEx( int sock,const char* buf,int len )
	{
//label_again:
		int bytes = SendAsync(sock,buf,len);
		if( bytes > 0 )
			return bytes;

		int lasterror = GetLastError();
		// 缓冲区已满,等待PULLOUT
		if( lasterror == ERROR_WOULDBLOCK)
			return 0;

		// 系统调用中断,再试
// 		if( lasterror == ERROR_INTERRUPTED)
// 			goto label_again;

		return -1;
	}
}
