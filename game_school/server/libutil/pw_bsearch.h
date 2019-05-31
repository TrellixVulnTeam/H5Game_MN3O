#ifndef _pw_bsearch_
#define _pw_bsearch_

namespace pwutils
{
	template<class T1, class T2,class RandomIter>
	int BinarySearch(RandomIter begin, 
					 RandomIter end, 
					 const T2& key,
					 int (*compare)(const T1&, const T2&, void* param), 
					 void *param)
	{
		int length = (int)(end - begin);
		if( length <= 0)
			return -1;

		int indexRet = -1;
		int mid = length / 2;
		int cmp = compare(*(begin+mid), key, param);

		if (cmp == 0)
		{
			indexRet = mid;
		}
		else if (length != 1)
		{
			if (cmp < 0 && length != 1)
			{
				//中间元素小于 key，表示元素在右边
				indexRet = BinarySearch<T1,T2,RandomIter>(begin + mid, end, key, compare, param);
				if (indexRet != -1)
				{
					indexRet += mid;
				}
			}
			else 
			{
				indexRet = BinarySearch<T1,T2,RandomIter>(begin, begin+mid, key, compare, param);
			}
		}

		return indexRet;
	}

	template<class T1, class T2,class RandomIter>
	int BinarySearchNearest(RandomIter begin, 
		RandomIter end, 
		const T2& key,
		int (*compare)(const T1&, const T2&, void* param), 
		void *param,
		int& nearest)
	{
		int length = (int)(end - begin);
		if( length <= 0)
			return -1;

		int indexRet = -1;
		int mid = length / 2;
		int cmp = compare(*(begin+mid), key, param);

		if (cmp == 0)
		{
			nearest = mid;
			indexRet = mid;
		}
		else if (length != 1)
		{
			if (cmp < 0 && length != 1)
			{
				//中间元素小于 key，表示元素在右边
				indexRet = BinarySearchNearest<T1,T2,RandomIter>(begin + mid, end, key, compare, param,nearest);
				if (indexRet != -1)
				{
					indexRet += mid;
				}
				nearest += mid;
			}
			else 
			{
				indexRet = BinarySearchNearest<T1,T2,RandomIter>(begin, begin+mid, key, compare, param,nearest);
			}
		}
		else
		{
			if(cmp == -1)
				nearest = 1;
			else
				nearest = 0;
		}

		return indexRet;
	}

	template<class T> int CompareFunc(const T& v1,const T& v2)
	{
		if(v1 == v2)
			return 0;
		if(v1 > v2)
			return 1;
		return -1;
	}

}



#endif // _pw_bsearch_