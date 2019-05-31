#ifndef pw_robot_module_motion
#define pw_robot_module_motion

#include "pw_robot_motion_def.h"
#include "pw_robot_module.h"
#include "pw_robot_message_filter.h"

namespace pwngs
{


	class RobotMotionObject;

	class RModMotion : public RobotModule,public RobotMessageFilter
	{
	public:
		RModMotion(RobotCharacter* human);
		virtual ~RModMotion();
	public:
		int Stop();
		int MovePosition(const G3D::Vector3& pos);
		int MoveWaypoint(const G3D::Vector3& pos);
		int MoveWaypointRandom(const G3D::Vector3& pos,float dist);
	public:
		int Update();
		int HandleMessage(int msgid,char* buf,size_t len);
	public:
		int DoMotionBegan();
		int DoMotionOrientation();
		int DoMotionEnded();
	public:
		RobotMotionObject* m_pMotionObject;
	};
}

#endif // pw_robot_module_motion