#include "pw_gdb_database_dumpthread.h"
#include "pw_gdb_database.h"

namespace gdb
{
	DatabaseDumpThread::DatabaseDumpThread( Database* src,Database* dst )
		: m_pSrcDB(src)
		, m_pDstDB(dst)
	{
		m_pSrcSnapshot = src->GetLevelDB()->GetSnapshot();
	}

	void DatabaseDumpThread::Run()
	{
		leveldb::DB* srcdb = m_pSrcDB->GetLevelDB();
		assert(srcdb);

		leveldb::DB* dstdb = m_pDstDB->GetLevelDB();
		assert(dstdb);

		leveldb::ReadOptions options;
		options.snapshot = m_pSrcSnapshot;
		options.fill_cache = false;

		leveldb::WriteOptions woptions;

		leveldb::Iterator* iter = srcdb->NewIterator(options);
		iter->SeekToFirst();

		while(iter->Valid() && !this->m_bClosed)
		{
			dstdb->Put(woptions,iter->key(),iter->value());
			iter->Next();
		}
		delete iter;

		srcdb->ReleaseSnapshot(m_pSrcSnapshot);

		this->m_pSrcSnapshot = 0;
		this->m_bClosed = true;

//		m_pSrcDB->OnDumpFinished(m_pDstDB);
	}

	void DatabaseDumpThread::OnThreadStopped()
	{
		gdb::Thread::OnThreadStopped();

		delete this;
	}

}