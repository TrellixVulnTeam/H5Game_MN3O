#ifndef _pwdist_utils_
#define _pwdist_utils_

#include "pwdist_def.h"
#include "pw_time.h"

namespace pwdist_utils
{


	class mutex
	{
	public:
		mutex()
		{
			pthread_mutex_init(&mLock,NULL);
		}

		~mutex()
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

	template<class T> class thread_mutex_guard
	{
	public:
		thread_mutex_guard(T& t)
			: mActualLock(t)
		{
			mActualLock.lock();
		}

		~thread_mutex_guard()
		{
			mActualLock.unlock();
		}
	private:
		T& mActualLock;
	};

#ifdef _DEBUG
	class rwlock
	{
	public:
		rwlock()
		{
			m_cw = 0;
			m_cr = 0;
		}

		~rwlock()
		{
		}

		bool try_rlock()
		{
			bool result = true;

			m_cs.lock();
			if(m_cw != 0)
				result = false;
			else
				m_cr ++;
			m_cs.unlock();

			return result;
		}

		bool runlock()
		{
			bool result = true;

			m_cs.lock();
			m_cr --;
			m_cs.unlock();

			return result;
		}

		bool try_wlock()
		{
			bool result = true;

			m_cs.lock();
			if(m_cw != 0 || m_cr != 0)
				result = false;
			else
				m_cw ++;
			m_cs.unlock();

			return result;
		}

		bool wunlock()
		{
			bool result = true;

			m_cs.lock();
			if(m_cw != 0)
				m_cw --;
			else
				result = false;
			m_cs.unlock();

			return result;
		}

		void rlock()
		{
			while(!try_rlock())
				;
		}

		void wlock()
		{
			while(!try_wlock())
				;
		}
	private:
		mutex m_cs;
		int m_cw;
		int m_cr;
	};

#else
	class rwlock
	{
	public:
		rwlock()
		{
			pthread_rwlock_init(&m_objLock,NULL);
		}

		~rwlock()
		{
			pthread_rwlock_destroy(&m_objLock);
		}
	public:
		int rlock()
		{
			return pthread_rwlock_rdlock(&m_objLock);
		}

		int wlock()
		{
			while(1)
			{
				int result = pthread_rwlock_trywrlock(&m_objLock);
				if( result == 0 )
					break;
				pwutils::time::sleep(1);
			}
			return 0;
		}

		int runlock()
		{
			assert(pthread_rwlock_unlock(&m_objLock) == 0);
			return 0;
		}

		int wunlock()
		{
			assert(pthread_rwlock_unlock(&m_objLock) == 0);
			return 0;
		}
	public:
		pthread_rwlock_t m_objLock;
	};
#endif
}

#endif // _pwdist_utils_