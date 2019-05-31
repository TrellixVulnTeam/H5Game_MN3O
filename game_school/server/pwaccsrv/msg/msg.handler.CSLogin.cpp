#include "msg.handler.h"
#include "pw_ngs_def.h"
#include "pw_human_def.h"
#include "msg.def.h"
#include "pw_connsrv_utils.h"
#include "pw_accsrv_service_port.h"

namespace pwaccsrv
{
	// msgid:11 name:CSLogin
	int MsgHandler::Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLogin& msg)
	{
		using namespace pwngs::protocol::accsrv;

		pwaccsrv::SImplAcc* port = (pwaccsrv::SImplAcc*)mContext;

		std::string fromNode = port->GetSenderNode();
		std::string fromPort = port->GetSenderPort();

		pwngs::ConnectionStatus& status = port->m_objConnectionStatus;

		// ---------------------------------------------------------------------------------------
	
		if(!port->IsLegalIP(status.szSocketIP))
		{
			SCLoginResult loginResult;

			status.szAccount[0] = '\0';
			status.nState = pwngs::connection::_StateLosted;
			loginResult.set_result(-3);
			loginResult.set_error("IsLegalIP = false");
			pwconnsrv::SendMsg(port,fromNode,fromPort,conn,msgid_SCLoginResult,loginResult);
			return 0;
		}

		if(msg.token().length() > 0)
			port->HandleLadderLogin(msg.name(),msg.token(),&status);
		else
			port->HandleUserPswdLogin(msg.name(),msg.pswd(),&status);

		return 0;
	}
} //end namespace pwaccsrv
