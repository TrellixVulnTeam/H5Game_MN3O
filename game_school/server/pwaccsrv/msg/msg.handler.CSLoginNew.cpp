#include "msg.handler.h"
#include "msg.def.h"
#include "pw_accsrv_service_port.h"
#include "pw_connsrv_utils.h"
#include "pw_server_group.h"

namespace pwaccsrv
{
	// msgid:16 name:CSLoginNew
	int MsgHandler::Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLoginNew& msg)
	{
		using namespace pwngs::protocol::accsrv;
		using namespace pwngs;
		pwaccsrv::SImplAcc* port = (pwaccsrv::SImplAcc*)mContext;

		std::string fromNode = port->GetSenderNode();
		std::string fromPort = port->GetSenderPort();
		pwngs::ConnectionStatus& status = port->m_objConnectionStatus;

		// ---------------------------------------------------------------------------------------
		// 检查版本
		// ---------------------------------------------------------------------------------------
		if(!port->CheckVersion(msg.mutable_logininfo()))
		{
			gLoginStream("CSLoginNew CheckVersion Failed, ip=" << status.szSocketIP
				<< " expect=" << pwngs::protocol::accsrv::MajorVersion << " got=" << msg.mutable_logininfo()->major_version());

			status.szAccount[0] = '\0';
			status.nState = pwngs::connection::_StateLosted;

			SCLoginResult loginResult;
			loginResult.set_result(-100);
			loginResult.set_error("version nomatch");
			pwconnsrv::SendMsg(port,fromNode,fromPort,conn,msgid_SCLoginResult,loginResult);
			return -1;
		}

		port->UpdateConnectionStatus(msg.mutable_logininfo());

		// ---------------------------------------------------------------------------------------
		// IP是否被禁用
		// ---------------------------------------------------------------------------------------
		if(!port->IsLegalIP(status.szSocketIP))
		{
			gLoginStream("CSLoginNew CheckLegalIP Failed,ip=" << status.szSocketIP);

			status.szAccount[0] = '\0';
			status.nState = pwngs::connection::_StateLosted;

			SCLoginResult loginResult;
			loginResult.set_result(-3);
			loginResult.set_error("IsLegalIP = false");
			pwconnsrv::SendMsg(port,fromNode,fromPort,conn,msgid_SCLoginResult,loginResult);
			return 0;
		}

		gLoginStream("CSLoginNew HandleLoginType:" << msg.type() << " ip=" <<status.szSocketIP);

		switch(msg.type())
		{
		case LoginType_Ladder:
			pwassertn(g_bLadderServer);
			break;
		default:
			pwassertn(!g_bLadderServer);
			break;
		}

		switch(msg.type())
		{
		case LoginType_UserPswd:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLoginUserPswd)& info = msg.loginuserpswd();
				port->HandleUserPswdLogin(info.name(),info.pswd(),&status);
			}
			break;
		case LoginType_173:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLogin173)& info = msg.login173();
				port->Handle173Login(info,&status);
			}
			break;
		case LoginType_LianYun:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLoginLianYun)& info = msg.loginlianyun();
				port->HandleLianYunLogin(info,&status);
			}
			break;
		case LoginType_LaoHu:
			{
				const MsgA(SLoginToken)& info = msg.logintoken();
				port->HandleLaoHuLogin(info.name(),info.token(),&status);
			}
			break;
		case LoginType_Tencent:
			{
				pwdist::CallEndpoint* sender = port->GetSender();
				pwassertf(sender);

				const MsgA(SLoginTencent)& info = msg.logintencent();

				if(info.has_platform_key())
					strncpy(status.vTencentUserInfo.platform_key,info.platform_key().c_str(),_countof(status.vTencentUserInfo.platform_key));
				
				status.vTencentUserInfo.pid = info.pid();

				port->HandleTencentLogin(*sender,info.openid(),info.openkey(),info.platform(),&status);
			}
			break;
		case LoginType_ARC:
			{
				pwdist::CallEndpoint* sender = port->GetSender();
				pwassertf(sender);

				const MsgA(SLoginToken)& info = msg.logintoken();

				port->HandleArcTokenLogin(*sender,info.name(),info.token(),&status);
			}
			break;
		case LoginType_XiYou:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLoginXiYou)& info = msg.loginxiyou();
				port->HandleXiYouLogin(info, &status);
			}
			break;
		case LoginType_360:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLogin360)& info = msg.login360();
				port->Handle360Login(info, &status);
			}
			break;
		case LoginType_Kor:
			{
				status.szAccount[0] = '\0';
				status.nState = pwngs::connection::_StateLosted;

				const MsgA(SLoginKor)& info = msg.loginkor();
				port->HandleKorLogin(info, &status);
			}
			break;
		case LoginType_Ladder:
			{
				const MsgA(SLoginToken)& info = msg.logintoken();
				port->HandleLadderLogin(info.name(),info.token(),&status);
			}
			break;
		}


		return 0;
	}
} //end namespace pwaccsrv

