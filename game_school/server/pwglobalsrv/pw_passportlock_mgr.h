#ifndef _pw_passportlock_mgr_
#define _pw_passportlock_mgr_

#include "pw_def.h"
#include "pwdist_port_generic.h"
#include "kvorm/pw_orm_globalpassportlock.h"
#include "gdb/pw_gdb_asynchronous_client.h"

namespace pwngs
{
	class SImplGlobal;
	typedef orm::GlobalPassportLock GlobalPassportLock;

	/**
	* @class PassportLockMgr
	* @author
	* @date 2015年05月03日
	* @file pw_passportlock_mgr.h
	* @brief 全局帐号锁定管理器
	*/
	class PassportLockMgr : public pwdist::ICallableObject, public pwutils::memory::ObjectInThread<PassportLockMgr>
	{
	public:
		PassportLockMgr(SImplGlobal* port);
		virtual ~PassportLockMgr();
	public:
		virtual int64 GetID();
	public:
		static int InitialRpcs(pwdist::Port* port);
	public:
		int Pull();
		void pfnPassportLockDataCallback(gdb::Client::Future* f,int mode);
	public:
		void _rpc_call_LockAdded(int32 zoneid,const_char_ptr passport,int64 secs);
		void _rpc_call_LockDeled(int32 zoneid,const_char_ptr passport);
		void _rpc_call_LockCheck(int32 zoneid,const_char_ptr passport,int64 hid);
	private:
		SImplGlobal* m_pImplGlobal;
	private:
		typedef std_unordered_map<std::string,GlobalPassportLock> CollectionPassportLocksT;
		CollectionPassportLocksT m_mapLocks;
	};
}

#endif //_pw_passportlock_mgr_