#include "pw_robot_module_ladder.h"
#include <cassert>
#include "pw_ngs_def.h"
#include "pw_byte_order.h"
#include "pw_robot_human.h"
#include "pw_robot_thread.h"
#include "pw_robot_module_socket.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "../pwaccsrv/msg/msg.def.h"
#include "../pwworldsrv/msg/msg.def.h"
#include "../pwworldsrv/msg/worldsrv.pb.h"
#include "../pwaccsrv/msg/accsrv.pb.h"

namespace pwngs
{
	using namespace pwngs::protocol::accsrv;
	using namespace pwngs::protocol::worldsrv;

	RModLadder::RModLadder( RobotHuman* human )
		: RobotModule(human)
		, m_nSeq(629)
	{
		m_objBuffer.initial(pwngs::cst_max_msg_size);
		m_objSendBuffer.initial(pwngs::cst_max_msg_size);
		m_nLadderPort = 0;
		m_nStatus = STATUS_CLOSED;
		m_nLadderServerIndex = -1;
		m_nLadderCharacterId = -1;
		m_nStartCtime = 0;
	}

	RModLadder::~RModLadder()
	{
		GetCurrentReactor()->Del(this);
	}

	int RModLadder::SendMsg( int mid,google::protobuf::Message& msg )
	{
		char buf[40960];
		MsgHeaderEx* header = (MsgHeaderEx*)buf;
		header->mid = mid;
		header->len = msg.ByteSize() + sizeof(MsgHeaderEx);

		++m_nSeq;
		if (m_nSeq > 999)
			m_nSeq = 629;
		int maskSeq = (m_nSeq << 5) ^ 0xAE8B;
		header->seq = maskSeq;

		assert(sizeof(buf) >= header->len);
		msg.SerializeToArray(&buf[sizeof(MsgHeaderEx)], header->len - sizeof(MsgHeaderEx));

		int len = header->len;

		pwutils::Convert<uint32>::ToNetworkOrder(header->mid);
		pwutils::Convert<uint32>::ToNetworkOrder(header->len);
		pwutils::Convert<uint32>::ToNetworkOrder(header->seq);

		return this->Send(buf,len);
	}

	int RModLadder::HandleIncoming()
	{
		while(m_objBuffer.length() > 0)
		{
			uint32 len = 0;

			size_t peeked = (size_t)m_objBuffer.peek((char*)&len,sizeof(uint32));

			if(peeked < sizeof(uint32))
				return -1;

			pwutils::Convert<uint32>::ToHostOrder(len);

			// 错误的包长,直接断开
			if(len > pwngs::cst_max_msg_size || len <= 0)
			{
				return -1;
			}

			if(m_objBuffer.length() < (long)len)
				return 1;

			char buf[pwngs::cst_max_msg_size];
			m_objBuffer.get(buf,len);

			// 将长度和消息id转化为本机字节顺序
			pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf;
			pwutils::Convert<uint32>::ToHostOrder(header->len);
			pwutils::Convert<uint32>::ToHostOrder(header->mid);

			HandleIncomingMsg(buf,len);
		}
		return 0;
	}

	int RModLadder::HandleIncomingMsg( char* buf,size_t len )
	{
		pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf;
		return this->HandleLadderMessage(header->mid,&buf[sizeof(MsgHeader)],len - sizeof(MsgHeader));
	}

	int RModLadder::OnDataIncoming( char* buf,int32 len  )
	{
		if(m_objBuffer.space() > len)
		{
			m_objBuffer.put(buf,len);
			HandleIncoming();
		}
		else
		{
			pwasserte(false && "buffer full.");
			this->m_objBuffer.skip(m_objBuffer.length());
		}
		return 0;
	}

	int RModLadder::OnClose()
	{
		std::cout << __FUNCTION__ << " h:" << GetHuman()->GetUniqueName() << " Closed" << std::endl;
		return pwutils::SocketClient::OnClose();
	}

	// 来自RModSocket
	int RModLadder::HandleMessage( int msgid,char* buf,size_t len )
	{
		switch(msgid)
		{
		case msgid_SC_CrossServer_QueryConfigsResult:
			{
				SC_CrossServer_QueryConfigsResult msg;
				msg.ParseFromArray(buf,len);

				if(msg.configs_size() > 0)
				{
					SCrossServerConfig* config = msg.mutable_configs(0);
					m_sLadderHost = config->addr();
					m_nLadderPort = config->port();
				}
			}
			break;
		case msgid_SC_CrossServer_Start:
			{
				m_nLadderServerIndex = 0;
// 				m_strLadderAccount = msg.login_acc();
// 				m_strLadderPassword = msg.login_pswd();
				SetStatus(STATUS_LOGIN);

				this->Startup();
			}
			break;
		}
		return 0;
	}

	int RModLadder::HandleLadderMessage( int msgid,char* buf,size_t len )
	{
		switch(msgid)
		{		
		case msgid_SCLoginResult:
			{
				SCLoginResult msg;
				msg.ParseFromArray(buf,len);

				if(msg.result() != 0)
				{
					std::cout << "Ladder msgid_SCLoginResult striderror=" << msg.result() << std::endl;
					SetStatus(STATUS_ERROR);
				}
				else
				{
					SetStatus(STATUS_GATE);

					CSLoginGate sendmsg;
					this->SendMsg(msgid_CSLoginGate,sendmsg);
				}
			}
			break;
		case msgid_SCLoginGate:
			{
				CSQueryCharacters msg;
				this->SendMsg(msgid_CSQueryCharacters,msg);
			}
			break;
		case msgid_SCQueryCharacters:
			{
				SCQueryCharacters msg;
				msg.ParseFromArray(buf,len);

				if(msg.characters_size() <= 0)
				{
					std::cout << "Ladder msgid_SCQueryCharacters no characters " << std::endl;
					SetStatus(STATUS_ERROR);
				}
				else
				{
					CSCharacterLogin sendmsg;
					sendmsg.set_cid(msg.characters(0).id());
					this->SendMsg(msgid_CSCharacterLogin,sendmsg);
					this->m_nLadderCharacterId = msg.characters(0).id();
				}
			}
			break;
		case msgid_SCCharacterLogin:
			{
				SCCharacterLogin msg;
				msg.ParseFromArray(buf,len);

				if(msg.result() != 0)
				{
					std::cout << "Ladder msgid_SCCharacterLogin failed:" << msg.result() << std::endl;
					SetStatus(STATUS_ERROR);
				}
				else
				{
					SetStatus(STATUS_ENTERWORLD);
					{
						CSCharacterEnterWorld sendmsg;
						sendmsg.set_id(m_nLadderCharacterId);
						this->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);
					}

					SetStatus(STATUS_COMPLETED);
				}
			}
			break;		
		case msgid_SCTransport:
			{
				SCTransport msg;
				msg.ParseFromArray(buf,len);

				int seconds = pwutils::random(12,25);

				std::cout << "Ladder msgid_SCTransport idscene=" << msg.idscene() << " iddungeon=" << msg.iddungeon() 
					<< " delay seconds:" << seconds << " acc=" << m_pOwner->GetUniqueName() << std::endl;


				pwutils::Timer::TRef ref;
				GetCurrentRobotThread()->GetTimerQueue()->CreateTimer(&ref,pwutils::time::Second(seconds),0,&RModLadder::pfnEnterWorldTimer,NULL);
				ref->AddDependsPointer<std::string>(new std::string(m_pOwner->GetUniqueName()));

// 				CSCharacterEnterWorld sendmsg;
// 				sendmsg.set_id(m_nLadderCharacterId);
// 				this->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);
			}
			break;
		default:
			{
				// std::cout << __FUNCTION__ << " h:" << GetHuman()->GetUniqueName() << " mid:" << msgid << std::endl;
			}
			break;
		}
		return 0;
	}

	int RModLadder::Startup()
	{
		if(m_nStatus != STATUS_CLOSED)
			return -1;

		SetStatus(STATUS_LOGIN);

		this->Connect(m_sLadderHost.c_str(),m_nLadderPort);
		GetCurrentReactor()->Add(this,pwutils::SocketReactor::MASK_DEFAULT);

		return 0;
	}

	int RModLadder::OnConnected()
	{
		if(m_nStatus == STATUS_LOGIN)
		{
			CSLogin msg;
			msg.set_name(m_strLadderAccount);
			msg.set_pswd(m_strLadderPassword);
			msg.set_token(m_strLadderPassword);
			msg.set_major_version(MajorVersion);
			msg.set_minor_version(MinorVersion);
			this->SendMsg(msgid_CSLogin,msg);
		}
		else
		{
			std::cout << __FUNCTION__ << " invalid status:" << m_nStatus << std::endl;
		}
		return SocketClient::OnConnected();
	}

	int RModLadder::Update()
	{
		this->FlushSendBuffer();

		if(m_nStatus == STATUS_ERROR)
		{
			SetStatus(STATUS_CLOSED);
			this->Close();
		}
		else if(m_nStatus != STATUS_CLOSED && m_nStatus != STATUS_COMPLETED)
		{
			int64 curr = pwutils::time::clib_time();
#ifdef _DEBUG
			if((curr - m_nStartCtime) > 50)
#else
			if((curr - m_nStartCtime) > 10)
#endif
			{
				std::cout << __FUNCTION__ << " ladder timeout,last_status=" << m_nStatus << std::endl;
				this->Cleanup();
			}
		}
		return 0;
	}

	int RModLadder::Cleanup()
	{
		SetStatus(STATUS_CLOSED);
		this->Close();
		this->m_objBuffer.skip(m_objBuffer.length());
		this->m_nStartCtime = 0;
		return 0;
	}

	int RModLadder::OnEnterWorld()
	{
		CS_CrossServer_QueryConfigs msg;
		GetHuman()->GetModSocket()->SendMsg(msgid_CS_CrossServer_QueryConfigs,msg);
		return 0;
	}

	int RModLadder::SetStatus( int status )
	{
		// std::cout << "ladder:" << GetHuman()->GetUniqueName() << " newstatus=" << status << " oldstatus=" << m_nStatus << std::endl;
		m_nStatus = status;

		if(status == STATUS_COMPLETED)
		{
			std::cout << GetHuman()->GetUniqueName() << " ladder completed" << std::endl;
		}
		return 0;
	}

	void RModLadder::pfnEnterWorldTimer( void* t,void* p )
	{
		pwutils::Timer* tt = (pwutils::Timer*)t;

		std::string& name = *tt->GetDependsPointer<std::string>(0);

		RobotHuman* h = (RobotHuman*)GetCurrentRobotThread()->Get(name);
		if(h != NULL)
		{
			h->GetModLadder()->DoEnterWorld();
		}
	}

	int RModLadder::DoEnterWorld()
	{
		std::cout << m_pOwner->GetUniqueName() << " Ladder::DoEnterWorld" << std::endl;

		CSCharacterEnterWorld sendmsg;
		sendmsg.set_id(m_nLadderCharacterId);
		this->SendMsg(msgid_CSCharacterEnterWorld,sendmsg);
		return 0;
	}

}