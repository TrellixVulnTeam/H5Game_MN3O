#include "pw_orm_helperex.h"
#include "pw_logger.h"
#include "pw_ngs_def.h"
#include "pw_logger.h"
#include "pw_backtrace.h"

namespace pwngs
{
	OrmHelperEx::OrmHelperEx()
	{
	}

	OrmHelperEx::~OrmHelperEx()
	{
	}

	void OrmHelperEx::GOrmInsert(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj)
	{
		OrmHelperEx::Commit(dbc,obj,OPERATION_INSERT);
	}

	void OrmHelperEx::GOrmUpdate(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj)
	{
		int64 oldhash = obj->hash_origin();
		int64 newhash = obj->hash_make(0);
		if(oldhash == newhash)
		{
//#ifdef _DEBUG
//			std::cout << __FUNCTION__ << " " << obj->getmeta() << " key=" << obj->getkey() << " skiped" << std::endl;
//#endif
			return ;
		}
		obj->hash_update(newhash);

		OrmHelperEx::Commit(dbc,obj,OPERATION_UPDATE);
	}

	void OrmHelperEx::GOrmDelete(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj)
	{
		OrmHelperEx::Commit(dbc,obj,OPERATION_DELETE);
	}

	bool OrmHelperEx::Commit(gdb::AsynchronousClient* dbc,pwutils::KvormBase* obj,int operation)
	{
		pwassertn(dbc && dbc->IsConnected());

		switch(operation)
		{
		case OPERATION_INSERT:
			{
				std::string key,meta,val;
				obj->to_bson(val);

				key = obj->getkey();
				meta = obj->getmeta();

				if(key.length() <= 0 || meta.length() <= 0)
				{
					gDebugStream(__FUNCTION__ << " invalid key,meta=" << meta << " stack=" << get_stack_trace(20));
					break;
				}

				dbc->Hsetnx((meta),(key),(val));
			}
			break;
		case OPERATION_UPDATE:
			{
				std::string key,meta,val;
				obj->to_bson(val);

				key = obj->getkey();
				meta = obj->getmeta();

				if(key.length() <= 0 || meta.length() <= 0)
				{
					gDebugStream(__FUNCTION__ << " invalid key,meta=" << meta << " stack=" << get_stack_trace(20));
					break;
				}

				dbc->Hset((meta),(key),(val));
			}
			break;
		case OPERATION_DELETE:
			{
				std::string key,meta;

				key = obj->getkey();
				meta = obj->getmeta();

				if(key.length() <= 0 || meta.length() <= 0)
				{
					gDebugStream(__FUNCTION__ << " invalid key,meta=" << meta << " stack=" << get_stack_trace(20));
					break;
				}

				dbc->Hdel((meta),(key));
			}
			break;
		}
		return true;
	}
}