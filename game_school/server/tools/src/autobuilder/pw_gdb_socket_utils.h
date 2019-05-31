#ifndef _pw_gdb_socket_utils_
#define _pw_gdb_socket_utils_

#include "pw_gdb_platform.h"

namespace gdb
{
	struct SocketUtils
	{
		static bool		IsSocketEagain();
		static char*	InetNtoa(struct in_addr in);
		static int		InetAton(const char *, struct in_addr *);
		static int		Ioctl(int s,long cmd,int *argp);
		static bool		ResolveHost(const char* host,char* ip);
		
		static int		RecvSynco(int sock,char* buf,int len);
		static int		RecvAsync(int sock,char* buf,int len);
		static int		RecvUntilError(int sock,char* buf,int len);

		static int		SendAsync(int sock,const char* buf,int len);
		static int		SendAsyncEx( int sock,const char* buf,int len );

		static int		Close(int sock);
		static int		Shutdown(int sock);
	};
}

#endif // _pw_socket_utils_
