#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_connsrv_service_port.h"


namespace pwconnsrv
{
	int SImplSend::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplSend>(rpcnames::connsrv::SImplSend::_rpc_call_Broadcast,&SImplSend::_rpc_call_Broadcast);
		port->Impl<SImplSend>(rpcnames::connsrv::SImplSend::_rpc_call_BroadcastEx,&SImplSend::_rpc_call_BroadcastEx);
		return 0;
	}
}
