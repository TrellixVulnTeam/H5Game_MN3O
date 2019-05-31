#include "pw_runnable.h"
#include "pw_tss.h"

namespace pwutils
{
	pwutils::ThreadSpecific<Runnable> g_objCurrentThread;

	namespace memory
	{
		void atthreadexit(void (*_pfn)())
		{
			if(Runnable* r = g_objCurrentThread.get())
				r->AtThreadExit(_pfn);
		}
	}

	Runnable::Runnable()
	{
		mClosed = true;
		mThreadStack = NULL;
	}

	Runnable::~Runnable()
	{
		Cleanup();
	}

	int Runnable::Cleanup()
	{
		if(!mClosed)
		{
			mClosed = true;
			for(size_t i = 0; i < mThreads.size(); ++i)
				pthread_join(mThreads[i],nullptr);
			mThreads.clear();
			
			// 释放栈
			for(size_t i = 0; i < mThreadStacks.size(); ++i)
				free(mThreadStacks[i]);
			mThreadStacks.clear();

			return 0;
		}
		return -1;
	}

	int Runnable::create_stack(void*& buf,size_t& len)
	{
		const size_t cst_stack_size = 5 * cst_tmp_buf_size;

		buf = malloc(cst_stack_size);
		len = cst_stack_size;

		return 0;
	}

	int Runnable::Startup(int threads)
	{
		if(!mClosed)
			return -1;
		if(mThreads.size() > 0)
			return -2;

		mClosed = false;

		for(int i = 0; i < threads; ++i)
		{
			pthread_attr_t   tattr;
			pthread_attr_init(&tattr);

			void* stack = nullptr;
			size_t stack_len = 0;

			this->create_stack(stack,stack_len);

#ifdef _MSC_VER
			pthread_attr_setstacksize(&tattr,stack_len);
			pthread_attr_setstackaddr(&tattr,stack);
#else
			pthread_attr_setstack(&tattr,stack,stack_len);
#endif

			pthread_t thread;
			pthread_create(&thread,&tattr,&Runnable::thread_routine,this);
			mThreads.push_back(thread);
			mThreadStacks.push_back(stack);

			pthread_attr_destroy(&tattr);
		}
		return 0;
	}

	int Runnable::run()
	{
		return svc();
	}

	int Runnable::svc()
	{
		return 0;
	}

	void* Runnable::thread_routine(void* param)
	{
		Runnable* runnable = (Runnable*)param;

		g_objCurrentThread.set(runnable);

		void* result = (void*)runnable->run();

		// 调用AtThreadExit
		runnable->CallAtThreadExit();
		runnable->FreeAtThreadExit();

		g_objCurrentThread.set(NULL);

		return result;
	}

	void Runnable::AtThreadExit(void (*pfn)())
	{
		mAtExits.push_back(pfn);
	}

	void Runnable::CallAtThreadExit()
	{
		for(size_t i = 0; i < mAtExits.size(); ++i)
			(mAtExits[i])();
		mAtExits.clear();
	}

	void Runnable::FreeAtThreadExit()
	{
// 		pthread_t self = pthread_self();
// 		for(size_t i = 0; i < mThreads.size(); ++i)
// 		{
// 			if(memcmp(&mThreads[i],&self,sizeof(pthread_t)) == 0)
// 			{
// 				free(mThreadStacks[i]);
// 				mThreads.erase(mThreads.begin() + i);
// 				mThreadStacks.erase(mThreadStacks.begin() + i);
// 				break;
// 			}
// 		}
	}

}
