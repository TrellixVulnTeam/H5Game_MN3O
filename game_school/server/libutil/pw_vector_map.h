#ifndef _pw_vector_map_
#define _pw_vector_map_

#include <vector>
#include <algorithm>

namespace pwutils
{
	template<class K,class V> class vector_map
	{
	public:
		struct SStored
		{
			K first;
			V second;

			bool operator<(const SStored& r) const
			{
				return first < r.first;
			}

			bool operator==(const SStored& r) const
			{
				return first == r.first;
			}
		};
		typedef std::vector<SStored> ContainerType;
		typedef typename ContainerType::iterator iterator;
		typedef typename ContainerType::const_iterator const_iterator;
	public:
		iterator begin() { return m_vObjs.begin(); }
		const_iterator begin() const { return m_vObjs.begin(); }
		iterator end() { return m_vObjs.end(); }
		const_iterator end() const { return m_vObjs.end(); }
		size_t size() { return m_vObjs.size(); }

		iterator find(const K& k)
		{
			for(typename ContainerType::iterator iter = m_vObjs.begin(); iter != m_vObjs.end(); ++iter)
			{
				if(iter->first == k)
					return iter;
			}
			return m_vObjs.end();
		}

		const_iterator find(const K& k) const
		{
			for(typename ContainerType::const_iterator iter = m_vObjs.begin(); iter != m_vObjs.end(); ++iter)
			{
				if(iter->first == k)
					return iter;
			}
			return m_vObjs.end();
		}

		iterator erase(iterator iter)
		{
			return m_vObjs.erase(iter);
		}

		iterator erase(iterator _start,iterator _end)
		{
			return m_vObjs.erase(_start,_end);
		}

		bool insert(const K& k,const V& v)
		{
			if(this->find(k) != this->end())
				return false;
			SStored s;
			s.first = k;
			s.second = v;
			m_vObjs.push_back(s);
			return true;
		}

		void clear()
		{
			m_vObjs.clear();
		}

		void sort()
		{
			std::sort(m_vObjs.begin(),m_vObjs.end());
		}

		iterator lower_bound(const K& k)
		{
			SStored eq;
			eq.first = k;

			return std::lower_bound(begin(),end(),eq);
		}
		const_iterator lower_bound(const K& k) const
		{
			SStored eq;
			eq.first = k;
			return std::lower_bound(begin(),end(),eq);
		}

		iterator upper_bound(const K& k)
		{
			SStored eq;
			eq.first = k;
			return std::upper_bound(begin(),end(),eq);
		}
		const_iterator upper_bound(const K& k) const
		{
			SStored eq;
			eq.first = k;
			return std::upper_bound(begin(),end(),eq);
		}
	private:
		ContainerType m_vObjs;
	};
}

#endif // _pw_vector_map_