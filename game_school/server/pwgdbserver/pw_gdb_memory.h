/*

#ifndef _pw_gdb_memory_
#define _pw_gdb_memory_

#include "pw_gdb_thread.h"

namespace gdb
{
	namespace memory
	{
		template<class T> class MemPool
		{
		public:
			MemPool()
			{
				pthread_mutex_init(&mLock,0);
			}
			~MemPool()
			{
				cleanup();
				pthread_mutex_destroy(&mLock);
			}
		public:
			size_t allocated()
			{
				return mObjects.size();
			}

			T* allocate()
			{
				pthread_mutex_lock(&mLock);
				if(!mObjects.empty())
				{
					T* result = mObjects.front();
					mObjects.pop_front();
					pthread_mutex_unlock(&mLock);
					return result;
				}
				pthread_mutex_unlock(&mLock);

				return (T*)malloc(sizeof(T));
			}

			void deallocate(T* val)
			{
				pthread_mutex_lock(&mLock);
				mObjects.push_back(val);
				pthread_mutex_unlock(&mLock);
			}

			void cleanup()
			{
				while(!mObjects.empty())
				{
					free(mObjects.front());
					mObjects.pop_front();
				}
			}
		private:
			typedef std::list<T*> CollectionObjectsT;
		private:
			CollectionObjectsT mObjects;
			pthread_mutex_t mLock;
		};

		// 受管理的对象基类
		template<class T> class ObjectMT
		{
		public:
			static MemPool<T>* GetMemPool()
			{
				static MemPool<T> sobj_MemPool;

				return &sobj_MemPool;
			}
			static void* operator new(size_t s)
			{
				return GetMemPool()->allocate();
			}

			static void operator delete(void* p,size_t s)
			{
				GetMemPool()->deallocate((T*)p);
			}
		};
	}
}

#endif // _pw_gdb_memory_
*/
