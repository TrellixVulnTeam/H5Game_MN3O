#ifndef _pw_gdb_thread_
#define _pw_gdb_thread_

#ifndef pid_t
	typedef int pid_t;
#endif

#include <pthread.h>

namespace gdb
{
	class Thread
	{
	public:
		Thread();
	public:
		void Start();
		void Close();
	public:
		static Thread* Self();
	protected:
		virtual void Run() = 0;
	protected:
		static void* fnThread(void*);
	protected:
		virtual void OnThreadStarted();
		virtual void OnThreadStopped();
	protected:
		pthread_t m_mThread;
	protected:
		volatile bool m_bClosed;
	};


	enum ETLSDESTRUCTOR
	{
		TLS_DESTRUCTOR_NIL,
		TLS_DESTRUCTOR_DELETE,
		TLS_DESTRUCTOR_DELETE_ARRAY,
		TLS_DESTRUCTOR_FREE,
	};

	template<class T> class TLS
	{
	public:
		TLS(ETLSDESTRUCTOR destructor = TLS_DESTRUCTOR_DELETE)
		{
			void (*fn)(void*) = 0;
			switch(destructor)
			{
			case TLS_DESTRUCTOR_DELETE:
				fn = &TLS<T>::fnDestructorDelete;
				break;
			case TLS_DESTRUCTOR_DELETE_ARRAY:
				fn = &TLS<T>::fnDestructorDeleteArray;
				break;
			case TLS_DESTRUCTOR_FREE:
				fn = &TLS<T>::fnDestructorFree;
				break;
			}
			pthread_key_create(&m_mKey,fn);
		}
	public:
		T* Get()
		{
			return (T*)pthread_getspecific(m_mKey);
		}

		void Set(T* value)
		{
			pthread_setspecific(m_mKey,value);
		}
	public:
		static void fnDestructorDelete(void* val)
		{
			delete (T*)val;
		}

		static void fnDestructorDeleteArray(void* val)
		{
			delete [] (T*)val;
		}

		static void fnDestructorFree(void* val)
		{
			free((T*)val);
		}
	protected:
		pthread_key_t m_mKey;
	};
}


#endif // _pw_thread_