#ifndef _pw_socket_utils_
#define _pw_socket_utils_


#include "pw_platform.h"
#include <string>

namespace pwutils
{
	extern bool is_socket_eagain();
	extern char* _inet_ntoa(struct in_addr in);
	extern int inet_aton (const char *, struct in_addr *);
	extern unsigned long int inet_aton (const char *,bool to_host_order = false);
	extern int my_ioctl(int s,long cmd,int *argp);
	extern bool resolve_host(const char* host,char* ip);

	extern std::string get_sock_name(int sock,bool port);
	extern std::string get_peer_name(int sock,bool port);
}

#ifndef __linux
	typedef int socklen_t;
#endif

#endif // _pw_socket_utils_
