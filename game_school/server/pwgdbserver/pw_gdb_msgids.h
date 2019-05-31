#ifndef _pw_gdb_msgids_
#define _pw_gdb_msgids_

#include "pw_functional.h"
#include "pw_gdb_messaged_thread.h"
#include "pw_gdb_memory.h"

namespace gdb
{
	enum
	{
		MSGID_POST_DUMP_FINISHED = 100,
		MSGID_POST_DATABASE_REMOVED,

		MSGID_PUSH_OPLOG_TO_MASTER,

		MSGID_CREATE_DUMP = 200,
		MSGID_CREATE_DUMP_FINISHED,

		MSGID_BACKUP_DATABASE = 300,
	};

	struct SChunk;

	class DatabaseBackup;
	class MasterConnection;

	namespace thread_message
	{
		typedef pwutils::function0<void> CallbackT_0;

		struct PostDumpFinished : public ThreadMessage
		{
			PostDumpFinished()
			{
				this->mid = MSGID_POST_DUMP_FINISHED;
			}

			CallbackT_0 callback;
		};

		struct PostDatabaseRemoved : public ThreadMessage
		{
			PostDatabaseRemoved()
			{
				this->mid = MSGID_POST_DATABASE_REMOVED;
			}
			std::string dbname;
		};

		struct PushOplogToMaster : public ThreadMessage
		{
			PushOplogToMaster()
			{
				this->mid = MSGID_PUSH_OPLOG_TO_MASTER;
			}

			std::string dbname;
			SChunk* oplog_chunk;
		};

		struct CreateDump : public ThreadMessage
		{
			CreateDump()
			{
				this->mid = MSGID_CREATE_DUMP;
				this->connection = NULL;
			}
			std::string dbname;
			MasterConnection* connection;
		};

		struct CreateDumpFinished : public ThreadMessage
		{
			CreateDumpFinished()
			{
				this->mid = MSGID_CREATE_DUMP_FINISHED;
				this->connection = NULL;
			}
			std::string error;
			std::string dbname;
			std::string directory;
			MasterConnection* connection;
		};

		struct BackupDatabase : public ThreadMessage
		{
			BackupDatabase()
			{
				this->mid = MSGID_BACKUP_DATABASE;
			}
			
			std::string directory;
		};
	}

}

#endif // _pw_gdb_msgids_