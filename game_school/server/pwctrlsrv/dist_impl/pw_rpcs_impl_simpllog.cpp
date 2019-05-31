#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_service_log.h"


namespace pwngs
{
	int SImplLog::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplLog>(rpcnames::ctrlsrv::SImplLog::_rpc_call_Write,&SImplLog::_rpc_call_Write);
		port->Impl<SImplLog>(rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_WM,&SImplLog::_rpc_call_Write_WM);
		port->Impl<SImplLog>(rpcnames::ctrlsrv::SImplLog::_rpc_call_WriteBetaLog,&SImplLog::_rpc_call_WriteBetaLog);
		port->Impl<SImplLog>(rpcnames::ctrlsrv::SImplLog::_rpc_call_ZeroHour,&SImplLog::_rpc_call_ZeroHour);
		port->Impl<SImplLog>(rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_MData,&SImplLog::_rpc_call_Write_MData);
		return 0;
	}
}
