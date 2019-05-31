#ifndef _CppMysql_RecordFetcher_
#define _CppMysql_RecordFetcher_

#include "CppMysql.h"

namespace mysql
{
	class RecordObjectEx;
	class RecordFields;

	typedef void (*pfnFetchCallback)(RecordObjectEx& record,void* context);

	class RecordFecher
	{
	public:
		RecordFecher(pfnFetchCallback pfn,void* context);
		~RecordFecher();
	public:
		int Initial(MYSQL_RES* res);
	public:
		uint64 GetRecordCount();
	public:
		int FetchAll();
		int FetchOne(RecordObjectEx& record);
	public:
		inline RecordFields* GetFields()
		{
			return m_pFields.get();
		}
	private:
		std::auto_ptr<RecordFields> m_pFields;
		pfnFetchCallback m_pfnFetch;
		void* m_pContext;
	private:
		MYSQL_RES* m_pRES;
	};
}

#endif // _CppMysql_RecordFetcher_