#ifndef _pw_memory_
#define _pw_memory_

#include <deque>
#include <malloc.h>
#include <pthread.h>

#define PW_MEMORY_OPEN

namespace pwutils
{
	namespace memory
	{
        template<unsigned N,bool MultiThread = false> class FixedAllocator
		{
		public:
			FixedAllocator()
				: m_nLastBlockUsed(0)
			{
                if(MultiThread)
                    pthread_mutex_init(&m_objLock,NULL);

				if(N <= 512)
					m_nBlockSize = N * 100;
				else if(N <= 8196)
					m_nBlockSize = N * 20;
				else
					m_nBlockSize = N * 10;
			}

			~FixedAllocator()
			{
				while(m_vBlocks.size() > 0)
				{
					char* mem = (char*)m_vBlocks.front();
					m_vBlocks.pop_front();

					free(mem);
				}
                if(MultiThread)
                    pthread_mutex_destroy(&m_objLock);
			}
		public:
			void* allocate()
			{
				void* r = NULL;

                if(MultiThread)
                    pthread_mutex_lock(&m_objLock);

				if(!m_vFreeMemorys.empty())
				{
					r = m_vFreeMemorys.front();
					m_vFreeMemorys.pop_front();
				}
				else
				{
					r = _allocate();	
				}

                if(MultiThread)
                    pthread_mutex_unlock(&m_objLock);

				return r;
			}
			void deallocate(void* ptr)
			{
                if(MultiThread)
                {
                    pthread_mutex_lock(&m_objLock);
                    m_vFreeMemorys.push_back(ptr);
                    pthread_mutex_unlock(&m_objLock);
                }
                else
                {
                    m_vFreeMemorys.push_back(ptr);
                }
			}
		protected:
			void* _allocate()
			{
				if(m_vBlocks.empty() || (m_nBlockSize - m_nLastBlockUsed) < N)
				{
					m_vBlocks.push_back(malloc(m_nBlockSize));
					m_nLastBlockUsed = 0;
				}
				char* curr = (char*)m_vBlocks.back();
				char* result = &curr[m_nLastBlockUsed];
				m_nLastBlockUsed += N;
				return result;
			}
		protected:
			typedef std::deque<void*> CollectionMemorysT;
		protected:
			size_t m_nBlockSize;
			size_t m_nLastBlockUsed;
			CollectionMemorysT m_vBlocks;
			CollectionMemorysT m_vFreeMemorys;
        protected:
            pthread_mutex_t m_objLock;
		};

        template<class T,bool MultiThread = false> class FixedAllocatorT
        {
        public:
            FixedAllocatorT()
                : m_nLastBlockUsed(0)
            {
                if(MultiThread)
                    pthread_mutex_init(&m_objLock,NULL);

                if(sizeof(T) <= 512)
                    m_nBlockSize = sizeof(T) * 100;
                else if(sizeof(T) <= 8196)
                    m_nBlockSize = sizeof(T) * 20;
                else
                    m_nBlockSize = sizeof(T) * 10;
            }

            ~FixedAllocatorT()
            {
                while(m_vBlocks.size() > 0)
                {
                    char* mem = (char*)m_vBlocks.front();
                    m_vBlocks.pop_front();

                    free(mem);
                }
                if(MultiThread)
                    pthread_mutex_destroy(&m_objLock);
            }
        public:
            void* allocate()
            {
                void* r = NULL;

                if(MultiThread)
                    pthread_mutex_lock(&m_objLock);

                if(!m_vFreeMemorys.empty())
                {
                    r = m_vFreeMemorys.front();
                    m_vFreeMemorys.pop_front();
                }
                else
                {
                    r = _allocate();
                }

                if(MultiThread)
                    pthread_mutex_unlock(&m_objLock);

                return r;
            }
            void deallocate(void* ptr)
            {
                if(MultiThread)
                {
                    pthread_mutex_lock(&m_objLock);
                    m_vFreeMemorys.push_back(ptr);
                    pthread_mutex_unlock(&m_objLock);
                }
                else
                {
                    m_vFreeMemorys.push_back(ptr);
                }
            }
        protected:
            void* _allocate()
            {
                if(m_vBlocks.empty() || (m_nBlockSize - m_nLastBlockUsed) < sizeof(T))
                {
                    m_vBlocks.push_back(malloc(m_nBlockSize));
                    m_nLastBlockUsed = 0;
                }
                char* curr = (char*)m_vBlocks.back();
                char* result = &curr[m_nLastBlockUsed];
                m_nLastBlockUsed += sizeof(T);
                return result;
            }
        protected:
            typedef std::deque<void*> CollectionMemorysT;
        protected:
            size_t m_nBlockSize;
            size_t m_nLastBlockUsed;
            CollectionMemorysT m_vBlocks;
            CollectionMemorysT m_vFreeMemorys;
        protected:
            pthread_mutex_t m_objLock;
        };

        class Allocator
        {
        public:
            virtual ~Allocator() {}
        public:
            virtual void* allocate(size_t size) = 0;
            virtual void* reallocate(void* ptr,size_t osize,size_t nsize) = 0;
            virtual void deallocate(void* ptr,size_t size) = 0;
        };

        template<bool MultiThread = false> class TAllocator : public Allocator
		{
		public:
            virtual void* allocate(size_t size)
            {
#ifdef PW_MEMORY_OPEN
				if(size <= 32)
					return m_allocator_32.allocate();
				if(size <= 48)
					return m_allocator_48.allocate();
				if(size <= 64)
					return m_allocator_64.allocate();
				if(size <= 96)
					return m_allocator_96.allocate();
				if(size <= 128)
					return m_allocator_128.allocate();
				if(size <= 256)
					return m_allocator_256.allocate();
				if(size <= 512)
					return m_allocator_512.allocate();
				if(size <= 1534)
					return m_allocator_1534.allocate();
				if(size <= 2048)
					return m_allocator_2048.allocate();
				if(size <= 8196)
					return m_allocator_8196.allocate();
#endif
                return malloc(size);
			}

            virtual void* reallocate(void* ptr,size_t osize,size_t nsize)
            {
#ifndef PW_MEMORY_OPEN
                return realloc(ptr,nsize);
#else
				if(nsize == 0)
				{
					deallocate(ptr,osize);
					return NULL;
				}

				if(ptr == NULL || osize == 0)
					return allocate(nsize);

				size_t capacity = getCapacity(osize);
				if( capacity >= nsize )
					return ptr;

				void* nptr = this->allocate(nsize);
				memcpy(nptr,ptr,osize);
				deallocate(ptr,osize);
                return nptr;
#endif
			}

            virtual void deallocate(void* ptr,size_t size)
			{
#ifdef PW_MEMORY_OPEN
                if(size <= 32)
					return m_allocator_32.deallocate(ptr);
				if(size <= 48)
					return m_allocator_48.deallocate(ptr);
				if(size <= 64)
					return m_allocator_64.deallocate(ptr);
				if(size <= 96)
					return m_allocator_96.deallocate(ptr);
				if(size <= 128)
					return m_allocator_128.deallocate(ptr);
				if(size <= 256)
					return m_allocator_256.deallocate(ptr);
				if(size <= 512)
					return m_allocator_512.deallocate(ptr);
				if(size <= 1534)
					return m_allocator_1534.deallocate(ptr);
				if(size <= 2048)
					return m_allocator_2048.deallocate(ptr);
				if(size <= 8196)
                    return m_allocator_8196.deallocate(ptr);
#endif
                free(ptr);
			}
		private:
			size_t getCapacity(size_t size)
			{
				if(size <= 32)
					return 32;
				if(size <= 48)
					return 48;
				if(size <= 64)
					return 64;
				if(size <= 96)
					return 96;
				if(size <= 128)
					return 128;
				if(size <= 256)
					return 256;
				if(size <= 512)
					return 512;
				if(size <= 1534)
					return 1534;
				if(size <= 2048)
					return 2048;
				if(size <= 8196)
					return 8196;
				return size;
			}
		private:
            FixedAllocator<32,MultiThread>	m_allocator_32;
            FixedAllocator<48,MultiThread>	m_allocator_48;
            FixedAllocator<64,MultiThread>	m_allocator_64;
            FixedAllocator<96,MultiThread>	m_allocator_96;
            FixedAllocator<128,MultiThread> m_allocator_128;
            FixedAllocator<256,MultiThread> m_allocator_256;
            FixedAllocator<512,MultiThread> m_allocator_512;
            FixedAllocator<1024,MultiThread> m_allocator_1024;
            FixedAllocator<1534,MultiThread> m_allocator_1534;
            FixedAllocator<2048,MultiThread> m_allocator_2048;
            FixedAllocator<8196,MultiThread> m_allocator_8196;
		};

        typedef TAllocator<true>  AllocatorMT;
        typedef TAllocator<false> AllocatorST;

        // ------------------------------------------------------------------------

        template<class T,bool MultiThread = false> class BaseObject
        {
            static FixedAllocatorT<T,MultiThread> sobj_pool;
        public:
            static void* operator new(size_t s)
            {
                return sobj_pool.allocate();
            }

            static void operator delete(void* p,size_t)
            {
                sobj_pool.deallocate(p);
            }
        };

        template<class T,bool MultiThread> FixedAllocatorT<T,MultiThread> BaseObject<T,MultiThread>::sobj_pool;

        // ------------------------------------------------------------------------
    }
}


#endif // _pw_memory_
