#ifndef _pw_gdb_database_dumpthread_
#define _pw_gdb_database_dumpthread_

#include "pw_gdb_thread.h"
#include "leveldb/db.h"

namespace gdb
{
	class Database;

	class DatabaseDumpThread : public gdb::Thread
	{
	public:
		DatabaseDumpThread(Database* src,Database* dst);
	public:
		inline bool IsFinished()
		{
			return m_bClosed;
		}
	protected:
		virtual void Run();
		virtual void OnThreadStopped();
	protected:
		Database* m_pSrcDB;
		Database* m_pDstDB;
	protected:
		const leveldb::Snapshot* m_pSrcSnapshot;
	};
}

#endif // _pw_gdb_database_dumpthread_