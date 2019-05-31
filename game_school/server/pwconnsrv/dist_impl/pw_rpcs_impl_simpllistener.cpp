#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_connsrv_listener.h"


namespace pwconnsrv
{
	int SImplListener::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplListener>(rpcnames::connsrv::SImplListener::_rpc_call_Enable,&SImplListener::_rpc_call_Enable);
		port->Impl<SImplListener>(rpcnames::connsrv::SImplListener::_rpc_call_Exit,&SImplListener::_rpc_call_Exit);
		port->Impl<SImplListener>(rpcnames::connsrv::SImplListener::_rpc_call_EnableMsgid,&SImplListener::_rpc_call_EnableMsgid);
		port->Impl<SImplListener>(rpcnames::connsrv::SImplListener::_rpc_call_GetDisabledMsgids,&SImplListener::_rpc_call_GetDisabledMsgids);
		return 0;
	}
}
