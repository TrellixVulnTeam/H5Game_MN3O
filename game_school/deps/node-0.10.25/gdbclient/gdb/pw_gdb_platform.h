#ifndef _pw_gdb_platform_
#define _pw_gdb_platform_

#ifndef nullptr
	#define nullptr ((void*)0)
#endif
#ifndef _MSC_VER
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <sys/epoll.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <errno.h>
	#include <execinfo.h>
	#include <netdb.h>
	#include <poll.h>
#else
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <WinSock2.h>
	#include <mswsock.h>
#endif 

#ifndef __linux
	typedef int socklen_t;
#endif


namespace platform
{
	extern int init();
	extern int fini();

	void pw_free(void* ptr);
	void* pw_malloc(size_t size);
	void* pw_realloc(void* ptr,size_t size);
}


#endif // _pw_platform_