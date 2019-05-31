#ifndef _pw_rpc_proxies_
#define _pw_rpc_proxies_

#include "pw_def.h"
#include "pwdist_def.h"
#include "pwdist_parameter.h"

namespace pwngs
{

	namespace worldsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_conf_Enable(pwdist::ICallableObject* caller,const char* name,bool enable);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_conf_Enable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,bool enable);
		public:
			// -------------------------------------
			//  _rpc_conf_Enable
			// -------------------------------------
			class CON_rpc_conf_Enable
			{
			public:
				CON_rpc_conf_Enable(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplLogin
		// *********************************
		class SImplLoginProxy : public BaseProxy
		{
		public:
			SImplLoginProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_ConnectionClosed(pwdist::ICallableObject* caller,int64 connid,int64 id);

			//@result desc
			int _rpc_call_ReturnCreateCharacterStage(pwdist::ICallableObject* caller,pwdist::Chunk connstatus);

			//@result desc
			int _rpc_call_AccountEnterWorld(pwdist::ICallableObject* caller,const char* acc,int64 id,int32 flags);

			//@result desc
			int _rpc_call_AccountLeaveWorld(pwdist::ICallableObject* caller,const char* acc,int64 id);

			//@result desc
			int _rpc_call_AccountFlagsChanged(pwdist::ICallableObject* caller,const char* acc,int64 id,int32 addflags,int32 delflags);
		public:

			//@result desc
			int _make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_ConnectionClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,int64 id);

			//@result desc
			int _make_rpc_call_ReturnCreateCharacterStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk connstatus);

			//@result desc
			int _make_rpc_call_AccountEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id,int32 flags);

			//@result desc
			int _make_rpc_call_AccountLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id);

			//@result desc
			int _make_rpc_call_AccountFlagsChanged(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id,int32 addflags,int32 delflags);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplStage
		// *********************************
		class SImplStageProxy : public BaseProxy
		{
		public:
			SImplStageProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_CreateStage(pwdist::ICallableObject* caller,int64 basemapid,int64 gamemapid,int32 flags,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			int _rpc_call_DestroyStage(pwdist::ICallableObject* caller,int64 gamemapid);

			//@result desc
			int _rpc_call_PrepareExit(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_Exit(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_Invoke(pwdist::ICallableObject* caller,pwdist::Chunk rpc);

			//@result desc
			int _rpc_call_GSetServerMode(pwdist::ICallableObject* caller,int32 mode);

			//@result desc
			int _rpc_call_GSetGlobalVariable(pwdist::ICallableObject* caller,const char* name,int64 intval,const char* strval);

			//@result desc
			int _rpc_call_GExecuteCommand(pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _rpc_call_GEventOccured(pwdist::ICallableObject* caller,int32 event,int32 flags,int64 eventData1,int64 eventData2,pwdist::Chunk eventData3);
		public:

			//@result desc
			int _make_rpc_call_CreateStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemapid,int64 gamemapid,int32 flags,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			int _make_rpc_call_DestroyStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid);

			//@result desc
			int _make_rpc_call_PrepareExit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk rpc);

			//@result desc
			int _make_rpc_call_GSetServerMode(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mode);

			//@result desc
			int _make_rpc_call_GSetGlobalVariable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,int64 intval,const char* strval);

			//@result desc
			int _make_rpc_call_GExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _make_rpc_call_GEventOccured(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 event,int32 flags,int64 eventData1,int64 eventData2,pwdist::Chunk eventData3);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplLoginObj
		// *********************************
		class SImplLoginObjProxy : public BaseProxy
		{
		public:
			SImplLoginObjProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_SendLoginGateStatus(pwdist::ICallableObject* caller,int32 status);
		public:

			//@result desc
			int _make_rpc_call_SendLoginGateStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 status);
		public:
		};

		// *********************************
		// rpc ProxyClass Stage
		// *********************************
		class StageProxy : public BaseProxy
		{
		public:
			StageProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_EnterWorld(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_Login(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk recordVarsBuf,pwdist::Chunk loginInfo);

			//@result desc
			int _rpc_call_Broadcast(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_Broadcast2(pwdist::ICallableObject* caller,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_ActivityStartup(pwdist::ICallableObject* caller,int64 activityId);

			//@result desc
			int _rpc_call_ActivityCleanup(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
			int _rpc_call_CallScript(pwdist::ICallableObject* caller,const char* func,pwdist::Chunk chunk);

			//@result desc
			int _rpc_call_SpawnMonster(pwdist::ICallableObject* caller,const char* spawnMethod);

			//@result desc
			int _rpc_call_InitialStageLogic(pwdist::ICallableObject* caller,pwdist::Chunk chunk);

			//@result desc
			int _rpc_call_DawnHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_MidnightEvent(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_Gmland_Load(pwdist::ICallableObject* caller,int64 id,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_Gmland_Unload(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_Gmland_Oper(pwdist::ICallableObject* caller,int64 hid,int64 hash,pwdist::Chunk params);

			//@result desc
			int _rpc_call_Invoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _rpc_call_GExecuteCommand(pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _rpc_call_FillBattleMember(pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			//@result 1, int32 result [required]
			int _rpc_call_SpawnMonsterEx(pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int32 x,int32 y,int32 z);
		public:

			//@result desc
			int _make_rpc_call_EnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_Login(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk recordVarsBuf,pwdist::Chunk loginInfo);

			//@result desc
			int _make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_Broadcast2(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_ActivityStartup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activityId);

			//@result desc
			int _make_rpc_call_ActivityCleanup(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
			int _make_rpc_call_CallScript(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* func,pwdist::Chunk chunk);

			//@result desc
			int _make_rpc_call_SpawnMonster(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* spawnMethod);

			//@result desc
			int _make_rpc_call_InitialStageLogic(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk chunk);

			//@result desc
			int _make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_Gmland_Load(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_Gmland_Unload(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_Gmland_Oper(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 hash,pwdist::Chunk params);

			//@result desc
			int _make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _make_rpc_call_GExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _make_rpc_call_FillBattleMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			//@result 1, int32 result [required]
			int _make_rpc_call_SpawnMonsterEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int32 x,int32 y,int32 z);
		public:
			// -------------------------------------
			//  _rpc_call_CallScript
			// -------------------------------------
			class CON_CallScript
			{
			public:
				CON_CallScript(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_Gmland_Load
			// -------------------------------------
			class CON_rpc_Gmland_Load
			{
			public:
				CON_rpc_Gmland_Load(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_Gmland_Unload
			// -------------------------------------
			class CON_rpc_Gmland_Unload
			{
			public:
				CON_rpc_Gmland_Unload(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_SpawnMonsterEx
			// -------------------------------------
			class CON_SpawnMonsterEx
			{
			public:
				CON_SpawnMonsterEx(pwdist::Port* port = NULL);
			public:
				int Return(int32 result);
				int ReturnAsyncEx(int64 pid,int32 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass Human
		// *********************************
		class HumanProxy : public BaseProxy
		{
		public:
			HumanProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_InitialDataToClient(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ConnectionClosed(pwdist::ICallableObject* caller,int64 connid,int64 id);

			//@result desc
			int _rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 hid,int64 connid,pwdist::Chunk buffer);

			//@result desc
			int _rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer,int32 count);

			//@result desc
			int _rpc_call_Kick(pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags);

			//@result desc
			int _rpc_call_Invoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _rpc_call_UpdateTeam(pwdist::ICallableObject* caller,int64 tid,pwdist::Chunk info,int64 flags);

			//@result desc
			int _rpc_call_UpdateGuild(pwdist::ICallableObject* caller,int64 gid,pwdist::Chunk info,int64 flags);

			//@result desc
			//@result 1, int64 result [required]
			int _rpc_call_SwitchStage(pwdist::ICallableObject* caller,int64 basemap,int64 gamemap,int32 type,pwdist::Chunk customParams);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Spend(pwdist::ICallableObject* caller,int64 gold,int64 silver,int32 spend_type,const char* desc);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Grant(pwdist::ICallableObject* caller,int64 gold,int64 gold_gift,int64 silver,int32 grant_type,const char* desc);

			//@result desc
			int _rpc_call_QueryPlayerInfo(pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_AddItem(pwdist::ICallableObject* caller,int32 tid,int32 count);

			//@result desc
			//@result 1, bool result [required]
			int _rpc_call_IsFunctionBlocked(pwdist::ICallableObject* caller,int32 id);

			//@result desc
			int _rpc_call_WarlordCombatResult(pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			int _rpc_call_WarlordWorship(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_UpdateCommonActivity(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_CommonActivityReward(pwdist::ICallableObject* caller,int32 aid,int32 gid,int32 code);

			//@result desc
			int _rpc_call_UpdateRewardActivity(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_DawnHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ZeroHourEvent2(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_BeforeMidnightEvent(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_AddExp(pwdist::ICallableObject* caller,int64 value);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _rpc_call_GMOper(pwdist::ICallableObject* caller,int64 hash,pwdist::Chunk chunk);

			//@result desc
			int _rpc_call_ServerAwardNotify(pwdist::ICallableObject* caller,pwdist::Chunk bsonbuf);

			//@result desc
			int _rpc_call_SyncLadderHumanInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _rpc_call_SyncNormalHumanInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _rpc_call_AdventureFinished(pwdist::ICallableObject* caller,int32 adventure_id);

			//@result desc
			int _rpc_call_FatigueChangeSeconds(pwdist::ICallableObject* caller,int32 seconds,const char* from);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_ExecuteOperation(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_ExecutePassportOperation(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_MultiplayerDungeonMatchOver(pwdist::ICallableObject* caller,int32 code);

			//@result desc
			int _rpc_call_WriteSnapshots(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_LadderLogined(pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params);

			//@result desc
			int _rpc_call_LadderStarted(pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params);

			//@result desc
			int _rpc_call_LadderMatched(pwdist::ICallableObject* caller,int32 point);

			//@result desc
			//@result 1, pwdist::Chunk point [required]
			int _rpc_call_CalcItemCombatPoint(pwdist::ICallableObject* caller,pwdist::Chunk itemInfo);

			//@result desc
			int _rpc_call_Award(pwdist::ICallableObject* caller,int32 itemtype,int32 itemcount);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_ShopBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_MallBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _rpc_call_ExecuteGM(pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _rpc_call_UpdateHotActivity(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_UpdateHotActivityEx(pwdist::ICallableObject* caller,int32 aid,pwdist::Chunk info);

			//@result desc
			int _rpc_call_UpdateAchievementArenaSeason(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_OpenAuctionBidFail(pwdist::ICallableObject* caller,int32 code,int32 cfgID);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 gold [required]
			//@result 3, int32 giftgold [required]
			int _rpc_call_OpenAuctionBidVerify(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_ArenaSeasonEnded(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_CommonActivityEvent(pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param);

			//@result desc
			int _rpc_call_ActivityEnd(pwdist::ICallableObject* caller,int32 aid,int64 endtime);

			//@result desc
			int _rpc_call_RunCarFinish(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_SendBackRedEnvelopLastGold(pwdist::ICallableObject* caller,int64 gold);
		public:

			//@result desc
			int _make_rpc_call_InitialDataToClient(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ConnectionClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,int64 id);

			//@result desc
			int _make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 connid,pwdist::Chunk buffer);

			//@result desc
			int _make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer,int32 count);

			//@result desc
			int _make_rpc_call_Kick(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags);

			//@result desc
			int _make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _make_rpc_call_UpdateTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,pwdist::Chunk info,int64 flags);

			//@result desc
			int _make_rpc_call_UpdateGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,pwdist::Chunk info,int64 flags);

			//@result desc
			//@result 1, int64 result [required]
			int _make_rpc_call_SwitchStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap,int64 gamemap,int32 type,pwdist::Chunk customParams);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Spend(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold,int64 silver,int32 spend_type,const char* desc);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Grant(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold,int64 gold_gift,int64 silver,int32 grant_type,const char* desc);

			//@result desc
			int _make_rpc_call_QueryPlayerInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_AddItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 tid,int32 count);

			//@result desc
			//@result 1, bool result [required]
			int _make_rpc_call_IsFunctionBlocked(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 id);

			//@result desc
			int _make_rpc_call_WarlordCombatResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			int _make_rpc_call_WarlordWorship(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_UpdateCommonActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_CommonActivityReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,int32 gid,int32 code);

			//@result desc
			int _make_rpc_call_UpdateRewardActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ZeroHourEvent2(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_BeforeMidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_AddExp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 value);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _make_rpc_call_GMOper(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hash,pwdist::Chunk chunk);

			//@result desc
			int _make_rpc_call_ServerAwardNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk bsonbuf);

			//@result desc
			int _make_rpc_call_SyncLadderHumanInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _make_rpc_call_SyncNormalHumanInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _make_rpc_call_AdventureFinished(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 adventure_id);

			//@result desc
			int _make_rpc_call_FatigueChangeSeconds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 seconds,const char* from);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_ExecuteOperation(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_ExecutePassportOperation(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_MultiplayerDungeonMatchOver(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code);

			//@result desc
			int _make_rpc_call_WriteSnapshots(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_LadderLogined(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params);

			//@result desc
			int _make_rpc_call_LadderStarted(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params);

			//@result desc
			int _make_rpc_call_LadderMatched(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 point);

			//@result desc
			//@result 1, pwdist::Chunk point [required]
			int _make_rpc_call_CalcItemCombatPoint(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk itemInfo);

			//@result desc
			int _make_rpc_call_Award(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 itemtype,int32 itemcount);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_ShopBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_MallBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _make_rpc_call_ExecuteGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text);

			//@result desc
			int _make_rpc_call_UpdateHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_UpdateHotActivityEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_UpdateAchievementArenaSeason(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_OpenAuctionBidFail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,int32 cfgID);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 gold [required]
			//@result 3, int32 giftgold [required]
			int _make_rpc_call_OpenAuctionBidVerify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_ArenaSeasonEnded(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_CommonActivityEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param);

			//@result desc
			int _make_rpc_call_ActivityEnd(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,int64 endtime);

			//@result desc
			int _make_rpc_call_RunCarFinish(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_SendBackRedEnvelopLastGold(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold);
		public:
			// -------------------------------------
			//  _rpc_call_SwitchStage
			// -------------------------------------
			class CON_SwitchStage
			{
			public:
				CON_SwitchStage(pwdist::Port* port = NULL);
			public:
				int Return(int64 result);
				int ReturnAsyncEx(int64 pid,int64 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Spend
			// -------------------------------------
			class CON_Spend
			{
			public:
				CON_Spend(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Grant
			// -------------------------------------
			class CON_Grant
			{
			public:
				CON_Grant(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AddItem
			// -------------------------------------
			class CON_AddItem
			{
			public:
				CON_AddItem(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_IsFunctionBlocked
			// -------------------------------------
			class CON_IsFunctionBlocked
			{
			public:
				CON_IsFunctionBlocked(pwdist::Port* port = NULL);
			public:
				int Return(bool result);
				int ReturnAsyncEx(int64 pid,bool result);
				int CancelAsyncReturn(int64 pid);
			public:
				static bool GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AddExp
			// -------------------------------------
			class CON_AddExp
			{
			public:
				CON_AddExp(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GMOper
			// -------------------------------------
			class CON_GMOper
			{
			public:
				CON_GMOper(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* error);
				int ReturnAsyncEx(int64 pid,int32 code,const char* error);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultError(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ExecuteOperation
			// -------------------------------------
			class CON_ExecuteOperation
			{
			public:
				CON_ExecuteOperation(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ExecutePassportOperation
			// -------------------------------------
			class CON_ExecutePassportOperation
			{
			public:
				CON_ExecutePassportOperation(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CalcItemCombatPoint
			// -------------------------------------
			class CON_CalcItemCombatPoint
			{
			public:
				CON_CalcItemCombatPoint(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk point);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk point);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultPoint(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ShopBuy
			// -------------------------------------
			class CON_ShopBuy
			{
			public:
				CON_ShopBuy(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_MallBuy
			// -------------------------------------
			class CON_MallBuy
			{
			public:
				CON_MallBuy(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ExecuteGM
			// -------------------------------------
			class CON_ExecuteGM
			{
			public:
				CON_ExecuteGM(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* error);
				int ReturnAsyncEx(int64 pid,int32 code,const char* error);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultError(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_OpenAuctionBidVerify
			// -------------------------------------
			class CON_OpenAuctionBidVerify
			{
			public:
				CON_OpenAuctionBidVerify(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 gold,int32 giftgold);
				int ReturnAsyncEx(int64 pid,int32 code,int32 gold,int32 giftgold);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultGold(pwdist::FutureObject& f);
				static int32 GetResultGiftgold(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplSupport
		// *********************************
		class SImplSupportProxy : public BaseProxy
		{
		public:
			SImplSupportProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int64 result [required]
			int _rpc_call_Load(pwdist::ICallableObject* caller,int64 humanId);

			//@result desc
			//@result 1, int64 result [required]
			int _rpc_call_Unload(pwdist::ICallableObject* caller,int64 humanId);
		public:

			//@result desc
			//@result 1, int64 result [required]
			int _make_rpc_call_Load(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId);

			//@result desc
			//@result 1, int64 result [required]
			int _make_rpc_call_Unload(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId);
		public:
			// -------------------------------------
			//  _rpc_call_Load
			// -------------------------------------
			class CON_Load
			{
			public:
				CON_Load(pwdist::Port* port = NULL);
			public:
				int Return(int64 result);
				int ReturnAsyncEx(int64 pid,int64 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Unload
			// -------------------------------------
			class CON_Unload
			{
			public:
				CON_Unload(pwdist::Port* port = NULL);
			public:
				int Return(int64 result);
				int ReturnAsyncEx(int64 pid,int64 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

	}

	namespace ctrlsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Null(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplAuctionHouse
		// *********************************
		class SImplAuctionHouseProxy : public BaseProxy
		{
		public:
			SImplAuctionHouseProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _rpc_call_Auction(pwdist::ICallableObject* caller,pwdist::Chunk auctionInfo,pwdist::Chunk item);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _rpc_call_AuctionCancel(pwdist::ICallableObject* caller,int32 position,int64 auctionId);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _rpc_call_AuctionBuy(pwdist::ICallableObject* caller,pwdist::Chunk buyinfo);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk itemsInSell [required]
			//@result 3, pwdist::Chunk itemInAuction [required]
			int _rpc_call_ItemsList(pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk buyinfo);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 count [required]
			//@result 3, pwdist::Chunk items [required]
			int _rpc_call_ItemsQuery(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk refs);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk items [required]
			int _rpc_call_ItemsSearch(pwdist::ICallableObject* caller,pwdist::Chunk searchinfo);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _make_rpc_call_Auction(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk auctionInfo,pwdist::Chunk item);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _make_rpc_call_AuctionCancel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 position,int64 auctionId);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
			int _make_rpc_call_AuctionBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buyinfo);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk itemsInSell [required]
			//@result 3, pwdist::Chunk itemInAuction [required]
			int _make_rpc_call_ItemsList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk buyinfo);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 count [required]
			//@result 3, pwdist::Chunk items [required]
			int _make_rpc_call_ItemsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk refs);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk items [required]
			int _make_rpc_call_ItemsSearch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk searchinfo);
		public:
			// -------------------------------------
			//  _rpc_call_Auction
			// -------------------------------------
			class CON_Auction
			{
			public:
				CON_Auction(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk item);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItem(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AuctionCancel
			// -------------------------------------
			class CON_AuctionCancel
			{
			public:
				CON_AuctionCancel(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk item);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItem(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AuctionBuy
			// -------------------------------------
			class CON_AuctionBuy
			{
			public:
				CON_AuctionBuy(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk item);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItem(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ItemsList
			// -------------------------------------
			class CON_ItemsList
			{
			public:
				CON_ItemsList(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk itemsInSell,pwdist::Chunk itemInAuction);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk itemsInSell,pwdist::Chunk itemInAuction);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItemsinsell(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultIteminauction(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ItemsQuery
			// -------------------------------------
			class CON_ItemsQuery
			{
			public:
				CON_ItemsQuery(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 count,pwdist::Chunk items);
				int ReturnAsyncEx(int64 pid,int32 code,int32 count,pwdist::Chunk items);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultCount(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItems(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ItemsSearch
			// -------------------------------------
			class CON_ItemsSearch
			{
			public:
				CON_ItemsSearch(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk items);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk items);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultItems(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImpl173
		// *********************************
		class SImpl173Proxy : public BaseProxy
		{
		public:
			SImpl173Proxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_GiftCard(pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId);

			//@result desc
			int _rpc_call_GiftCardLianYun(pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId,const char* agent);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* token [optional]
			int _rpc_call_RequestToken(pwdist::ICallableObject* caller,int64 userId,const char* accountId,const char* location);

			//@result desc
			int _rpc_call_LianYunPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_LianYunPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk head,const char* content);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* name [required]
			int _rpc_call_FetchServerName(pwdist::ICallableObject* caller,int64 server_group);

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
			int _rpc_call_FetchServerInfos(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk json [required]
			int _rpc_call_TXInvoke(pwdist::ICallableObject* caller,const char* apiname,pwdist::Chunk params_chunk);

			//@result desc
			int _rpc_call_TXCompassPush(pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _rpc_call_TXUnionPush(pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _rpc_call_TXClogPush(pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _rpc_call_ActiveCodeKorCtrl(pwdist::ICallableObject* caller,int64 uid,const char* active_code);
		public:

			//@result desc
			int _make_rpc_call_GiftCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId);

			//@result desc
			int _make_rpc_call_GiftCardLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId,const char* agent);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* token [optional]
			int _make_rpc_call_RequestToken(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 userId,const char* accountId,const char* location);

			//@result desc
			int _make_rpc_call_LianYunPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_LianYunPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk head,const char* content);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* name [required]
			int _make_rpc_call_FetchServerName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 server_group);

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
			int _make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk json [required]
			int _make_rpc_call_TXInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* apiname,pwdist::Chunk params_chunk);

			//@result desc
			int _make_rpc_call_TXCompassPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _make_rpc_call_TXUnionPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _make_rpc_call_TXClogPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url);

			//@result desc
			int _make_rpc_call_ActiveCodeKorCtrl(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,const char* active_code);
		public:
			// -------------------------------------
			//  _rpc_call_RequestToken
			// -------------------------------------
			class CON_RequestToken
			{
			public:
				CON_RequestToken(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,const char* token);
				int ReturnAsyncEx(int64 pid,int32 code,const char* token);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultToken(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_FetchServerName
			// -------------------------------------
			class CON_FetchServerName
			{
			public:
				CON_FetchServerName(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* name);
				int ReturnAsyncEx(int64 pid,int32 code,const char* name);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultName(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_FetchServerInfos
			// -------------------------------------
			class CON_FetchServerInfos
			{
			public:
				CON_FetchServerInfos(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_TXInvoke
			// -------------------------------------
			class CON_TXInvoke
			{
			public:
				CON_TXInvoke(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk json);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk json);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultJson(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SimplXiyou
		// *********************************
		class SimplXiyouProxy : public BaseProxy
		{
		public:
			SimplXiyouProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_FetchServerInfos(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_XiYouPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk _info);

			//@result desc
			int _rpc_call_XiYouPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content);
		public:

			//@result desc
			int _make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_XiYouPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info);

			//@result desc
			int _make_rpc_call_XiYouPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content);
		public:
		};

		// *********************************
		// rpc ProxyClass Simpl360
		// *********************************
		class Simpl360Proxy : public BaseProxy
		{
		public:
			Simpl360Proxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_FetchServerInfos(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_SanLiuLingPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk _info);

			//@result desc
			int _rpc_call_SanLiuLingPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content);

			//@result desc
			int _rpc_call_NewActiveCodeCtrl(pwdist::ICallableObject* caller,int64 uid,int64 roleID,int32 server_id,const char* active_code);

			//@result desc
			int _rpc_call_HumanEnterWorld(pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee);

			//@result desc
			int _rpc_call_HumanLeaveWorld(pwdist::ICallableObject* caller,int64 id,const char* callee);

			//@result desc
			int _rpc_call_HumanUpdate(pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee);
		public:

			//@result desc
			int _make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_SanLiuLingPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info);

			//@result desc
			int _make_rpc_call_SanLiuLingPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content);

			//@result desc
			int _make_rpc_call_NewActiveCodeCtrl(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 roleID,int32 server_id,const char* active_code);

			//@result desc
			int _make_rpc_call_HumanEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee);

			//@result desc
			int _make_rpc_call_HumanLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* callee);

			//@result desc
			int _make_rpc_call_HumanUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplBase
		// *********************************
		class SImplBaseProxy : public BaseProxy
		{
		public:
			SImplBaseProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Broadcast(pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _rpc_call_HumanEnterWorld(pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee);

			//@result desc
			int _rpc_call_HumanLeaveWorld(pwdist::ICallableObject* caller,int64 id,const char* callee);

			//@result desc
			int _rpc_call_HumanUpdate(pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee);

			//@result desc
			int _rpc_call_HumanEnterWorldAfter(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_HumanDropped(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_HumanReconnected(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_SendMsg(pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _rpc_call_SendMsgReliable(pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer,int32 count);
		public:

			//@result desc
			int _make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _make_rpc_call_HumanEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee);

			//@result desc
			int _make_rpc_call_HumanLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* callee);

			//@result desc
			int _make_rpc_call_HumanUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee);

			//@result desc
			int _make_rpc_call_HumanEnterWorldAfter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_HumanDropped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_HumanReconnected(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _make_rpc_call_SendMsgReliable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer,int32 count);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplCommon
		// *********************************
		class SImplCommonProxy : public SImplBaseProxy
		{
		public:
			SImplCommonProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_HumanQuery(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_HumanQueryByName(pwdist::ICallableObject* caller,const char* name);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_AccountQuery(pwdist::ICallableObject* caller,const char* account);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_Query(pwdist::ICallableObject* caller,const char* account,int64 id);

			//@result desc
			int _rpc_call_HumanKick(pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags);

			//@result desc
			int _rpc_call_HumanInvoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _rpc_call_HumanCreated(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_GMInjectZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_HumanRenamed(pwdist::ICallableObject* caller,int64 id,const char* name);

			//@result desc
			int _rpc_call_BroadcastOpenScene(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _rpc_call_SelectHumanToExecuteGM(pwdist::ICallableObject* caller,const char* text);

			//@result desc
			//@result 1, int32 online [required]
			//@result 2, int32 max_online [required]
			//@result 3, int32 min_online [required]
			int _rpc_call_LianYunQueryTodayOnline(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_PassportLock(pwdist::ICallableObject* caller,const char* passport,int64 hid,int64 secs);

			//@result desc
			int _rpc_call_PassportUnlock(pwdist::ICallableObject* caller,const char* passport);
		public:

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_HumanQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_HumanQueryByName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_AccountQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 id);

			//@result desc
			int _make_rpc_call_HumanKick(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags);

			//@result desc
			int _make_rpc_call_HumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _make_rpc_call_HumanCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_GMInjectZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_HumanRenamed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* name);

			//@result desc
			int _make_rpc_call_BroadcastOpenScene(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _make_rpc_call_SelectHumanToExecuteGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text);

			//@result desc
			//@result 1, int32 online [required]
			//@result 2, int32 max_online [required]
			//@result 3, int32 min_online [required]
			int _make_rpc_call_LianYunQueryTodayOnline(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_PassportLock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 hid,int64 secs);

			//@result desc
			int _make_rpc_call_PassportUnlock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);
		public:
			// -------------------------------------
			//  _rpc_call_HumanQuery
			// -------------------------------------
			class CON_HumanQuery
			{
			public:
				CON_HumanQuery(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_HumanQueryByName
			// -------------------------------------
			class CON_HumanQueryByName
			{
			public:
				CON_HumanQueryByName(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AccountQuery
			// -------------------------------------
			class CON_AccountQuery
			{
			public:
				CON_AccountQuery(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Query
			// -------------------------------------
			class CON_Query
			{
			public:
				CON_Query(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_SelectHumanToExecuteGM
			// -------------------------------------
			class CON_SelectHumanToExecuteGM
			{
			public:
				CON_SelectHumanToExecuteGM(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* error);
				int ReturnAsyncEx(int64 pid,int32 code,const char* error);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultError(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LianYunQueryTodayOnline
			// -------------------------------------
			class CON_LianYunQueryTodayOnline
			{
			public:
				CON_LianYunQueryTodayOnline(pwdist::Port* port = NULL);
			public:
				int Return(int32 online,int32 max_online,int32 min_online);
				int ReturnAsyncEx(int64 pid,int32 online,int32 max_online,int32 min_online);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultOnline(pwdist::FutureObject& f);
				static int32 GetResultMax_online(pwdist::FutureObject& f);
				static int32 GetResultMin_online(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplGuild
		// *********************************
		class SImplGuildProxy : public SImplBaseProxy
		{
		public:
			SImplGuildProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_CreateGuild(pwdist::ICallableObject* caller,const char* gname,int64 uid,const char* uname);

			//@result desc
			int _rpc_call_ApplyGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid,const char* uname);

			//@result desc
			int _rpc_call_ApplyGuildResult(pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,const char* uname,int64 operid);

			//@result desc
			int _rpc_call_InviteGuild(pwdist::ICallableObject* caller,int64 gid,const char* uname,int64 operid);

			//@result desc
			int _rpc_call_InviteGuildResult(pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,int64 operid);

			//@result desc
			int _rpc_call_LeaveGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid);

			//@result desc
			int _rpc_call_KickGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid,int64 operid);

			//@result desc
			int _rpc_call_QueryGuildList(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_FetchGuildOrderByLiveness(pwdist::ICallableObject* caller,int32 num,int32 level);

			//@result desc
			int _rpc_call_FetchGuildList(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_FetchGuildById(pwdist::ICallableObject* caller,int64 id1,int64 id2);

			//@result desc
			int _rpc_call_BroadcastMail(pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_BroadcastMailExceptNew(pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail);

			//@result desc
			int _rpc_call_PrepareExit(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, pwdist::Chunk chunk1 [required]
			//@result 2, pwdist::Chunk chunk2 [required]
			int _rpc_call_FetchCommander(pwdist::ICallableObject* caller,int64 gid1,int64 gid2);

			//@result desc
			int _rpc_call_ResetLiveness(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_CancelApply(pwdist::ICallableObject* caller,int64 gid,int64 uid);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_MidnightEvent(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_DismissGuild(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _rpc_call_ChangeGuildCommander(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_QueryGuildIsExist(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_LianYunChangeGuildCommander(pwdist::ICallableObject* caller,int64 gid,const char* newCommanderName);

			//@result desc
			int _rpc_call_FetchGuildListLianYun(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _rpc_call_FetchGuildByIdLianYun(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			int _rpc_call_FetchGuildByPassportLianYun(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_ChangeGuildNoticeByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid,const char* notice,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_FetchGuildMembersByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_AuthGuildByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid,int32 operType,int32 needsort);
		public:

			//@result desc
			int _make_rpc_call_CreateGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* gname,int64 uid,const char* uname);

			//@result desc
			int _make_rpc_call_ApplyGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,const char* uname);

			//@result desc
			int _make_rpc_call_ApplyGuildResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,const char* uname,int64 operid);

			//@result desc
			int _make_rpc_call_InviteGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* uname,int64 operid);

			//@result desc
			int _make_rpc_call_InviteGuildResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,int64 operid);

			//@result desc
			int _make_rpc_call_LeaveGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid);

			//@result desc
			int _make_rpc_call_KickGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,int64 operid);

			//@result desc
			int _make_rpc_call_QueryGuildList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_FetchGuildOrderByLiveness(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 num,int32 level);

			//@result desc
			int _make_rpc_call_FetchGuildList(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_FetchGuildById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id1,int64 id2);

			//@result desc
			int _make_rpc_call_BroadcastMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_BroadcastMailExceptNew(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail);

			//@result desc
			int _make_rpc_call_PrepareExit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, pwdist::Chunk chunk1 [required]
			//@result 2, pwdist::Chunk chunk2 [required]
			int _make_rpc_call_FetchCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid1,int64 gid2);

			//@result desc
			int _make_rpc_call_ResetLiveness(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_CancelApply(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_DismissGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _make_rpc_call_ChangeGuildCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_QueryGuildIsExist(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_LianYunChangeGuildCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* newCommanderName);

			//@result desc
			int _make_rpc_call_FetchGuildListLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _make_rpc_call_FetchGuildByIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			int _make_rpc_call_FetchGuildByPassportLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_ChangeGuildNoticeByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* notice,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_FetchGuildMembersByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_AuthGuildByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int32 operType,int32 needsort);
		public:
			// -------------------------------------
			//  _rpc_call_BroadcastMailExceptNew
			// -------------------------------------
			class CON_BroadcastMailExceptNew
			{
			public:
				CON_BroadcastMailExceptNew(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_FetchCommander
			// -------------------------------------
			class CON_FetchCommander
			{
			public:
				CON_FetchCommander(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk chunk1,pwdist::Chunk chunk2);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk chunk1,pwdist::Chunk chunk2);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultChunk1(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk2(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_DismissGuild
			// -------------------------------------
			class CON_DismissGuild
			{
			public:
				CON_DismissGuild(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ChangeGuildCommander
			// -------------------------------------
			class CON_ChangeGuildCommander
			{
			public:
				CON_ChangeGuildCommander(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryGuildIsExist
			// -------------------------------------
			class CON_QueryGuildIsExist
			{
			public:
				CON_QueryGuildIsExist(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LianYunChangeGuildCommander
			// -------------------------------------
			class CON_LianYunChangeGuildCommander
			{
			public:
				CON_LianYunChangeGuildCommander(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_FetchGuildByIdLianYun
			// -------------------------------------
			class CON_FetchGuildByIdLianYun
			{
			public:
				CON_FetchGuildByIdLianYun(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ChangeGuildNoticeByGuildIdLianYun
			// -------------------------------------
			class CON_ChangeGuildNoticeByGuildIdLianYun
			{
			public:
				CON_ChangeGuildNoticeByGuildIdLianYun(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_FetchGuildMembersByGuildIdLianYun
			// -------------------------------------
			class CON_FetchGuildMembersByGuildIdLianYun
			{
			public:
				CON_FetchGuildMembersByGuildIdLianYun(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AuthGuildByGuildIdLianYun
			// -------------------------------------
			class CON_AuthGuildByGuildIdLianYun
			{
			public:
				CON_AuthGuildByGuildIdLianYun(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass Guild
		// *********************************
		class GuildProxy : public BaseProxy
		{
		public:
			GuildProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryOther(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_ChangeTitle(pwdist::ICallableObject* caller,int64 operid,int32 title,int64 expectid1,int64 expectid2);

			//@result desc
			int _rpc_call_ChangeNotice(pwdist::ICallableObject* caller,int64 operid,const char* content);

			//@result desc
			int _rpc_call_AddMemberDevotion(pwdist::ICallableObject* caller,int64 uid,int32 val,bool bAddGuild);

			//@result desc
			int _rpc_call_AddDevelopment(pwdist::ICallableObject* caller,int32 val);

			//@result desc
			int _rpc_call_BroadcastGuild(pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_LevelupBuilding(pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _rpc_call_RecruitMember(pwdist::ICallableObject* caller,int64 operid);

			//@result desc
			int _rpc_call_AddLog(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk params);

			//@result desc
			int _rpc_call_GDepositoryQuery(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_GDepositoryAllot(pwdist::ICallableObject* caller,int64 uid,int32 type,int32 count,int64 target);

			//@result desc
			int _rpc_call_GDepositoryAllotByIndex(pwdist::ICallableObject* caller,int64 uid,int32 index,int32 type,int32 count,int64 target);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_GDepositoryGrantItems(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_GDepositorySpendItems(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk);

			//@result desc
			int _rpc_call_GDepositoryClearItems(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryGuildFruiter(pwdist::ICallableObject* caller,int64 uid,int32 remain_pickup_count,int32 remain_pickup_cd);

			//@result desc
			int _rpc_call_PickupGuildFruit(pwdist::ICallableObject* caller,int64 uid,int32 index,int32 id);

			//@result desc
			int _rpc_call_DragonHuntQuery(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_DragonHuntDouble(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_DragonHuntAdd(pwdist::ICallableObject* caller,int64 uid,int32 dragontype,int32 dragonquality,int32 dragonlevel);

			//@result desc
			int _rpc_call_DragonHuntStart(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_DragonHuntClose(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_TrialLandQuery(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_TrialLandStart(pwdist::ICallableObject* caller,int64 hid,int32 tid,const char* bossname);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_TrialLandEnter(pwdist::ICallableObject* caller,int64 hid,int32 tid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 flag [required]
			int _rpc_call_TrialLandComplete(pwdist::ICallableObject* caller,int32 tid,bool succ,int64 startTime,int64 endTime,const char* bossname);

			//@result desc
			int _rpc_call_TrialLandGmClear(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_BroadcastNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notify,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_BroadcastCommonActivityEvent(pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param);

			//@result desc
			int _rpc_call_ChangeApplyWay(pwdist::ICallableObject* caller,int64 hid,bool bIsAutoApply);

			//@result desc
			int _rpc_call_GetSYDungeonStatus(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_OpenSYDungeon(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_OnSYDungeonClosed(pwdist::ICallableObject* caller,int64 nTotalDamage);

			//@result desc
			int _rpc_call_EnterSYDungeon(pwdist::ICallableObject* caller,int64 hid);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryOther(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_ChangeTitle(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid,int32 title,int64 expectid1,int64 expectid2);

			//@result desc
			int _make_rpc_call_ChangeNotice(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid,const char* content);

			//@result desc
			int _make_rpc_call_AddMemberDevotion(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 val,bool bAddGuild);

			//@result desc
			int _make_rpc_call_AddDevelopment(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 val);

			//@result desc
			int _make_rpc_call_BroadcastGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_LevelupBuilding(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _make_rpc_call_RecruitMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid);

			//@result desc
			int _make_rpc_call_AddLog(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk params);

			//@result desc
			int _make_rpc_call_GDepositoryQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_GDepositoryAllot(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,int32 count,int64 target);

			//@result desc
			int _make_rpc_call_GDepositoryAllotByIndex(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 index,int32 type,int32 count,int64 target);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_GDepositoryGrantItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_GDepositorySpendItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk);

			//@result desc
			int _make_rpc_call_GDepositoryClearItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryGuildFruiter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 remain_pickup_count,int32 remain_pickup_cd);

			//@result desc
			int _make_rpc_call_PickupGuildFruit(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 index,int32 id);

			//@result desc
			int _make_rpc_call_DragonHuntQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_DragonHuntDouble(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_DragonHuntAdd(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 dragontype,int32 dragonquality,int32 dragonlevel);

			//@result desc
			int _make_rpc_call_DragonHuntStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_DragonHuntClose(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_TrialLandQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_TrialLandStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 tid,const char* bossname);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_TrialLandEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 tid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 flag [required]
			int _make_rpc_call_TrialLandComplete(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 tid,bool succ,int64 startTime,int64 endTime,const char* bossname);

			//@result desc
			int _make_rpc_call_TrialLandGmClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_BroadcastNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notify,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_BroadcastCommonActivityEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param);

			//@result desc
			int _make_rpc_call_ChangeApplyWay(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,bool bIsAutoApply);

			//@result desc
			int _make_rpc_call_GetSYDungeonStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_OpenSYDungeon(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_OnSYDungeonClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nTotalDamage);

			//@result desc
			int _make_rpc_call_EnterSYDungeon(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);
		public:
			// -------------------------------------
			//  _rpc_call_GDepositoryGrantItems
			// -------------------------------------
			class CON_GDepositoryGrantItems
			{
			public:
				CON_GDepositoryGrantItems(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GDepositorySpendItems
			// -------------------------------------
			class CON_GDepositorySpendItems
			{
			public:
				CON_GDepositorySpendItems(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_TrialLandStart
			// -------------------------------------
			class CON_TrialLandStart
			{
			public:
				CON_TrialLandStart(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_TrialLandEnter
			// -------------------------------------
			class CON_TrialLandEnter
			{
			public:
				CON_TrialLandEnter(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_TrialLandComplete
			// -------------------------------------
			class CON_TrialLandComplete
			{
			public:
				CON_TrialLandComplete(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 flag);
				int ReturnAsyncEx(int64 pid,int32 code,int32 flag);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultFlag(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplRelation
		// *********************************
		class SImplRelationProxy : public SImplBaseProxy
		{
		public:
			SImplRelationProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk varsbuf [required]
			int _rpc_call_AddRelationObject(pwdist::ICallableObject* caller,int64 id,int64 rid,const char* name,int32 type);

			//@result desc
			//@result 1, int32 result [required]
			int _rpc_call_DelRelationObject(pwdist::ICallableObject* caller,int64 id,int64 rid,int32 type);

			//@result desc
			//@result 1, int32 result [required]
			int _rpc_call_QueryRelationList(pwdist::ICallableObject* caller,int64 id,int32 type);

			//@result desc
			int _rpc_call_BroadcastNotifyBall(pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk notify);

			//@result desc
			int _rpc_call_BroadcastMail(pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk mail);

			//@result desc
			int _rpc_call_FetchRelationList(pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _rpc_call_RequestRecommendLists(pwdist::ICallableObject* caller,int64 uid);
		public:

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk varsbuf [required]
			int _make_rpc_call_AddRelationObject(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int64 rid,const char* name,int32 type);

			//@result desc
			//@result 1, int32 result [required]
			int _make_rpc_call_DelRelationObject(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int64 rid,int32 type);

			//@result desc
			//@result 1, int32 result [required]
			int _make_rpc_call_QueryRelationList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 type);

			//@result desc
			int _make_rpc_call_BroadcastNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk notify);

			//@result desc
			int _make_rpc_call_BroadcastMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk mail);

			//@result desc
			int _make_rpc_call_FetchRelationList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _make_rpc_call_RequestRecommendLists(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);
		public:
			// -------------------------------------
			//  _rpc_call_AddRelationObject
			// -------------------------------------
			class CON_AddRelationObject
			{
			public:
				CON_AddRelationObject(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,pwdist::Chunk varsbuf);
				int ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk varsbuf);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultVarsbuf(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_DelRelationObject
			// -------------------------------------
			class CON_DelRelationObject
			{
			public:
				CON_DelRelationObject(pwdist::Port* port = NULL);
			public:
				int Return(int32 result);
				int ReturnAsyncEx(int64 pid,int32 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryRelationList
			// -------------------------------------
			class CON_QueryRelationList
			{
			public:
				CON_QueryRelationList(pwdist::Port* port = NULL);
			public:
				int Return(int32 result);
				int ReturnAsyncEx(int64 pid,int32 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplStageMgr
		// *********************************
		class SImplStageMgrProxy : public SImplBaseProxy
		{
		public:
			SImplStageMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_StageThreadReport(pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_StageCreated(pwdist::ICallableObject* caller,int64 stage,int64 basemap,int32 stagetype);

			//@result desc
			int _rpc_call_StageDestructed(pwdist::ICallableObject* caller,int64 stage,int32 reason);

			//@result desc
			int _rpc_call_CreateStage(pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_CreateStageSublines(pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			int _rpc_call_BroadcastOnSublines(pwdist::ICallableObject* caller,int32 basemap,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_DestroyStage(pwdist::ICallableObject* caller,int64 mapid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_DestroyStageSublines(pwdist::ICallableObject* caller,int32 mapid);

			//@result desc
			int _rpc_call_QueryStage(pwdist::ICallableObject* caller,int64 stage);

			//@result desc
			//@result 1, pwdist::Chunk r [required]
			int _rpc_call_QueryStageSubline(pwdist::ICallableObject* caller,int64 basemap);

			//@result desc
			int _rpc_call_QuerySwitchableSubline(pwdist::ICallableObject* caller,int64 basemap);

			//@result desc
			int _rpc_call_LoginToStage(pwdist::ICallableObject* caller,int64 targetMap,pwdist::Chunk loginbuf,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk varsbuf);

			//@result desc
			int _rpc_call_ExitAfter(pwdist::ICallableObject* caller,int32 seconds);

			//@result desc
			int _rpc_call_DisconnectAll(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_DawnHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_MidnightEvent(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Lock(pwdist::ICallableObject* caller,int64 hid,int32 seconds);

			//@result desc
			int _rpc_call_Unlock(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_StageInvoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _rpc_call_StageThreadInvoke(pwdist::ICallableObject* caller,bool _1threadPerNode,pwdist::Chunk rpc);

			//@result desc
			//@result 1, const char* info [required]
			int _rpc_call_StageThreadExecuteCommand(pwdist::ICallableObject* caller,bool _1threadPerNode,const char* text);

			//@result desc
			int _rpc_call_HumanCreated(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_WildBossCreated(pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid);

			//@result desc
			int _rpc_call_WildBossDestructed(pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid);

			//@result desc
			//@result 1, pwdist::Chunk ret [required]
			int _rpc_call_WildBossQuery(pwdist::ICallableObject* caller,int64 basemap,int32 sublineNO);
		public:

			//@result desc
			int _make_rpc_call_StageThreadReport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_StageCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage,int64 basemap,int32 stagetype);

			//@result desc
			int _make_rpc_call_StageDestructed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage,int32 reason);

			//@result desc
			int _make_rpc_call_CreateStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_CreateStageSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk);

			//@result desc
			int _make_rpc_call_BroadcastOnSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 basemap,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_DestroyStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 mapid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_DestroyStageSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mapid);

			//@result desc
			int _make_rpc_call_QueryStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage);

			//@result desc
			//@result 1, pwdist::Chunk r [required]
			int _make_rpc_call_QueryStageSubline(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap);

			//@result desc
			int _make_rpc_call_QuerySwitchableSubline(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap);

			//@result desc
			int _make_rpc_call_LoginToStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 targetMap,pwdist::Chunk loginbuf,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk varsbuf);

			//@result desc
			int _make_rpc_call_ExitAfter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 seconds);

			//@result desc
			int _make_rpc_call_DisconnectAll(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Lock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 seconds);

			//@result desc
			int _make_rpc_call_Unlock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_StageInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count);

			//@result desc
			int _make_rpc_call_StageThreadInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool _1threadPerNode,pwdist::Chunk rpc);

			//@result desc
			//@result 1, const char* info [required]
			int _make_rpc_call_StageThreadExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool _1threadPerNode,const char* text);

			//@result desc
			int _make_rpc_call_HumanCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_WildBossCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid);

			//@result desc
			int _make_rpc_call_WildBossDestructed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid);

			//@result desc
			//@result 1, pwdist::Chunk ret [required]
			int _make_rpc_call_WildBossQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap,int32 sublineNO);
		public:
			// -------------------------------------
			//  _rpc_call_CreateStageSublines
			// -------------------------------------
			class CON_CreateStageSublines
			{
			public:
				CON_CreateStageSublines(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_DestroyStageSublines
			// -------------------------------------
			class CON_DestroyStageSublines
			{
			public:
				CON_DestroyStageSublines(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryStageSubline
			// -------------------------------------
			class CON_QueryStageSubline
			{
			public:
				CON_QueryStageSubline(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk r);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk r);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultR(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Lock
			// -------------------------------------
			class CON_Lock
			{
			public:
				CON_Lock(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_StageThreadExecuteCommand
			// -------------------------------------
			class CON_StageThreadExecuteCommand
			{
			public:
				CON_StageThreadExecuteCommand(pwdist::Port* port = NULL);
			public:
				int Return(const char* info);
				int ReturnAsyncEx(int64 pid,const char* info);
				int CancelAsyncReturn(int64 pid);
			public:
				static const char* GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_WildBossQuery
			// -------------------------------------
			class CON_WildBossQuery
			{
			public:
				CON_WildBossQuery(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk ret);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk ret);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultRet(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass Miscellaneous
		// *********************************
		class MiscellaneousProxy
		{
		public:
			MiscellaneousProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_GSpendNotify(pwdist::ICallableObject* caller,int32 event,int64 hid,int32 reason,int64 gold);
		public:

			//@result desc
			int _make_rpc_call_GSpendNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 event,int64 hid,int32 reason,int64 gold);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplActivity
		// *********************************
		class SImplActivityProxy : public SImplBaseProxy
		{
		public:
			SImplActivityProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Signup(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid,int64 data,pwdist::Chunk params);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_CancelSignup(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
			int _rpc_call_CallScript(pwdist::ICallableObject* caller,int64 activity,const char* func,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Enter(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 humanid);

			//@result desc
			int _rpc_call_SendActivityStatus(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_GMStart(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_GMClean(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_MidnightEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_UpdateHumanCounter(pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int32 human_count);

			//@result desc
			int _rpc_call_UpdatePCU(pwdist::ICallableObject* caller,int32 count);

			//@result desc
			int _rpc_call_GetStartTime(pwdist::ICallableObject* caller,int32 activityId);

			//@result desc
			int _rpc_call_UpdateHumanEnter(pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int64 uid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_CreateSubstitute(pwdist::ICallableObject* caller,int32 activityId,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_DeleteSubstitute(pwdist::ICallableObject* caller,int32 activityId,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_IsSubstituteCreated(pwdist::ICallableObject* caller,int32 activityId,int64 hid);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Signup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid,int64 data,pwdist::Chunk params);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_CancelSignup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
			int _make_rpc_call_CallScript(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,const char* func,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Enter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 humanid);

			//@result desc
			int _make_rpc_call_SendActivityStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_GMStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_GMClean(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_UpdateHumanCounter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int32 human_count);

			//@result desc
			int _make_rpc_call_UpdatePCU(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count);

			//@result desc
			int _make_rpc_call_GetStartTime(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId);

			//@result desc
			int _make_rpc_call_UpdateHumanEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int64 uid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_CreateSubstitute(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_DeleteSubstitute(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_IsSubstituteCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid);
		public:
			// -------------------------------------
			//  _rpc_call_Signup
			// -------------------------------------
			class CON_Signup
			{
			public:
				CON_Signup(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CancelSignup
			// -------------------------------------
			class CON_CancelSignup
			{
			public:
				CON_CancelSignup(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CallScript
			// -------------------------------------
			class CON_CallScript
			{
			public:
				CON_CallScript(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Enter
			// -------------------------------------
			class CON_Enter
			{
			public:
				CON_Enter(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CreateSubstitute
			// -------------------------------------
			class CON_CreateSubstitute
			{
			public:
				CON_CreateSubstitute(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_DeleteSubstitute
			// -------------------------------------
			class CON_DeleteSubstitute
			{
			public:
				CON_DeleteSubstitute(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_IsSubstituteCreated
			// -------------------------------------
			class CON_IsSubstituteCreated
			{
			public:
				CON_IsSubstituteCreated(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ActivityNJTZ
		// *********************************
		class ActivityNJTZProxy : public BaseProxy
		{
		public:
			ActivityNJTZProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Init(pwdist::ICallableObject* caller,int32 round);

			//@result desc
			int _rpc_call_InitWithGuilds(pwdist::ICallableObject* caller,int64 g1,int64 g2);

			//@result desc
			int _rpc_call_Finish(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_GuildDismissed(pwdist::ICallableObject* caller,int64 guild);

			//@result desc
			int _rpc_call_GuildMemberLeaved(pwdist::ICallableObject* caller,int64 guild,int64 memberid);

			//@result desc
			int _rpc_call_QueryGuilds(pwdist::ICallableObject* caller,int64 human,int64 guildid);

			//@result desc
			int _rpc_call_SupportGuild(pwdist::ICallableObject* caller,int64 human,int64 guildid);

			//@result desc
			int _rpc_call_SupportQuery(pwdist::ICallableObject* caller,int64 human);

			//@result desc
			//@result 1, int64 gid1 [required]
			//@result 2, int64 gid2 [required]
			int _rpc_call_HistoryQuery(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_GetGBInfo(pwdist::ICallableObject* caller,int64 human);

			//@result desc
			int _rpc_call_GMClear(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_GMRefresh(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 round [required]
			int _rpc_call_GMGoToRound(pwdist::ICallableObject* caller,int32 round);
		public:

			//@result desc
			int _make_rpc_call_Init(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 round);

			//@result desc
			int _make_rpc_call_InitWithGuilds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 g1,int64 g2);

			//@result desc
			int _make_rpc_call_Finish(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_GuildDismissed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild);

			//@result desc
			int _make_rpc_call_GuildMemberLeaved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,int64 memberid);

			//@result desc
			int _make_rpc_call_QueryGuilds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int64 guildid);

			//@result desc
			int _make_rpc_call_SupportGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int64 guildid);

			//@result desc
			int _make_rpc_call_SupportQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human);

			//@result desc
			//@result 1, int64 gid1 [required]
			//@result 2, int64 gid2 [required]
			int _make_rpc_call_HistoryQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_GetGBInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human);

			//@result desc
			int _make_rpc_call_GMClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_GMRefresh(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 round [required]
			int _make_rpc_call_GMGoToRound(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 round);
		public:
			// -------------------------------------
			//  _rpc_call_HistoryQuery
			// -------------------------------------
			class CON_HistoryQuery
			{
			public:
				CON_HistoryQuery(pwdist::Port* port = NULL);
			public:
				int Return(int64 gid1,int64 gid2);
				int ReturnAsyncEx(int64 pid,int64 gid1,int64 gid2);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultGid1(pwdist::FutureObject& f);
				static int64 GetResultGid2(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GMGoToRound
			// -------------------------------------
			class CON_GMGoToRound
			{
			public:
				CON_GMGoToRound(pwdist::Port* port = NULL);
			public:
				int Return(int32 round);
				int ReturnAsyncEx(int64 pid,int32 round);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultRound(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ActivityKFMZ
		// *********************************
		class ActivityKFMZProxy : public BaseProxy
		{
		public:
			ActivityKFMZProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_KF_SyncSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nCount,pwdist::Chunk info);

			//@result desc
			int _rpc_call_KF_SyncStatus(pwdist::ICallableObject* caller,int32 nStatus,pwdist::Chunk info);

			//@result desc
			int _rpc_call_KF_SyncTTSInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nRound,pwdist::Chunk info);

			//@result desc
			int _rpc_call_KF_TTSReward(pwdist::ICallableObject* caller,int32 nWarZoneId);

			//@result desc
			int _rpc_call_GetSYBoardInfo(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_GetTTSInfo(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_UpdateSYInfo(pwdist::ICallableObject* caller,int64 nGuildId,const char* szGuildName,int64 nTotalDamage,int32 nTotalFight);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_GetTopRankInfo(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int64 nLadderLevel [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int64 nGameMapId [required]
			int _rpc_call_GetEnterLadderTTSInfo(pwdist::ICallableObject* caller,int64 hid,int64 nGuildId);

			//@result desc
			int _rpc_call_GMCommand(pwdist::ICallableObject* caller,int64 hid,const char* param1,const char* param2);
		public:

			//@result desc
			int _make_rpc_call_KF_SyncSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nCount,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_KF_SyncStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nStatus,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_KF_SyncTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nRound,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_KF_TTSReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId);

			//@result desc
			int _make_rpc_call_GetSYBoardInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_GetTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_UpdateSYInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nGuildId,const char* szGuildName,int64 nTotalDamage,int32 nTotalFight);

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_GetTopRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int64 nLadderLevel [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int64 nGameMapId [required]
			int _make_rpc_call_GetEnterLadderTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 nGuildId);

			//@result desc
			int _make_rpc_call_GMCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,const char* param1,const char* param2);
		public:
			// -------------------------------------
			//  _rpc_call_GetTopRankInfo
			// -------------------------------------
			class CON_GetTopRankInfo
			{
			public:
				CON_GetTopRankInfo(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetEnterLadderTTSInfo
			// -------------------------------------
			class CON_GetEnterLadderTTSInfo
			{
			public:
				CON_GetEnterLadderTTSInfo(pwdist::Port* port = NULL);
			public:
				int Return(int64 nLadderLevel,int64 nBaseMapId,int64 nGameMapId);
				int ReturnAsyncEx(int64 pid,int64 nLadderLevel,int64 nBaseMapId,int64 nGameMapId);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultNladderlevel(pwdist::FutureObject& f);
				static int64 GetResultNbasemapid(pwdist::FutureObject& f);
				static int64 GetResultNgamemapid(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ActivityKFMZ_Ladder
		// *********************************
		class ActivityKFMZ_LadderProxy : public BaseProxy
		{
		public:
			ActivityKFMZ_LadderProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_KF_GMCommand(pwdist::ICallableObject* caller,const char* param1,const char* param2);

			//@result desc
			int _rpc_call_KF_UpdateSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,pwdist::Chunk info);

			//@result desc
			int _rpc_call_KF_ObtainSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int64 nServerGroupId);

			//@result desc
			int _rpc_call_GuildWin(pwdist::ICallableObject* caller,int64 nGuildId);
		public:

			//@result desc
			int _make_rpc_call_KF_GMCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* param1,const char* param2);

			//@result desc
			int _make_rpc_call_KF_UpdateSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_KF_ObtainSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int64 nServerGroupId);

			//@result desc
			int _make_rpc_call_GuildWin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nGuildId);
		public:
		};

		// *********************************
		// rpc ProxyClass ActivityRunCar
		// *********************************
		class ActivityRunCarProxy : public BaseProxy
		{
		public:
			ActivityRunCarProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 result [required]
			int _rpc_call_CreateRunCar(pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int64 nGameMapId,int32 x,int32 y,int32 z);

			//@result desc
			int _rpc_call_SyncRunCarPosition(pwdist::ICallableObject* caller,int64 hid,int64 nBaseMapId,int32 x,int32 y,int32 z);

			//@result desc
			int _rpc_call_FinishRunCar(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int32 x [required]
			//@result 4, int32 y [required]
			//@result 5, int32 z [required]
			int _rpc_call_GetRunCarPoisition(pwdist::ICallableObject* caller,int64 hid);
		public:

			//@result desc
			//@result 1, int32 result [required]
			int _make_rpc_call_CreateRunCar(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int64 nGameMapId,int32 x,int32 y,int32 z);

			//@result desc
			int _make_rpc_call_SyncRunCarPosition(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 nBaseMapId,int32 x,int32 y,int32 z);

			//@result desc
			int _make_rpc_call_FinishRunCar(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int32 x [required]
			//@result 4, int32 y [required]
			//@result 5, int32 z [required]
			int _make_rpc_call_GetRunCarPoisition(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);
		public:
			// -------------------------------------
			//  _rpc_call_CreateRunCar
			// -------------------------------------
			class CON_CreateRunCar
			{
			public:
				CON_CreateRunCar(pwdist::Port* port = NULL);
			public:
				int Return(int32 result);
				int ReturnAsyncEx(int64 pid,int32 result);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetRunCarPoisition
			// -------------------------------------
			class CON_GetRunCarPoisition
			{
			public:
				CON_GetRunCarPoisition(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,int64 nBaseMapId,int32 x,int32 y,int32 z);
				int ReturnAsyncEx(int64 pid,int32 result,int64 nBaseMapId,int32 x,int32 y,int32 z);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static int64 GetResultNbasemapid(pwdist::FutureObject& f);
				static int32 GetResultX(pwdist::FutureObject& f);
				static int32 GetResultY(pwdist::FutureObject& f);
				static int32 GetResultZ(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ActivityLGKJ
		// *********************************
		class ActivityLGKJProxy : public BaseProxy
		{
		public:
			ActivityLGKJProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Finish(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Finish(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplArena
		// *********************************
		class SImplArenaProxy : public SImplBaseProxy
		{
		public:
			SImplArenaProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

		// *********************************
		// rpc ProxyClass ArenaQueueMgr
		// *********************************
		class ArenaQueueMgrProxy : public BaseProxy
		{
		public:
			ArenaQueueMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplBattle
		// *********************************
		class SImplBattleProxy : public SImplBaseProxy
		{
		public:
			SImplBattleProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

		// *********************************
		// rpc ProxyClass BattleQueueMgr
		// *********************************
		class BattleQueueMgrProxy : public BaseProxy
		{
		public:
			BattleQueueMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplMisc
		// *********************************
		class SImplMiscProxy : public SImplBaseProxy
		{
		public:
			SImplMiscProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

		// *********************************
		// rpc ProxyClass GameSellerMgr
		// *********************************
		class GameSellerMgrProxy : public BaseProxy
		{
		public:
			GameSellerMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
			int _rpc_call_BecomeGS(pwdist::ICallableObject* caller,int64 hid,const char* passport,int32 lev);

			//@result desc
			int _rpc_call_ChargeNotify(pwdist::ICallableObject* caller,int64 hid,int64 date,int64 gold);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
			int _make_rpc_call_BecomeGS(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,const char* passport,int32 lev);

			//@result desc
			int _make_rpc_call_ChargeNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 date,int64 gold);
		public:
			// -------------------------------------
			//  _rpc_call_BecomeGS
			// -------------------------------------
			class CON_BecomeGS
			{
			public:
				CON_BecomeGS(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* info);
				int ReturnAsyncEx(int64 pid,int32 code,const char* info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ShopMgr
		// *********************************
		class ShopMgrProxy : public BaseProxy
		{
		public:
			ShopMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
			int _rpc_call_ShopQuery(pwdist::ICallableObject* caller,int32 shopid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
			int _rpc_call_ShopBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid);
		public:

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
			int _make_rpc_call_ShopQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 shopid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
			int _make_rpc_call_ShopBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid);
		public:
			// -------------------------------------
			//  _rpc_call_ShopQuery
			// -------------------------------------
			class CON_ShopQuery
			{
			public:
				CON_ShopQuery(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ShopBuy
			// -------------------------------------
			class CON_ShopBuy
			{
			public:
				CON_ShopBuy(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 leftCount);
				int ReturnAsyncEx(int64 pid,int32 code,int32 leftCount);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultLeftcount(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass LotteryMgr
		// *********************************
		class LotteryMgrProxy : public BaseProxy
		{
		public:
			LotteryMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass LotteryPrizeMgr
		// *********************************
		class LotteryPrizeMgrProxy : public BaseProxy
		{
		public:
			LotteryPrizeMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass ChestMgr
		// *********************************
		class ChestMgrProxy : public BaseProxy
		{
		public:
			ChestMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt);

			//@result desc
			int _make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass MallMgr
		// *********************************
		class MallMgrProxy : public BaseProxy
		{
		public:
			MallMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 indexLimit [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _rpc_call_MallQuery(pwdist::ICallableObject* caller,int32 type,int32 indexMin,int32 indexMax,int32 nSex);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
			int _rpc_call_MallBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid);
		public:

			//@result desc
			//@result 1, int32 indexLimit [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _make_rpc_call_MallQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 indexMin,int32 indexMax,int32 nSex);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
			int _make_rpc_call_MallBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid);
		public:
			// -------------------------------------
			//  _rpc_call_MallQuery
			// -------------------------------------
			class CON_MallQuery
			{
			public:
				CON_MallQuery(pwdist::Port* port = NULL);
			public:
				int Return(int32 indexLimit,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 indexLimit,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultIndexlimit(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_MallBuy
			// -------------------------------------
			class CON_MallBuy
			{
			public:
				CON_MallBuy(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 leftCount);
				int ReturnAsyncEx(int64 pid,int32 code,int32 leftCount);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultLeftcount(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass AwardServerMgr
		// *********************************
		class AwardServerMgrProxy : public BaseProxy
		{
		public:
			AwardServerMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int64 id [required]
			int _rpc_call_CreateAward(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_QueryAward(pwdist::ICallableObject* caller,int64 awardedLastId);
		public:

			//@result desc
			//@result 1, int64 id [required]
			int _make_rpc_call_CreateAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_QueryAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 awardedLastId);
		public:
			// -------------------------------------
			//  _rpc_call_CreateAward
			// -------------------------------------
			class CON_CreateAward
			{
			public:
				CON_CreateAward(pwdist::Port* port = NULL);
			public:
				int Return(int64 id);
				int ReturnAsyncEx(int64 pid,int64 id);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultId(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass WarlordMgr
		// *********************************
		class WarlordMgrProxy : public BaseProxy
		{
		public:
			WarlordMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, pwdist::Chunk buf [required]
			int _rpc_call_WarlordQueryByID(pwdist::ICallableObject* caller,int64 hid,bool createRank);

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* passport [required]
			int _rpc_call_WarlordQuery(pwdist::ICallableObject* caller,int64 rank);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
			int _rpc_call_CombatSucc(pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
			int _rpc_call_CombatFail(pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 worshipToday [required]
			//@result 3, int64 worshipTotal [required]
			int _rpc_call_WarlordWorship(pwdist::ICallableObject* caller,int64 rivalID);

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
			int _rpc_call_AddWorshiped(pwdist::ICallableObject* caller,int64 rivalID,int32 cnt);

			//@result desc
			int _rpc_call_FetchWarlordRank(pwdist::ICallableObject* caller,int32 type,int32 cnt);

			//@result desc
			int _rpc_call_GrantRankAward(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
			int _rpc_call_QueryWorshiped(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _rpc_call_AdjustRank(pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			int _rpc_call_QueryChallengeWarlord(pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk param);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* passport [required]
			int _rpc_call_ChallengeWarlord(pwdist::ICallableObject* caller,pwdist::Chunk param);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* passport [required]
			int _rpc_call_QueryWarlordInfo(pwdist::ICallableObject* caller,int64 rank);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_QueryWarlordRankList(pwdist::ICallableObject* caller,int64 hid);
		public:

			//@result desc
			//@result 1, pwdist::Chunk buf [required]
			int _make_rpc_call_WarlordQueryByID(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,bool createRank);

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* passport [required]
			int _make_rpc_call_WarlordQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rank);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
			int _make_rpc_call_CombatSucc(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
			int _make_rpc_call_CombatFail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 worshipToday [required]
			//@result 3, int64 worshipTotal [required]
			int _make_rpc_call_WarlordWorship(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rivalID);

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
			int _make_rpc_call_AddWorshiped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rivalID,int32 cnt);

			//@result desc
			int _make_rpc_call_FetchWarlordRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 cnt);

			//@result desc
			int _make_rpc_call_GrantRankAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
			int _make_rpc_call_QueryWorshiped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			int _make_rpc_call_AdjustRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			int _make_rpc_call_QueryChallengeWarlord(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk param);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* passport [required]
			int _make_rpc_call_ChallengeWarlord(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk param);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* passport [required]
			int _make_rpc_call_QueryWarlordInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rank);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_QueryWarlordRankList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);
		public:
			// -------------------------------------
			//  _rpc_call_WarlordQueryByID
			// -------------------------------------
			class CON_WarlordQueryByID
			{
			public:
				CON_WarlordQueryByID(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk buf);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk buf);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultBuf(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_WarlordQuery
			// -------------------------------------
			class CON_WarlordQuery
			{
			public:
				CON_WarlordQuery(pwdist::Port* port = NULL);
			public:
				int Return(int64 hid,const char* passport);
				int ReturnAsyncEx(int64 pid,int64 hid,const char* passport);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultHid(pwdist::FutureObject& f);
				static const char* GetResultPassport(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CombatSucc
			// -------------------------------------
			class CON_CombatSucc
			{
			public:
				CON_CombatSucc(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,pwdist::Chunk buf,pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk buf,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultBuf(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CombatFail
			// -------------------------------------
			class CON_CombatFail
			{
			public:
				CON_CombatFail(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,pwdist::Chunk buf,pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk buf,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultBuf(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_WarlordWorship
			// -------------------------------------
			class CON_WarlordWorship
			{
			public:
				CON_WarlordWorship(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,int64 worshipToday,int64 worshipTotal);
				int ReturnAsyncEx(int64 pid,int32 result,int64 worshipToday,int64 worshipTotal);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static int64 GetResultWorshiptoday(pwdist::FutureObject& f);
				static int64 GetResultWorshiptotal(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_AddWorshiped
			// -------------------------------------
			class CON_AddWorshiped
			{
			public:
				CON_AddWorshiped(pwdist::Port* port = NULL);
			public:
				int Return(int64 today,int64 total);
				int ReturnAsyncEx(int64 pid,int64 today,int64 total);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultToday(pwdist::FutureObject& f);
				static int64 GetResultTotal(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryWorshiped
			// -------------------------------------
			class CON_QueryWorshiped
			{
			public:
				CON_QueryWorshiped(pwdist::Port* port = NULL);
			public:
				int Return(int64 today,int64 total);
				int ReturnAsyncEx(int64 pid,int64 today,int64 total);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultToday(pwdist::FutureObject& f);
				static int64 GetResultTotal(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryChallengeWarlord
			// -------------------------------------
			class CON_QueryChallengeWarlord
			{
			public:
				CON_QueryChallengeWarlord(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_ChallengeWarlord
			// -------------------------------------
			class CON_ChallengeWarlord
			{
			public:
				CON_ChallengeWarlord(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* passport);
				int ReturnAsyncEx(int64 pid,int32 code,const char* passport);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultPassport(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryWarlordInfo
			// -------------------------------------
			class CON_QueryWarlordInfo
			{
			public:
				CON_QueryWarlordInfo(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk info,const char* passport);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk info,const char* passport);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
				static const char* GetResultPassport(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryWarlordRankList
			// -------------------------------------
			class CON_QueryWarlordRankList
			{
			public:
				CON_QueryWarlordRankList(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass OpenAuctionMgr
		// *********************************
		class OpenAuctionMgrProxy : public BaseProxy
		{
		public:
			OpenAuctionMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _rpc_call_QueryItem(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_BidCheck(pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_GMRestartAuction(pwdist::ICallableObject* caller,bool bForce,int32 type);
		public:

			//@result desc
			//@result 1, pwdist::Chunk info [required]
			int _make_rpc_call_QueryItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_BidCheck(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_GMRestartAuction(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool bForce,int32 type);
		public:
			// -------------------------------------
			//  _rpc_call_QueryItem
			// -------------------------------------
			class CON_QueryItem
			{
			public:
				CON_QueryItem(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GMRestartAuction
			// -------------------------------------
			class CON_GMRestartAuction
			{
			public:
				CON_GMRestartAuction(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass BroadcastMgr
		// *********************************
		class BroadcastMgrProxy : public BaseProxy
		{
		public:
			BroadcastMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Create(pwdist::ICallableObject* caller,const char* msgid,const char* msg,int32 latencyMin,int32 intervalMin,int32 times);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Delete(pwdist::ICallableObject* caller,const char* msgid);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* msgid,const char* msg,int32 latencyMin,int32 intervalMin,int32 times);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Delete(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* msgid);
		public:
			// -------------------------------------
			//  _rpc_call_Create
			// -------------------------------------
			class CON_Create
			{
			public:
				CON_Create(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_Delete
			// -------------------------------------
			class CON_Delete
			{
			public:
				CON_Delete(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass ChatMgr
		// *********************************
		class ChatMgrProxy : public BaseProxy
		{
		public:
			ChatMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryChatMsgList(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_SendChatMsg(pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,const char* content,pwdist::Chunk to_info);

			//@result desc
			int _rpc_call_AckChatMsgRecved(pwdist::ICallableObject* caller,int64 from,int64 to,int64 timestamp);

			//@result desc
			int _rpc_call_QueryChatContactList(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk contacts);

			//@result desc
			int _rpc_call_SendChatMsgToHuman(pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _rpc_call_CachedChatItems(pwdist::ICallableObject* caller,pwdist::Chunk items,int64 timestamp);

			//@result desc
			//@result 1, pwdist::Chunk item [required]
			int _rpc_call_QueryCachedItem(pwdist::ICallableObject* caller,int64 from,int64 to,int64 itemid,int64 timestamp);

			//@result desc
			int _rpc_call_SendLadderHorn(pwdist::ICallableObject* caller,int32 zone,pwdist::Chunk info);
		public:

			//@result desc
			int _make_rpc_call_QueryChatMsgList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_SendChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,const char* content,pwdist::Chunk to_info);

			//@result desc
			int _make_rpc_call_AckChatMsgRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,int64 timestamp);

			//@result desc
			int _make_rpc_call_QueryChatContactList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk contacts);

			//@result desc
			int _make_rpc_call_SendChatMsgToHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,int32 msgid,pwdist::Chunk buffer);

			//@result desc
			int _make_rpc_call_CachedChatItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk items,int64 timestamp);

			//@result desc
			//@result 1, pwdist::Chunk item [required]
			int _make_rpc_call_QueryCachedItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,int64 itemid,int64 timestamp);

			//@result desc
			int _make_rpc_call_SendLadderHorn(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zone,pwdist::Chunk info);
		public:
			// -------------------------------------
			//  _rpc_call_QueryCachedItem
			// -------------------------------------
			class CON_QueryCachedItem
			{
			public:
				CON_QueryCachedItem(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk item);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk item);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultItem(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass OperationsMgr
		// *********************************
		class OperationsMgrProxy : public BaseProxy
		{
		public:
			OperationsMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Create(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_HumanReady(pwdist::ICallableObject* caller,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_HumanReady(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass PassportOperationsMgr
		// *********************************
		class PassportOperationsMgrProxy : public BaseProxy
		{
		public:
			PassportOperationsMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Create(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_HumanReady(pwdist::ICallableObject* caller,const char* pasport);
		public:

			//@result desc
			int _make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_HumanReady(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* pasport);
		public:
		};

		// *********************************
		// rpc ProxyClass MailMgr
		// *********************************
		class MailMgrProxy : public BaseProxy
		{
		public:
			MailMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryMailList(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_SendMail(pwdist::ICallableObject* caller,pwdist::Chunk mailbuf);

			//@result desc
			int _rpc_call_SendMultiMail(pwdist::ICallableObject* caller,pwdist::Chunk mailbuf);

			//@result desc
			int _rpc_call_AckMailRecved(pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _rpc_call_RecvMailReward(pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _rpc_call_AckMailRewardRecved(pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _rpc_call_DeleteMail(pwdist::ICallableObject* caller,int64 uid,int64 mid);
		public:

			//@result desc
			int _make_rpc_call_QueryMailList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_SendMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk mailbuf);

			//@result desc
			int _make_rpc_call_SendMultiMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk mailbuf);

			//@result desc
			int _make_rpc_call_AckMailRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _make_rpc_call_RecvMailReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _make_rpc_call_AckMailRewardRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid);

			//@result desc
			int _make_rpc_call_DeleteMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid);
		public:
		};

		// *********************************
		// rpc ProxyClass LoginQueueMgr
		// *********************************
		class LoginQueueMgrProxy : public BaseProxy
		{
		public:
			LoginQueueMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_RequestLoginGate(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_ConnectionClosedWhenLogin(pwdist::ICallableObject* caller,int64 id);
		public:

			//@result desc
			int _make_rpc_call_RequestLoginGate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_ConnectionClosedWhenLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);
		public:
		};

		// *********************************
		// rpc ProxyClass NotifyBallMgr
		// *********************************
		class NotifyBallMgrProxy : public BaseProxy
		{
		public:
			NotifyBallMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryNotifyBallList(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_SendNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf,int64 uid);

			//@result desc
			int _rpc_call_SendMultiNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf);

			//@result desc
			int _rpc_call_DeleteNotifyBall(pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk info);
		public:

			//@result desc
			int _make_rpc_call_QueryNotifyBallList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_SendNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf,int64 uid);

			//@result desc
			int _make_rpc_call_SendMultiNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf);

			//@result desc
			int _make_rpc_call_DeleteNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk info);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplAdventure
		// *********************************
		class SImplAdventureProxy : public SImplBaseProxy
		{
		public:
			SImplAdventureProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_CreateAdventure(pwdist::ICallableObject* caller,int32 cfg,int64 creator,pwdist::Chunk humans);

			//@result desc
			int _rpc_call_Leave(pwdist::ICallableObject* caller,int64 human,int32 flags);
		public:

			//@result desc
			int _make_rpc_call_CreateAdventure(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfg,int64 creator,pwdist::Chunk humans);

			//@result desc
			int _make_rpc_call_Leave(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int32 flags);
		public:
		};

		// *********************************
		// rpc ProxyClass TeamMgr
		// *********************************
		class TeamMgrProxy : public BaseProxy
		{
		public:
			TeamMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_CreateTeam(pwdist::ICallableObject* caller,const char* tname,int64 uid,int32 ladder_level,int32 nFightPointLimit,bool bAutoJoin);

			//@result desc
			int _rpc_call_DismissTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_JoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,const char* tname);

			//@result desc
			int _rpc_call_ApplyJoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_AgreeJoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 operId,int64 applicantId);

			//@result desc
			int _rpc_call_OperTeam(pwdist::ICallableObject* caller,int64 tid,int64 operId,int32 type,int32 nParam);

			//@result desc
			int _rpc_call_InviteTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid);

			//@result desc
			int _rpc_call_InviteTeamReturn(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_LeaveTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,bool bForce);

			//@result desc
			int _rpc_call_KickTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid);

			//@result desc
			int _rpc_call_RecruitTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 type,int64 context);

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryMembers(pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _rpc_call_RestoreTeam(pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_ChangeTeamMemberAuth(pwdist::ICallableObject* caller,int64 tid,int64 leader,int64 target,int32 auth);

			//@result desc
			int _rpc_call_ChangeTeamLeader(pwdist::ICallableObject* caller,int64 tid,int64 oper,int64 target);

			//@result desc
			int _rpc_call_BroadcastTeam(pwdist::ICallableObject* caller,int64 tid,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _rpc_call_ChangeTeamMemberFlag(pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 flag,bool apply);

			//@result desc
			int _rpc_call_FillTeamMember(pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _rpc_call_ChangeStateFreeze(pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _rpc_call_TeamReward(pwdist::ICallableObject* caller,int64 tid,int64 hid,int32 rank,bool succ);

			//@result desc
			int _rpc_call_SyncLadderTeamInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _rpc_call_SyncNormalTeamInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _rpc_call_SyncLadderTeamReward(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);
		public:

			//@result desc
			int _make_rpc_call_CreateTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* tname,int64 uid,int32 ladder_level,int32 nFightPointLimit,bool bAutoJoin);

			//@result desc
			int _make_rpc_call_DismissTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_JoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,const char* tname);

			//@result desc
			int _make_rpc_call_ApplyJoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_AgreeJoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 operId,int64 applicantId);

			//@result desc
			int _make_rpc_call_OperTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 operId,int32 type,int32 nParam);

			//@result desc
			int _make_rpc_call_InviteTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid);

			//@result desc
			int _make_rpc_call_InviteTeamReturn(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_LeaveTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,bool bForce);

			//@result desc
			int _make_rpc_call_KickTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid);

			//@result desc
			int _make_rpc_call_RecruitTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 type,int64 context);

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryMembers(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _make_rpc_call_RestoreTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_ChangeTeamMemberAuth(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 leader,int64 target,int32 auth);

			//@result desc
			int _make_rpc_call_ChangeTeamLeader(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 oper,int64 target);

			//@result desc
			int _make_rpc_call_BroadcastTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2);

			//@result desc
			int _make_rpc_call_ChangeTeamMemberFlag(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 flag,bool apply);

			//@result desc
			int _make_rpc_call_FillTeamMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _make_rpc_call_ChangeStateFreeze(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid);

			//@result desc
			int _make_rpc_call_TeamReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 hid,int32 rank,bool succ);

			//@result desc
			int _make_rpc_call_SyncLadderTeamInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _make_rpc_call_SyncNormalTeamInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);

			//@result desc
			int _make_rpc_call_SyncLadderTeamReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplRanklist
		// *********************************
		class SImplRanklistProxy : public SImplBaseProxy
		{
		public:
			SImplRanklistProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid,int64 rtype,int32 rpage);

			//@result desc
			int _rpc_call_QueryTopTen(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_QueryDetail(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryPlayer(pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname);

			//@result desc
			int _rpc_call_UpdateGuildFightPoint(pwdist::ICallableObject* caller,pwdist::Chunk fightpoints);

			//@result desc
			int _rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ClearRanklist(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_FetchRanklistData(pwdist::ICallableObject* caller,int32 callid,int32 type,int32 cnt);

			//@result desc
			//@result 1, pwdist::Chunk result [required]
			int _rpc_call_FetchRanklistDataEx(pwdist::ICallableObject* caller,int32 type,int32 cnt);

			//@result desc
			int _rpc_call_EndedArenaSeason(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_QuerySeasonOrder(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			//@result 1, int32 level [required]
			int _rpc_call_GetHumanAverageLevel(pwdist::ICallableObject* caller,int32 topcount);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_RebuildRanklistMsg(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_GuildDismissed(pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_QueryGlobalPlayer(pwdist::ICallableObject* caller,int64 uid,int32 rtype,int64 target);

			//@result desc
			int _rpc_call_QueryGlobal(pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _rpc_call_GlobalRankUpdate(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk result);

			//@result desc
			int _rpc_call_StartHotActivity(pwdist::ICallableObject* caller,int32 type,int32 subtype);

			//@result desc
			int _rpc_call_EndedHotActivity(pwdist::ICallableObject* caller,int32 type,int32 subtype);

			//@result desc
			int _rpc_call_SyncHumanOfflineData(pwdist::ICallableObject* caller,pwdist::Chunk info,const char* data,int32 type);

			//@result desc
			//@result 1, int32 errno [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* result [required]
			//@result 4, pwdist::Chunk extInfo [required]
			int _rpc_call_GetHumanOfflineData(pwdist::ICallableObject* caller,int64 hid,int32 type);

			//@result desc
			//@result 1, int32 order [required]
			int _rpc_call_GetRankOrder(pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _rpc_call_SaveHeroCard(pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk info [required]
			int _rpc_call_GetHeroCard(pwdist::ICallableObject* caller,int64 hid);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,int32 rpage);

			//@result desc
			int _make_rpc_call_QueryTopTen(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_QueryDetail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryPlayer(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname);

			//@result desc
			int _make_rpc_call_UpdateGuildFightPoint(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk fightpoints);

			//@result desc
			int _make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ClearRanklist(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_FetchRanklistData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 callid,int32 type,int32 cnt);

			//@result desc
			//@result 1, pwdist::Chunk result [required]
			int _make_rpc_call_FetchRanklistDataEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 cnt);

			//@result desc
			int _make_rpc_call_EndedArenaSeason(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_QuerySeasonOrder(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			//@result 1, int32 level [required]
			int _make_rpc_call_GetHumanAverageLevel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 topcount);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_RebuildRanklistMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_GuildDismissed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_QueryGlobalPlayer(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 rtype,int64 target);

			//@result desc
			int _make_rpc_call_QueryGlobal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _make_rpc_call_GlobalRankUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk result);

			//@result desc
			int _make_rpc_call_StartHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 subtype);

			//@result desc
			int _make_rpc_call_EndedHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 subtype);

			//@result desc
			int _make_rpc_call_SyncHumanOfflineData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,const char* data,int32 type);

			//@result desc
			//@result 1, int32 errno [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* result [required]
			//@result 4, pwdist::Chunk extInfo [required]
			int _make_rpc_call_GetHumanOfflineData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type);

			//@result desc
			//@result 1, int32 order [required]
			int _make_rpc_call_GetRankOrder(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type);

			//@result desc
			int _make_rpc_call_SaveHeroCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk info [required]
			int _make_rpc_call_GetHeroCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid);
		public:
			// -------------------------------------
			//  _rpc_call_FetchRanklistDataEx
			// -------------------------------------
			class CON_FetchRanklistDataEx
			{
			public:
				CON_FetchRanklistDataEx(pwdist::Port* port = NULL);
			public:
				int Return(pwdist::Chunk result);
				int ReturnAsyncEx(int64 pid,pwdist::Chunk result);
				int CancelAsyncReturn(int64 pid);
			public:
				static pwdist::Chunk GetResultResult(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetHumanAverageLevel
			// -------------------------------------
			class CON_GetHumanAverageLevel
			{
			public:
				CON_GetHumanAverageLevel(pwdist::Port* port = NULL);
			public:
				int Return(int32 level);
				int ReturnAsyncEx(int64 pid,int32 level);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultLevel(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_RebuildRanklistMsg
			// -------------------------------------
			class CON_RebuildRanklistMsg
			{
			public:
				CON_RebuildRanklistMsg(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GuildDismissed
			// -------------------------------------
			class CON_GuildDismissed
			{
			public:
				CON_GuildDismissed(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetHumanOfflineData
			// -------------------------------------
			class CON_GetHumanOfflineData
			{
			public:
				CON_GetHumanOfflineData(pwdist::Port* port = NULL);
			public:
				int Return(int32 errno,pwdist::Chunk info,const char* result,pwdist::Chunk extInfo);
				int ReturnAsyncEx(int64 pid,int32 errno,pwdist::Chunk info,const char* result,pwdist::Chunk extInfo);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultErrno(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
				static const char* GetResultResult(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultExtinfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetRankOrder
			// -------------------------------------
			class CON_GetRankOrder
			{
			public:
				CON_GetRankOrder(pwdist::Port* port = NULL);
			public:
				int Return(int32 order);
				int ReturnAsyncEx(int64 pid,int32 order);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultOrder(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetHeroCard
			// -------------------------------------
			class CON_GetHeroCard
			{
			public:
				CON_GetHeroCard(pwdist::Port* port = NULL);
			public:
				int Return(int32 result,pwdist::Chunk info);
				int ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultResult(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplEntranceSrv
		// *********************************
		class SImplEntranceSrvProxy : public BaseProxy
		{
		public:
			SImplEntranceSrvProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_HumanInvoke(pwdist::ICallableObject* caller,int64 gid,int64 uid,pwdist::Chunk rpc);

			//@result desc
			int _rpc_call_LadderEntranceCli(pwdist::ICallableObject* caller,bool expectResult,int64 server_group,pwdist::Chunk _call);

			//@result desc
			int _rpc_call_BroadCastCall(pwdist::ICallableObject* caller,bool expectResult,pwdist::Chunk _call);

			//@result desc
			int _rpc_call_LadderLogin(pwdist::ICallableObject* caller,const char* account,const char* token);

			//@result desc
			int _rpc_call_QueryServerName(pwdist::ICallableObject* caller,int32 server_group);

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* token [required]
			int _rpc_call_CreateLadderToken(pwdist::ICallableObject* caller,const char* account,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
			int _rpc_call_BroadcastGM(pwdist::ICallableObject* caller,const char* text);

			//@result desc
			//@result 1, const char* servers [required]
			int _rpc_call_QueryConnectedServer(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_HumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,pwdist::Chunk rpc);

			//@result desc
			int _make_rpc_call_LadderEntranceCli(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,int64 server_group,pwdist::Chunk _call);

			//@result desc
			int _make_rpc_call_BroadCastCall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,pwdist::Chunk _call);

			//@result desc
			int _make_rpc_call_LadderLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,const char* token);

			//@result desc
			int _make_rpc_call_QueryServerName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 server_group);

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* token [required]
			int _make_rpc_call_CreateLadderToken(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 hid);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
			int _make_rpc_call_BroadcastGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text);

			//@result desc
			//@result 1, const char* servers [required]
			int _make_rpc_call_QueryConnectedServer(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
			// -------------------------------------
			//  _rpc_call_CreateLadderToken
			// -------------------------------------
			class CON_CreateLadderToken
			{
			public:
				CON_CreateLadderToken(pwdist::Port* port = NULL);
			public:
				int Return(int64 hid,const char* token);
				int ReturnAsyncEx(int64 pid,int64 hid,const char* token);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultHid(pwdist::FutureObject& f);
				static const char* GetResultToken(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_BroadcastGM
			// -------------------------------------
			class CON_BroadcastGM
			{
			public:
				CON_BroadcastGM(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* info);
				int ReturnAsyncEx(int64 pid,int32 code,const char* info);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultInfo(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_QueryConnectedServer
			// -------------------------------------
			class CON_QueryConnectedServer
			{
			public:
				CON_QueryConnectedServer(pwdist::Port* port = NULL);
			public:
				int Return(const char* servers);
				int ReturnAsyncEx(int64 pid,const char* servers);
				int CancelAsyncReturn(int64 pid);
			public:
				static const char* GetResultServers(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplEntranceCli
		// *********************************
		class SImplEntranceCliProxy : public BaseProxy
		{
		public:
			SImplEntranceCliProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryConfigs(pwdist::ICallableObject* caller,int64 human_id);

			//@result desc
			int _rpc_call_LadderEntranceSrv(pwdist::ICallableObject* caller,bool expectResult,int32 ladderLevel,pwdist::Chunk _call);

			//@result desc
			int _rpc_call_LadderHumanInvoke(pwdist::ICallableObject* caller,int32 ladderLevel,int64 uid,pwdist::Chunk rpc);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_LaddderIsConnected(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_QueryConfigs(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human_id);

			//@result desc
			int _make_rpc_call_LadderEntranceSrv(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,int32 ladderLevel,pwdist::Chunk _call);

			//@result desc
			int _make_rpc_call_LadderHumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 ladderLevel,int64 uid,pwdist::Chunk rpc);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_LaddderIsConnected(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
			// -------------------------------------
			//  _rpc_call_LaddderIsConnected
			// -------------------------------------
			class CON_LaddderIsConnected
			{
			public:
				CON_LaddderIsConnected(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplMultiplayerDungeon
		// *********************************
		class SImplMultiplayerDungeonProxy : public SImplBaseProxy
		{
		public:
			SImplMultiplayerDungeonProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,bool all);
		public:

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,bool all);
		public:
		};

		// *********************************
		// rpc ProxyClass MultiplayerDungeonMgr
		// *********************************
		class MultiplayerDungeonMgrProxy : public BaseProxy
		{
		public:
			MultiplayerDungeonMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Start(pwdist::ICallableObject* caller,int64 tid,int64 leader);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 timeout [required]
			int _rpc_call_StartMatch(pwdist::ICallableObject* caller,int64 humanId);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 humanId);
		public:

			//@result desc
			int _make_rpc_call_Start(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 leader);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 timeout [required]
			int _make_rpc_call_StartMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId);
		public:
			// -------------------------------------
			//  _rpc_call_StartMatch
			// -------------------------------------
			class CON_StartMatch
			{
			public:
				CON_StartMatch(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int32 timeout);
				int ReturnAsyncEx(int64 pid,int32 code,int32 timeout);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int32 GetResultTimeout(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CancelMatch
			// -------------------------------------
			class CON_CancelMatch
			{
			public:
				CON_CancelMatch(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplLog
		// *********************************
		class SImplLogProxy
		{
		public:
			SImplLogProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Write(pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _rpc_call_Write_WM(pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _rpc_call_WriteBetaLog(pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _rpc_call_ZeroHour(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_Write_MData(pwdist::ICallableObject* caller,int32 type,const char* text);
		public:

			//@result desc
			int _make_rpc_call_Write(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _make_rpc_call_Write_WM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _make_rpc_call_WriteBetaLog(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text);

			//@result desc
			int _make_rpc_call_ZeroHour(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_Write_MData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass NameMgr
		// *********************************
		class NameMgrProxy
		{
		public:
			NameMgrProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_Check(pwdist::ICallableObject* caller,const char* name);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_TakeUp(pwdist::ICallableObject* caller,const char* name,const char* info);

			//@result desc
			int _rpc_call_Free(pwdist::ICallableObject* caller,const char* name);
		public:

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_Check(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_TakeUp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,const char* info);

			//@result desc
			int _make_rpc_call_Free(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name);
		public:
			// -------------------------------------
			//  _rpc_call_Check
			// -------------------------------------
			class CON_Check
			{
			public:
				CON_Check(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_TakeUp
			// -------------------------------------
			class CON_TakeUp
			{
			public:
				CON_TakeUp(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplCommonActivity
		// *********************************
		class SImplCommonActivityProxy : public SImplBaseProxy
		{
		public:
			SImplCommonActivityProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryActivity(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_Reward(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _rpc_call_FinishGoal(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _rpc_call_ResetGoal(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _rpc_call_CA_UpdateRanklist(pwdist::ICallableObject* caller,pwdist::Chunk info,int32 type);

			//@result desc
			int _rpc_call_set_end(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_set_reward_end(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_set_kaifu(pwdist::ICallableObject* caller,int64 uid,int32 kaifu);

			//@result desc
			int _rpc_call_HumanCharge(pwdist::ICallableObject* caller,int64 uid,int64 gold);

			//@result desc
			int _rpc_call_HumanSpend(pwdist::ICallableObject* caller,int64 uid,int64 gold);

			//@result desc
			int _rpc_call_QueryPlayerRank(pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname);

			//@result desc
			int _rpc_call_web_query_activity(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_web_set_activitytime(pwdist::ICallableObject* caller,int64 time);
		public:

			//@result desc
			int _make_rpc_call_QueryActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_Reward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _make_rpc_call_FinishGoal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _make_rpc_call_ResetGoal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _make_rpc_call_CA_UpdateRanklist(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int32 type);

			//@result desc
			int _make_rpc_call_set_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_set_reward_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_set_kaifu(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 kaifu);

			//@result desc
			int _make_rpc_call_HumanCharge(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 gold);

			//@result desc
			int _make_rpc_call_HumanSpend(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 gold);

			//@result desc
			int _make_rpc_call_QueryPlayerRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname);

			//@result desc
			int _make_rpc_call_web_query_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_web_set_activitytime(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 time);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplHotActivity
		// *********************************
		class SImplHotActivityProxy : public SImplBaseProxy
		{
		public:
			SImplHotActivityProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_QueryActivity(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_set_end(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_set_reward_end(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_set_kaifu(pwdist::ICallableObject* caller,int64 uid,int32 kaifu);

			//@result desc
			int _rpc_call_web_open_activity(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _rpc_call_web_close_activity(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_web_delete_activity(pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _rpc_call_web_query_activity(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_web_update_activity(pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_RewardActivity(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_QueryActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_set_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_set_reward_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_set_kaifu(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 kaifu);

			//@result desc
			int _make_rpc_call_web_open_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			int _make_rpc_call_web_close_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_web_delete_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid);

			//@result desc
			int _make_rpc_call_web_query_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_web_update_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_RewardActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
			// -------------------------------------
			//  _rpc_call_RewardActivity
			// -------------------------------------
			class CON_RewardActivity
			{
			public:
				CON_RewardActivity(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplDevil
		// *********************************
		class SImplDevilProxy : public SImplBaseProxy
		{
		public:
			SImplDevilProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);
		public:
		};

		// *********************************
		// rpc ProxyClass DevilQueueMgr
		// *********************************
		class DevilQueueMgrProxy : public BaseProxy
		{
		public:
			DevilQueueMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart);

			//@result desc
			int _rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart);

			//@result desc
			int _make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplPVE
		// *********************************
		class SImplPVEProxy : public SImplBaseProxy
		{
		public:
			SImplPVEProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);

			//@result desc
			int _rpc_call_HalfHourEvent(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);

			//@result desc
			int _make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

		// *********************************
		// rpc ProxyClass PVEQueueMgr
		// *********************************
		class PVEQueueMgrProxy : public BaseProxy
		{
		public:
			PVEQueueMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart);

			//@result desc
			int _rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:

			//@result desc
			int _make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart);

			//@result desc
			int _make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid);

			//@result desc
			int _make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplTeam
		// *********************************
		class SImplTeamProxy : public SImplBaseProxy
		{
		public:
			SImplTeamProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Query(pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);
		public:

			//@result desc
			int _make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid);

			//@result desc
			int _make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplRedEnvelope
		// *********************************
		class SImplRedEnvelopeProxy : public SImplBaseProxy
		{
		public:
			SImplRedEnvelopeProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 nGold [required]
			int _rpc_call_CreateRedEnvelope(pwdist::ICallableObject* caller,int64 nHid,int64 nGold,const char* strcontent);

			//@result desc
			//@result 1, int64 nGold [required]
			int _rpc_call_GetRedEnvelope(pwdist::ICallableObject* caller,int64 nHid,int64 nIndex,int32 nVipLev,const char* strGetName,int64 nGetID);
		public:

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 nGold [required]
			int _make_rpc_call_CreateRedEnvelope(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nHid,int64 nGold,const char* strcontent);

			//@result desc
			//@result 1, int64 nGold [required]
			int _make_rpc_call_GetRedEnvelope(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nHid,int64 nIndex,int32 nVipLev,const char* strGetName,int64 nGetID);
		public:
			// -------------------------------------
			//  _rpc_call_CreateRedEnvelope
			// -------------------------------------
			class CON_CreateRedEnvelope
			{
			public:
				CON_CreateRedEnvelope(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,int64 nGold);
				int ReturnAsyncEx(int64 pid,int32 code,int64 nGold);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int64 GetResultNgold(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_GetRedEnvelope
			// -------------------------------------
			class CON_GetRedEnvelope
			{
			public:
				CON_GetRedEnvelope(pwdist::Port* port = NULL);
			public:
				int Return(int64 nGold);
				int ReturnAsyncEx(int64 pid,int64 nGold);
				int CancelAsyncReturn(int64 pid);
			public:
				static int64 GetResultNgold(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

	}

	namespace dbsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Null(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplKVDB
		// *********************************
		class SImplKVDBProxy : public BaseProxy
		{
		public:
			SImplKVDBProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Hsetnx_incrid(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk bson);

			//@result desc
			int _rpc_call_Hsetnx(pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson);

			//@result desc
			int _rpc_call_Hset(pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson);

			//@result desc
			int _rpc_call_Hget(pwdist::ICallableObject* caller,const char* meta,const char* key);

			//@result desc
			int _rpc_call_HgetByid(pwdist::ICallableObject* caller,const char* meta,int64 id);

			//@result desc
			int _rpc_call_Hdel(pwdist::ICallableObject* caller,const char* meta,const char* key);

			//@result desc
			int _rpc_call_Hall(pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _rpc_call_Hvals(pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _rpc_call_Hsize(pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _rpc_call_Hclear(pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _rpc_call_Hmultiget(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey);

			//@result desc
			int _rpc_call_Hmultidel(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey);

			//@result desc
			int _rpc_call_Hmultiset(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);

			//@result desc
			int _rpc_call_HcrossallFetch(pwdist::ICallableObject* caller,const char* meta);

			//@result desc
			int _rpc_call_HvalsFetch(pwdist::ICallableObject* caller,const char* meta);

			//@result desc
			int _rpc_call_HvalsIndexQueryStr(pwdist::ICallableObject* caller,const char* meta,const char* field,const char* value);

			//@result desc
			int _rpc_call_HvalsIndexQueryInt(pwdist::ICallableObject* caller,const char* meta,const char* field,int64 value);

			//@result desc
			int _rpc_call_HvalsIndexQueryRangeStr(pwdist::ICallableObject* caller,const char* meta,const char* field,const char* start,const char* ended);

			//@result desc
			int _rpc_call_HvalsIndexQueryRangeInt(pwdist::ICallableObject* caller,const char* meta,const char* field,int64 start,int64 ended);

			//@result desc
			int _rpc_call_HmultisetnxLoose(pwdist::ICallableObject* caller,pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);

			//@result desc
			int _rpc_call_MallocIncrid(pwdist::ICallableObject* caller,const char* meta,int64 size);

			//@result desc
			int _rpc_call_Zset(pwdist::ICallableObject* caller,const char* zsetname,const char* key,int64 value);

			//@result desc
			int _rpc_call_Zdel(pwdist::ICallableObject* caller,const char* zsetname,const char* key);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 value [optional]
			int _rpc_call_Zget(pwdist::ICallableObject* caller,const char* zsetname,const char* key);

			//@result desc
			int _rpc_call_Ztop(pwdist::ICallableObject* caller,const char* zsetname,int64 limit);

			//@result desc
			int _rpc_call_ZRtop(pwdist::ICallableObject* caller,const char* zsetname,int64 limit);

			//@result desc
			int _rpc_call_Zclear(pwdist::ICallableObject* caller,const char* zsetname);

			//@result desc
			int _rpc_call_Hscan(pwdist::ICallableObject* caller,const char* meta,const char* start,const char* pattern,int64 limit);

			//@result desc
			int _rpc_call_Exit(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Hsetnx_incrid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk bson);

			//@result desc
			int _make_rpc_call_Hsetnx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson);

			//@result desc
			int _make_rpc_call_Hset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson);

			//@result desc
			int _make_rpc_call_Hget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key);

			//@result desc
			int _make_rpc_call_HgetByid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,int64 id);

			//@result desc
			int _make_rpc_call_Hdel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key);

			//@result desc
			int _make_rpc_call_Hall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _make_rpc_call_Hvals(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _make_rpc_call_Hsize(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _make_rpc_call_Hclear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName);

			//@result desc
			int _make_rpc_call_Hmultiget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey);

			//@result desc
			int _make_rpc_call_Hmultidel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey);

			//@result desc
			int _make_rpc_call_Hmultiset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);

			//@result desc
			int _make_rpc_call_HcrossallFetch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta);

			//@result desc
			int _make_rpc_call_HvalsFetch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta);

			//@result desc
			int _make_rpc_call_HvalsIndexQueryStr(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,const char* value);

			//@result desc
			int _make_rpc_call_HvalsIndexQueryInt(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,int64 value);

			//@result desc
			int _make_rpc_call_HvalsIndexQueryRangeStr(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,const char* start,const char* ended);

			//@result desc
			int _make_rpc_call_HvalsIndexQueryRangeInt(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,int64 start,int64 ended);

			//@result desc
			int _make_rpc_call_HmultisetnxLoose(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);

			//@result desc
			int _make_rpc_call_MallocIncrid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,int64 size);

			//@result desc
			int _make_rpc_call_Zset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key,int64 value);

			//@result desc
			int _make_rpc_call_Zdel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 value [optional]
			int _make_rpc_call_Zget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key);

			//@result desc
			int _make_rpc_call_Ztop(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,int64 limit);

			//@result desc
			int _make_rpc_call_ZRtop(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,int64 limit);

			//@result desc
			int _make_rpc_call_Zclear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname);

			//@result desc
			int _make_rpc_call_Hscan(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* start,const char* pattern,int64 limit);

			//@result desc
			int _make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
			// -------------------------------------
			//  _rpc_call_Zget
			// -------------------------------------
			class CON_Zget
			{
			public:
				CON_Zget(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,int64 value);
				int ReturnAsyncEx(int64 pid,int32 code,int64 value);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static int64 GetResultValue(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass SImplKVDBLoader
		// *********************************
		class SImplKVDBLoaderProxy : public BaseProxy
		{
		public:
			SImplKVDBLoaderProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_UpdateGlobalWelfareId(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_QueryCharacers(pwdist::ICallableObject* caller,const char* account);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk ormHuman [optional]
			int _rpc_call_CreateCharacter(pwdist::ICallableObject* caller,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			//@result 3, pwdist::Chunk passport_collection [optional]
			int _rpc_call_LoadHuman(pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			int _rpc_call_LoadHumanItems(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_LadderRewriteHuman(pwdist::ICallableObject* caller,pwdist::Chunk human,pwdist::Chunk reserve);

			//@result desc
			int _rpc_call_LadderRewriteHumans(pwdist::ICallableObject* caller,pwdist::Chunk humans,pwdist::Chunk reserve);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _rpc_call_CreateHumanFromRawData(pwdist::ICallableObject* caller,const char* newname,const char* passport,pwdist::Chunk collectionData);

			//@result desc
			int _rpc_call_HumanRename(pwdist::ICallableObject* caller,int64 id,const char* oldname,const char* newname);

			//@result desc
			int _rpc_call_DiscardHuman(pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			int _rpc_call_DisconnectHuman(pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			int _rpc_call_HumanQuery(pwdist::ICallableObject* caller,const char* name);

			//@result desc
			int _rpc_call_HumanQueryByName(pwdist::ICallableObject* caller,const char* name);

			//@result desc
			int _rpc_call_HumanQueryById(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_HumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _rpc_call_LianYunHumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _rpc_call_XiYouHumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _rpc_call_DeleteCharacter(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_CleanupDatabase(pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_LockPassport(pwdist::ICallableObject* caller,const char* passport,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_UnlockPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_LockChatPassport(pwdist::ICallableObject* caller,const char* passport,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _rpc_call_UnlockChatPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _rpc_call_LoadVips(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ILoadHuman(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_ILoadPassport(pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _rpc_call_GetPlayersInfoByPassport360(pwdist::ICallableObject* caller,pwdist::Chunk passports);

			//@result desc
			int _rpc_call_Human360QueryById(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_Human360QueryRideByRoleId(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_Human360QuerySkillByRoleId(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_Human360QueryMagicWeaponByRoleId(pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _rpc_call_Human360QueryByIdBatch(pwdist::ICallableObject* caller,pwdist::Chunk ids);
		public:

			//@result desc
			int _make_rpc_call_UpdateGlobalWelfareId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_QueryCharacers(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk ormHuman [optional]
			int _make_rpc_call_CreateCharacter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk chunk);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			//@result 3, pwdist::Chunk passport_collection [optional]
			int _make_rpc_call_LoadHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			int _make_rpc_call_LoadHumanItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_LadderRewriteHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk human,pwdist::Chunk reserve);

			//@result desc
			int _make_rpc_call_LadderRewriteHumans(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk humans,pwdist::Chunk reserve);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
			int _make_rpc_call_CreateHumanFromRawData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* newname,const char* passport,pwdist::Chunk collectionData);

			//@result desc
			int _make_rpc_call_HumanRename(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* oldname,const char* newname);

			//@result desc
			int _make_rpc_call_DiscardHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			int _make_rpc_call_DisconnectHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id);

			//@result desc
			int _make_rpc_call_HumanQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name);

			//@result desc
			int _make_rpc_call_HumanQueryByName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name);

			//@result desc
			int _make_rpc_call_HumanQueryById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_HumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
			int _make_rpc_call_LianYunHumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _make_rpc_call_XiYouHumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _make_rpc_call_DeleteCharacter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_CleanupDatabase(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_LockPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_UnlockPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_LockChatPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 seconds);

			//@result desc
			//@result 1, int32 code [required]
			int _make_rpc_call_UnlockChatPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _make_rpc_call_LoadVips(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ILoadHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_ILoadPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport);

			//@result desc
			int _make_rpc_call_GetPlayersInfoByPassport360(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk passports);

			//@result desc
			int _make_rpc_call_Human360QueryById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_Human360QueryRideByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_Human360QuerySkillByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_Human360QueryMagicWeaponByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id);

			//@result desc
			int _make_rpc_call_Human360QueryByIdBatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk ids);
		public:
			// -------------------------------------
			//  _rpc_call_CreateCharacter
			// -------------------------------------
			class CON_CreateCharacter
			{
			public:
				CON_CreateCharacter(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,pwdist::Chunk ormHuman);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk ormHuman);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultOrmhuman(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LoadHuman
			// -------------------------------------
			class CON_LoadHuman
			{
			public:
				CON_LoadHuman(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,pwdist::Chunk collection,pwdist::Chunk passport_collection);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk collection,pwdist::Chunk passport_collection);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultCollection(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultPassport_collection(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LoadHumanItems
			// -------------------------------------
			class CON_LoadHumanItems
			{
			public:
				CON_LoadHumanItems(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
				int Return(int32 code,pwdist::Chunk collection);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk collection);
				
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultCollection(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_CreateHumanFromRawData
			// -------------------------------------
			class CON_CreateHumanFromRawData
			{
			public:
				CON_CreateHumanFromRawData(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,const char* error);
				int ReturnAsyncEx(int64 pid,int32 code,const char* error);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static const char* GetResultError(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LianYunHumanQueryByPassport
			// -------------------------------------
			class CON_LianYunHumanQueryByPassport
			{
			public:
				CON_LianYunHumanQueryByPassport(pwdist::Port* port = NULL);
			public:
				int Return(int32 code,pwdist::Chunk chunk);
				int ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultChunk(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LockPassport
			// -------------------------------------
			class CON_LockPassport
			{
			public:
				CON_LockPassport(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_UnlockPassport
			// -------------------------------------
			class CON_UnlockPassport
			{
			public:
				CON_UnlockPassport(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_LockChatPassport
			// -------------------------------------
			class CON_LockChatPassport
			{
			public:
				CON_LockChatPassport(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
			// -------------------------------------
			//  _rpc_call_UnlockChatPassport
			// -------------------------------------
			class CON_UnlockChatPassport
			{
			public:
				CON_UnlockChatPassport(pwdist::Port* port = NULL);
			public:
				int Return(int32 code);
				int ReturnAsyncEx(int64 pid,int32 code);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCode(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

	}

	namespace accsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Null(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplAcc
		// *********************************
		class SImplAccProxy : public BaseProxy
		{
		public:
			SImplAccProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_Exit(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_ReloadWhiteList(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_EnableWhiteList(pwdist::ICallableObject* caller,bool enable);
		public:

			//@result desc
			int _make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_ReloadWhiteList(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_EnableWhiteList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool enable);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplWallow
		// *********************************
		class SImplWallowProxy : public BaseProxy
		{
		public:
			SImplWallowProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_WallowLogin(pwdist::ICallableObject* caller,const char* account,int64 roleID);

			//@result desc
			int _rpc_call_WallowLogout(pwdist::ICallableObject* caller,const char* account,int64 roleID);
		public:

			//@result desc
			int _make_rpc_call_WallowLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 roleID);

			//@result desc
			int _make_rpc_call_WallowLogout(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 roleID);
		public:
		};

	}

	namespace connsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Null(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplSend
		// *********************************
		class SImplSendProxy : public BaseProxy
		{
		public:
			SImplSendProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Broadcast(pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_BroadcastEx(pwdist::ICallableObject* caller,pwdist::Chunk buf);
		public:

			//@result desc
			int _make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_BroadcastEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf);
		public:
		};

		// *********************************
		// rpc ProxyClass SImplListener
		// *********************************
		class SImplListenerProxy : public BaseProxy
		{
		public:
			SImplListenerProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Enable(pwdist::ICallableObject* caller,bool value);

			//@result desc
			int _rpc_call_Exit(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_EnableMsgid(pwdist::ICallableObject* caller,int32 msgid,bool enable);

			//@result desc
			//@result 1, int32 count [required]
			//@result 2, pwdist::Chunk ids [required]
			int _rpc_call_GetDisabledMsgids(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Enable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool value);

			//@result desc
			int _make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_EnableMsgid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,bool enable);

			//@result desc
			//@result 1, int32 count [required]
			//@result 2, pwdist::Chunk ids [required]
			int _make_rpc_call_GetDisabledMsgids(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
			// -------------------------------------
			//  _rpc_call_GetDisabledMsgids
			// -------------------------------------
			class CON_GetDisabledMsgids
			{
			public:
				CON_GetDisabledMsgids(pwdist::Port* port = NULL);
			public:
				int Return(int32 count,pwdist::Chunk ids);
				int ReturnAsyncEx(int64 pid,int32 count,pwdist::Chunk ids);
				int CancelAsyncReturn(int64 pid);
			public:
				static int32 GetResultCount(pwdist::FutureObject& f);
				static pwdist::Chunk GetResultIds(pwdist::FutureObject& f);
			private:
				pwdist::Port* m_pPort;
			};
			
		};

		// *********************************
		// rpc ProxyClass Connection
		// *********************************
		class ConnectionProxy : public BaseProxy
		{
		public:
			ConnectionProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_CloseTcp(pwdist::ICallableObject* caller,const char* _caller,int32 _lineno);

			//@result desc
			int _rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_SendMsgEx(pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_MsgIncomingResult(pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_UpdateStatus(pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage,int64 objid);

			//@result desc
			int _rpc_call_CheckStatus(pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage);

			//@result desc
			int _rpc_call_ReturnCreateCharacterStage(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_CloseTcp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* _caller,int32 _lineno);

			//@result desc
			int _make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_SendMsgEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_MsgIncomingResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_UpdateStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage,int64 objid);

			//@result desc
			int _make_rpc_call_CheckStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage);

			//@result desc
			int _make_rpc_call_ReturnCreateCharacterStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		};

	}

	namespace globalsrv
	{
		// *********************************
		// rpc ProxyClass Base
		// *********************************
		class BaseProxy
		{
		public:
			BaseProxy(pwdist::Port* port = NULL);
		public:
			inline pwdist::Port* port()
			{
				return m_pPort;
			}
		public:
			int _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);
			int _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);
			int _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);
			int _set_call_target(const char* node,const char* port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1);
			int _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);
		public:

			//@result desc
			int _rpc_call_Null(pwdist::ICallableObject* caller);
		public:

			//@result desc
			int _make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller);
		public:
		protected:
			pwdist::Port* m_pPort;
		};

		// *********************************
		// rpc ProxyClass SImplGlobal
		// *********************************
		class SImplGlobalProxy : public BaseProxy
		{
		public:
			SImplGlobalProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_Test(pwdist::ICallableObject* caller);

			//@result desc
			int _rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 zoneid,int32 mid,pwdist::Chunk buf);
		public:

			//@result desc
			int _make_rpc_call_Test(pwdist::MsgCall& call,pwdist::ICallableObject* caller);

			//@result desc
			int _make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,int32 mid,pwdist::Chunk buf);
		public:
		};

		// *********************************
		// rpc ProxyClass PassportLockMgr
		// *********************************
		class PassportLockMgrProxy : public BaseProxy
		{
		public:
			PassportLockMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_LockAdded(pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 secs);

			//@result desc
			int _rpc_call_LockDeled(pwdist::ICallableObject* caller,int32 zoneid,const char* passport);

			//@result desc
			int _rpc_call_LockCheck(pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 hid);
		public:

			//@result desc
			int _make_rpc_call_LockAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 secs);

			//@result desc
			int _make_rpc_call_LockDeled(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport);

			//@result desc
			int _make_rpc_call_LockCheck(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 hid);
		public:
		};

		// *********************************
		// rpc ProxyClass RanklistMgr
		// *********************************
		class RanklistMgrProxy : public BaseProxy
		{
		public:
			RanklistMgrProxy(pwdist::Port* port = NULL);
		public:

			//@result desc
			int _rpc_call_RankUpdate(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk buf);

			//@result desc
			int _rpc_call_RankQuery(pwdist::ICallableObject* caller,int32 type,int32 zoneid);

			//@result desc
			int _rpc_call_RankClear(pwdist::ICallableObject* caller,int32 type,int32 zoneid);
		public:

			//@result desc
			int _make_rpc_call_RankUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk buf);

			//@result desc
			int _make_rpc_call_RankQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 zoneid);

			//@result desc
			int _make_rpc_call_RankClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 zoneid);
		public:
		};

	}

}
#endif
