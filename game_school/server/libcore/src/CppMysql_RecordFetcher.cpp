#include "CppMysql_RecordFetcher.h"
#include "CppMysql_RecordsetEx.h"

namespace mysql
{
	RecordFecher::RecordFecher( pfnFetchCallback pfn,void* context )
		: m_pfnFetch(pfn)
		, m_pContext(context)
		, m_pRES(NULL)
	{

	}

	RecordFecher::~RecordFecher()
	{
		mysql_free_result(m_pRES);
		m_pRES = NULL;
	}

	int RecordFecher::Initial( MYSQL_RES* res )
	{
		m_pRES = res;

		MYSQL_FIELD* fields = ::mysql_fetch_field(m_pRES);
		unsigned int fieldcount = ::mysql_num_fields(m_pRES);

		m_pFields.reset(new RecordFields);
		if(m_pFields->Initial(fields,fieldcount) != 0)
			return -1;

		return 0;
	}

	uint64 RecordFecher::GetRecordCount()
	{
		return ::mysql_num_rows(m_pRES);
	}

	int RecordFecher::FetchAll()
	{
		uint64 count = ::mysql_num_rows(m_pRES);
		for(uint64 i = 0; i < count; ++i)
		{
			RecordObjectEx record(m_pFields.get());
			this->FetchOne(record);
		}
		return 0;
	}

	int RecordFecher::FetchOne(RecordObjectEx& record)
	{
		MYSQL_ROW row = mysql_fetch_row(m_pRES);
		unsigned long* lengths = mysql_fetch_lengths(m_pRES);

		record.InitialFrom(row,lengths);

		if(m_pfnFetch != NULL)
		{
			m_pfnFetch(record,m_pContext);
		}
		return 0;
	}

}


