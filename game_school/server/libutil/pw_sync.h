#ifndef _pw_sync_
#define _pw_sync_

#include "pw_def.h"

namespace pwutils
{
	class NullMutex
	{
	public:
		inline int lock() { return 0; }
		inline int unlock() { return 0; }
		inline int trylock() { return 0; }
	};

	class ThreadMutex
	{
	public:
		ThreadMutex()
		{
			pthread_mutex_init(&mLock,NULL);
		}

		~ThreadMutex()
		{
			pthread_mutex_destroy(&mLock);
		}

		inline int lock() 
		{
			return pthread_mutex_lock(&mLock);
		}

		inline int unlock() 
		{
			return pthread_mutex_unlock(&mLock);
		}

		inline int trylock()
		{
			return pthread_mutex_trylock(&mLock);
		}
	private:
		pthread_mutex_t mLock;
	};

	template<class T> class ThreadMutexGuard
	{
	public:
		ThreadMutexGuard(T& t)
			: mActualLock(t)
		{
			mActualLock.lock();
		}

		~ThreadMutexGuard()
		{
			mActualLock.unlock();
		}
	private:
		T& mActualLock;
	};

	template<class T,class LOCK = NullMutex> struct Singleton
	{
		static T*& instance()
		{
			static T* sp_instance = NULL;
			static LOCK sp_lock;

			if(sp_instance == NULL)
			{
				ThreadMutexGuard<LOCK> guard(sp_lock);
				if(sp_instance == NULL)
					sp_instance = new T();
			}
			return sp_instance;
		}

		static void close_instance()
		{
			if(T*& v = instance())
			{
				delete v;
				v = NULL;
			}
		}
	};

	
}

#endif // _pw_sync_