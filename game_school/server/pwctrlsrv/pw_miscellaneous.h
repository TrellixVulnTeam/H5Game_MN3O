#ifndef _pw_miscellaneous_
#define _pw_miscellaneous_

#include "pwdist_port_generic.h"
#include "kvorm/pw_orm_globalcharge.h"
#include "kvorm/pw_orm_ghotfixcommand.h"
#include "kvorm/pw_orm_globaldailyinfolianyun.h"

namespace pwngs
{
	class SImplStageMgr;

	class Miscellaneous : public pwdist::ICallableObject
	{
		friend class SImplStageMgr;
	public:
		Miscellaneous();
		virtual ~Miscellaneous();
	public:
		virtual int64 GetID();
	public:
		static int InitialRpcs(pwdist::Port* port);
	public:
		void OnCharged(float rmb,float pubacct_rmb = 0.0f);
	public:
		const orm::GlobalCharge* GetCurrentDailyCharge();
	public:
		orm::GlobalDailyInfoLianYun* GetDailyInfo(int32 date);
		orm::GlobalDailyInfoLianYun* MutableCurrentDailyInfo();
	public:
		void Pull();
		void UpdatePer3Sec();
		void UpdateGlobalCharge();
		void BroadcastGlobalChargeEvent(int32 flags);
		void BroadcastGlobalSpendEvent(int32 flags);
		void HandleHumanCreated(pwdist::Chunk hinfo);

		struct SNewUserInfo
		{
			int32 hhmm;
			int32 count;

			bool operator<(const SNewUserInfo& r) const
			{
				return hhmm > r.hhmm;
			}
		};

		void RetriveNewUserCounters(int32 date,std::vector<SNewUserInfo>& counters);
	public:
		void _rpc_call_GSpendNotify(int32 event,int64 hid,int32 reason,int64 gold);
	public:
		/**
		 * @brief 使用命令建一个热补丁
		 * @param text
		 * @param invoke 是否立刻执行
		 */
		void CreateHotfixCommand(const char* text,bool invoke = false);

		/**
		 * @brief 获取热补丁列表
		 * @param cmds
		 */
		void RetriveHotfixCommands(std::vector<std::string>& cmds);
		/**
		 * @brief 删除所有已经保存的热补丁
		 */
		void RemoveAllHotfixCommands();
	private:
		/**
		 * @brief 执行所有热补丁,如果该是线程还没执行过
		 * @param threadName 地图线程组合名
		 * @param node 地图线程node
		 * @param port 地图线程port
		 */
		void InvokeHotfixCommandsIfNeed(const std::string& threadName,const char* node,const char* port);
	private:
		typedef std::deque<orm::GlobalCharge*> CollectionChargesT;
		typedef std::deque<orm::GHotfixCommand*> CollectionHotfixCommandsT;
		typedef std_unordered_set<std::string> CollectionHotfixCommandFinishedThreadNamesT;
		typedef std_unordered_map<int32,orm::GlobalDailyInfoLianYun*> CollectionDailyInfosT;
		typedef std_unordered_map<int32,std_unordered_map<int32,int32>> CollectionNewUserCountersT; // date=>[HHMM=>num]
	private:
		CollectionChargesT m_vGlobalCharges;
		CollectionDailyInfosT m_vDailyInfos;
		CollectionHotfixCommandsT m_vHotfixCommands;
		CollectionHotfixCommandFinishedThreadNamesT m_vHoftixCommandFinishedThreadNames;
		CollectionNewUserCountersT m_vNewUserCounters;
	private:
		int32 m_vSpendVersion;
	};
}

#endif // _pw_miscellaneous_