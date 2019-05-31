#include "pw_robot_human.h"
#include "pw_robot_module_socket.h"
#include "pw_robot_thread.h"
#include "pw_robot_message_filter.h"
#include "pw_robot_module_motion.h"
#include "pw_robot_module_magic.h"
#include "pw_robot_module_ladder.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "../pwaccsrv/msg/msg.def.h"
#include "../pwaccsrv/msg/accsrv.pb.h"

#include "../pwworldsrv/msg/msg.def.h"
#include "../pwworldsrv/msg/worldsrv.pb.h"

namespace pwngs
{
	RobotHuman::RobotHuman(int accid,const char* account,const char* password)
	{
		m_nId = -1;
		m_nAccId = accid;
		m_strAccount = account;
		m_strPassword = password;
		m_pModSocket = new RModSocket(this);
		m_pModSocket->doref();
		m_pModMagic = new RModMagic(this);
		m_pModLadder = new RModLadder(this);

		m_vtMessageFilters.push_back(m_pModMotion);
		m_vtMessageFilters.push_back(m_pModMagic);
		m_vtMessageFilters.push_back(m_pModLadder);
		m_objPingTimer.Startup(pwutils::time::Second(1));
		m_objTimeCheckTimer.Startup(pwutils::time::Second(10));
	}

	RobotHuman::~RobotHuman()
	{
		_safe_delete(m_pModSocket);
		_safe_delete(m_pModMagic);
		_safe_delete(m_pModLadder);
	}

	int RobotHuman::HandleIncomingMsg( int mid,char* buf,size_t len )
	{
		using namespace pwngs::protocol::accsrv;
		using namespace pwngs::protocol::worldsrv;

		switch(mid)
		{
		case msgid_SCCharacterKick:
			{
				this->DiscardObject();
				print_response("%s kicked.",m_strAccount.c_str());
			}
			break;
		case msgid_SCLoginResult:
			{
				SCLoginResult msg;
				pwassertf(msg.ParseFromArray(buf,len));

				if(msg.result() != 0)
				{
					this->LeaveWorld("msgid_SCLoginResult");
				}
				else
				{
					CSLoginGate msg;
					this->m_pModSocket->SendMsg(msgid_CSLoginGate,msg);
				}
			}
			break;
		case msgid_SCLoginGate:
			{
				SCLoginGate msg;
				pwassertf(msg.ParseFromArray(buf,len));
				if(msg.result() == 0)
				{
					CSQueryCharacters msg;
					this->m_pModSocket->SendMsg(msgid_CSQueryCharacters,msg);

					//std::cout << this->GetUniqueName() << " GateOK" << std::endl;
				}
				else
				{
					//std::cout << this->GetUniqueName() << " GatePosition:" << msg.result() << std::endl;
				}
			}
			break;
		case msgid_SCQueryCharacters:
			{
				SCQueryCharacters msg;
				pwassertf(msg.ParseFromArray(buf,len));
				if(msg.characters_size() > 0 && !msg.characters(0).newbie())
				{
					CSCharacterLogin sendmsg;
					sendmsg.set_cid(msg.characters(0).id());
					this->m_pModSocket->SendMsg(msgid_CSCharacterLogin,sendmsg);
				}
				else
				{
					CreateCharacter();
				}
			}
			break;
		case msgid_SCCharacterCreate:
			{
				SCCharacterCreate msg;
				pwassertf(msg.ParseFromArray(buf,len));

				if(msg.result() != 0)
				{
					print_response("%s create character failed:%d",m_strAccount.c_str(),msg.result());
					CreateCharacter();
				}
				else
				{
					CSCharacterLogin sendmsg;
					sendmsg.set_cid(msg.character().id());
					this->m_pModSocket->SendMsg(msgid_CSCharacterLogin,sendmsg);
				}
			}
			break;
		case msgid_SCReturnCreateCharacterUI:
			{
				CreateCharacter();
			}
			break;
		case msgid_SCCharacterLogin:
			{
				SCCharacterLogin msg;
				pwassertf(msg.ParseFromArray(buf,len));

				m_nId = msg.character().id();
				m_nMapId = msg.scene_info().id();

				m_vLoc = G3D::Vector3(msg.position().x(),msg.position().y(),msg.position().z());
				m_vDir = G3D::Vector3(msg.orientation().x(),msg.orientation().y(),msg.orientation().z());

				pwutils::Timer::TRef ref;
				GetCurrentRobotThread()->GetTimerQueue()->CreateTimer(&ref,pwutils::time::Second(2),0,&RobotHuman::pfnEnterWorldTimer,NULL);
				ref->AddDependsPointer<std::string>(new std::string(this->GetUniqueName()));

// 				CSCharacterEnterWorld sendmsg;
// 				sendmsg.set_id(m_nId);
// 				this->m_pModSocket->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);
// 
// 				this->EnterWorld();
			}
			break;
		case msgid_SCTransport:
			{
				SCTransport msg;
				pwassertf(msg.ParseFromArray(buf,len));

				this->LeaveWorld("msgid_SCTransport");
				m_nMapId = msg.idscene();
				m_vLoc = G3D::Vector3(msg.pos().x(),msg.pos().y(),msg.pos().z());
				m_vDir = G3D::Vector3(msg.ori().x(),msg.ori().y(),msg.ori().z());
// 				this->EnterWorld();

				pwutils::Timer::TRef ref;
				GetCurrentRobotThread()->GetTimerQueue()->CreateTimer(&ref,pwutils::time::Second(2),0,&RobotHuman::pfnEnterWorldTimer,NULL);
				ref->AddDependsPointer<std::string>(new std::string(this->GetUniqueName()));

// 				CSCharacterEnterWorld sendmsg;
// 				sendmsg.set_id(m_nId);
// 				this->m_pModSocket->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);

			}
			break;
		case msgid_SC_CrossServer_Close:
			{
				std::cout << GetUniqueName() << " msgid_SC_CrossServer_Close" << std::endl;
				m_pModLadder->Cleanup();
			}
			break;
		default:
			{
				for(size_t i = 0; i < m_vtMessageFilters.size(); ++i)
				{
					m_vtMessageFilters[i]->HandleMessage(mid,buf,len);
				}
			}
			break;
		}
		

		return 0;
	}

	int RobotHuman::DoEnterWorld()
	{
		using namespace pwngs::protocol::accsrv;
		using namespace pwngs::protocol::worldsrv;

		CSCharacterEnterWorld sendmsg;
		sendmsg.set_id(m_nId);
		this->m_pModSocket->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);

		return this->EnterWorld();
	}

	void RobotHuman::pfnEnterWorldTimer( void* t,void* p )
	{
		pwutils::Timer* tt = (pwutils::Timer*)t;

		std::string& name = *tt->GetDependsPointer<std::string>(0);

		RobotHuman* h = (RobotHuman*)GetCurrentRobotThread()->Get(name);
		if(h != NULL)
		{
			h->DoEnterWorld();
		}
	}

	int RobotHuman::OnConnected()
	{
		pwngs::protocol::accsrv::CSLoginNew msg;
		msg.set_type(pwngs::protocol::accsrv::LoginType_UserPswd);
		msg.mutable_loginuserpswd()->set_name(m_strAccount);
		msg.mutable_loginuserpswd()->set_pswd(m_strPassword);
		msg.mutable_logininfo()->set_major_version(pwngs::protocol::accsrv::MajorVersion);
		msg.mutable_logininfo()->set_minor_version(pwngs::protocol::accsrv::MinorVersion);
		return m_pModSocket->SendMsg(pwngs::protocol::accsrv::msgid_CSLoginNew,msg);
	}

	int RobotHuman::EnterWorld()
	{
		if(IsBitSet(ROBOT_BITEX_INWORLD))
			return -1;

		SetBit(ROBOT_BITEX_INWORLD,true);

		for(size_t i = 0; i < m_vtMessageFilters.size(); ++i)
		{
			m_vtMessageFilters[i]->OnEnterWorld();
		}

		print_response("%s enterworld. %d",m_strAccount.c_str(),(int)m_nMapId);
		return RobotCharacter::EnterWorld();
	}

	int RobotHuman::LeaveWorld(const char* caller)
	{
		if(!IsBitSet(ROBOT_BITEX_INWORLD))
			return -1;
		SetBit(ROBOT_BITEX_INWORLD,false);

		print_response("%s leaveworld. caller=%s",m_strAccount.c_str(),caller);
		return RobotCharacter::LeaveWorld(caller);
	}

	int RobotHuman::CreateCharacter()
	{
		using namespace pwngs::protocol::accsrv;
		using namespace pwngs::protocol::worldsrv;

		char buf[100] = "";
		int64 r = pwutils::random() % 7777777;
		pwutils::itoa(buf,r);

		std::string name = m_strAccount;
		name.append(buf);

		print_response("%s create character",m_strAccount.c_str());

		CSCharacterCreate sendmsg;
		sendmsg.set_name(name);
		sendmsg.set_sex(0);
		sendmsg.set_profession(2);
		//sendmsg.set_profession(pwutils::random(1,4));

		switch(sendmsg.profession())
		{
		case 1: // Õ½
			sendmsg.set_sex(0);
			break;
		case 2: // ¼ý
			sendmsg.set_sex(1);
			break;
		case 3: // ·¨
			sendmsg.set_sex(0);
			break;
		}
		return this->m_pModSocket->SendMsg(msgid_CSCharacterCreate,sendmsg);
	}

	int RobotHuman::Update()
	{
		if(this->IsBitSet(ROBOT_BITEX_INWORLD))
		{
			m_pModMagic->Update();
			m_pModLadder->Update();
		}

		m_pModSocket->FlushSendBuffer();

		return RobotCharacter::Update();
	}

	int RobotHuman::UpdatePer1Sec()
	{
		if(m_objPingTimer.IsPeriodExpired(GetCurrentRobotThread()->GetCurrentTick()))
		{
			pwngs::protocol::worldsrv::CSPing sendmsg;
			sendmsg.set_time(0);
			this->SendMsg(pwngs::protocol::worldsrv::msgid_CSPing,sendmsg);

			if(this->m_pModLadder->IsOK())
			{
				m_pModLadder->SendMsg(pwngs::protocol::worldsrv::msgid_CSPing,sendmsg);
			}
		}
		if(m_objTimeCheckTimer.IsPeriodExpired(GetCurrentRobotThread()->GetCurrentTick()))
		{
			pwngs::protocol::worldsrv::CSTimeCheck sendmsg;
			sendmsg.set_data(0);
			this->SendMsg(pwngs::protocol::worldsrv::msgid_CSTimeCheck,sendmsg);

			if(this->m_pModLadder->IsOK())
			{
				m_pModLadder->SendMsg(pwngs::protocol::worldsrv::msgid_CSTimeCheck,sendmsg);
			}
		}
		return RobotCharacter::UpdatePer1Sec();
	}

	int RobotHuman::DiscardObject()
	{
		return RobotCharacter::DiscardObject();
	}

	int RobotHuman::SendMsg( int msgid,google::protobuf::Message& msg )
	{
		return m_pModSocket->SendMsg(msgid,msg);
	}

}
