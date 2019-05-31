/*
#ifndef _pw_gdb_database_backup_
#define _pw_gdb_database_backup_

#include "pw_gdb_refcounted.h"
#include "pw_gdb_reader_writer.h"
#include "pw_gdb_chunks.h"

namespace gdb
{
	class DatabaseBackup : public gdb::Refcounted<true>
	{
	public:
		DatabaseBackup(const std::string& name,const std::string& backupDirectory);
		~DatabaseBackup();
	public:
		inline const std::string& GetName()
		{
			return m_sName;
		}

		inline const std::string& GetBackupDirectory()
		{
			return m_sBackupDirectory;
		}
	public:
		void GetOplogs(std::vector<SChunk*>& chunks);
	public:
		void Merge(gdb::ChunksWriter* writer);
		void Merge(SChunk* chunks);
	protected:
		std::string m_sName;
		std::string m_sBackupDirectory;
		gdb::ChunksWriter* m_pOplogStream;
	};
}

#endif // _pw_gdb_database_backup_
*/