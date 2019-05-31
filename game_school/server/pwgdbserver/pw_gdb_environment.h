#ifndef _pw_gdb_environment_
#define _pw_gdb_environment_

#include <vector>
#include <string>
#include "pw_gdb_stdint.h"
#include "pw_orm_user.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "json/json.h"

namespace gdb
{
	class Database;
	class TwoPartComparator;

	class AuthenticationInformation
	{
	public:
		AuthenticationInformation(const orm::User& u);
	public:
		bool CheckSysPermission();
		bool CheckUsrPermission(int64 cmd,Database* db);
	protected:
		orm::User m_mUserInfo;
	};

	class Environment
	{
	public:
		Environment(const std::string& directory,Json::Value& dbconf);
		~Environment();
	public:
		inline leveldb::Env* GetLeveldbEnv()
		{
			return m_pEnv;
		}
	public:
		Database* OpenDatabase(const std::string& name);
		bool CloseDatabase(const std::string& name);
	public:
		Database* CreateDatabase(const std::string& name);
		bool RemoveDatabase(const std::string& name);
		bool RepairDatabase(const std::string& name);
	public:
		leveldb::Status CopyFile(const std::string& src,const std::string& dst,uint64_t size);
		leveldb::Status LinkFile(const std::string& src,const std::string& dst);
		leveldb::Status TouchFile(const std::string& dst);
	public:
		Database* GetDatabase(const std::string& name);
	public:
		void ListDatabases(std::vector<std::string>& list);
	protected:
		void SetupOptions(leveldb::Options& options);
	protected:
		typedef std::vector<Database*> CollectionDatabasesT;
	protected:
		CollectionDatabasesT m_vDatabases;
	protected:
		std::string m_sDirectory;
		TwoPartComparator* m_pComparator;
		Json::Value m_mDefaultOptions;
		leveldb::Env* m_pEnv;
	};

	extern const char* g_szSystemDatabase;
	extern const char* g_szSystemUserTable;
	extern Environment* g_pEnvironment;
}

#endif // _pw_gdb_environment_