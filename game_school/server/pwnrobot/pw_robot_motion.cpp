#include "pw_robot_motion.h"
#include "pw_robot_motion_def.h"
#include "pw_robot_thread.h"
#include "pw_robot_characater.h"
#include "pw_robot_module_motion.h"
#include "pw_logger.h"

namespace pwngs
{
	RobotMotionObject::RobotMotionObject(RobotCharacter* obj)
		: m_pOwner(obj)
		, m_fSpeed(5.0f)
	{
		
	}

	RobotMotionObject::~RobotMotionObject()
	{

	}

	int RobotMotionObject::Update()
	{
		return 0;
	}

	int RobotMotionObject::Startup()
	{
		return m_pOwner->GetModMotion()->DoMotionBegan();
	}

	int RobotMotionObject::OnSpeedChanged()
	{
		return 0;
	}

	int RobotMotionObject::Cleanup()
	{
		return m_pOwner->GetModMotion()->DoMotionEnded();
	}

	RobotPositionMotionObject::RobotPositionMotionObject( RobotCharacter* obj,const G3D::Vector3& target )
		: RobotMotionObject(obj)
		, m_vStart(obj->GetPosition())
		, m_vTarget(target)
	{
		m_fElapsedTime = 0.0f;	
	}

	RobotPositionMotionObject::~RobotPositionMotionObject()
	{

	}

	int RobotPositionMotionObject::Startup()
	{
		G3D::Vector3 dir = (m_vTarget - m_vStart).directionOrZero();
		m_fTotalTime = (m_vTarget - m_vStart).length() / m_fSpeed;
		m_pOwner->ChangeOrientation(dir);

		return RobotMotionObject::Startup();
	}

	int RobotPositionMotionObject::Cleanup()
	{
		return RobotMotionObject::Cleanup();
	}

	int RobotPositionMotionObject::Update()
	{
		RobotThread* thr = GetCurrentRobotThread();

		float f = thr->GetCurrentDiffSec();
		m_fElapsedTime = __min(m_fElapsedTime + f,m_fTotalTime);

		G3D::Vector3 pos = m_vStart + m_pOwner->GetOrientation() * (m_vTarget - m_vStart).length() * m_fElapsedTime / m_fTotalTime;

		m_pOwner->ChangePosition(pos);

		return 0;
	}

	int RobotPositionMotionObject::OnSpeedChanged()
	{
		m_vStart = m_pOwner->GetPosition();
		m_fTotalTime = (m_vTarget - m_vStart).length() / m_fSpeed;
		m_fElapsedTime = 0.0f;
		return 0;
	}

	int RobotPositionMotionObject::OnGetMotionInfo( RMotionInfo& info )
	{
		info.nMotionType = RMOTION_TYPE_POSITION;
		info.vMotionPosition = m_vTarget;
		return 0;
	}

	int RobotPositionMotionObject::IsFinished()
	{
		return m_fElapsedTime >= m_fTotalTime;
	}


	int RobotWaypointMotionObject::IsFinished()
	{
		return m_nCurrentNode >= m_vNodes.size();
	}

	RobotWaypointMotionObject::RobotWaypointMotionObject( RobotCharacter* obj,const std::vector<G3D::Vector3>& nodes )
		: RobotMotionObject(obj)
	{
		m_vNodes = nodes;
		m_nCurrentNode = 0;
		m_pMotionObject = NULL;
	}

	RobotWaypointMotionObject::~RobotWaypointMotionObject()
	{
		_safe_delete(m_pMotionObject);
	}

	int RobotWaypointMotionObject::Startup()
	{
		if(IsFinished())
			return -1;

		m_nCurrentNode = 0;
		m_pMotionObject = new RobotPositionMotionObject(m_pOwner,m_vNodes[m_nCurrentNode]);
		return m_pMotionObject->Startup();
	}

	int RobotWaypointMotionObject::Update()
	{
		if(IsFinished())
			return -1;

		if(m_pMotionObject == NULL)
			return -2;

		m_pMotionObject->Update();

		if(m_pMotionObject->IsFinished())
		{
			m_nCurrentNode++;
			_safe_delete(m_pMotionObject);
			
			if(!IsFinished())
			{
				m_pMotionObject = new RobotPositionMotionObject(m_pOwner,m_vNodes[m_nCurrentNode]);
				m_pMotionObject->Startup();
			}
		}
		return 0;
	}

	int RobotWaypointMotionObject::OnSpeedChanged()
	{
		pwassertf(m_pMotionObject);
		return m_pMotionObject->OnSpeedChanged();		
	}

	int RobotWaypointMotionObject::OnGetMotionInfo( RMotionInfo& info )
	{
		pwassertf(m_pMotionObject);
		return m_pMotionObject->OnGetMotionInfo(info);
	}

}