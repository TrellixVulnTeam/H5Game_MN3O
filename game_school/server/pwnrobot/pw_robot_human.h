#ifndef _pw_robot_human_
#define _pw_robot_human_

#include "pw_robot_characater.h"
#include "pw_tick_timer.h"

namespace pwngs
{
	class RobotMessageFilter;
	class RModSocket;
	class RModMagic;
	class RModLadder;

	class RobotHuman : public RobotCharacter
	{
		CLSID(RobotHuman,RobotCharacter,RCLSID_Human);
	public:
		RobotHuman(int accid,const char* account,const char* password);
		virtual ~RobotHuman();
	public:
		int CreateCharacter();
	public:
		int OnConnected();
	public:
		int DoEnterWorld();
		static void pfnEnterWorldTimer( void* t,void* p );
	public:
		virtual int Update();
		virtual int UpdatePer1Sec();
		virtual int EnterWorld();
		virtual int LeaveWorld(const char* caller);
		virtual int DiscardObject();
		virtual int SendMsg(int msgid,google::protobuf::Message& msg);
	public:
		virtual int HandleIncomingMsg(int mid,char* buf,size_t len);
	public:
		inline int32 GetAccId()
		{
			return m_nAccId;
		}

		inline RModSocket* GetModSocket()
		{
			return m_pModSocket;
		}

		inline RModMagic* GetModMagic()
		{
			return m_pModMagic;
		}

		inline RModLadder* GetModLadder()
		{
			return m_pModLadder;
		}
	public:
		virtual const char* GetUniqueName()
		{
			return m_strAccount.c_str();
		}
	public:
		typedef std::vector<RobotMessageFilter*> CollectionMessageFiltersT;
	protected:
		CollectionMessageFiltersT m_vtMessageFilters;
	protected:
		RModSocket* m_pModSocket;
		RModMagic* m_pModMagic;
		RModLadder* m_pModLadder;
	protected:
		std::string m_strAccount;
		std::string m_strPassword;
	protected:
		int32 m_nAccId;
		int64 m_nMapId;	
		pwutils::TickTimer m_objPingTimer;
		pwutils::TickTimer m_objTimeCheckTimer;
	};
}

#endif // _pw_robot_human_