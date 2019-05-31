#ifndef _pw_robot_message_filter_
#define _pw_robot_message_filter_

#include "google/protobuf/message.h"

namespace pwngs
{
	class RobotMessageFilter
	{
	public:
		virtual ~RobotMessageFilter() {}
	public:
		virtual int HandleMessage(int msgid,char* buf,size_t len) = 0;
		virtual int OnEnterWorld() { return 0; }
	};
}

#endif // _pw_robot_message_filter_