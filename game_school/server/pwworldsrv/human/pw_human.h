#ifndef _pw_human_
#define _pw_human_

#include "msg.handler.h"
#include "pw_memory.h"
#include "pw_tick_timer.h"
struct lua_State;

namespace pwconf
{
	struct SHumanStatistic;
}

namespace pwngs
{
	

	struct SSwitchStageContext;
	struct SSwitchStageParams;


	/**
	 * @class HumanMsgHandler
	 * @author sherry
	 * @date 2018年8月8日
	 * @file pw_human.h
	 * @brief msg handler
	 */
	class HumanMsgHandler : public pwworldsrv::MsgHandler
	{
	public:
		HumanMsgHandler(void* context);
	public:
		virtual bool IsAccept(int msgid);
	};

	/**
	 * @class Human
	 * @author sherry
	 * @date 2018年8月8日
	 * @file pw_human.h
	 * @brief 玩家主角色类
	 */
	class Human : public pwutils::memory::ObjectInThread<Human>
	{
	public:
		Human(int64 hid, int64 sid);
		virtual ~Human();
	public:
		/**
		 * @brief 初始化连接相关信息
		 * @param logininfo
		 * @param _vars
		 * @return
		 */
		//int Initial(SLoginToStage* logininfoOrNil,pwdist::Chunk data,pwdist::Chunk passportData,pwdist::Chunk tmpdata);
		//int InitialReconnect(SLoginToStage* logininfo);
	
		int InjectLoginNextDayEvent();
		int InjectZeroHourEvent();
		int InjectDawnHourEvent();
		int InjectHalfHourEvent();

	//public:
	//	bool IsLocalObject();
	//	bool IsFakeObject();
	//	bool IsNormalHumanObject();
	//public:
	//	bool IsIncludeDBFlags(int32 flags);

	//public:
	//	int32 GetZoneId();
	//	const char* GetAgent();

	//public:
	//	int LeaveWorldAndDiscardObject(sint64 context,const char* caller);
	//public:
	//	int ConnectionDropped();
	//	int ConnectionReconnecting();
	//	int ConnectionReconnectEnterWorld();
	//	int RetrunCreateChracterStatus(int mode = 0); // mode: 0=返回创角界面 1=返回角色列表界面
	//public:
	//	//virtual int BuildEnterMsg(pwngs::protocol::worldsrv::SCGameObjectEnter& msg);
	//
	//public:
	//	virtual int Update();
	//	virtual int UpdateMsg();
	//	virtual int UpdateMsg(pwdist::Chunk buf);
	//	virtual int UpdatePer1Sec();
	//	virtual int UpdatePer1Min();
	//	virtual int UpdatePer10Sec();
	//	virtual int SendMsg(int msgid,pwdist::Chunk buf);
	//	virtual int SendMsg(int msgid,google::protobuf::Message& msg);
	//	virtual int SendMsg(MsgCluster& cluster);
	//	virtual int SendMsg(const char* clusterbuf,size_t clusterlen);
	//	virtual int FlushCluster();

	//public:
	//	int Rename(const char* newname, bool bNotify = false);
	//	void _rpc_result_Rename(pwdist::FutureObject& future,void* context1,void* context2,int32 flags);
	//	void SendRenameMail(const char* pOldName, const char* pNewname);
	//	void SendRenameNotify(const char* pOldName, const char* pNewname);
	//public:
	//	int CheckDungeonEnterCondition(int32 baseMapId, std::string* pstrNeedMap,int* needLevel = NULL);
	//	int UnloadDatas();
	//public:
	//	bool SetEquipFashion(bool dressed);
	//	bool GetEquipFashion();
	//
	//public:
	//	int InjectQuestEvent(int32 mtype, int32 stype, int32 count = 1);
	//protected:
	//	virtual int OnBitChanged(int bit,bool value);
	//	virtual int OnBitExChanged(int bit);
	//private:
	//	int MakeVarsBuf(std::string& compressedData);
	//private:
	//	typedef std::list<pwdist::Chunk> CollectionMsgsT;
	//private:
	//	CollectionMsgsT m_lstMsgs;
	private:
		HumanMsgHandler m_objMsgHandler;
	//private:
	//	std::string m_strSocketNode;
	//	std::string m_strSocketPort;
	//	std::string m_strSocketIp;
	//	std::string m_strDeviceId;
	//	std::string m_strAdid;
	//	sint64 m_nSocketId;
	//	sint32 m_nLoginFlags;
	//private:
	//	pwutils::TickTimer m_objTestTimer;

	//	
	//private:
	//	pwconf::SHumanStatistic* m_pHumanStatistic;
	private:
		sint64 m_nPingMS;
		sint64 m_nLastPingTime;
		pwutils::TickTimer m_objPingCheckTimer;
		pwutils::TickTimer m_obj1MinTimer;
		pwutils::TickTimer m_obj10SecTimer;
		pwutils::TickTimer m_obj03SecTimer;
	//private:
	//	std::string m_sMac;
	//	std::string m_sUTF8Name;

	//private:
	//	int32 m_nFlags;
	//	int32 m_nLocalObjectType;
	//	int32 m_nTencentDomain;
	//private:
	//	sint64 m_nLoginClibTime;
	//	sint64 m_nLastFlushOnlineTime;
	//	sint64 m_nOnlineSecondsToday;
	//	sint64 m_nSwitchClibTime;
	//	bool m_bCanPickupInStage;
	//private:
	//	EHumanClientType m_eHumanClientType;

	//private:
	//	orm::Human* m_pOrmHuman;
	//	orm::Human* m_pOrmHumanGM;


	};

	extern int InitialHuman();
}

#endif //_pw_human_
