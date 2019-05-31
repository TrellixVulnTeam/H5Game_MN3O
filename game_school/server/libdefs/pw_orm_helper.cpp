#include "pw_orm_helper.h"
#include "pw_logger.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"
#include "pw_time.h"
#include "pw_logger.h"
#include "pw_backtrace.h"

namespace pwngs
{
	OrmHelper::OrmHelper()
		: m_nFlags(0)
	{
	}

	OrmHelper::~OrmHelper()
	{
	}

	bool OrmHelper::OrmInsert( pwutils::KvormBase* obj)
	{
		if(this->IsIncludeFlags(ORM_HELP_FLAGS_DISABLE))
			return false;

		Commit(obj,OPERATION_INSERT);

		return true;
	}

	bool OrmHelper::OrmUpdate( pwutils::KvormBase* obj,int level /*= ORM_SYNC_FAST*/ )
	{
		if(this->IsIncludeFlags(ORM_HELP_FLAGS_DISABLE))
			return false;

		int64 oldhash = obj->hash_origin();
		int64 newhash = obj->hash_make(0);
		if(oldhash == newhash)
		{
//#ifdef _DEBUG
//			std::cout << __FUNCTION__ <<  " " << obj->getmeta() << " key=" << obj->getkey() << " skiped" << std::endl;
//#endif
			return false;
		}
		obj->hash_update(newhash);

		Commit(obj,OPERATION_UPDATE);
		
		return true;
	}

	void OrmHelper::OrmDelete( pwutils::KvormBase* obj )
	{
		if(this->IsIncludeFlags(ORM_HELP_FLAGS_DISABLE))
			return;

		Commit(obj,OPERATION_DELETE);
	}

	bool OrmHelper::Commit( pwutils::KvormBase* obj,int operation )
	{
		switch(operation)
		{
		case OPERATION_INSERT:
			{
				std::string key,meta,tmpbuf;
				obj->to_bson(tmpbuf);

				key = obj->getkey();
				meta = obj->getmeta();

				if(key.length() <= 0 || meta.length() <= 0)
				{
					gDebugStream(__FUNCTION__ << " invalid key,meta=" << meta << " stack=" << get_stack_trace(20));
					break;
				}

				pwngs::dbsrv::SImplKVDBProxy prx(NULL);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hsetnx(NULL,meta.c_str(),key.c_str(),pwdist::Chunk((char*)tmpbuf.c_str(),tmpbuf.length()));
			}
			break;
		case OPERATION_UPDATE:
			{
				std::string key,meta,tmpbuf;
				obj->to_bson(tmpbuf);

				key = obj->getkey();
				meta = obj->getmeta();

				if(key.length() <= 0 || meta.length() <= 0)
				{
					gDebugStream(__FUNCTION__ << " invalid key,meta=" << meta << " stack=" << get_stack_trace(20));
					break;
				}

				pwngs::dbsrv::SImplKVDBProxy prx(NULL);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hset(NULL,meta.c_str(),key.c_str(),pwdist::Chunk((char*)tmpbuf.c_str(),tmpbuf.length()));
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

				pwngs::dbsrv::SImplKVDBProxy prx(NULL);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hdel(NULL,meta.c_str(),key.c_str());
			}
			break;
		}
		return true;
	}

	void OrmHelper::Update( int64 tick )
	{
	}

	void OrmHelper::GOrmInsert( pwutils::KvormBase* obj )
	{
		OrmHelper::Commit(obj,OPERATION_INSERT);
	}

	int OrmHelper::GOrmUpdate(pwutils::KvormBase* obj)
	{
		int64 oldhash = obj->hash_origin();
		int64 newhash = obj->hash_make(0);
		if (oldhash == newhash)
		{
//#ifdef _DEBUG
//			std::cout << __FUNCTION__ << " " << obj->getmeta() << " key=" << obj->getkey() << " skiped" << std::endl;
//#endif
			return EResult_SameHash;
		}
		obj->hash_update(newhash);

		OrmHelper::Commit(obj, OPERATION_UPDATE);

		return EResult_OK;
	}

	void OrmHelper::GOrmDelete( pwutils::KvormBase* obj )
	{
		OrmHelper::Commit(obj,OPERATION_DELETE);
	}

}