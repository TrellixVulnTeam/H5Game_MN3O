#ifndef _pwdist_ordered_array_
#define _pwdist_ordered_array_


#include "pwdist_def.h"

namespace pwdist
{
	template<class T,class PRED = std::less<T>,int LEN = 100> class OrderedArray
	{
	public:
		typedef T* iterator;
	public:
		OrderedArray()
			: m_cObjects(0)
		{			
		}

		inline void clear()
		{
			m_cObjects = 0;
		}

		inline T& at(int32 i)
		{
			return m_pObjects[i];
		}

		inline void push_back(const T& v)
		{
			assert((m_cObjects + 1) < LEN);
			
			m_pObjects[m_cObjects] = v;
			++ m_cObjects;
		}

		inline T* find(const T& v)
		{
			T* result = std::lower_bound(begin(),end(),PRED());
			if(result == end())
				return NULL;
			return result;
		}

		inline size_t num()
		{
			return m_cObjects;
		}

		inline void sort()
		{
			std::sort(begin(),end(),PRED());
		}

		inline size_t erase(T* start)
		{
			if(start == end() || start < begin())
				return 0;
			size_t n = (start - begin()) / sizeof(T);
			m_cObjects -= n;
			return n;
		}
	public:
		inline T* begin()
		{
			return m_pObjects;
		}

		inline T* end()
		{
			return m_pObjects + m_cObjects;
		}
	private:
		T m_pObjects[LEN];
		size_t m_cObjects;
	};
}

#endif // _pwdist_ordered_array_