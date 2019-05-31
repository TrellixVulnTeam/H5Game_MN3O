#include "pw_gdb_platform.h"
#include <malloc.h>

#ifdef __linux
	#include <dirent.h>
	#include <unistd.h>
	#include <string.h>
	#include <assert.h>
	#include <stdio.h>
#endif

namespace platform
{
	int init()
	{

#ifndef __linux
		WSADATA data = {0};
		WSAStartup(MAKEWORD(2,2),&data);
#else
		{
			char buf[1024] = "";
			readlink("/proc/self/exe",buf,1024);
			char* chr = strrchr(buf,'/');
			assert(chr != NULL);
			chr[1] = 0;			
			chdir(buf);
			printf("chdir:%s\n",buf);
		}
#endif
		return 0;
	}

	int fini()
	{
#ifndef __linux
		WSACleanup();
#endif
		return 0;
	}

	void pw_free( void* ptr )
	{
		::free(ptr);
	}

	void* pw_malloc( size_t size )
	{
		return ::malloc(size);
	}

	void* pw_realloc( void* ptr,size_t size )
	{
		return ::realloc(ptr,size);
	}
}