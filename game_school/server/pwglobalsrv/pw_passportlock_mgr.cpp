#include "pw_passportlock_mgr.h"
#include "pwdist_port_generic.h"
#include "pw_rpc_proxy.h"
#include "pw_service_global.h"
#include "pw_misc_consts.h"
#include "pw_ngs_common.h"
#include "pw_ngs_def.h"
#include "pw_class.h"
#include "pw_orm_helperex.h"
#include "pwdist_node.h"
#include "pw_rpc_proxy.h"
#include "pw_utils.h"

namespace pwngs
{
	PassportLockMgr::PassportLockMgr(SImplGlobal* port)
		: m_pImplGlobal(port)
	{
		m_pImplGlobal->AddCallableObject(this);
		InitialRpcs(m_pImplGlobal);
	}

	PassportLockMgr::~PassportLockMgr()
	{
		m_pImplGlobal->DelCallableObject(GetID());
	}

	int64 PassportLockMgr::GetID()
	{
		return GLOBAL_TYPE_PASSPORTLOCK_MGR;
	}

	int PassportLockMgr::Pull()
	{
		pwassertf(m_pImplGlobal->GetDBC() && m_pImplGlobal->GetDBC()->IsConnected());

		m_pImplGlobal->GetDBC()->Hvals((GlobalPassportLock::meta()));
		m_pImplGlobal->GetDBC()->ListenFuture(gdb::Client::fnFutureCallback(this,&PassportLockMgr::pfnPassportLockDataCallback));

		return 0;
	}

	void PassportLockMgr::pfnPassportLockDataCallback(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		if(!f->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << ", failed");
			return;
		}

		GMDB_FOREACH_PACKETS(i,f)
		{
			char* data = NULL;
			size_t size = 0;
			f->CheckedBuffer(i,&data,&size);

			if(data == NULL || size <= 0)
				continue;
			
			GlobalPassportLock orm;
			orm.from_bson(data,size);
			
			gDebugStream(__FUNCTION__ << ", passport=" << orm.passport << ", time=" << orm.locked_time);

			m_mapLocks.insert(std::make_pair(orm.passport.c_str(),orm));
		}
	}

	void PassportLockMgr::_rpc_call_LockAdded(int32 zoneid,const_char_ptr passport,int64 secs)
	{
		pwassert(this && "_rpc_call_LockAdded");
		pwassert(secs > 0);

		CollectionPassportLocksT::iterator iter = m_mapLocks.find(passport);

		// 已有锁定信息，以最近一次为准刷新时间
		if(iter != m_mapLocks.end())
		{
			gDebugStream(__FUNCTION__ << ", lock exists, passport=" << passport);
			m_mapLocks.erase(iter);
		}
		
		GlobalPassportLock orm;
		{
			orm.set_passport(passport);
			orm.set_locked_time(secs + pwutils::time::clib_time());
		}
		OrmHelperEx::GOrmUpdate(m_pImplGlobal->GetDBC(),&orm);

		m_mapLocks.insert(std::make_pair(passport,orm));

		gDebugStream(__FUNCTION__ << ", zoneid=" << zoneid  << ", passport=" << passport << ", time=" << orm.locked_time);
	}

	void PassportLockMgr::_rpc_call_LockDeled(int32 zoneid,const_char_ptr passport)
	{
		pwassert(this && "_rpc_call_LockDeled");

		CollectionPassportLocksT::iterator iter = m_mapLocks.find(passport);

		// 无锁定信息
		if(iter == m_mapLocks.end())
		{
			gDebugStream(__FUNCTION__ << ", lock no exists, passport=" << passport);
			return;
		}

		std::vector<std::string> nodes;
		m_pImplGlobal->GetNode()->GetRemoteNodes(cst_node_ctrl,nodes);
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			pwngs::ctrlsrv::SImplCommonProxy prx(m_pImplGlobal);
			prx._set_call_target(nodes[i].c_str(),pwngs::cst_port_ctrlsrv_common,0);
			prx._rpc_call_PassportUnlock(this,passport);
		}

		GlobalPassportLock& orm = iter->second;
		OrmHelperEx::GOrmDelete(m_pImplGlobal->GetDBC(),&orm);
		m_mapLocks.erase(iter);

		gDebugStream(__FUNCTION__ << ", zoneid=" << zoneid << ", passport=" << passport);
	}

	void PassportLockMgr::_rpc_call_LockCheck(int32 zoneid,const_char_ptr passport,int64 hid)
	{
		pwassert(this && "_rpc_call_LockCheck");
		pwassert(m_pImplGlobal);

		CollectionPassportLocksT::iterator iter = m_mapLocks.find(passport);

		// 无此帐号锁定信息
		if(iter == m_mapLocks.end())
			return;

		GlobalPassportLock& orm = iter->second;

		// 此帐号已解除锁定
		int32 secs = (int32)__max(0,orm.locked_time - pwutils::time::clib_time());
		if(secs <= 0)
		{
			OrmHelperEx::GOrmDelete(m_pImplGlobal->GetDBC(),&orm);
			m_mapLocks.erase(iter);
			return;
		}
		
		std::string actualNode;
		actualNode.append(cst_node_ctrl).append(pwutils::itoa2(zoneid));

		pwngs::ctrlsrv::SImplCommonProxy prx(m_pImplGlobal);
		prx._set_call_target(actualNode.c_str(),pwngs::cst_port_ctrlsrv_common,0);
		prx._rpc_call_PassportLock(this,passport,hid,secs);

		gDebugStream(__FUNCTION__ << ", zoneid=" << zoneid  << ", passport=" << passport << ", time=" << orm.locked_time);
	}
}