#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_ranklist_mgr.h"


namespace pwngs
{
	int RanklistMgr::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<RanklistMgr>(rpcnames::globalsrv::RanklistMgr::_rpc_call_RankUpdate,&RanklistMgr::_rpc_call_RankUpdate);
		port->Impl<RanklistMgr>(rpcnames::globalsrv::RanklistMgr::_rpc_call_RankQuery,&RanklistMgr::_rpc_call_RankQuery);
		port->Impl<RanklistMgr>(rpcnames::globalsrv::RanklistMgr::_rpc_call_RankClear,&RanklistMgr::_rpc_call_RankClear);
		return 0;
	}
}
