#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_service_base.h"


namespace pwngs
{
	int SImplBase::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_Broadcast,&SImplBase::_rpc_call_Broadcast);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorld,&SImplBase::_rpc_call_HumanEnterWorld);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanLeaveWorld,&SImplBase::_rpc_call_HumanLeaveWorld);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanUpdate,&SImplBase::_rpc_call_HumanUpdate);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorldAfter,&SImplBase::_rpc_call_HumanEnterWorldAfter);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanDropped,&SImplBase::_rpc_call_HumanDropped);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanReconnected,&SImplBase::_rpc_call_HumanReconnected);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsg,&SImplBase::_rpc_call_SendMsg);
		port->Impl<SImplBase>(rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsgReliable,&SImplBase::_rpc_call_SendMsgReliable);
		return 0;
	}
}
