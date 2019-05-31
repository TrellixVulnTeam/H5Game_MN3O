/*
#include "pw_gdb_database_backup.h"

namespace gdb
{
	DatabaseBackup::DatabaseBackup( const std::string& name,const std::string& backupDirectory )
		: m_sName(name)
		, m_sBackupDirectory(backupDirectory)
	{
		m_pOplogStream = new gdb::ChunksWriter(64*1024);
	}

	DatabaseBackup::~DatabaseBackup()
	{
		delete m_pOplogStream;
	}

	void DatabaseBackup::Merge( gdb::ChunksWriter* writer )
	{
		while(gdb::SChunk* chunk = writer->PeekBuffer(true))
		{
			m_pOplogStream->Write(chunk->data,chunk->size);
			gdb::SChunk::FreeChain(chunk);
		}
	}

	void DatabaseBackup::Merge( SChunk* chunks )
	{
		SChunk* curr = chunks;
		while(curr != NULL)
		{
			m_pOplogStream->Write(curr->data,curr->size);
			curr = curr->next;
		}

		if(chunks != NULL)
		{
			gdb::SChunk::FreeChain(chunks);
		}
	}

	void DatabaseBackup::GetOplogs( std::vector<SChunk*>& chunks )
	{
		SChunk* head = m_pOplogStream->GetChain();
		while(head != NULL && head->size > 0)
		{
			chunks.push_back(head);
			head = head->next;
		}
	}

}
*/