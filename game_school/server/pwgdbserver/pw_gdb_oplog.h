#ifndef _pw_gdb_oplog_
#define _pw_gdb_oplog_

#include "pw_gdb_operation_def.h"
#include "pw_gdb_chunks.h"
#include "pw_gdb_def.h"

namespace gdb
{
	class Oplog
	{
		static const int64 OP_PUT = CMD_SLAVE_SC_OPLOG_PUT;
		static const int64 OP_DELETE = CMD_SLAVE_SC_OPLOG_DEL;
		static const int64 OP_CONSISTENT_POINT = CMD_SLAVE_SC_OPLOG_CONSISTENT_POINT;
		static const int64 OP_CLEAR = CMD_SLAVE_SC_OPLOG_CLEAR;
	public:
		void Put(const Slice& dbname,const Slice& dbvalue);
		void Delete(const Slice& dbname);
		void Clear();
		void PutConsistentPoint();
		void Merge(Oplog* log);
	public:
		gdb::ChunksWriter m_mBuffer;
	};
}

#endif // _pw_gdb_oplog_