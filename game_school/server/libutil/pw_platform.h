#ifndef _pw_platform_
#define _pw_platform_

#ifdef __linux
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
	#include <sys/inotify.h>
	
// 	#define JEMALLOC_MANGLE
// 	#include "jemalloc/jemalloc.h"
#else
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <WinSock2.h>
	#include <mswsock.h>
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