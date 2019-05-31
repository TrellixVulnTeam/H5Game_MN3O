#ifndef _cpp_mysql_primary_keys_
#define _cpp_mysql_primary_keys_

#include "pw_def.h"
#include "CppMysql.h"
#include "CppMysql_Recordset.h"
#include "pw_sync.h"
#include "pw_mem_stream.h"

namespace mysql
{
	const int max_primary_keys = 10;

	class PrimaryKeys
	{
	public:
		int Initial(mysql::Connection& db,const char* table);
		int Initial(mysql::RecordsetPtr& recordset);
	public:
		size_t Bytes();
	public:
		int Load(pwutils::MemStream& s);
		int Save(pwutils::MemStream& s);
	public:
		unsigned long mPrimaryKeys[max_primary_keys];
		unsigned long cPrimaryKeys;
	};


	class PrimaryKeysSet
	{
	public:
		int Initial(mysql::Connection& db);
		int Initial(mysql::Connection& db,const_char_ptr table);
	public:		
		void Add(const std::string& name,mysql::PrimaryKeys& keys)
		{
			CollectionPrimaryKeysT::accessor a;
			mPrimaryKeys.insert(a,std::make_pair(name,keys));
		}

		void Del(const std::string& name)
		{
			mPrimaryKeys.erase(name);
		}

		mysql::PrimaryKeys* Get(const std::string& name)
		{
			CollectionPrimaryKeysT::accessor a;
			mysql::PrimaryKeys* result = nullptr;
			if(mPrimaryKeys.find(a,name))
				result = &a->second;
			return result;
		}
	private:
		typedef tbb::concurrent_hash_map<std::string,mysql::PrimaryKeys> CollectionPrimaryKeysT;
	private:
		CollectionPrimaryKeysT mPrimaryKeys;
	};

}

typedef pwutils::Singleton<mysql::PrimaryKeysSet,pwutils::ThreadMutex> mysql_PrimaryKeys;


#endif //_cpp_mysql_primary_keys_
