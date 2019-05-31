#include "msg.handler.h"
#include "accsrv.pb.h"
#include "pw_accsrv_service_port.h"
#include "pw_connsrv_utils.h"
#include "msg.def.h"

namespace pwaccsrv
{
	// msgid:10 name:CSLoginEx
	int MsgHandler::Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLoginEx& msg)
	{
		using namespace pwngs;
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

			gDebugStream("Process CSLoginEx Socket Drop:" << status.szSocketIP);
			return 0;
		}

		MsgA(SLogin173) info;
		info.set_userid(msg.userid());
		info.set_tm(msg.tm());
		info.set_signature(msg.signature());
		info.set_fatigue(msg.fatigue());

		port->Handle173Login(info,&status);
		
		return 0;
	}
} //end namespace pwaccsrv

