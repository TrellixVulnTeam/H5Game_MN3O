#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"


namespace pwngs
{
	int Base::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<Base>(rpcnames::accsrv::Base::_rpc_call_Null,&Base::_rpc_call_Null);
		return 0;
	}
}
