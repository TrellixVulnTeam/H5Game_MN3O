#ifndef _cpp_mysql_recordset_ex_
#define _cpp_mysql_recordset_ex_

#include "CppMysql.h"
#include "CppMysql_PrimaryKeys.h"
#include "pw_memory.h"
#include "pw_mem_stream.h"

namespace mysql
{

	class RecordsetEx;

	// --------------------------------------------------------------------

	const int max_field_count = 512;
	
	// --------------------------------------------------------------------

	class RecordField
	{
	public:
		enum { I32 = 0,I64,DEC,BUF,FIXED_STR };
		enum { NON,MOD,NEW,DEL,REP, };
	public:
		static uint GetStoreLen(uint type,uint dblen);
		static uint GetRelativeType(uint type);
	public:
		pwutils::MemStream& Load(pwutils::MemStream& s);
		pwutils::MemStream& Save(pwutils::MemStream& s);
	public:
		size_t ByteSize();
	public:
		uint m_nType;
		uint m_uRelativeType;
		uint m_nStoreLen;
		std::string m_strName;
		uint m_uOffset;
		uint m_nFlags;
	};

	// --------------------------------------------------------------------

	class RecordFields : public std::vector<RecordField>,public pwutils::memory::Object<RecordFields,true>
	{
	public:
		int Initial(MYSQL_FIELD* fields,unsigned int count);
		int	Initial(const char* defs);
	public:
		pwutils::MemStream& Load(pwutils::MemStream& s);
		pwutils::MemStream& Save(pwutils::MemStream& s);
	public:
		size_t ByteSize();
	public:
		uint GetStoreLen();
	private:
		uint m_nStoreLen;
	};

	// --------------------------------------------------------------------

	class RecordObjectEx : public pwutils::Refcounted<true>,public pwutils::memory::Object<RecordObjectEx,true>
	{
	public:
		RecordObjectEx(RecordFields* fields);
		RecordObjectEx(RecordFields* fields,MYSQL_ROW row,unsigned long* lengths);
		~RecordObjectEx();
	public:
		int InitialFrom(MYSQL_ROW row,unsigned long* lengths);
	public:
		int Sync(mysql::Connection* conn,const std::string& table,PrimaryKeys* keys);
		int MakeSyncSql(mysql::Connection* conn,const std::string& table,PrimaryKeys* keys,std::string& sql);
	public:
		GET_BYNAME_IMPL;
		SET_BYNAME_IMPL;
	public:
		sint32 GetI32(uint field);
		sint64 GetI64(uint field);
		const_char_ptr GetStr(uint field);
		Buffer GetBuf(uint field);
		double GetDec(uint field);
		void   GetAsStr(uint field,char* buf,size_t len);
	public:
		void SetI32(uint field,sint32 val);
		void SetI64(uint field,sint64 val);
		void SetStr(uint field,const_char_ptr val);
		void SetBuf(uint field,Buffer val);
		void SetDec(uint field,double val);
	public:
		void SetBuf(uint field,RecordObjectEx& record);
		bool GetBuf(uint field,RecordObjectEx& record);
	public:
		bool IsNew();
		bool IsModified();
	public:
		bool GenerateUpdateSql(Connection* conn,const std::string& table,std::string& sql,mysql::PrimaryKeys* keys);
		void CleanupRecordStatus();
		void CleanupRecordStatus(int field);
		void CommitChanges();
	public:
		pwutils::MemStream& Patch(pwutils::MemStream& s);
		pwutils::MemStream& GenPatch(pwutils::MemStream& s);
	public:
		pwutils::MemStream& Load(pwutils::MemStream& s);
		pwutils::MemStream& Save(pwutils::MemStream& s);
	public:
		size_t ByteSize();
	public:
		unsigned int GetFieldIndex(const_char_ptr name);
		const std::string& GetFieldName(uint field);
		RecordFields* GetFields();
		void SetFields(RecordFields* fields);
	private:
		bool GenerateSQL_Insert(Connection* conn,const std::string& table,std::string& sql);
		bool GenerateSQL_Replace(Connection* conn,const std::string& table,std::string& sql);
		bool GenerateSQL_Delete(Connection* conn,const std::string& table,mysql::PrimaryKeys* keys,std::string& sql);
		bool GenerateSQL_Update(Connection* conn,const std::string& table,mysql::PrimaryKeys* keys,std::string& sql);
		void GenerateSQL_Value(Connection* conn,unsigned long field,std::string& value);
	public:
		char GetRecordStatu();
		void SetRecordStatu(uint statu);
	private:
		int Initial();
		int Initial(MYSQL_ROW row,unsigned long* lengths);
		int Cleanup();
	private:
		char_ptr GetFieldPtr(RecordField& field);
	public:
		void SetFieldStatus(uint field,uint status);
	private:
		RecordFields* m_pFields;
		char_ptr m_pRecordBuf;
		char m_cRecordStatu;
		char m_szRecordStatus[max_field_count];
		//unsigned char mRecordVersion[max_field_count];
	};

	// --------------------------------------------------------------------

	class RecordsetEx : public std::vector<RecordObjectEx*>,public pwutils::Refcounted<true>,public pwutils::memory::Object<RecordsetEx,true>
	{
		friend class RecordObjectEx;
	public:
		RecordsetEx();
		RecordsetEx(RecordFields* fields);
		RecordsetEx(Connection& conn,MYSQL_RES* result);
		~RecordsetEx();
	protected:
		int Initial(Connection& conn,MYSQL_RES* result);
		int Cleanup();
	public:
		RecordObjectEx* CreateObject();
		RecordObjectEx* GetObject(size_t i);
		RecordObjectEx* DetachObject(size_t i);
		RecordFields* GetFields();
	public:
		inline const char* GetDefaultTable()
		{
			return m_pDefaultTable;
		}

		void SetDefaultTable(const char* v);
	public:
		int DeleteObject(size_t i);
	public:
		void CommitChanges();
	public:
		pwutils::MemStream& Load(pwutils::MemStream& s);
		pwutils::MemStream& Save(pwutils::MemStream& s);
	public:
		size_t ByteSize();
	public:
		unsigned int GetFieldCount();
		unsigned int GetFieldIndex(const_char_ptr name);
	public:
		int GenerateUpdateSql(Connection* conn,const std::string& table,std::vector<std::string>& sqls,mysql::PrimaryKeys* keys);
	private:
		const std::string& GetFieldName(uint field);
	private:
		std::auto_ptr<RecordFields> m_pFields;
		std::vector<RecordObjectEx*> m_vtDeletedObjs;
		char* m_pDefaultTable;
	};
}

#endif //_cpp_mysql_recordset