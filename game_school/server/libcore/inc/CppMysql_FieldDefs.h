#ifndef _cpp_mysql_field_defs_
#define _cpp_mysql_field_defs_

#include "pw_def.h"
#include "CppMysql_RecordsetEx.h"
#include "pw_sync.h"

namespace mysql
{
	class FieldDefs
	{
	public:
		~FieldDefs()
		{
			Cleanup();
		}
	public:
		void Cleanup()
		{
			for(CollectionFieldDefsT::iterator iter = mFieldDefs.begin(); iter != mFieldDefs.end(); ++iter)
				delete iter->second;
			mFieldDefs.clear();
		}
	public:
		void Add(const std::string& name,mysql::RecordFields& fields)
		{
			pwutils::ThreadMutexGuard<pwutils::ThreadMutex> g(mLock);

			mFieldDefs.insert(std::make_pair(name,new mysql::RecordFields(fields)));
		}

		void Del(const std::string& name)
		{
			pwutils::ThreadMutexGuard<pwutils::ThreadMutex> g(mLock);

			mysql::RecordFields* result = Get(name);

			mFieldDefs.erase(name);

			if(result != nullptr)
				delete result;
		}

		mysql::RecordFields* Get(const std::string& name)
		{
			pwutils::ThreadMutexGuard<pwutils::ThreadMutex> g(mLock);

			CollectionFieldDefsT::iterator iter = mFieldDefs.find(name);
			if(iter == mFieldDefs.end())
				return NULL;
			return iter->second;
		}
	private:
		typedef std::map<std::string,mysql::RecordFields*> CollectionFieldDefsT;
	private:
		pwutils::ThreadMutex mLock;
		CollectionFieldDefsT mFieldDefs;
	};
	/*
	class FieldDefs
		{
		public:
			~FieldDefs()
			{
				Cleanup();
			}
		public:
			void Cleanup()
			{
				for(CollectionFieldDefsT::iterator iter = mFieldDefs.begin(); iter != mFieldDefs.end(); ++iter)
					delete iter->second;
				mFieldDefs.clear();
			}
		public:
			void Add(const std::string& name,mysql::RecordFields& fields)
			{
				CollectionFieldDefsT::accessor a;
				mFieldDefs.insert(a,std::make_pair(name,new mysql::RecordFields(fields)));
			}
	
			void Del(const std::string& name)
			{
				mysql::RecordFields* result = Get(name);
	
				mFieldDefs.erase(name);
	
				if(result != nullptr)
					delete result;
			}
	
			mysql::RecordFields* Get(const std::string& name)
			{
				CollectionFieldDefsT::accessor a;
				mysql::RecordFields* result = nullptr;
				if(mFieldDefs.find(a,name))
					result = a->second;
				return result;
			}
		private:
			typedef tbb::concurrent_hash_map<std::string,mysql::RecordFields*> CollectionFieldDefsT;
		private:
			CollectionFieldDefsT mFieldDefs;
		};*/
	
}

typedef pwutils::Singleton<mysql::FieldDefs,pwutils::ThreadMutex> mysql_FieldDefs;

#endif //_cpp_mysql_field_defs_
