#ifndef _pw_ring_hashtable_
#define _pw_ring_hashtable_

#include "pw_types.h"

namespace pwutils
{
	template<class T> struct SObjectDestroyerNull
	{
		void operator()(T* t)
		{			
		}
	};

	template<class T> struct SObjectDestroyerDelete
	{
		void operator()(T* t)
		{
			delete t;
		}
	};

	template<class T> struct SObjectIdEqualer
	{
		bool operator()(T* obj,int64 context)
		{
			return obj->id == context;
		}
	};

	template<class T,class HASH_FUNC,class DESTROYER = SObjectDestroyerNull<T> > class RingHashTable
	{
	public:
		struct Enumerator
		{
		private:
			RingHashTable<T,HASH_FUNC,DESTROYER>* hashtable;
			int32 curr;
			int32 enumed;
			T* current_object;
		public:
			Enumerator(RingHashTable<T,HASH_FUNC,DESTROYER>* table)
				: hashtable(table)
				, curr(-1)
				, enumed(0)
				, current_object(NULL)
			{
			}
		public:
			inline bool MoveNext()
			{
				++curr;				
				if(curr < hashtable->m_nCapacity && enumed < hashtable->m_nCount)
				{
					current_object = this->_Current();
					if(current_object != NULL)
						++enumed;
					return true;
				}
				return false;
			}

			inline T* Current()
			{
				return current_object;
			}
		private:
			inline T* _Current()
			{
				for(int i = curr; i < hashtable->m_nCapacity; ++i)
				{
					if(hashtable->m_pArray[i] != NULL)
					{
						curr = i;
						return hashtable->m_pArray[i];
					}
				}
				return NULL;
			}
		};
	public:
		Enumerator GetEnumerator()
		{
			return Enumerator(this);
		}
	public:
		RingHashTable(int32 capacity = 1313)
		{
			m_nCount = 0;
			m_nCapacity = capacity;
			m_pArray = new T*[capacity];
			memset(m_pArray,0,sizeof(T*) * capacity);
		}

		virtual ~RingHashTable()
		{
			clear();			
			delete [] m_pArray;
		}
	public:
		void clear()
		{
			DESTROYER destroyer;
			{
				Enumerator e = this->GetEnumerator();
				while(e.MoveNext())
				{
					destroyer(e.Current());
				}
			}

			memset(m_pArray,0,sizeof(T*) * m_nCapacity);
			m_nCount = 0;
		}
	public:
		int32 add(T* obj)
		{
			HASH_FUNC func;
			return add(func(obj),obj);
		}

		int32 add(int32 hash,T* obj)
		{
			int32 index = find(hash,NULL);
			if(index >= 0)
			{
				m_pArray[index] = obj;
				++m_nCount;
				return index;
			}
			return -1;
		}

		bool del(T* obj)
		{
			HASH_FUNC func;
			return del(func(obj),obj);
		}

		bool del(int32 hash,T* obj)
		{
			if(obj == NULL)
				return false;

			int32 index = find(hash,obj);
			if(index >= 0)
			{
				m_pArray[index] = NULL;
				--m_nCount;
				return true;
			}
			return false;
		}

		bool exists(T* obj)
		{
			HASH_FUNC func;
			return exists(func(obj),obj);
		}

		bool exists(int32 hash,T* obj)
		{
			return this->find(hash,obj) >= 0;
		}
	public:
		template<class FIND_FUNC> T* search(int32 hash,int64 context)
		{
			FIND_FUNC findfunc;

			int32 index = hash % m_nCapacity;
			for(int32 i = index; i < m_nCapacity; ++i)
			{
				if(m_pArray[i] && findfunc(m_pArray[i],context))
					return m_pArray[i];
			}

			for(int32 i = 0; i < index; ++i)
			{
				if(m_pArray[i] && findfunc(m_pArray[i],context))
					return m_pArray[i];
			}
			return NULL;
		}
	public:
		void grow(int32 capacity)
		{
			if(capacity <= m_nCapacity)
				return ;
			T** oldbuf = m_pArray;
			int32 oldcount = m_nCount;
			int32 oldcapacity = m_nCapacity;

			m_pArray = new T*[capacity];
			m_nCapacity = capacity;
			m_nCount = 0;
			memset(m_pArray,0,sizeof(T*) * capacity);

			for(int32 i = 0; i < oldcapacity; ++i)
			{
				if(oldbuf[i] != NULL)
					this->add(oldbuf[i]);
			}

			delete [] oldbuf;
		}
	protected:
		int32 find(int32 hash,T* obj)
		{
			int32 index = hash % m_nCapacity;
			for(int32 i = index; i < m_nCapacity; ++i)
			{
				if(m_pArray[i] == obj)
					return i;
			}

			for(int32 i = 0; i < index; ++i)
			{
				if(m_pArray[i] == obj)
					return i;
			}
			return -1;
		}
	protected:
		T** m_pArray;
		int32 m_nCount;
		int32 m_nCapacity;
	};
}


#endif // _pw_ring_hashtable_