#include "pw_human.h"

namespace pwngs
{
	HumanMsgHandler::HumanMsgHandler(void* context)
		: pwworldsrv::MsgHandler(context)
	{

	}

	bool HumanMsgHandler::IsAccept(int msgid)
	{
		using namespace pwngs::protocol::worldsrv;

		// 还没进世界
		Human* h = (Human*)mContext;
		if (h == NULL)
		{
			//gDebugStream(" mContext = Null,ignore msg :" << msgid);
			return false;
		}

	


		return false;
	}

	/*Human::Human(int64 hid, int64 sid)
	{

	}*/

}