#ifndef RUNNABLE_H
#define RUNNABLE_H

#include "pw_def.h"
#include "pthread.h"

namespace pwutils
{
	class Runnable
	{
	public:
		Runnable();
		virtual ~Runnable();
	public:
		int Startup(int threads = 1);
		int Cleanup();
	public:
		inline char* GetStackPtr()
		{
			return (char*)mThreadStack;
		}
	public:
		void AtThreadExit(void (*pfn)());
	protected:
		virtual int run();
		virtual int svc();
	protected:
		virtual	int create_stack(void*& buf,size_t& len);
	protected:
		static void* thread_routine(void* param);
	protected:
		void CallAtThreadExit();
		void FreeAtThreadExit();
	protected:
		volatile bool mClosed;
		std::vector<pthread_t> mThreads;
		std::vector<void*> mThreadStacks;
		std::vector<void (*)()> mAtExits;
		void* mThreadStack;
	};

	namespace memory
	{
		extern void atthreadexit(void (*_pfn)());
	};
}

#endif // RUNNABLE_H
