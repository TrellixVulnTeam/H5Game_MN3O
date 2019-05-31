#ifndef _cpp_mysql_recordset_
#define _cpp_mysql_recordset_

#include "CppMysql.h"
#include "pw_memory.h"

namespace mysql
{
	class Recordset;

// ---------------------------------------------------------------------------

	class RecordObject : public pwutils::memory::Object<RecordObject,true>
	{
	public:
		RecordObject();
	public:
		int Initial(Recordset* recordset,MYSQL_ROW row,unsigned long* lengths);
	public:
		GET_BYNAME_IMPL;
	public:
		sint32 GetI32(uint field);
		sint64 GetI64(uint field);
		const_char_ptr GetStr(uint field);
		Buffer GetBuf(uint field);
		double GetDec(uint field);
	public:
		unsigned int GetFieldIndex(const_char_ptr name);
	private:
		MYSQL_ROW mRecord;
		unsigned long* mLengths;
		Recordset* mRecordset;
	};

// ---------------------------------------------------------------------------

	class Recordset : public std::vector<RecordObject*>,public pwutils::Refcounted<true>,public pwutils::memory::Object<Recordset,true>
	{
	public:
		Recordset(Connection& conn,MYSQL_RES* result);
		~Recordset();
	protected:
		int Initial(Connection& conn,MYSQL_RES* result);
		int Cleanup();
	public:
		RecordObject* GetObject(size_t i);
	public:
		unsigned int GetFieldCount();
		unsigned int GetFieldIndex(const_char_ptr name);
	private:
		MYSQL_RES* mStoredResult;
		MYSQL_FIELD* m_pFields;
	};
}

#endif //_cpp_mysql_recordset_
