#include "pw_gdb_operation.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_database.h"
#include "pw_gdb_client_script.h"
#include <new>

namespace gdb
{
	const char* g_szErrorString[ERROR_NUM] = 
	{
		"ERROR_OK",
		"ERROR_NOFOUND",
		"ERROR_CORRUPTION",
		"ERROR_NOTSUPPORTED",
		"ERROR_INVALIDARGUMENT",
		"ERROR_IOERROR",
		"__INVALID_ERROR_6",
		"__INVALID_ERROR_7",
		"__INVALID_ERROR_8",
		"__INVALID_ERROR_9",

		"ERROR_EXISTS",
		"ERROR_EXISTS_INVALID_DATA",
	};

	static ClientScriptNull g_objClientScriptNull;

	void OperationResult::SetErrorCode( const leveldb::Status& status,size_t line )
	{
		if(status.ok())
			errorcode = ERROR_OK;
		else if(status.IsIOError())
			errorcode = ERROR_IOERROR;
		else if(status.IsCorruption())
			errorcode = ERROR_CORRUPTION;
		else if(status.IsNotFound())
			errorcode = ERROR_NOFOUND;
		else
			errorcode = ERROR_INVALIDARGUMENT;
		lineno = line;
	}

	void OperationResult::SetErrorCode( ErrorCode code,size_t line /*= 0*/ )
	{
		errorcode = code;
		lineno = line;
	}
	
	OperationResult::OperationResult()
		 : lineno(0)
		 , errorcode(0)
		 , m_pOplog(0)
	{

	}

	OperationResult::~OperationResult()
	{
		if(m_pOplog != 0)
			delete m_pOplog;
		m_pOplog = 0;
	}

	Oplog* OperationResult::MutableOplog()
	{
		if(m_pOplog == 0)
		{
			m_pOplog = new Oplog();
		}
		return m_pOplog;
	}

	const char* OperationResult::GetErrorString()
	{
		return g_szErrorString[errorcode];
	}

	int64 OperationResult::GetErrorCode()
	{
		return this->errorcode;
	}

	int TwoPartComparator::Compare( const leveldb::Slice& a, const leveldb::Slice& b ) const
	{
		const char* abuf = a.data();
		const char* bbuf = b.data();

		// ZSCORE 解析出score并比较,相等则不继续向下
		if(abuf[0] == SO_PREFIX && bbuf[0] == SO_PREFIX && abuf[1] == bbuf[1])
		{
			const char* asp = strchr(abuf,SEPARATOR2);
			const char* bsp = strchr(bbuf,SEPARATOR2);
			
			assert(asp != NULL && bsp != NULL);

			size_t apos = asp - abuf;
			size_t bpos = bsp - bbuf;

			if(apos == bpos && memcmp(abuf,bbuf,apos) == 0)
			{				
				int64 aval = *reinterpret_cast<const int64*>(&asp[1]);
				int64 bval = *reinterpret_cast<const int64*>(&bsp[1]);
				const char* akey = &asp[1] + sizeof(int64) + 1;
				const char* bkey = &bsp[1] + sizeof(int64) + 1;

				int32 result = 0;

				if(aval == bval)
				{
					Slice akeybuf(akey,abuf + a.size() - akey);
					Slice bkeybuf(bkey,bbuf + b.size() - bkey);
					result = m_pBaseComparator->Compare(akeybuf,bkeybuf);
				}
				else
				{
					result = aval > bval ? 1 : -1;
				}

				if(abuf[1] == SEPARATOR1_R)
					return result * -1;
				return result;
			}
		}
		
		return m_pBaseComparator->Compare(a,b);
	}

	TwoPartComparator::TwoPartComparator()
	{
		m_pBaseComparator = leveldb::BytewiseComparator();
	}


	OperationEnvironment::OperationEnvironment( Database* _db,ClientScript* _clientScript )
		: db(_db->GetLevelDB())
		, database(_db)
		, client_script(_clientScript)
	{
		if(client_script == 0)
			client_script = &g_objClientScriptNull;
	}

}