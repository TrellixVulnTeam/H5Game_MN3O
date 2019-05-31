#include "pw_robot_module_magic.h"
#include "../pwworldsrv/msg/msg.def.h"
#include "../pwworldsrv/msg/worldsrv.pb.h"
#include "pw_time.h"
#include "pw_robot_characater.h"
#include "pw_robot_thread.h"
#include "pw_utils.h"

namespace pwngs
{
	RModMagic::RModMagic( RobotCharacter* obj )
		: RobotModule(obj)
	{

	}

	int RModMagic::HandleMessage( int msgid,char* buf,size_t len )
	{
		using namespace pwngs::protocol::worldsrv;

		switch(msgid)
		{
		case msgid_SCMagicTypeOper:
			{
				SCMagicTypeOper msg;
				pwassertf(msg.ParseFromArray(buf,len));
				m_vMagics.clear();

				for(int i = 0; i < msg.magics_size(); ++i)
				{
					const pwngs::protocol::worldsrv::SMagicType& r = msg.magics(i);
					SMagicInformation info;
					info.id = r.id();
					info.loc = r.loc();
					info.cd = 0;
					m_vMagics.push_back(info);
				}
			}
			break;
		case msgid_SCMagicCooldown:
			{
				SCMagicCooldown msg;
				pwassertf(msg.ParseFromArray(buf,len));

				int64 tick = GetCurrentRobotThread()->GetCurrentTick();

				for(size_t i = 0; i < m_vMagics.size(); ++i)
				{
					SMagicInformation& r = m_vMagics[i];
					if(r.id == msg.magic_type())
					{
						r.cd = tick + pwutils::time::Msec(msg.cooldown_ms());
						break;
					}
				}
			}
			break;
		}
		return 0;
	}

	int RModMagic::OnEnterWorld()
	{
		pwngs::protocol::worldsrv::CSMagicTypeOper sendmsg;
		sendmsg.set_oper((pwngs::protocol::worldsrv::EMagicTypeOper)0);
		sendmsg.set_data(0);
		return m_pOwner->SendMsg(pwngs::protocol::worldsrv::msgid_CSMagicTypeOper,sendmsg);
	}

	int RModMagic::Update()
	{
		int64 tick = GetCurrentRobotThread()->GetCurrentTick();

		if(m_objCasterTimer.IsStarted() && m_objCasterTimer.IsPeriodExpired(tick))
		{
			this->RandomCast();
		}
		return 0;
	}

	int RModMagic::StartAutomaticCaster()
	{
		m_objCasterTimer.Startup(pwutils::time::Second(3));
		return 0;
	}

	int RModMagic::CleanAutomaticCaster()
	{
		m_objCasterTimer.Cleanup();
		return 0;
	}

	int RModMagic::RandomCast()
	{
		int32 id = 0;
		int64 tick = GetCurrentRobotThread()->GetCurrentTick();

		if(m_vMagics.size() <= 0)
			return 0;

		for(int i = 0; i < 1000; ++i)
		{
			int n = pwutils::random(0,m_vMagics.size());
			if(n < (int)m_vMagics.size())
			{
				if(m_vMagics[n].cd < tick)
				{
					id = m_vMagics[n].id;
					break;
				}
			}
		}

		{
			pwngs::protocol::worldsrv::CSInterruptCast sendmsg;
			sendmsg.set_caster(m_pOwner->GetID());
			m_pOwner->SendMsg(pwngs::protocol::worldsrv::msgid_CSInterruptCast,sendmsg);
		}

		if(id > 0)
		{
			G3D::Vector3 dir(pwutils::random(0.0f,1.0f),0.0f,pwutils::random(0.0f,1.0f));
			dir = dir.directionOrZero();
			G3D::Vector3 pos = m_pOwner->GetPosition() + dir * 2.0f;

			pwngs::protocol::worldsrv::CSCastMagic sendmsg;
			sendmsg.set_magic_type(id);
			sendmsg.set_param1(0);
			sendmsg.set_param2(0);
			sendmsg.mutable_cast_target()->set_target_type(0);
			sendmsg.mutable_cast_target()->mutable_target_position()->set_x(pos.x);
			sendmsg.mutable_cast_target()->mutable_target_position()->set_y(pos.y);
			sendmsg.mutable_cast_target()->mutable_target_position()->set_z(pos.z);
			return m_pOwner->SendMsg(pwngs::protocol::worldsrv::msgid_CSCastMagic,sendmsg);
		}
		return 0;
	}

}


