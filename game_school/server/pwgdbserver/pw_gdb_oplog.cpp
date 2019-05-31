#include "pw_gdb_oplog.h"
#include "pw_gdb_protocol.h"

namespace gdb
{


	void Oplog::Put( const Slice& dbname,const Slice& dbvalue )
	{
		gdb::ProtocolWriter writer(&m_mBuffer);
		writer.WriteI(OP_PUT,true);
		writer.WriteB(dbname.data(),dbname.size(),true);
		writer.WriteB(dbvalue.data(),dbvalue.size(),false);
	}

	void Oplog::Delete( const Slice& dbname )
	{
		gdb::ProtocolWriter writer(&m_mBuffer);
		writer.WriteI(OP_DELETE,true);
		writer.WriteB(dbname.data(),dbname.size(),false);
	}

	void Oplog::PutConsistentPoint()
	{
		gdb::ProtocolWriter writer(&m_mBuffer);
		writer.WriteI(OP_CONSISTENT_POINT,false);
	}

	void Oplog::Merge( Oplog* log )
	{
		SChunk* chunk = log->m_mBuffer.Detach();
		SChunk* head = chunk;
		while(head != NULL)
		{
			m_mBuffer.Write(head->data,head->size);
			head = head->next;
		}
		SChunk::FreeChain(chunk);
	}

	void Oplog::Clear()
	{
		gdb::ProtocolWriter writer(&m_mBuffer);
		writer.WriteI(CMD_SLAVE_SC_OPLOG_CLEAR,false);
	}

}