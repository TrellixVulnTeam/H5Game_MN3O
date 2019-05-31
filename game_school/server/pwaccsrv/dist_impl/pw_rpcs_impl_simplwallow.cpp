#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_service_wallow.h"


namespace pwaccsrv
{
	int SImplWallow::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplWallow>(rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogin,&SImplWallow::_rpc_call_WallowLogin);
		port->Impl<SImplWallow>(rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogout,&SImplWallow::_rpc_call_WallowLogout);
		return 0;
	}
}
