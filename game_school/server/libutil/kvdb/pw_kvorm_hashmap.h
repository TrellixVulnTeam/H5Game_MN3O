#ifndef _pw_kvorm_map_
#define _pw_kvorm_map_

#include "pw_def.h"
#include <type_traits>

namespace pwutils
{
	extern int64 city_hash(const void* buf,size_t len,int64 seed);

	template<class K,class T> class KvormHashmap : public std_unordered_map<K,T>
	{
	public:
		typedef std_unordered_map<K,T> ContainerType;
		typedef typename ContainerType::const_iterator const_iterator;
	public:
		bool is_default_value() const
		{
			return this->size() == 0;
		}

		void cleanup()
		{
			this->clear();
		}

		bool exists(const std::string& key)
		{
			return ContainerType::find(key) != ContainerType::end();
		}
	public:
		int64 hash_make(int64 seed)
		{
			size_t size = this->size();
			int64 _result = city_hash(&size,sizeof(size_t),seed);
			for(typename ContainerType::iterator iter = ContainerType::begin(); iter != ContainerType::end(); ++iter)
			{
				_result = BsonMakeHash<K>::make(iter->first,_result);
				_result = BsonMakeHash<T>::make(iter->second,_result);
			}
			return _result;
		}
	};

	template<class K,class T> class KvormObjectHashmap : public std_unordered_map<K,T>
	{
	public:
		typedef std_unordered_map<K,T> ContainerType;
		typedef typename ContainerType::const_iterator const_iterator;
	public:
		~KvormObjectHashmap()
		{
			this->cleanup();
		}

		bool is_default_value() const
		{
			return this->size() == 0;
		}
	public:
		void cleanup(bool freeIt = true)
		{
			if(freeIt)
			{
				for(typename ContainerType::iterator iter = ContainerType::begin(); iter != ContainerType::end(); ++iter)
				{
					delete iter->second;
				}
			}
			ContainerType::clear();
		}
	public:
		int64 hash_make(int64 seed)
		{
			size_t size = this->size();
			int64 _result = city_hash(&size,sizeof(size_t),seed);
			for(typename ContainerType::iterator iter = ContainerType::begin(); iter != ContainerType::end(); ++iter)
			{
				_result = BsonMakeHash<K>::make(iter->first,_result);
				_result = iter->second->hash_make(_result);
			}
			return _result;
		}
	};
}

#endif // _pw_kvorm_map_