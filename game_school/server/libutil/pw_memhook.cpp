//#ifdef _PW_MEMORY_TRACE_
//#ifdef _PW_MEMORY_TRACE_XXX_
#if 0


#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unordered_map>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <dlfcn.h>

static void *(*old_malloc_hook)(size_t size, const void* ptr);
static void  (*old_free_hook)(void* ptr, const void* caller);
static void *(*old_realloc_hook)(void *ptr, size_t size, const void *caller);

static void memory_trace_backup(void);
static void memory_trace_hook(void);
static void memory_trace_restore(void);
static void memory_trace_deinit(void);
static void memory_trace_init(void);

static void *my_malloc_hook (size_t size, const void* ptr);
static void  my_free_hook (void* ptr, const void* caller);
static void *my_realloc_hook (void *ptr, size_t size, const void *caller);

static const void* memory_trace_resolve(const void* addr);
static const char* memory_trace_resolve_str(const void* addr);

static pthread_mutex_t g_mutex;
static std::unordered_map<void*,const void*>* g_trace = 0;
static std::fstream* g_stream = 0;
static void* g_prog_base = 0;

static void my_init_hook(void)
{
	memory_trace_init();
}

static void memory_trace_init(void)
{
	g_trace = new std::unordered_map<void*,const void*>();
	g_stream = new std::fstream;
	pthread_mutex_init(&g_mutex,0);
	{
		char buf[256];
		sprintf(buf,"./mem_%d.log",getpid());
		g_stream->open(buf,std::ios_base::out);
		assert(g_stream->good());
	}
	memory_trace_backup();
	memory_trace_hook();
	atexit(memory_trace_deinit);
	
	Dl_info info;
	dladdr((void*)&memory_trace_init,&info);
	g_prog_base = info.dli_fbase;

	return;
}

static void memory_trace_deinit(void)
{
	memory_trace_restore();

	if(g_trace->size() > 0)
	{
		(*g_stream) << "MemoryLeaks:" << std::endl;

		for(auto iter = g_trace->begin(); iter != g_trace->end(); ++iter)
		{
			(*g_stream) << "\t" << iter->first << " " << memory_trace_resolve_str(iter->second) << std::endl;
		}
	}


	pthread_mutex_destroy(&g_mutex);

	delete g_trace;
	delete g_stream;

	return;
}

static const void* memory_trace_resolve(const void* addr)
{
	void* buf[10];
	void* result = 0;

	int n = backtrace(buf,sizeof(buf)/sizeof(buf[0]));
	int offset = 0;

	result = buf[0];
	for(int i = 0; i < n; ++i)
	{
		if(addr == buf[i])
		{
			offset = i;
			break;
		}
	}

	for(int i = offset; i < n; ++i)
	{
		Dl_info info;
		if(!dladdr(buf[i],&info))
			continue;

		if(info.dli_fbase == g_prog_base)
		{
			result = buf[i];
			break;
		}
	}
	return result;
}

static const char* memory_trace_resolve_str(const void* addr)
{
	static char s_buf[256] = "";

	void* buf[1];

	buf[0] = (void*)addr;

	char** symbols = ::backtrace_symbols(buf,1);
	strcpy(s_buf,symbols[0]);
	return s_buf;
}

/* Override initializing hook from the C library. */
void (*__malloc_initialize_hook) (void) = my_init_hook;

static void memory_trace_backup(void)
{
	old_malloc_hook  = __malloc_hook;
	old_free_hook    = __free_hook;
	old_realloc_hook = __realloc_hook;

	return;
}

static void memory_trace_restore(void)
{
	__malloc_hook  = old_malloc_hook;
	__free_hook    = old_free_hook;
	__realloc_hook = old_realloc_hook;

	return;
}

static void memory_trace_hook(void)
{
	__malloc_hook  = my_malloc_hook;
	__free_hook    = my_free_hook;
	__realloc_hook = my_realloc_hook;

	return;
}

static void * my_malloc_hook (size_t size, const void *caller)
{
	pthread_mutex_lock(&g_mutex);

	void *result = NULL;
	memory_trace_restore();
	result = malloc (size);
	
	if(g_trace->find(result) != g_trace->end())
	{
		(*g_stream) << "malloc failed:"  << result << " caller:" << memory_trace_resolve(caller) << std::endl;
	}
	g_trace->insert(std::make_pair(result,caller));

	memory_trace_hook();
	pthread_mutex_unlock(&g_mutex);

	return result;
}

static void my_free_hook (void *ptr, const void *caller)
{
	pthread_mutex_lock(&g_mutex);

	memory_trace_restore();
	free (ptr);
	
	if(ptr != 0)
	{
		switch(g_trace->erase(ptr))
		{
		case 0:
			(*g_stream) << "(double free),free failed:"  << ptr << " caller:" << memory_trace_resolve(caller) << std::endl;
			//assert(false);
			break;
		case 1 :
			break;
		default:
			//assert(false);
			break;
		}
	}
	memory_trace_hook();
	pthread_mutex_unlock(&g_mutex);
	return;
}

static void *my_realloc_hook (void *ptr, size_t size, const void *caller)
{
	pthread_mutex_lock(&g_mutex);

	void* result = NULL;
	memory_trace_restore();
	result = realloc(ptr, size);

	if(ptr != 0)
	{
		switch(g_trace->erase(ptr))
		{
		case 0:
			(*g_stream) << "(double free),remalloc failed:"  << result << " caller:" << memory_trace_resolve(caller) << std::endl;
			//assert(false);
			break;
		case 1 :
			break;
		default:
			//assert(false);
			break;
		}
	}

	if(g_trace->find(result) != g_trace->end())
	{
		(*g_stream) << "remalloc failed:"  << result << " caller:" << memory_trace_resolve(caller) << std::endl;
	}
	g_trace->insert(std::make_pair(result,caller));
	
	memory_trace_hook();
	pthread_mutex_unlock(&g_mutex);

	return result;
}

#endif //_PW_MEMORY_TRACE_
