#ifndef _pw_kvorm_array_
#define _pw_kvorm_array_

#include <deque>
#include <vector>
#include <string.h>
#include "bson/bson.h"
#include "pw_bsontocpp.h"

namespace pwutils
{
	extern int64 city_hash(const void* buf,size_t len,int64 seed);

	template<class T> class KvormArray : public std::vector<T>
	{
	public:
		typedef std::vector<T> ContainerType;
	public:
		inline bool is_default_value() const
		{
			return this->size() == 0;
		}

		void cleanup()
		{
			ContainerType::clear();
		}
	public:
		void load(const mongo::BSONObj& obj)
		{
			mongo::BSONObjIterator iter(obj);
			while(iter.more())
			{
				T tmp;
				mongo::BSONElement be = iter.next();
				tmp.from_bson(be.Obj());
				this->push_back(tmp);
			}
		}

		bool load(const char* data,size_t size)
		{
			try
			{
				this->cleanup();

				mongo::BSONObj obj(data);
				if(obj.objsize() != size)
					throw 1;

				this->load(obj);
			}
			catch(...)
			{
				return false;
			}
			return true;
		}

		void save(mongo::BSONObj& obj)
		{
			mongo::BSONArrayBuilder builder;
			for(size_t i = 0; i < ContainerType::size(); ++i)
			{
				T& tmp = ContainerType::at(i);
				mongo::BSONObj tmpobj;
				tmp.to_bson(tmpobj);
				builder.append(tmpobj);
			}
			obj = builder.obj();
		}

		void save(std::string& result)
		{
			mongo::BSONObj bsonobj;
			this->save(bsonobj);
			result.clear();
			result.append(bsonobj.objdata(),bsonobj.objsize());
		}
	public:
		int64 hash_make(int64 seed)
		{
			size_t size = ContainerType::size();
			int64 _result = city_hash(&size,sizeof(size_t),seed);
			for(size_t i = 0; i < size; ++i)
			{
				_result = city_hash(&i,sizeof(size_t),_result);
				_result = BsonMakeHash<T>::make(ContainerType::at(i),_result);
			}
			return _result;
		}
	public:
		void loadBuiltType(const char* data,size_t size)
		{
			this->cleanup();
			this->loadBuiltType(mongo::BSONObj(data));
		}

		void loadBuiltType(const mongo::BSONObj& obj)
		{
			mongo::BSONObjIterator iter(obj);
			while(iter.more())
			{
				T tmp;
				mongo::BSONElement be = iter.next();
				pwutils::bsonToCppVariable(tmp,be);
				this->push_back(tmp);
			}
		}

		void saveBuiltType(mongo::BSONObj& obj)
		{
			mongo::BSONArrayBuilder builder;
			for(size_t i = 0; i < ContainerType::size(); ++i)
			{
				T& tmp = ContainerType::at(i);
				builder.append(tmp);
			}
			obj = builder.obj();
		}
	};
	
	// ---------------------------------------------------------------------------------

	template<class T> class KvormObjectArray : public std::vector<T>
	{
		template<class U> struct ExtractValueType
		{
			typedef U result_type;
		};
		template<class U> struct ExtractValueType<U*>
		{
			typedef U result_type;
		};
	public:
		typedef std::vector<T> ContainerType;
		typedef typename std::vector<T>::const_iterator const_iterator;
	public:
		~KvormObjectArray()
		{
			this->cleanup();
		}

		inline bool is_default_value() const
		{
			return this->size() == 0;
		}
	public:
		void cleanup(bool freeIt = true)
		{
			if(freeIt)
			{
				for(typename ContainerType::iterator iter = ContainerType::begin(); iter != ContainerType::end(); ++iter)
					delete (*iter);
			}
			ContainerType::clear();
		}

		bool remove(T value,bool freeIt)
		{
			typename ContainerType::iterator iter = std::remove(ContainerType::begin(),ContainerType::end(),value);
			if(iter == ContainerType::end())
				return false;

			if(freeIt)
				delete value;
			ContainerType::erase(iter,ContainerType::end());
			return true;
		}
	public:
		void load(const char* data,size_t size)
		{
			this->cleanup();
			this->load(mongo::BSONObj(data,size));
		}

		void load(const mongo::BSONObj& obj)
		{
			mongo::BSONObjIterator iter(obj);
			while(iter.more())
			{
				T tmp = new typename ExtractValueType<T>::result_type();
				mongo::BSONElement be = iter.next();
				tmp->from_bson(be.Obj());
				this->push_back(tmp);
			}
		}

		void save(mongo::BSONObj& obj)
		{
			mongo::BSONArrayBuilder builder;
			for(size_t i = 0; i < ContainerType::size(); ++i)
			{
				T tmp = ContainerType::at(i);
				mongo::BSONObj tmpobj;
				tmp->to_bson(tmpobj);
				builder.append(tmpobj);
			}
			obj = builder.obj();
		}
	public:
		int64 hash_make(int64 seed)
		{
			size_t size = ContainerType::size();
			int64 _result = city_hash(&size,sizeof(size_t),seed);
			for(size_t i = 0; i < size; ++i)
			{
				_result = city_hash(&i,sizeof(size_t),_result);

				if(T v = ContainerType::at(i))
					_result = v->hash_make(_result);
			}
			return _result;
		}
	};

	// ---------------------------------------------------------------------------------

/*
	template<class T,unsigned N> class KvormStaticObjectArray
	{
	public:
		inline bool is_default_value()
		{
			for(size_t i = 0; i < N; ++i)
				if(m_pValues[i] != 0)
					return false;
			return true;
		}

		KvormStaticObjectArray()
		{
			memset(m_pValues,0,sizeof(m_pValues));
		}

		~KvormStaticObjectArray()
		{
			this->cleanup();
		}

		void cleanup(bool freeIt = true)
		{
			if(!freeIt)
			{
				memset(m_pValues,0,sizeof(m_pValues));
				return ;
			}

			for(size_t i = 0; i < N; ++i)
			{
				if(m_pValues[i] != NULL)
				{
					delete m_pValues[i];
					m_pValues[i] = NULL;
				}
			}
		}

		inline size_t size()
		{
			return N;
		}

		inline const T& at(size_t i)
		{
			return m_pValues[i];
		}

		inline void set(size_t i,T v)
		{
			if(i < N)
			{
				if(m_pValues[i] == v)
					return ;

				if(m_pValues[i] != 0)
					delete m_pValues[i];
				
				m_pValues[i] = v;

			}
		}
	protected:
		T m_pValues[N];
	};

*/

	// ---------------------------------------------------------------------------------
}

#endif // _pw_kvorm_array_