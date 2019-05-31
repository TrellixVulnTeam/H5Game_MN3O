#ifndef _cpp_mysql_
#define _cpp_mysql_

#include "pw_def.h"
#include "pw_platform.h"
#include <string>
#include <mysql/mysql.h>
#include <memory>
#include "pw_refcounted.h"

namespace mysql
{

	class Recordset;
	class RecordsetEx;
	class RecordObjectEx;
	class RecordFecher;
	
	typedef pwutils::RefcountedPtr<Recordset> RecordsetPtr;
	typedef pwutils::RefcountedPtr<RecordsetEx> RecordsetExPtr;
	typedef pwutils::RefcountedPtr<RecordObjectEx> RecordObjectExPtr;

// ----------------------------------------------------------------------

	class Connection
	{
	public:
		Connection();
		virtual ~Connection();
	public:
		int Startup(const char* host,const char* user,const char* pswd,const char* db,int port = 3306);
		int Cleanup();
	public:
		int CleanupResults();
		int Update();
		int IsConnected();
	public:
		sint64 ExecuteSQL(const char* sql);
		sint64 ExecuteSQL(const char* sql,RecordsetPtr& recordset);
		sint64 ExecuteSQL(const char* sql,RecordsetExPtr& recordset);
		sint64 ExecuteSQL(const char* sql,RecordObjectEx& record);
		sint64 ExecuteFetcher(const char* sql,RecordFecher& fethcer);
	public:
		unsigned long RealEscapeString(char* to,const char* from,unsigned long fromLen);
	public:
		sint64 GetLastInsertId();
	protected:
		int LogError(const char* sql);
	protected:
		MYSQL mMysql;
	};

// ----------------------------------------------------------------------

	struct Buffer
	{
		char_ptr buf;
		unsigned long len;

		Buffer(char* _buf = 0,unsigned long _len = 0)
		{
			buf = _buf;
			len = _len;
		}
	};

// ----------------------------------------------------------------------

#define GET_BYNAME_IMPL \
	sint32 GetI32(const std::string& field) { return GetI32(GetFieldIndex(field.c_str())); }\
	sint64 GetI64(const std::string& field){return GetI64(GetFieldIndex(field.c_str()));}\
	const_char_ptr GetStr(const std::string& field){return GetStr(GetFieldIndex(field.c_str()));}\
	Buffer GetBuf(const std::string& field){return GetBuf(GetFieldIndex(field.c_str()));}\
	double GetDec(const std::string& field){return GetDec(GetFieldIndex(field.c_str()));}

#define SET_BYNAME_IMPL \
	void SetI32(const std::string& field,sint32 val){SetI32(GetFieldIndex(field.c_str()),val);}\
	void SetI64(const std::string& field,sint64 val){SetI64(GetFieldIndex(field.c_str()),val);}\
	void SetStr(const std::string& field,const_char_ptr val){SetStr(GetFieldIndex(field.c_str()),val);}\
	void SetBuf(const std::string& field,Buffer val){SetBuf(GetFieldIndex(field.c_str()),val);}\
	void SetDec(const std::string& field,double val){SetDec(GetFieldIndex(field.c_str()),val);}

// ----------------------------------------------------------------------


}

#endif //_cpp_mysql_
