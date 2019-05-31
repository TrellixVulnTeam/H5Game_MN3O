#include "msg.handler.h"
#include "msg.def.h"
#include "pw_connsrv_utils.h"
#include "accsrv.pb.h"
#include "pw_accsrv_service_port.h"

namespace pwaccsrv
{
	// msgid:15 name:CSTokenLogin
	int MsgHandler::Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSTokenLogin& msg)
	{
		using namespace pwngs;
		using namespace pwngs::protocol::accsrv;

		pwaccsrv::SImplAcc* port = (pwaccsrv::SImplAcc*)mContext;
		pwngs::ConnectionStatus& status = port->m_objConnectionStatus;

		enum
		{
			TOKEN_LOGIN_TYPE_LAOHU = 1,
		};

		switch(msg.type())
		{
		case TOKEN_LOGIN_TYPE_LAOHU:
			{
				port->HandleLaoHuLogin(msg.name(),msg.token(),&status);
			}
			break;
		default:
			{
				gDebugStream("CSTokenLogin invalid login_type=" << msg.type() << " uid=" << msg.name());
			}
			break;
		}

		return 0;
	}
} //end namespace pwaccsrv

