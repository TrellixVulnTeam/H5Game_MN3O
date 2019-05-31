#ifndef _pw_cpp_sqlite_
#define _pw_cpp_sqlite_

#include "pw_def.h"
#include "sqlite3.h"

namespace sqlite
{

	typedef int (*pfnExecCallback)(void* context,int colnum,char** coldata,char** colname);

	class CppSQLite
	{
	public:
		CppSQLite();
		virtual ~CppSQLite();
	public:
		int Startup(const std::string& dbname);
		int Cleanup();
	public:
		/**
		 * @brief 执行插入/更新/删除等操作
		 * @param sql
		 */
		int ExecuteSQL(const_char_ptr sql,pfnExecCallback pfn = NULL,void* context = NULL);

		/**
		 * @brief 执行批量操作，使用事务处理
		 * @param sql
		 */
		int ExecuteBatchSQL(const_char_ptr sql);
	public:
		sint64 GetLastInsertId();
	private:
		CppSQLite(const CppSQLite& db);
		CppSQLite& operator=(const CppSQLite& db);
	private:
		sqlite3* m_pDB;
		
	};
}

#endif // _pw_cpp_sqlite_
