#ifndef _pw_ordered_vector_
#define _pw_ordered_vector_

#include <vector>
#include <deque>
#include <algorithm>
#include <functional>

namespace pwutils
{
	/**
	 * @class ordered_vector
	 * @author cbh
	 * @date 2011年10月17日
	 * @file pw_ordered_vector.h
	 * @brief 有序数组,可快速查找
	 */
	template<class T,class PRED = std::less<T>,class PRED_EQUAL = std::equal_to<T>,class TCONTAINER = std::vector<T> >
	class ordered_vector : public TCONTAINER
	{
	public:
		typedef typename TCONTAINER::iterator iterator;
		typedef typename TCONTAINER::const_iterator const_iterator;
	public:
		void ordered_push_back(const T& v)
		{
			push_back(v);
			sort();
		}

		void ordered_push_front(const T& v)
		{
			push_front(v);
			sort();
		}

		void sort()
		{
			std::sort(TCONTAINER::begin(),TCONTAINER::end(),PRED());
		}

		iterator find(const T& v)
		{
			PRED_EQUAL equal;
			iterator iter = std::lower_bound(TCONTAINER::begin(),TCONTAINER::end(),v,PRED());
			if(iter != TCONTAINER::end() && equal(*iter,v))
				return iter;
			return TCONTAINER::end();
		}

		template<class K>
		iterator find(const K& v)
		{
			PRED_EQUAL equal;
			iterator iter = std::lower_bound(TCONTAINER::begin(),TCONTAINER::end(),v,PRED());
			if(iter != TCONTAINER::end() && equal(*iter,v))
				return iter;
			return TCONTAINER::end();
		}
	};

	namespace _detail
	{
		template<class K,class V>
		struct less
		{
			bool operator()(const std::pair<K,V>& _Left, const std::pair<K,V>& _Right) const
			{
				return (_Left.first < _Right.first);
			}
		};

		template<class K,class V>
		struct equal_to
		{
			bool operator()(const std::pair<K,V>& _Left, const std::pair<K,V>& _Right) const
			{
				return (_Left.first == _Right.first);
			}
		};
	}

//	template<class T,class V,class PRED = _detail::less<T,V>,class PRED_EQUAL = _detail::equal_to<T,V> >
//	class ordered_vector_map : public ordered_vector<std::pair<T,V> ,PRED,PRED_EQUAL>
//	{
//	public:
//		iterator find(const T& k)
//		{
//			V vv = {0};
//			return ordered_vector<std::pair<T,V> ,PRED,PRED_EQUAL>::find(std::pair<T,V>(k,vv));
//		}
//	};
}

#endif // _pw_ordered_vector_