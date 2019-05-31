#include "pw_robot_module_motion.h"
#include "pw_robot_human.h"
#include "../pwworldsrv/msg/msg.def.h"
#include "../pwworldsrv/msg/worldsrv.pb.h"
#include "pw_robot_motion.h"

namespace pwngs
{
	RModMotion::RModMotion( RobotCharacter* human )
		: RobotModule(human)
		, m_pMotionObject(NULL)
	{

	}

	RModMotion::~RModMotion()
	{
		_safe_delete(m_pMotionObject);
	}

	int RModMotion::HandleMessage( int msgid,char* buf,size_t len )
	{
		using namespace pwngs::protocol::worldsrv;

		switch(msgid)
		{
		case msgid_SCDebugFindPath:
			{
				SCDebugFindPath msg;
				pwassertf(msg.ParseFromArray(buf,len));

				if(msg.path_size() > 0)
				{
					std::vector<G3D::Vector3> nodes;
					for(int i = 0; i < msg.path_size(); ++i)
					{
						G3D::Vector3 pos(msg.path(i).x(),msg.path(i).y(),msg.path(i).z());
						nodes.push_back(pos);
					}
					this->Stop();

					m_pMotionObject = new RobotWaypointMotionObject(m_pOwner,nodes);
					m_pMotionObject->Startup();
				}
			}
			break;
		case msgid_SCStartForward:
			break;
		case msgid_SCChangeOrientation:
			break;
		case msgid_SCCleanForward:
			{
				SCCleanForward msg;
				pwassertf(msg.ParseFromArray(buf,len));

				if(msg.id() == m_pOwner->GetID())
				{
					this->Stop();

					G3D::Vector3 loc(msg.position().x(),msg.position().y(),msg.position().z());
					G3D::Vector3 dir(msg.orientation().x(),msg.orientation().y(),msg.orientation().z());

					m_pOwner->ChangePosition(loc);
					m_pOwner->ChangeOrientation(dir);
				}
			}
			break;
		}
		return 0;
	}

	int RModMotion::DoMotionBegan()
	{
		using namespace pwngs::protocol::worldsrv;

		pwassertf(m_pMotionObject);

		if(m_pOwner->IsBitSet(ROBOT_BITEX_MOTION))
			return DoMotionOrientation();

		m_pOwner->SetBit(ROBOT_BITEX_MOTION,true);

		CSStartForward msg;
		G3D::Vector3 pos = m_pOwner->GetPosition();
		G3D::Vector3 dir = m_pOwner->GetOrientation();
		msg.mutable_position()->set_x(pos.x);
		msg.mutable_position()->set_y(pos.y);
		msg.mutable_position()->set_z(pos.z);
		msg.mutable_orientation()->set_x(dir.x);
		msg.mutable_orientation()->set_y(dir.y);
		msg.mutable_orientation()->set_z(dir.z);

		RMotionInfo info;
		m_pMotionObject->OnGetMotionInfo(info);

		msg.mutable_motion()->set_motion_type(info.nMotionType);
		msg.mutable_motion()->mutable_motion_position()->set_x(info.vMotionPosition.x);
		msg.mutable_motion()->mutable_motion_position()->set_y(info.vMotionPosition.y);
		msg.mutable_motion()->mutable_motion_position()->set_z(info.vMotionPosition.z);

		return m_pOwner->SendMsg(msgid_CSStartForward,msg);
	}

	int RModMotion::DoMotionEnded()
	{
		using namespace pwngs::protocol::worldsrv;

		pwassertf(m_pMotionObject);

		if(m_pOwner->IsBitSet(ROBOT_BITEX_MOTION))
		{
			m_pOwner->SetBit(ROBOT_BITEX_MOTION,false);

			CSCleanForward msg;
			G3D::Vector3 pos = m_pOwner->GetPosition();
			G3D::Vector3 dir = m_pOwner->GetOrientation();
			msg.mutable_position()->set_x(pos.x);
			msg.mutable_position()->set_y(pos.y);
			msg.mutable_position()->set_z(pos.z);
			msg.mutable_orientation()->set_x(dir.x);
			msg.mutable_orientation()->set_y(dir.y);
			msg.mutable_orientation()->set_z(dir.z);

			return m_pOwner->SendMsg(msgid_CSCleanForward,msg);
		}
		return -1;
	}

	int RModMotion::DoMotionOrientation()
	{
		using namespace pwngs::protocol::worldsrv;
		pwassertf(m_pMotionObject);

		CSChangeOrientation msg;
		G3D::Vector3 pos = m_pOwner->GetPosition();
		G3D::Vector3 dir = m_pOwner->GetOrientation();
		msg.mutable_position()->set_x(pos.x);
		msg.mutable_position()->set_y(pos.y);
		msg.mutable_position()->set_z(pos.z);
		msg.mutable_orientation()->set_x(dir.x);
		msg.mutable_orientation()->set_y(dir.y);
		msg.mutable_orientation()->set_z(dir.z);

		RMotionInfo info;
		m_pMotionObject->OnGetMotionInfo(info);

		msg.mutable_motion()->set_motion_type(info.nMotionType);
		msg.mutable_motion()->mutable_motion_position()->set_x(info.vMotionPosition.x);
		msg.mutable_motion()->mutable_motion_position()->set_y(info.vMotionPosition.y);
		msg.mutable_motion()->mutable_motion_position()->set_z(info.vMotionPosition.z);

		return m_pOwner->SendMsg(msgid_CSChangeOrientation,msg);
	}

	int RModMotion::Update()
	{
		if(m_pMotionObject != NULL)
		{
			m_pMotionObject->Update();

			if(m_pMotionObject->IsFinished())
			{
				m_pMotionObject->Cleanup();
				_safe_delete(m_pMotionObject);
			}
		}

		return 0;
	}

	int RModMotion::MovePosition( const G3D::Vector3& pos )
	{
		Stop();

		m_pMotionObject = new RobotPositionMotionObject(m_pOwner,pos);
		m_pMotionObject->Startup();

		return 0;
	}

	int RModMotion::MoveWaypoint( const G3D::Vector3& pos )
	{
		this->Stop();

		using namespace pwngs::protocol::worldsrv;

		G3D::Vector3 v = m_pOwner->GetPosition();

		CSDebugFindPath sendmsg;
		sendmsg.mutable_start()->set_x(v.x);
		sendmsg.mutable_start()->set_y(v.y);
		sendmsg.mutable_start()->set_z(v.z);
		sendmsg.mutable_target()->set_x(pos.x);
		sendmsg.mutable_target()->set_y(pos.y);
		sendmsg.mutable_target()->set_z(pos.z);
		sendmsg.set_context(0);
		return m_pOwner->SendMsg(msgid_CSDebugFindPath,sendmsg);
	}

	int RModMotion::MoveWaypointRandom( const G3D::Vector3& pos,float dist )
	{
		this->Stop();

		using namespace pwngs::protocol::worldsrv;

		G3D::Vector3 v = m_pOwner->GetPosition();

		CSDebugRandomPath sendmsg;
		sendmsg.mutable_start()->set_x(v.x);
		sendmsg.mutable_start()->set_y(v.y);
		sendmsg.mutable_start()->set_z(v.z);
		sendmsg.mutable_target()->set_x(pos.x);
		sendmsg.mutable_target()->set_y(pos.y);
		sendmsg.mutable_target()->set_z(pos.z);
		sendmsg.set_random_dist(dist);
		sendmsg.set_context(0);
		return m_pOwner->SendMsg(msgid_CSDebugRandomPath,sendmsg);
	}

	int RModMotion::Stop()
	{
		if(m_pMotionObject != NULL)
		{
			m_pMotionObject->Cleanup();
			_safe_delete(m_pMotionObject);
		}
		return 0;
	}

}