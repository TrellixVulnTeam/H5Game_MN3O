
#ifndef __pw_tss__
#define __pw_tss__

#include "pthread.h"

namespace pwutils
{
	template<class T> class ThreadSpecific
	{
	public:
		ThreadSpecific()
		{
			pthread_key_create(&mKey,ThreadSpecific<T>::destructor);
		}

		~ThreadSpecific()
		{
			pthread_key_delete(mKey);
		}
	public:
		void set(T* value)
		{
			pthread_setspecific(mKey,value);
		}

		T* get()
		{
			return (T*)pthread_getspecific(mKey);
		}
	private:
		static void destructor(void* )
		{

		}
	private:
		pthread_key_t mKey;
	};
}

#endif