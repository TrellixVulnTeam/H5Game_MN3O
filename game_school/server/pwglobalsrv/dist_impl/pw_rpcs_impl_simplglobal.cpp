#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_service_global.h"


namespace pwngs
{
	int SImplGlobal::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplGlobal>(rpcnames::globalsrv::SImplGlobal::_rpc_call_Test,&SImplGlobal::_rpc_call_Test);
		port->Impl<SImplGlobal>(rpcnames::globalsrv::SImplGlobal::_rpc_call_SendMsg,&SImplGlobal::_rpc_call_SendMsg);
		return 0;
	}
}
