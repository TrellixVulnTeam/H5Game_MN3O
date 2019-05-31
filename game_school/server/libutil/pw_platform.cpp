#include "pw_platform.h"
#include <malloc.h>

#ifdef __linux
// 	#define _JE_MALLOC_

	#include <dirent.h>
	#include <unistd.h>
	#include <string.h>
	#include <assert.h>
	#include <stdio.h>

	#ifdef _JE_MALLOC_
		#define JEMALLOC_NO_DEMANGLE
		#include <jemalloc/jemalloc.h>
	#endif

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
// #ifndef _JE_MALLOC_
// 	void pw_free( void* ptr )
// 	{
// 		::free(ptr);
// 	}
// 
// 	void* pw_malloc( size_t size )
// 	{
// 		return ::malloc(size);
// 	}
// 
// 	void* pw_realloc( void* ptr,size_t size )
// 	{
// 		return ::realloc(ptr,size);
// 	}
// #else
// 	void pw_free( void* ptr )
// 	{
// 		::je_free(ptr);
// 	}
// 
// 	void* pw_malloc( size_t size )
// 	{
// 		return ::je_malloc(size);
// 	}
// 
// 	void* pw_realloc( void* ptr,size_t size )
// 	{
// 		return ::je_realloc(ptr,size);
// 	}
// #endif
}