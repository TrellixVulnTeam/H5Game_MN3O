#include "pw_cpp_sqlite.h"
#include "pw_logger.h"

namespace sqlite
{

	CppSQLite::CppSQLite()
		: m_pDB(NULL)
	{
	}

	CppSQLite::~CppSQLite()
	{
		Cleanup();
	}
	
	int CppSQLite::Startup(const std::string& dbname)
	{
		int result = sqlite3_open(dbname.c_str(),&m_pDB);
		if(result != SQLITE_OK)
		{
			pwreportvars(false,"sqlite3_open failed, result=" << result);
			return -1;		
		}
		return 0;
	}

	int CppSQLite::Cleanup()
	{
		if(m_pDB)
		{
			sqlite3_close(m_pDB);
			m_pDB = NULL;
		}
		return 0;
	}

	int CppSQLite::ExecuteSQL(const_char_ptr sql,pfnExecCallback pfn /* = NULL */,void* context /* = NULL */)
	{
		char* errmsg = NULL;
		int result = sqlite3_exec(m_pDB,sql,pfn,context,&errmsg);
		if(result != SQLITE_OK)
		{
			pwreportvars(false,"sqlite3_exec failed, sql=" << sql << ", errmsg=" << errmsg);
			sqlite3_free(errmsg);
			return -1;
		}
		return sqlite3_changes(m_pDB);
	}

	int CppSQLite::ExecuteBatchSQL(const_char_ptr sql)
	{
		pwassertf(this->ExecuteSQL("begin;") >= 0);

		int result = this->ExecuteSQL(sql);
		if(result < 0)
		{
			this->ExecuteSQL("rollback;");
			return -1;
		}

		pwassertf(this->ExecuteSQL("commit;") >= 0);
		return result;
	}

	sint64 CppSQLite::GetLastInsertId()
	{
		return sqlite3_last_insert_rowid(m_pDB);
	}
}
