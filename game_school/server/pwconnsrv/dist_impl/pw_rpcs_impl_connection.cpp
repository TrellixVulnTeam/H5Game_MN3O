#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_connsrv_connection.h"


namespace pwconnsrv
{
	int Connection::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_CloseTcp,&Connection::_rpc_call_CloseTcp);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_SendMsg,&Connection::_rpc_call_SendMsg);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_SendMsgEx,&Connection::_rpc_call_SendMsgEx);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_MsgIncomingResult,&Connection::_rpc_call_MsgIncomingResult);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_UpdateStatus,&Connection::_rpc_call_UpdateStatus);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_CheckStatus,&Connection::_rpc_call_CheckStatus);
		port->Impl<Connection>(rpcnames::connsrv::Connection::_rpc_call_ReturnCreateCharacterStage,&Connection::_rpc_call_ReturnCreateCharacterStage);
		return 0;
	}
}
