#ifndef _pw_orm_helperex_
#define _pw_orm_helperex_

#include "pw_def.h"
#include "kvdb/pw_kvorm.h"
#include "pw_tick_timer.h"
#include "gdb/pw_gdb_asynchronous_client.h"

namespace pwngs
{
	class OrmHelperEx
	{
		enum
		{
			OPERATION_INSERT,
			OPERATION_UPDATE,
			OPERATION_DELETE,
			OPERATION_MAX,
		};
	public:
		OrmHelperEx();
		~OrmHelperEx();
	public:
		static void GOrmInsert(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj);
		static void GOrmUpdate(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj);
		static void GOrmDelete(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj);
	protected:
		static bool Commit(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj,int operation);
	};
}

#endif // _pw_orm_helperex_