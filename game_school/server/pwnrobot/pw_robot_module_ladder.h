#ifndef _pw_robot_module_ladder_
#define _pw_robot_module_ladder_

#include "pw_def.h"
#include <google/protobuf/message.h>
#include "pw_circle_buffer.h"
#include "pw_robot_module.h"
#include "pw_socket_client.h"
#include "pw_robot_message_filter.h"

namespace pwngs
{
	class RobotHuman;

	class RModLadder : public RobotModule,public pwutils::SocketClient,public RobotMessageFilter
	{
	public:
		enum
		{
			STATUS_CLOSED,
			STATUS_LOGIN,
			STATUS_GATE,
			STATUS_ENTERWORLD,		
			STATUS_COMPLETED,
			STATUS_ERROR,
		};
	public:
		RModLadder(RobotHuman* human);
		virtual ~RModLadder();
	public:
		int SendMsg(int mid,google::protobuf::Message& msg);
	public:
		inline int IsOK()
		{
			return m_nStatus == STATUS_COMPLETED;
		}
	public:
		inline RobotHuman* GetHuman()
		{
			return (RobotHuman*)m_pOwner;
		}
	public:
		int Startup();
		int Cleanup();
	public:
		int Update();
	public:
		virtual int OnClose();
		virtual int OnConnected();
	public:
		int OnDataIncoming(char* buf,int32 len );
	public:
		int HandleIncoming();
		int HandleIncomingMsg(char* buf,size_t len);
	public:
		virtual int OnEnterWorld();
	public:
		int HandleMessage(int msgid,char* buf,size_t len);
		int HandleLadderMessage(int msgid,char* buf,size_t len);
	public:
		static void pfnEnterWorldTimer(void* t,void* p);
	public:
		int SetStatus(int status);
		int DoEnterWorld();
	public:
		pwutils::CircleBuffer m_objBuffer;
	public:
		std::string m_sLadderHost;
		int32 m_nLadderPort;
	public:
		int32 m_nStatus;
		int64 m_nLadderCharacterId;
		int64 m_nStartCtime;
	private:
		int32 m_nLadderServerIndex;
		std::string m_strLadderAccount;
		std::string m_strLadderPassword;
		int32 m_nSeq;
	};


}

#endif // _pw_robot_module_ladder_