#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_passportlock_mgr.h"


namespace pwngs
{
	int PassportLockMgr::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<PassportLockMgr>(rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockAdded,&PassportLockMgr::_rpc_call_LockAdded);
		port->Impl<PassportLockMgr>(rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockDeled,&PassportLockMgr::_rpc_call_LockDeled);
		port->Impl<PassportLockMgr>(rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockCheck,&PassportLockMgr::_rpc_call_LockCheck);
		return 0;
	}
}
