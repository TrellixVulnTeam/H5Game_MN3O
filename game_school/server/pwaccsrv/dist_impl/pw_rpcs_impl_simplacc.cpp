#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_accsrv_service_port.h"


namespace pwaccsrv
{
	int SImplAcc::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplAcc>(rpcnames::accsrv::SImplAcc::_rpc_call_MsgIncoming,&SImplAcc::_rpc_call_MsgIncoming);
		port->Impl<SImplAcc>(rpcnames::accsrv::SImplAcc::_rpc_call_Exit,&SImplAcc::_rpc_call_Exit);
		port->Impl<SImplAcc>(rpcnames::accsrv::SImplAcc::_rpc_call_ReloadWhiteList,&SImplAcc::_rpc_call_ReloadWhiteList);
		port->Impl<SImplAcc>(rpcnames::accsrv::SImplAcc::_rpc_call_EnableWhiteList,&SImplAcc::_rpc_call_EnableWhiteList);
		return 0;
	}
}
