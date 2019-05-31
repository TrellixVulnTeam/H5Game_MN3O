#ifndef _pw_robot_motion_
#define _pw_robot_motion_

#include "pw_robot_def.h"

namespace pwngs
{

	class RMotionInfo;
	class RobotCharacter;

	class RobotMotionObject
	{
	public:
		RobotMotionObject(RobotCharacter* obj);
		virtual ~RobotMotionObject();
	public:
		virtual int IsFinished() = 0;
		virtual int Startup();
		virtual int Cleanup();
		virtual int Update();
		virtual int OnSpeedChanged();
		virtual int OnGetMotionInfo(RMotionInfo& info) = 0;
	public:
		RobotCharacter* m_pOwner;
		float m_fSpeed;
	};

	class RobotPositionMotionObject : public RobotMotionObject
	{
	public:
		RobotPositionMotionObject(RobotCharacter* obj,const G3D::Vector3& target);
		virtual ~RobotPositionMotionObject();
	public:
		virtual int IsFinished();
		virtual int Startup();
		virtual int Cleanup();
		virtual int Update();
		virtual int OnSpeedChanged();
		virtual int OnGetMotionInfo(RMotionInfo& info);
	public:
		G3D::Vector3 m_vStart;
		G3D::Vector3 m_vTarget;
	public:
		float m_fTotalTime;
		float m_fElapsedTime;
	};

	class RobotWaypointMotionObject : public RobotMotionObject
	{
	public:
		RobotWaypointMotionObject(RobotCharacter* obj,const std::vector<G3D::Vector3>& nodes);
		virtual ~RobotWaypointMotionObject();
	public:
		virtual int IsFinished();
		virtual int Startup();
		virtual int Update();
		virtual int OnSpeedChanged();
		virtual int OnGetMotionInfo(RMotionInfo& info);
	public:
		size_t m_nCurrentNode;
		std::vector<G3D::Vector3> m_vNodes;
		RobotPositionMotionObject* m_pMotionObject;
	};
}

#endif // _pw_robot_motion_