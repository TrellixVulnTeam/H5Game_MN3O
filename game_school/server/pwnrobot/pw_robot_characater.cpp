
#include "pw_robot_characater.h"
#include "pw_robot_thread.h"
#include "pw_robot_module_motion.h"
#include "pw_utils.h"

namespace pwngs
{
	RobotCharacter::RobotCharacter()
	{
		m_szUniqueName[0] = '\0';
		m_pModMotion = new RModMotion(this);
	}

	RobotCharacter::~RobotCharacter()
	{
		_safe_delete(m_pModMotion);
	}

	int RobotCharacter::Update()
	{
		m_pModMotion->Update();

		return 0;
	}

	int RobotCharacter::UpdatePer1Sec()
	{
		return 0;
	}

	int RobotCharacter::EnterWorld()
	{
		return 0;
	}

	int RobotCharacter::LeaveWorld(const char* caller)
	{
		return 0;
	}

	int RobotCharacter::DiscardObject()
	{
		GetCurrentRobotThread()->Del(this);
		return 0;
	}

	const char* RobotCharacter::GetUniqueName()
	{
		if(m_szUniqueName[0] == 0)
			pwutils::itoa(m_szUniqueName,m_nId);
		return m_szUniqueName;
	}

	int RobotCharacter::SendMsg( int msgid,google::protobuf::Message& msg )
	{
		return -1;
	}

}