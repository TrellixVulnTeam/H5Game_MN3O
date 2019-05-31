#ifndef _pw_robot_module_magic_
#define _pw_robot_module_magic_

#include "pw_def.h"
#include "pw_robot_module.h"
#include "pw_robot_message_filter.h"
#include "pw_tick_timer.h"

namespace pwngs
{
	class RModMagic : public RobotModule,public RobotMessageFilter
	{
		struct SMagicInformation
		{
			int id;
			int loc;
			int64 cd;
		};
	public:
		RModMagic(RobotCharacter* obj);
	public:
		int Update();
		virtual int OnEnterWorld();
	public:
		int StartAutomaticCaster();
		int CleanAutomaticCaster();
	public:
		int RandomCast();
	public:
		int HandleMessage(int msgid,char* buf,size_t len);
	protected:
		typedef std::vector<SMagicInformation> CollectionMagicInformationsT;
	protected:
		CollectionMagicInformationsT m_vMagics;
		pwutils::TickTimer m_objCasterTimer;
	};

}
#endif // _pw_robot_module_magic_