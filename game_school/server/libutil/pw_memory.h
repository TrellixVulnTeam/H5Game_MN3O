#ifndef _pw_memory_
#define _pw_memory_

#include "pw_def.h"
#include <iostream>
#include <list>
#include "pw_tss.h"
#include <malloc.h>
#include "pw_backtrace.h"

#define _PWNGS_USE_MEMPOOL

namespace pwutils
{
	namespace memory
	{
		extern void atthreadexit(void (*pfn)());

		// ------------------------------------------------------------------------------

		template<class T,bool MultiThread = true> class Object
		{

		};

		typedef std::list<void*> CollectionObjectsT;
		typedef std_unordered_set<void*> CollectionPointersT;

		struct __ObjectTSS
		{
			CollectionObjectsT freelist;
			CollectionPointersT used_pointers;
			CollectionPointersT free_pointers;
		};

		// 受管理的对象基类
		template<class T,bool CheckPointer = false> class ObjectInThread
		{
#ifdef _PWNGS_USE_MEMPOOL
			static pwutils::ThreadSpecific<__ObjectTSS> s_tss;

			static __ObjectTSS* getTSS()
			{
				__ObjectTSS* list = s_tss.get();
				if(list == NULL)
				{
					list = new __ObjectTSS();
					s_tss.set(list);

					atthreadexit(ObjectInThread<T,CheckPointer>::freeObjects);
				}
				return list;
			}

			static void freeObjects()
			{
				__ObjectTSS* tss = getTSS();
				if(tss != NULL)
				{
					std::cout << "ObjectInThread<T>::freeObjects T=" << typeid(T).name() << " size=" << tss->freelist.size() << std::endl;

					while(!tss->freelist.empty())
					{
						::free(tss->freelist.front());
						tss->freelist.pop_front();
					}
					delete tss;
					s_tss.set(NULL);
				}
			}
		public:
			static void* operator new(size_t s)
			{
				if(s != sizeof(T))
				{
// 					std::cout << "ObjectInThread<T>::new sizeof(T) != s, T=" << typeid(T).name() << "\n";
					return ::malloc(s);
				}

				__ObjectTSS* tss = getTSS();
				assert(tss);

				CollectionObjectsT* freelist = &tss->freelist;
				assert(freelist);

				void* result = 0;

				if(!freelist->empty())
				{
					result = freelist->front();
					freelist->pop_front();
				}
				else
				{
					result = ::malloc(s);
				}

				if(CheckPointer)
				{
					CollectionPointersT* used_pointers = &tss->used_pointers;
					CollectionPointersT* free_pointers = &tss->free_pointers;
					assert(used_pointers && free_pointers);

					used_pointers->insert(result);
					free_pointers->erase(result);
				}
				return result;
			}

			static void operator delete(void* p,size_t s)
			{
				if(s != sizeof(T))
				{
// 					std::cout << "ObjectInThread<T>::delete sizeof(T) != s, T=" << typeid(T).name() << "\n";
					::free(p);
					return;
				}

				__ObjectTSS* tss = getTSS();
				assert(tss);

				if(CheckPointer)
				{
					CollectionPointersT* used_pointers = &tss->used_pointers;
					CollectionPointersT* free_pointers = &tss->free_pointers;
					assert(used_pointers && free_pointers);

					// 是否已经在已用指针中
					if(used_pointers->erase(p) != 1)
					{
						std::cout << "ObjectInThread<T>::delete invalid pointer, T=" << typeid(T).name() << " stack=" << get_stack_trace(15) << "\n";
#ifdef _DEBUG
						assert(false && "ObjectInThread<T>::delete invalid pointer");
#endif
						return ;
					}

					if(free_pointers->find(p) != free_pointers->end())
					{
						std::cout << "ObjectInThread<T>::delete allready freed , T=" << typeid(T).name() << " stack=" << get_stack_trace(15) << "\n";
#ifdef _DEBUG
						assert(false && "ObjectInThread<T>::delete allready freed");
#endif
						return ;
					}

					free_pointers->insert(p);
				}

				CollectionObjectsT* freelist = &tss->freelist;
				assert(freelist);
				
				memset(p,0xcdcdcdcd,s);

				freelist->push_back(p);
			}
#endif
		};

#ifdef _PWNGS_USE_MEMPOOL
		template<class T,bool CheckPointer> pwutils::ThreadSpecific<__ObjectTSS> ObjectInThread<T,CheckPointer>::s_tss;
#endif
	}
}


#endif //_pw_memory
