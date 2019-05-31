#ifndef _pw_rpc_names_
#define _pw_rpc_names_


namespace rpcnames
{
	namespace worldsrv
	{
		 namespace Base
		 {
			 const char _rpc_conf_Enable[] = "_rpc_conf_Enable@379";
		 }
		 namespace SImplLogin
		 {
			 const char _rpc_call_MsgIncoming[] = "_rpc_call_MsgIncoming@990";
			 const char _rpc_call_ConnectionClosed[] = "_rpc_call_ConnectionClosed@990";
			 const char _rpc_call_ReturnCreateCharacterStage[] = "_rpc_call_ReturnCreateCharacterStage@990";
			 const char _rpc_call_AccountEnterWorld[] = "_rpc_call_AccountEnterWorld@990";
			 const char _rpc_call_AccountLeaveWorld[] = "_rpc_call_AccountLeaveWorld@990";
			 const char _rpc_call_AccountFlagsChanged[] = "_rpc_call_AccountFlagsChanged@990";
		 }
		 namespace SImplStage
		 {
			 const char _rpc_call_CreateStage[] = "_rpc_call_CreateStage@985";
			 const char _rpc_call_DestroyStage[] = "_rpc_call_DestroyStage@985";
			 const char _rpc_call_PrepareExit[] = "_rpc_call_PrepareExit@985";
			 const char _rpc_call_Exit[] = "_rpc_call_Exit@985";
			 const char _rpc_call_Invoke[] = "_rpc_call_Invoke@985";
			 const char _rpc_call_GSetServerMode[] = "_rpc_call_GSetServerMode@985";
			 const char _rpc_call_GSetGlobalVariable[] = "_rpc_call_GSetGlobalVariable@985";
			 const char _rpc_call_GExecuteCommand[] = "_rpc_call_GExecuteCommand@985";
			 const char _rpc_call_GEventOccured[] = "_rpc_call_GEventOccured@985";
		 }
		 namespace SImplLoginObj
		 {
			 const char _rpc_call_SendLoginGateStatus[] = "_rpc_call_SendLoginGateStatus@1273";
		 }
		 namespace Stage
		 {
			 const char _rpc_call_EnterWorld[] = "_rpc_call_EnterWorld@500";
			 const char _rpc_call_Login[] = "_rpc_call_Login@500";
			 const char _rpc_call_Broadcast[] = "_rpc_call_Broadcast@500";
			 const char _rpc_call_Broadcast2[] = "_rpc_call_Broadcast2@500";
			 const char _rpc_call_ActivityStartup[] = "_rpc_call_ActivityStartup@500";
			 const char _rpc_call_ActivityCleanup[] = "_rpc_call_ActivityCleanup@500";
			 const char _rpc_call_CallScript[] = "_rpc_call_CallScript@500";
			 const char _rpc_call_SpawnMonster[] = "_rpc_call_SpawnMonster@500";
			 const char _rpc_call_InitialStageLogic[] = "_rpc_call_InitialStageLogic@500";
			 const char _rpc_call_DawnHourEvent[] = "_rpc_call_DawnHourEvent@500";
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@500";
			 const char _rpc_call_MidnightEvent[] = "_rpc_call_MidnightEvent@500";
			 const char _rpc_Gmland_Load[] = "_rpc_Gmland_Load@500";
			 const char _rpc_Gmland_Unload[] = "_rpc_Gmland_Unload@500";
			 const char _rpc_Gmland_Oper[] = "_rpc_Gmland_Oper@500";
			 const char _rpc_call_Invoke[] = "_rpc_call_Invoke@500";
			 const char _rpc_call_GExecuteCommand[] = "_rpc_call_GExecuteCommand@500";
			 const char _rpc_call_FillBattleMember[] = "_rpc_call_FillBattleMember@500";
			 const char _rpc_call_SpawnMonsterEx[] = "_rpc_call_SpawnMonsterEx@500";
		 }
		 namespace Human
		 {
			 const char _rpc_call_InitialDataToClient[] = "_rpc_call_InitialDataToClient@505";
			 const char _rpc_call_ConnectionClosed[] = "_rpc_call_ConnectionClosed@505";
			 const char _rpc_call_MsgIncoming[] = "_rpc_call_MsgIncoming@505";
			 const char _rpc_call_SendMsg[] = "_rpc_call_SendMsg@505";
			 const char _rpc_call_Kick[] = "_rpc_call_Kick@505";
			 const char _rpc_call_Invoke[] = "_rpc_call_Invoke@505";
			 const char _rpc_call_UpdateTeam[] = "_rpc_call_UpdateTeam@505";
			 const char _rpc_call_UpdateGuild[] = "_rpc_call_UpdateGuild@505";
			 const char _rpc_call_SwitchStage[] = "_rpc_call_SwitchStage@505";
			 const char _rpc_call_Spend[] = "_rpc_call_Spend@505";
			 const char _rpc_call_Grant[] = "_rpc_call_Grant@505";
			 const char _rpc_call_QueryPlayerInfo[] = "_rpc_call_QueryPlayerInfo@505";
			 const char _rpc_call_AddItem[] = "_rpc_call_AddItem@505";
			 const char _rpc_call_IsFunctionBlocked[] = "_rpc_call_IsFunctionBlocked@505";
			 const char _rpc_call_WarlordCombatResult[] = "_rpc_call_WarlordCombatResult@505";
			 const char _rpc_call_WarlordWorship[] = "_rpc_call_WarlordWorship@505";
			 const char _rpc_call_UpdateCommonActivity[] = "_rpc_call_UpdateCommonActivity@505";
			 const char _rpc_call_CommonActivityReward[] = "_rpc_call_CommonActivityReward@505";
			 const char _rpc_call_UpdateRewardActivity[] = "_rpc_call_UpdateRewardActivity@505";
			 const char _rpc_call_DawnHourEvent[] = "_rpc_call_DawnHourEvent@505";
			 const char _rpc_call_ZeroHourEvent2[] = "_rpc_call_ZeroHourEvent2@505";
			 const char _rpc_call_BeforeMidnightEvent[] = "_rpc_call_BeforeMidnightEvent@505";
			 const char _rpc_call_AddExp[] = "_rpc_call_AddExp@505";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@505";
			 const char _rpc_call_GMOper[] = "_rpc_call_GMOper@505";
			 const char _rpc_call_ServerAwardNotify[] = "_rpc_call_ServerAwardNotify@505";
			 const char _rpc_call_SyncLadderHumanInfo[] = "_rpc_call_SyncLadderHumanInfo@505";
			 const char _rpc_call_SyncNormalHumanInfo[] = "_rpc_call_SyncNormalHumanInfo@505";
			 const char _rpc_call_AdventureFinished[] = "_rpc_call_AdventureFinished@505";
			 const char _rpc_call_FatigueChangeSeconds[] = "_rpc_call_FatigueChangeSeconds@505";
			 const char _rpc_call_ExecuteOperation[] = "_rpc_call_ExecuteOperation@505";
			 const char _rpc_call_ExecutePassportOperation[] = "_rpc_call_ExecutePassportOperation@505";
			 const char _rpc_call_MultiplayerDungeonMatchOver[] = "_rpc_call_MultiplayerDungeonMatchOver@505";
			 const char _rpc_call_WriteSnapshots[] = "_rpc_call_WriteSnapshots@505";
			 const char _rpc_call_LadderLogined[] = "_rpc_call_LadderLogined@505";
			 const char _rpc_call_LadderStarted[] = "_rpc_call_LadderStarted@505";
			 const char _rpc_call_LadderMatched[] = "_rpc_call_LadderMatched@505";
			 const char _rpc_call_CalcItemCombatPoint[] = "_rpc_call_CalcItemCombatPoint@505";
			 const char _rpc_call_Award[] = "_rpc_call_Award@505";
			 const char _rpc_call_ShopBuy[] = "_rpc_call_ShopBuy@505";
			 const char _rpc_call_MallBuy[] = "_rpc_call_MallBuy@505";
			 const char _rpc_call_ExecuteGM[] = "_rpc_call_ExecuteGM@505";
			 const char _rpc_call_UpdateHotActivity[] = "_rpc_call_UpdateHotActivity@505";
			 const char _rpc_call_UpdateHotActivityEx[] = "_rpc_call_UpdateHotActivityEx@505";
			 const char _rpc_call_UpdateAchievementArenaSeason[] = "_rpc_call_UpdateAchievementArenaSeason@505";
			 const char _rpc_call_OpenAuctionBidFail[] = "_rpc_call_OpenAuctionBidFail@505";
			 const char _rpc_call_OpenAuctionBidVerify[] = "_rpc_call_OpenAuctionBidVerify@505";
			 const char _rpc_call_ArenaSeasonEnded[] = "_rpc_call_ArenaSeasonEnded@505";
			 const char _rpc_call_CommonActivityEvent[] = "_rpc_call_CommonActivityEvent@505";
			 const char _rpc_call_ActivityEnd[] = "_rpc_call_ActivityEnd@505";
			 const char _rpc_call_RunCarFinish[] = "_rpc_call_RunCarFinish@505";
			 const char _rpc_call_SendBackRedEnvelopLastGold[] = "_rpc_call_SendBackRedEnvelopLastGold@505";
		 }
		 namespace SImplSupport
		 {
			 const char _rpc_call_Load[] = "_rpc_call_Load@1250";
			 const char _rpc_call_Unload[] = "_rpc_call_Unload@1250";
		 }
	}
	namespace ctrlsrv
	{
		 namespace Base
		 {
			 const char _rpc_call_Null[] = "_rpc_call_Null@379";
		 }
		 namespace SImplAuctionHouse
		 {
			 const char _rpc_call_Auction[] = "_rpc_call_Auction@1724";
			 const char _rpc_call_AuctionCancel[] = "_rpc_call_AuctionCancel@1724";
			 const char _rpc_call_AuctionBuy[] = "_rpc_call_AuctionBuy@1724";
			 const char _rpc_call_ItemsList[] = "_rpc_call_ItemsList@1724";
			 const char _rpc_call_ItemsQuery[] = "_rpc_call_ItemsQuery@1724";
			 const char _rpc_call_ItemsSearch[] = "_rpc_call_ItemsSearch@1724";
		 }
		 namespace SImpl173
		 {
			 const char _rpc_call_GiftCard[] = "_rpc_call_GiftCard@640";
			 const char _rpc_call_GiftCardLianYun[] = "_rpc_call_GiftCardLianYun@640";
			 const char _rpc_call_RequestToken[] = "_rpc_call_RequestToken@640";
			 const char _rpc_call_LianYunPushHuman[] = "_rpc_call_LianYunPushHuman@640";
			 const char _rpc_call_LianYunPushChatMsg[] = "_rpc_call_LianYunPushChatMsg@640";
			 const char _rpc_call_FetchServerName[] = "_rpc_call_FetchServerName@640";
			 const char _rpc_call_FetchServerInfos[] = "_rpc_call_FetchServerInfos@640";
			 const char _rpc_call_TXInvoke[] = "_rpc_call_TXInvoke@640";
			 const char _rpc_call_TXCompassPush[] = "_rpc_call_TXCompassPush@640";
			 const char _rpc_call_TXUnionPush[] = "_rpc_call_TXUnionPush@640";
			 const char _rpc_call_TXClogPush[] = "_rpc_call_TXClogPush@640";
			 const char _rpc_call_ActiveCodeKorCtrl[] = "_rpc_call_ActiveCodeKorCtrl@640";
		 }
		 namespace SimplXiyou
		 {
			 const char _rpc_call_FetchServerInfos[] = "_rpc_call_FetchServerInfos@1059";
			 const char _rpc_call_XiYouPushHuman[] = "_rpc_call_XiYouPushHuman@1059";
			 const char _rpc_call_XiYouPushChatMsg[] = "_rpc_call_XiYouPushChatMsg@1059";
		 }
		 namespace Simpl360
		 {
			 const char _rpc_call_FetchServerInfos[] = "_rpc_call_FetchServerInfos@670";
			 const char _rpc_call_SanLiuLingPushHuman[] = "_rpc_call_SanLiuLingPushHuman@670";
			 const char _rpc_call_SanLiuLingPushChatMsg[] = "_rpc_call_SanLiuLingPushChatMsg@670";
			 const char _rpc_call_NewActiveCodeCtrl[] = "_rpc_call_NewActiveCodeCtrl@670";
			 const char _rpc_call_HumanEnterWorld[] = "_rpc_call_HumanEnterWorld@670";
			 const char _rpc_call_HumanLeaveWorld[] = "_rpc_call_HumanLeaveWorld@670";
			 const char _rpc_call_HumanUpdate[] = "_rpc_call_HumanUpdate@670";
		 }
		 namespace SImplBase
		 {
			 const char _rpc_call_Broadcast[] = "_rpc_call_Broadcast@864";
			 const char _rpc_call_HumanEnterWorld[] = "_rpc_call_HumanEnterWorld@864";
			 const char _rpc_call_HumanLeaveWorld[] = "_rpc_call_HumanLeaveWorld@864";
			 const char _rpc_call_HumanUpdate[] = "_rpc_call_HumanUpdate@864";
			 const char _rpc_call_HumanEnterWorldAfter[] = "_rpc_call_HumanEnterWorldAfter@864";
			 const char _rpc_call_HumanDropped[] = "_rpc_call_HumanDropped@864";
			 const char _rpc_call_HumanReconnected[] = "_rpc_call_HumanReconnected@864";
			 const char _rpc_call_SendMsg[] = "_rpc_call_SendMsg@864";
			 const char _rpc_call_SendMsgReliable[] = "_rpc_call_SendMsgReliable@864";
		 }
		 namespace SImplCommon
		 {
			 const char _rpc_call_HumanQuery[] = "_rpc_call_HumanQuery@1102";
			 const char _rpc_call_HumanQueryByName[] = "_rpc_call_HumanQueryByName@1102";
			 const char _rpc_call_AccountQuery[] = "_rpc_call_AccountQuery@1102";
			 const char _rpc_call_Query[] = "_rpc_call_Query@1102";
			 const char _rpc_call_HumanKick[] = "_rpc_call_HumanKick@1102";
			 const char _rpc_call_HumanInvoke[] = "_rpc_call_HumanInvoke@1102";
			 const char _rpc_call_HumanCreated[] = "_rpc_call_HumanCreated@1102";
			 const char _rpc_call_GMInjectZeroHourEvent[] = "_rpc_call_GMInjectZeroHourEvent@1102";
			 const char _rpc_call_HumanRenamed[] = "_rpc_call_HumanRenamed@1102";
			 const char _rpc_call_BroadcastOpenScene[] = "_rpc_call_BroadcastOpenScene@1102";
			 const char _rpc_call_SelectHumanToExecuteGM[] = "_rpc_call_SelectHumanToExecuteGM@1102";
			 const char _rpc_call_LianYunQueryTodayOnline[] = "_rpc_call_LianYunQueryTodayOnline@1102";
			 const char _rpc_call_PassportLock[] = "_rpc_call_PassportLock@1102";
			 const char _rpc_call_PassportUnlock[] = "_rpc_call_PassportUnlock@1102";
		 }
		 namespace SImplGuild
		 {
			 const char _rpc_call_CreateGuild[] = "_rpc_call_CreateGuild@986";
			 const char _rpc_call_ApplyGuild[] = "_rpc_call_ApplyGuild@986";
			 const char _rpc_call_ApplyGuildResult[] = "_rpc_call_ApplyGuildResult@986";
			 const char _rpc_call_InviteGuild[] = "_rpc_call_InviteGuild@986";
			 const char _rpc_call_InviteGuildResult[] = "_rpc_call_InviteGuildResult@986";
			 const char _rpc_call_LeaveGuild[] = "_rpc_call_LeaveGuild@986";
			 const char _rpc_call_KickGuild[] = "_rpc_call_KickGuild@986";
			 const char _rpc_call_QueryGuildList[] = "_rpc_call_QueryGuildList@986";
			 const char _rpc_call_FetchGuildOrderByLiveness[] = "_rpc_call_FetchGuildOrderByLiveness@986";
			 const char _rpc_call_FetchGuildList[] = "_rpc_call_FetchGuildList@986";
			 const char _rpc_call_FetchGuildById[] = "_rpc_call_FetchGuildById@986";
			 const char _rpc_call_BroadcastMail[] = "_rpc_call_BroadcastMail@986";
			 const char _rpc_call_BroadcastMailExceptNew[] = "_rpc_call_BroadcastMailExceptNew@986";
			 const char _rpc_call_PrepareExit[] = "_rpc_call_PrepareExit@986";
			 const char _rpc_call_FetchCommander[] = "_rpc_call_FetchCommander@986";
			 const char _rpc_call_ResetLiveness[] = "_rpc_call_ResetLiveness@986";
			 const char _rpc_call_CancelApply[] = "_rpc_call_CancelApply@986";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@986";
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@986";
			 const char _rpc_call_MidnightEvent[] = "_rpc_call_MidnightEvent@986";
			 const char _rpc_call_DismissGuild[] = "_rpc_call_DismissGuild@986";
			 const char _rpc_call_ChangeGuildCommander[] = "_rpc_call_ChangeGuildCommander@986";
			 const char _rpc_call_QueryGuildIsExist[] = "_rpc_call_QueryGuildIsExist@986";
			 const char _rpc_call_LianYunChangeGuildCommander[] = "_rpc_call_LianYunChangeGuildCommander@986";
			 const char _rpc_call_FetchGuildListLianYun[] = "_rpc_call_FetchGuildListLianYun@986";
			 const char _rpc_call_FetchGuildByIdLianYun[] = "_rpc_call_FetchGuildByIdLianYun@986";
			 const char _rpc_call_FetchGuildByPassportLianYun[] = "_rpc_call_FetchGuildByPassportLianYun@986";
			 const char _rpc_call_ChangeGuildNoticeByGuildIdLianYun[] = "_rpc_call_ChangeGuildNoticeByGuildIdLianYun@986";
			 const char _rpc_call_FetchGuildMembersByGuildIdLianYun[] = "_rpc_call_FetchGuildMembersByGuildIdLianYun@986";
			 const char _rpc_call_AuthGuildByGuildIdLianYun[] = "_rpc_call_AuthGuildByGuildIdLianYun@986";
		 }
		 namespace Guild
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@501";
			 const char _rpc_call_QueryOther[] = "_rpc_call_QueryOther@501";
			 const char _rpc_call_ChangeTitle[] = "_rpc_call_ChangeTitle@501";
			 const char _rpc_call_ChangeNotice[] = "_rpc_call_ChangeNotice@501";
			 const char _rpc_call_AddMemberDevotion[] = "_rpc_call_AddMemberDevotion@501";
			 const char _rpc_call_AddDevelopment[] = "_rpc_call_AddDevelopment@501";
			 const char _rpc_call_BroadcastGuild[] = "_rpc_call_BroadcastGuild@501";
			 const char _rpc_call_LevelupBuilding[] = "_rpc_call_LevelupBuilding@501";
			 const char _rpc_call_RecruitMember[] = "_rpc_call_RecruitMember@501";
			 const char _rpc_call_AddLog[] = "_rpc_call_AddLog@501";
			 const char _rpc_call_GDepositoryQuery[] = "_rpc_call_GDepositoryQuery@501";
			 const char _rpc_call_GDepositoryAllot[] = "_rpc_call_GDepositoryAllot@501";
			 const char _rpc_call_GDepositoryAllotByIndex[] = "_rpc_call_GDepositoryAllotByIndex@501";
			 const char _rpc_call_GDepositoryGrantItems[] = "_rpc_call_GDepositoryGrantItems@501";
			 const char _rpc_call_GDepositorySpendItems[] = "_rpc_call_GDepositorySpendItems@501";
			 const char _rpc_call_GDepositoryClearItems[] = "_rpc_call_GDepositoryClearItems@501";
			 const char _rpc_call_QueryGuildFruiter[] = "_rpc_call_QueryGuildFruiter@501";
			 const char _rpc_call_PickupGuildFruit[] = "_rpc_call_PickupGuildFruit@501";
			 const char _rpc_call_DragonHuntQuery[] = "_rpc_call_DragonHuntQuery@501";
			 const char _rpc_call_DragonHuntDouble[] = "_rpc_call_DragonHuntDouble@501";
			 const char _rpc_call_DragonHuntAdd[] = "_rpc_call_DragonHuntAdd@501";
			 const char _rpc_call_DragonHuntStart[] = "_rpc_call_DragonHuntStart@501";
			 const char _rpc_call_DragonHuntClose[] = "_rpc_call_DragonHuntClose@501";
			 const char _rpc_call_TrialLandQuery[] = "_rpc_call_TrialLandQuery@501";
			 const char _rpc_call_TrialLandStart[] = "_rpc_call_TrialLandStart@501";
			 const char _rpc_call_TrialLandEnter[] = "_rpc_call_TrialLandEnter@501";
			 const char _rpc_call_TrialLandComplete[] = "_rpc_call_TrialLandComplete@501";
			 const char _rpc_call_TrialLandGmClear[] = "_rpc_call_TrialLandGmClear@501";
			 const char _rpc_call_BroadcastNotifyBall[] = "_rpc_call_BroadcastNotifyBall@501";
			 const char _rpc_call_BroadcastCommonActivityEvent[] = "_rpc_call_BroadcastCommonActivityEvent@501";
			 const char _rpc_call_ChangeApplyWay[] = "_rpc_call_ChangeApplyWay@501";
			 const char _rpc_call_GetSYDungeonStatus[] = "_rpc_call_GetSYDungeonStatus@501";
			 const char _rpc_call_OpenSYDungeon[] = "_rpc_call_OpenSYDungeon@501";
			 const char _rpc_call_OnSYDungeonClosed[] = "_rpc_call_OnSYDungeonClosed@501";
			 const char _rpc_call_EnterSYDungeon[] = "_rpc_call_EnterSYDungeon@501";
		 }
		 namespace SImplRelation
		 {
			 const char _rpc_call_AddRelationObject[] = "_rpc_call_AddRelationObject@1315";
			 const char _rpc_call_DelRelationObject[] = "_rpc_call_DelRelationObject@1315";
			 const char _rpc_call_QueryRelationList[] = "_rpc_call_QueryRelationList@1315";
			 const char _rpc_call_BroadcastNotifyBall[] = "_rpc_call_BroadcastNotifyBall@1315";
			 const char _rpc_call_BroadcastMail[] = "_rpc_call_BroadcastMail@1315";
			 const char _rpc_call_FetchRelationList[] = "_rpc_call_FetchRelationList@1315";
			 const char _rpc_call_RequestRecommendLists[] = "_rpc_call_RequestRecommendLists@1315";
		 }
		 namespace SImplStageMgr
		 {
			 const char _rpc_call_StageThreadReport[] = "_rpc_call_StageThreadReport@1279";
			 const char _rpc_call_StageCreated[] = "_rpc_call_StageCreated@1279";
			 const char _rpc_call_StageDestructed[] = "_rpc_call_StageDestructed@1279";
			 const char _rpc_call_CreateStage[] = "_rpc_call_CreateStage@1279";
			 const char _rpc_call_CreateStageSublines[] = "_rpc_call_CreateStageSublines@1279";
			 const char _rpc_call_BroadcastOnSublines[] = "_rpc_call_BroadcastOnSublines@1279";
			 const char _rpc_call_DestroyStage[] = "_rpc_call_DestroyStage@1279";
			 const char _rpc_call_DestroyStageSublines[] = "_rpc_call_DestroyStageSublines@1279";
			 const char _rpc_call_QueryStage[] = "_rpc_call_QueryStage@1279";
			 const char _rpc_call_QueryStageSubline[] = "_rpc_call_QueryStageSubline@1279";
			 const char _rpc_call_QuerySwitchableSubline[] = "_rpc_call_QuerySwitchableSubline@1279";
			 const char _rpc_call_LoginToStage[] = "_rpc_call_LoginToStage@1279";
			 const char _rpc_call_ExitAfter[] = "_rpc_call_ExitAfter@1279";
			 const char _rpc_call_DisconnectAll[] = "_rpc_call_DisconnectAll@1279";
			 const char _rpc_call_DawnHourEvent[] = "_rpc_call_DawnHourEvent@1279";
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@1279";
			 const char _rpc_call_MidnightEvent[] = "_rpc_call_MidnightEvent@1279";
			 const char _rpc_call_Lock[] = "_rpc_call_Lock@1279";
			 const char _rpc_call_Unlock[] = "_rpc_call_Unlock@1279";
			 const char _rpc_call_StageInvoke[] = "_rpc_call_StageInvoke@1279";
			 const char _rpc_call_StageThreadInvoke[] = "_rpc_call_StageThreadInvoke@1279";
			 const char _rpc_call_StageThreadExecuteCommand[] = "_rpc_call_StageThreadExecuteCommand@1279";
			 const char _rpc_call_HumanCreated[] = "_rpc_call_HumanCreated@1279";
			 const char _rpc_call_WildBossCreated[] = "_rpc_call_WildBossCreated@1279";
			 const char _rpc_call_WildBossDestructed[] = "_rpc_call_WildBossDestructed@1279";
			 const char _rpc_call_WildBossQuery[] = "_rpc_call_WildBossQuery@1279";
		 }
		 namespace Miscellaneous
		 {
			 const char _rpc_call_GSpendNotify[] = "_rpc_call_GSpendNotify@1364";
		 }
		 namespace SImplActivity
		 {
			 const char _rpc_call_Signup[] = "_rpc_call_Signup@1330";
			 const char _rpc_call_CancelSignup[] = "_rpc_call_CancelSignup@1330";
			 const char _rpc_call_CallScript[] = "_rpc_call_CallScript@1330";
			 const char _rpc_call_Enter[] = "_rpc_call_Enter@1330";
			 const char _rpc_call_SendActivityStatus[] = "_rpc_call_SendActivityStatus@1330";
			 const char _rpc_call_GMStart[] = "_rpc_call_GMStart@1330";
			 const char _rpc_call_GMClean[] = "_rpc_call_GMClean@1330";
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@1330";
			 const char _rpc_call_MidnightEvent[] = "_rpc_call_MidnightEvent@1330";
			 const char _rpc_call_UpdateHumanCounter[] = "_rpc_call_UpdateHumanCounter@1330";
			 const char _rpc_call_UpdatePCU[] = "_rpc_call_UpdatePCU@1330";
			 const char _rpc_call_GetStartTime[] = "_rpc_call_GetStartTime@1330";
			 const char _rpc_call_UpdateHumanEnter[] = "_rpc_call_UpdateHumanEnter@1330";
			 const char _rpc_call_CreateSubstitute[] = "_rpc_call_CreateSubstitute@1330";
			 const char _rpc_call_DeleteSubstitute[] = "_rpc_call_DeleteSubstitute@1330";
			 const char _rpc_call_IsSubstituteCreated[] = "_rpc_call_IsSubstituteCreated@1330";
		 }
		 namespace ActivityNJTZ
		 {
			 const char _rpc_call_Init[] = "_rpc_call_Init@1171";
			 const char _rpc_call_InitWithGuilds[] = "_rpc_call_InitWithGuilds@1171";
			 const char _rpc_call_Finish[] = "_rpc_call_Finish@1171";
			 const char _rpc_call_GuildDismissed[] = "_rpc_call_GuildDismissed@1171";
			 const char _rpc_call_GuildMemberLeaved[] = "_rpc_call_GuildMemberLeaved@1171";
			 const char _rpc_call_QueryGuilds[] = "_rpc_call_QueryGuilds@1171";
			 const char _rpc_call_SupportGuild[] = "_rpc_call_SupportGuild@1171";
			 const char _rpc_call_SupportQuery[] = "_rpc_call_SupportQuery@1171";
			 const char _rpc_call_HistoryQuery[] = "_rpc_call_HistoryQuery@1171";
			 const char _rpc_call_GetGBInfo[] = "_rpc_call_GetGBInfo@1171";
			 const char _rpc_call_GMClear[] = "_rpc_call_GMClear@1171";
			 const char _rpc_call_GMRefresh[] = "_rpc_call_GMRefresh@1171";
			 const char _rpc_call_GMGoToRound[] = "_rpc_call_GMGoToRound@1171";
		 }
		 namespace ActivityKFMZ
		 {
			 const char _rpc_call_KF_SyncSYRankInfo[] = "_rpc_call_KF_SyncSYRankInfo@1157";
			 const char _rpc_call_KF_SyncStatus[] = "_rpc_call_KF_SyncStatus@1157";
			 const char _rpc_call_KF_SyncTTSInfo[] = "_rpc_call_KF_SyncTTSInfo@1157";
			 const char _rpc_call_KF_TTSReward[] = "_rpc_call_KF_TTSReward@1157";
			 const char _rpc_call_GetSYBoardInfo[] = "_rpc_call_GetSYBoardInfo@1157";
			 const char _rpc_call_GetTTSInfo[] = "_rpc_call_GetTTSInfo@1157";
			 const char _rpc_call_UpdateSYInfo[] = "_rpc_call_UpdateSYInfo@1157";
			 const char _rpc_call_GetTopRankInfo[] = "_rpc_call_GetTopRankInfo@1157";
			 const char _rpc_call_GetEnterLadderTTSInfo[] = "_rpc_call_GetEnterLadderTTSInfo@1157";
			 const char _rpc_call_GMCommand[] = "_rpc_call_GMCommand@1157";
		 }
		 namespace ActivityKFMZ_Ladder
		 {
			 const char _rpc_call_KF_GMCommand[] = "_rpc_call_KF_GMCommand@1840";
			 const char _rpc_call_KF_UpdateSYRankInfo[] = "_rpc_call_KF_UpdateSYRankInfo@1840";
			 const char _rpc_call_KF_ObtainSYRankInfo[] = "_rpc_call_KF_ObtainSYRankInfo@1840";
			 const char _rpc_call_GuildWin[] = "_rpc_call_GuildWin@1840";
		 }
		 namespace ActivityRunCar
		 {
			 const char _rpc_call_CreateRunCar[] = "_rpc_call_CreateRunCar@1432";
			 const char _rpc_call_SyncRunCarPosition[] = "_rpc_call_SyncRunCarPosition@1432";
			 const char _rpc_call_FinishRunCar[] = "_rpc_call_FinishRunCar@1432";
			 const char _rpc_call_GetRunCarPoisition[] = "_rpc_call_GetRunCarPoisition@1432";
		 }
		 namespace ActivityLGKJ
		 {
			 const char _rpc_call_Finish[] = "_rpc_call_Finish@1141";
		 }
		 namespace SImplArena
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@972";
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@972";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@972";
		 }
		 namespace ArenaQueueMgr
		 {
			 const char _rpc_call_AckMatch[] = "_rpc_call_AckMatch@1298";
			 const char _rpc_call_AckEnter[] = "_rpc_call_AckEnter@1298";
		 }
		 namespace SImplBattle
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@1089";
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@1089";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@1089";
		 }
		 namespace BattleQueueMgr
		 {
			 const char _rpc_call_AckMatch[] = "_rpc_call_AckMatch@1415";
			 const char _rpc_call_AckEnter[] = "_rpc_call_AckEnter@1415";
		 }
		 namespace SImplMisc
		 {
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@881";
		 }
		 namespace GameSellerMgr
		 {
			 const char _rpc_call_BecomeGS[] = "_rpc_call_BecomeGS@1287";
			 const char _rpc_call_ChargeNotify[] = "_rpc_call_ChargeNotify@1287";
		 }
		 namespace ShopMgr
		 {
			 const char _rpc_call_ShopQuery[] = "_rpc_call_ShopQuery@704";
			 const char _rpc_call_ShopBuy[] = "_rpc_call_ShopBuy@704";
		 }
		 namespace LotteryMgr
		 {
			 const char _rpc_call_LogsAdded[] = "_rpc_call_LogsAdded@1049";
			 const char _rpc_call_LogsQuery[] = "_rpc_call_LogsQuery@1049";
		 }
		 namespace LotteryPrizeMgr
		 {
			 const char _rpc_call_LogsAdded[] = "_rpc_call_LogsAdded@1571";
			 const char _rpc_call_LogsQuery[] = "_rpc_call_LogsQuery@1571";
		 }
		 namespace ChestMgr
		 {
			 const char _rpc_call_LogsAdded[] = "_rpc_call_LogsAdded@797";
			 const char _rpc_call_LogsQuery[] = "_rpc_call_LogsQuery@797";
		 }
		 namespace MallMgr
		 {
			 const char _rpc_call_MallQuery[] = "_rpc_call_MallQuery@684";
			 const char _rpc_call_MallBuy[] = "_rpc_call_MallBuy@684";
		 }
		 namespace AwardServerMgr
		 {
			 const char _rpc_call_CreateAward[] = "_rpc_call_CreateAward@1420";
			 const char _rpc_call_QueryAward[] = "_rpc_call_QueryAward@1420";
		 }
		 namespace WarlordMgr
		 {
			 const char _rpc_call_WarlordQueryByID[] = "_rpc_call_WarlordQueryByID@1025";
			 const char _rpc_call_WarlordQuery[] = "_rpc_call_WarlordQuery@1025";
			 const char _rpc_call_CombatSucc[] = "_rpc_call_CombatSucc@1025";
			 const char _rpc_call_CombatFail[] = "_rpc_call_CombatFail@1025";
			 const char _rpc_call_WarlordWorship[] = "_rpc_call_WarlordWorship@1025";
			 const char _rpc_call_AddWorshiped[] = "_rpc_call_AddWorshiped@1025";
			 const char _rpc_call_FetchWarlordRank[] = "_rpc_call_FetchWarlordRank@1025";
			 const char _rpc_call_GrantRankAward[] = "_rpc_call_GrantRankAward@1025";
			 const char _rpc_call_QueryWorshiped[] = "_rpc_call_QueryWorshiped@1025";
			 const char _rpc_call_AdjustRank[] = "_rpc_call_AdjustRank@1025";
			 const char _rpc_call_QueryChallengeWarlord[] = "_rpc_call_QueryChallengeWarlord@1025";
			 const char _rpc_call_ChallengeWarlord[] = "_rpc_call_ChallengeWarlord@1025";
			 const char _rpc_call_QueryWarlordInfo[] = "_rpc_call_QueryWarlordInfo@1025";
			 const char _rpc_call_QueryWarlordRankList[] = "_rpc_call_QueryWarlordRankList@1025";
		 }
		 namespace OpenAuctionMgr
		 {
			 const char _rpc_call_QueryItem[] = "_rpc_call_QueryItem@1419";
			 const char _rpc_call_BidCheck[] = "_rpc_call_BidCheck@1419";
			 const char _rpc_call_GMRestartAuction[] = "_rpc_call_GMRestartAuction@1419";
		 }
		 namespace BroadcastMgr
		 {
			 const char _rpc_call_Create[] = "_rpc_call_Create@1209";
			 const char _rpc_call_Delete[] = "_rpc_call_Delete@1209";
		 }
		 namespace ChatMgr
		 {
			 const char _rpc_call_QueryChatMsgList[] = "_rpc_call_QueryChatMsgList@678";
			 const char _rpc_call_SendChatMsg[] = "_rpc_call_SendChatMsg@678";
			 const char _rpc_call_AckChatMsgRecved[] = "_rpc_call_AckChatMsgRecved@678";
			 const char _rpc_call_QueryChatContactList[] = "_rpc_call_QueryChatContactList@678";
			 const char _rpc_call_SendChatMsgToHuman[] = "_rpc_call_SendChatMsgToHuman@678";
			 const char _rpc_call_CachedChatItems[] = "_rpc_call_CachedChatItems@678";
			 const char _rpc_call_QueryCachedItem[] = "_rpc_call_QueryCachedItem@678";
			 const char _rpc_call_SendLadderHorn[] = "_rpc_call_SendLadderHorn@678";
		 }
		 namespace OperationsMgr
		 {
			 const char _rpc_call_Create[] = "_rpc_call_Create@1354";
			 const char _rpc_call_HumanReady[] = "_rpc_call_HumanReady@1354";
		 }
		 namespace PassportOperationsMgr
		 {
			 const char _rpc_call_Create[] = "_rpc_call_Create@2214";
			 const char _rpc_call_HumanReady[] = "_rpc_call_HumanReady@2214";
		 }
		 namespace MailMgr
		 {
			 const char _rpc_call_QueryMailList[] = "_rpc_call_QueryMailList@681";
			 const char _rpc_call_SendMail[] = "_rpc_call_SendMail@681";
			 const char _rpc_call_SendMultiMail[] = "_rpc_call_SendMultiMail@681";
			 const char _rpc_call_AckMailRecved[] = "_rpc_call_AckMailRecved@681";
			 const char _rpc_call_RecvMailReward[] = "_rpc_call_RecvMailReward@681";
			 const char _rpc_call_AckMailRewardRecved[] = "_rpc_call_AckMailRewardRecved@681";
			 const char _rpc_call_DeleteMail[] = "_rpc_call_DeleteMail@681";
		 }
		 namespace LoginQueueMgr
		 {
			 const char _rpc_call_RequestLoginGate[] = "_rpc_call_RequestLoginGate@1316";
			 const char _rpc_call_ConnectionClosedWhenLogin[] = "_rpc_call_ConnectionClosedWhenLogin@1316";
		 }
		 namespace NotifyBallMgr
		 {
			 const char _rpc_call_QueryNotifyBallList[] = "_rpc_call_QueryNotifyBallList@1306";
			 const char _rpc_call_SendNotifyBall[] = "_rpc_call_SendNotifyBall@1306";
			 const char _rpc_call_SendMultiNotifyBall[] = "_rpc_call_SendMultiNotifyBall@1306";
			 const char _rpc_call_DeleteNotifyBall[] = "_rpc_call_DeleteNotifyBall@1306";
		 }
		 namespace SImplAdventure
		 {
			 const char _rpc_call_CreateAdventure[] = "_rpc_call_CreateAdventure@1427";
			 const char _rpc_call_Leave[] = "_rpc_call_Leave@1427";
		 }
		 namespace TeamMgr
		 {
			 const char _rpc_call_CreateTeam[] = "_rpc_call_CreateTeam@685";
			 const char _rpc_call_DismissTeam[] = "_rpc_call_DismissTeam@685";
			 const char _rpc_call_JoinTeam[] = "_rpc_call_JoinTeam@685";
			 const char _rpc_call_ApplyJoinTeam[] = "_rpc_call_ApplyJoinTeam@685";
			 const char _rpc_call_AgreeJoinTeam[] = "_rpc_call_AgreeJoinTeam@685";
			 const char _rpc_call_OperTeam[] = "_rpc_call_OperTeam@685";
			 const char _rpc_call_InviteTeam[] = "_rpc_call_InviteTeam@685";
			 const char _rpc_call_InviteTeamReturn[] = "_rpc_call_InviteTeamReturn@685";
			 const char _rpc_call_LeaveTeam[] = "_rpc_call_LeaveTeam@685";
			 const char _rpc_call_KickTeam[] = "_rpc_call_KickTeam@685";
			 const char _rpc_call_RecruitTeam[] = "_rpc_call_RecruitTeam@685";
			 const char _rpc_call_Query[] = "_rpc_call_Query@685";
			 const char _rpc_call_QueryMembers[] = "_rpc_call_QueryMembers@685";
			 const char _rpc_call_RestoreTeam[] = "_rpc_call_RestoreTeam@685";
			 const char _rpc_call_ChangeTeamMemberAuth[] = "_rpc_call_ChangeTeamMemberAuth@685";
			 const char _rpc_call_ChangeTeamLeader[] = "_rpc_call_ChangeTeamLeader@685";
			 const char _rpc_call_BroadcastTeam[] = "_rpc_call_BroadcastTeam@685";
			 const char _rpc_call_ChangeTeamMemberFlag[] = "_rpc_call_ChangeTeamMemberFlag@685";
			 const char _rpc_call_FillTeamMember[] = "_rpc_call_FillTeamMember@685";
			 const char _rpc_call_ChangeStateFreeze[] = "_rpc_call_ChangeStateFreeze@685";
			 const char _rpc_call_TeamReward[] = "_rpc_call_TeamReward@685";
			 const char _rpc_call_SyncLadderTeamInfo[] = "_rpc_call_SyncLadderTeamInfo@685";
			 const char _rpc_call_SyncNormalTeamInfo[] = "_rpc_call_SyncNormalTeamInfo@685";
			 const char _rpc_call_SyncLadderTeamReward[] = "_rpc_call_SyncLadderTeamReward@685";
		 }
		 namespace SImplRanklist
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@1325";
			 const char _rpc_call_QueryTopTen[] = "_rpc_call_QueryTopTen@1325";
			 const char _rpc_call_QueryDetail[] = "_rpc_call_QueryDetail@1325";
			 const char _rpc_call_QueryPlayer[] = "_rpc_call_QueryPlayer@1325";
			 const char _rpc_call_UpdateGuildFightPoint[] = "_rpc_call_UpdateGuildFightPoint@1325";
			 const char _rpc_call_ZeroHourEvent[] = "_rpc_call_ZeroHourEvent@1325";
			 const char _rpc_call_ClearRanklist[] = "_rpc_call_ClearRanklist@1325";
			 const char _rpc_call_FetchRanklistData[] = "_rpc_call_FetchRanklistData@1325";
			 const char _rpc_call_FetchRanklistDataEx[] = "_rpc_call_FetchRanklistDataEx@1325";
			 const char _rpc_call_EndedArenaSeason[] = "_rpc_call_EndedArenaSeason@1325";
			 const char _rpc_call_QuerySeasonOrder[] = "_rpc_call_QuerySeasonOrder@1325";
			 const char _rpc_call_GetHumanAverageLevel[] = "_rpc_call_GetHumanAverageLevel@1325";
			 const char _rpc_call_RebuildRanklistMsg[] = "_rpc_call_RebuildRanklistMsg@1325";
			 const char _rpc_call_GuildDismissed[] = "_rpc_call_GuildDismissed@1325";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@1325";
			 const char _rpc_call_QueryGlobalPlayer[] = "_rpc_call_QueryGlobalPlayer@1325";
			 const char _rpc_call_QueryGlobal[] = "_rpc_call_QueryGlobal@1325";
			 const char _rpc_call_GlobalRankUpdate[] = "_rpc_call_GlobalRankUpdate@1325";
			 const char _rpc_call_StartHotActivity[] = "_rpc_call_StartHotActivity@1325";
			 const char _rpc_call_EndedHotActivity[] = "_rpc_call_EndedHotActivity@1325";
			 const char _rpc_call_SyncHumanOfflineData[] = "_rpc_call_SyncHumanOfflineData@1325";
			 const char _rpc_call_GetHumanOfflineData[] = "_rpc_call_GetHumanOfflineData@1325";
			 const char _rpc_call_GetRankOrder[] = "_rpc_call_GetRankOrder@1325";
			 const char _rpc_call_SaveHeroCard[] = "_rpc_call_SaveHeroCard@1325";
			 const char _rpc_call_GetHeroCard[] = "_rpc_call_GetHeroCard@1325";
		 }
		 namespace SImplEntranceSrv
		 {
			 const char _rpc_call_HumanInvoke[] = "_rpc_call_HumanInvoke@1616";
			 const char _rpc_call_LadderEntranceCli[] = "_rpc_call_LadderEntranceCli@1616";
			 const char _rpc_call_BroadCastCall[] = "_rpc_call_BroadCastCall@1616";
			 const char _rpc_call_LadderLogin[] = "_rpc_call_LadderLogin@1616";
			 const char _rpc_call_QueryServerName[] = "_rpc_call_QueryServerName@1616";
			 const char _rpc_call_CreateLadderToken[] = "_rpc_call_CreateLadderToken@1616";
			 const char _rpc_call_BroadcastGM[] = "_rpc_call_BroadcastGM@1616";
			 const char _rpc_call_QueryConnectedServer[] = "_rpc_call_QueryConnectedServer@1616";
		 }
		 namespace SImplEntranceCli
		 {
			 const char _rpc_call_QueryConfigs[] = "_rpc_call_QueryConfigs@1581";
			 const char _rpc_call_LadderEntranceSrv[] = "_rpc_call_LadderEntranceSrv@1581";
			 const char _rpc_call_LadderHumanInvoke[] = "_rpc_call_LadderHumanInvoke@1581";
			 const char _rpc_call_LaddderIsConnected[] = "_rpc_call_LaddderIsConnected@1581";
		 }
		 namespace SImplMultiplayerDungeon
		 {
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@2381";
		 }
		 namespace MultiplayerDungeonMgr
		 {
			 const char _rpc_call_Start[] = "_rpc_call_Start@2190";
			 const char _rpc_call_StartMatch[] = "_rpc_call_StartMatch@2190";
			 const char _rpc_call_CancelMatch[] = "_rpc_call_CancelMatch@2190";
		 }
		 namespace SImplLog
		 {
			 const char _rpc_call_Write[] = "_rpc_call_Write@775";
			 const char _rpc_call_Write_WM[] = "_rpc_call_Write_WM@775";
			 const char _rpc_call_WriteBetaLog[] = "_rpc_call_WriteBetaLog@775";
			 const char _rpc_call_ZeroHour[] = "_rpc_call_ZeroHour@775";
			 const char _rpc_call_Write_MData[] = "_rpc_call_Write_MData@775";
		 }
		 namespace NameMgr
		 {
			 const char _rpc_call_Check[] = "_rpc_call_Check@679";
			 const char _rpc_call_TakeUp[] = "_rpc_call_TakeUp@679";
			 const char _rpc_call_Free[] = "_rpc_call_Free@679";
		 }
		 namespace SImplCommonActivity
		 {
			 const char _rpc_call_QueryActivity[] = "_rpc_call_QueryActivity@1947";
			 const char _rpc_call_Reward[] = "_rpc_call_Reward@1947";
			 const char _rpc_call_FinishGoal[] = "_rpc_call_FinishGoal@1947";
			 const char _rpc_call_ResetGoal[] = "_rpc_call_ResetGoal@1947";
			 const char _rpc_call_CA_UpdateRanklist[] = "_rpc_call_CA_UpdateRanklist@1947";
			 const char _rpc_call_set_end[] = "_rpc_call_set_end@1947";
			 const char _rpc_call_set_reward_end[] = "_rpc_call_set_reward_end@1947";
			 const char _rpc_call_set_kaifu[] = "_rpc_call_set_kaifu@1947";
			 const char _rpc_call_HumanCharge[] = "_rpc_call_HumanCharge@1947";
			 const char _rpc_call_HumanSpend[] = "_rpc_call_HumanSpend@1947";
			 const char _rpc_call_QueryPlayerRank[] = "_rpc_call_QueryPlayerRank@1947";
			 const char _rpc_call_web_query_activity[] = "_rpc_call_web_query_activity@1947";
			 const char _rpc_call_web_set_activitytime[] = "_rpc_call_web_set_activitytime@1947";
		 }
		 namespace SImplHotActivity
		 {
			 const char _rpc_call_QueryActivity[] = "_rpc_call_QueryActivity@1629";
			 const char _rpc_call_set_end[] = "_rpc_call_set_end@1629";
			 const char _rpc_call_set_reward_end[] = "_rpc_call_set_reward_end@1629";
			 const char _rpc_call_set_kaifu[] = "_rpc_call_set_kaifu@1629";
			 const char _rpc_call_web_open_activity[] = "_rpc_call_web_open_activity@1629";
			 const char _rpc_call_web_close_activity[] = "_rpc_call_web_close_activity@1629";
			 const char _rpc_call_web_delete_activity[] = "_rpc_call_web_delete_activity@1629";
			 const char _rpc_call_web_query_activity[] = "_rpc_call_web_query_activity@1629";
			 const char _rpc_call_web_update_activity[] = "_rpc_call_web_update_activity@1629";
			 const char _rpc_call_RewardActivity[] = "_rpc_call_RewardActivity@1629";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@1629";
		 }
		 namespace SImplDevil
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@985";
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@985";
		 }
		 namespace DevilQueueMgr
		 {
			 const char _rpc_call_AckMatch[] = "_rpc_call_AckMatch@1311";
			 const char _rpc_call_CancelMatch[] = "_rpc_call_CancelMatch@1311";
			 const char _rpc_call_AckEnter[] = "_rpc_call_AckEnter@1311";
		 }
		 namespace SImplPVE
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@720";
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@720";
			 const char _rpc_call_HalfHourEvent[] = "_rpc_call_HalfHourEvent@720";
		 }
		 namespace PVEQueueMgr
		 {
			 const char _rpc_call_AckMatch[] = "_rpc_call_AckMatch@1046";
			 const char _rpc_call_CancelMatch[] = "_rpc_call_CancelMatch@1046";
			 const char _rpc_call_AckEnter[] = "_rpc_call_AckEnter@1046";
		 }
		 namespace SImplTeam
		 {
			 const char _rpc_call_Query[] = "_rpc_call_Query@876";
			 const char _rpc_call_QueryTeamList[] = "_rpc_call_QueryTeamList@876";
		 }
		 namespace SImplRedEnvelope
		 {
			 const char _rpc_call_CreateRedEnvelope[] = "_rpc_call_CreateRedEnvelope@1598";
			 const char _rpc_call_GetRedEnvelope[] = "_rpc_call_GetRedEnvelope@1598";
		 }
	}
	namespace dbsrv
	{
		 namespace Base
		 {
			 const char _rpc_call_Null[] = "_rpc_call_Null@379";
		 }
		 namespace SImplKVDB
		 {
			 const char _rpc_call_Hsetnx_incrid[] = "_rpc_call_Hsetnx_incrid@780";
			 const char _rpc_call_Hsetnx[] = "_rpc_call_Hsetnx@780";
			 const char _rpc_call_Hset[] = "_rpc_call_Hset@780";
			 const char _rpc_call_Hget[] = "_rpc_call_Hget@780";
			 const char _rpc_call_HgetByid[] = "_rpc_call_HgetByid@780";
			 const char _rpc_call_Hdel[] = "_rpc_call_Hdel@780";
			 const char _rpc_call_Hall[] = "_rpc_call_Hall@780";
			 const char _rpc_call_Hvals[] = "_rpc_call_Hvals@780";
			 const char _rpc_call_Hsize[] = "_rpc_call_Hsize@780";
			 const char _rpc_call_Hclear[] = "_rpc_call_Hclear@780";
			 const char _rpc_call_Hmultiget[] = "_rpc_call_Hmultiget@780";
			 const char _rpc_call_Hmultidel[] = "_rpc_call_Hmultidel@780";
			 const char _rpc_call_Hmultiset[] = "_rpc_call_Hmultiset@780";
			 const char _rpc_call_HcrossallFetch[] = "_rpc_call_HcrossallFetch@780";
			 const char _rpc_call_HvalsFetch[] = "_rpc_call_HvalsFetch@780";
			 const char _rpc_call_HvalsIndexQueryStr[] = "_rpc_call_HvalsIndexQueryStr@780";
			 const char _rpc_call_HvalsIndexQueryInt[] = "_rpc_call_HvalsIndexQueryInt@780";
			 const char _rpc_call_HvalsIndexQueryRangeStr[] = "_rpc_call_HvalsIndexQueryRangeStr@780";
			 const char _rpc_call_HvalsIndexQueryRangeInt[] = "_rpc_call_HvalsIndexQueryRangeInt@780";
			 const char _rpc_call_HmultisetnxLoose[] = "_rpc_call_HmultisetnxLoose@780";
			 const char _rpc_call_MallocIncrid[] = "_rpc_call_MallocIncrid@780";
			 const char _rpc_call_Zset[] = "_rpc_call_Zset@780";
			 const char _rpc_call_Zdel[] = "_rpc_call_Zdel@780";
			 const char _rpc_call_Zget[] = "_rpc_call_Zget@780";
			 const char _rpc_call_Ztop[] = "_rpc_call_Ztop@780";
			 const char _rpc_call_ZRtop[] = "_rpc_call_ZRtop@780";
			 const char _rpc_call_Zclear[] = "_rpc_call_Zclear@780";
			 const char _rpc_call_Hscan[] = "_rpc_call_Hscan@780";
			 const char _rpc_call_Exit[] = "_rpc_call_Exit@780";
		 }
		 namespace SImplKVDBLoader
		 {
			 const char _rpc_call_UpdateGlobalWelfareId[] = "_rpc_call_UpdateGlobalWelfareId@1379";
			 const char _rpc_call_QueryCharacers[] = "_rpc_call_QueryCharacers@1379";
			 const char _rpc_call_CreateCharacter[] = "_rpc_call_CreateCharacter@1379";
			 const char _rpc_call_LoadHuman[] = "_rpc_call_LoadHuman@1379";
			 const char _rpc_call_LoadHumanItems[] = "_rpc_call_LoadHumanItems@1379";
			 const char _rpc_call_LadderRewriteHuman[] = "_rpc_call_LadderRewriteHuman@1379";
			 const char _rpc_call_LadderRewriteHumans[] = "_rpc_call_LadderRewriteHumans@1379";
			 const char _rpc_call_CreateHumanFromRawData[] = "_rpc_call_CreateHumanFromRawData@1379";
			 const char _rpc_call_HumanRename[] = "_rpc_call_HumanRename@1379";
			 const char _rpc_call_DiscardHuman[] = "_rpc_call_DiscardHuman@1379";
			 const char _rpc_call_DisconnectHuman[] = "_rpc_call_DisconnectHuman@1379";
			 const char _rpc_call_HumanQuery[] = "_rpc_call_HumanQuery@1379";
			 const char _rpc_call_HumanQueryByName[] = "_rpc_call_HumanQueryByName@1379";
			 const char _rpc_call_HumanQueryById[] = "_rpc_call_HumanQueryById@1379";
			 const char _rpc_call_HumanQueryByPassport[] = "_rpc_call_HumanQueryByPassport@1379";
			 const char _rpc_call_LianYunHumanQueryByPassport[] = "_rpc_call_LianYunHumanQueryByPassport@1379";
			 const char _rpc_call_XiYouHumanQueryByPassport[] = "_rpc_call_XiYouHumanQueryByPassport@1379";
			 const char _rpc_call_DeleteCharacter[] = "_rpc_call_DeleteCharacter@1379";
			 const char _rpc_call_CleanupDatabase[] = "_rpc_call_CleanupDatabase@1379";
			 const char _rpc_call_LockPassport[] = "_rpc_call_LockPassport@1379";
			 const char _rpc_call_UnlockPassport[] = "_rpc_call_UnlockPassport@1379";
			 const char _rpc_call_LockChatPassport[] = "_rpc_call_LockChatPassport@1379";
			 const char _rpc_call_UnlockChatPassport[] = "_rpc_call_UnlockChatPassport@1379";
			 const char _rpc_call_LoadVips[] = "_rpc_call_LoadVips@1379";
			 const char _rpc_call_ILoadHuman[] = "_rpc_call_ILoadHuman@1379";
			 const char _rpc_call_ILoadPassport[] = "_rpc_call_ILoadPassport@1379";
			 const char _rpc_call_GetPlayersInfoByPassport360[] = "_rpc_call_GetPlayersInfoByPassport360@1379";
			 const char _rpc_call_Human360QueryById[] = "_rpc_call_Human360QueryById@1379";
			 const char _rpc_call_Human360QueryRideByRoleId[] = "_rpc_call_Human360QueryRideByRoleId@1379";
			 const char _rpc_call_Human360QuerySkillByRoleId[] = "_rpc_call_Human360QuerySkillByRoleId@1379";
			 const char _rpc_call_Human360QueryMagicWeaponByRoleId[] = "_rpc_call_Human360QueryMagicWeaponByRoleId@1379";
			 const char _rpc_call_Human360QueryByIdBatch[] = "_rpc_call_Human360QueryByIdBatch@1379";
		 }
	}
	namespace accsrv
	{
		 namespace Base
		 {
			 const char _rpc_call_Null[] = "_rpc_call_Null@379";
		 }
		 namespace SImplAcc
		 {
			 const char _rpc_call_MsgIncoming[] = "_rpc_call_MsgIncoming@748";
			 const char _rpc_call_Exit[] = "_rpc_call_Exit@748";
			 const char _rpc_call_ReloadWhiteList[] = "_rpc_call_ReloadWhiteList@748";
			 const char _rpc_call_EnableWhiteList[] = "_rpc_call_EnableWhiteList@748";
		 }
		 namespace SImplWallow
		 {
			 const char _rpc_call_WallowLogin[] = "_rpc_call_WallowLogin@1115";
			 const char _rpc_call_WallowLogout[] = "_rpc_call_WallowLogout@1115";
		 }
	}
	namespace connsrv
	{
		 namespace Base
		 {
			 const char _rpc_call_Null[] = "_rpc_call_Null@379";
		 }
		 namespace SImplSend
		 {
			 const char _rpc_call_Broadcast[] = "_rpc_call_Broadcast@879";
			 const char _rpc_call_BroadcastEx[] = "_rpc_call_BroadcastEx@879";
		 }
		 namespace SImplListener
		 {
			 const char _rpc_call_Enable[] = "_rpc_call_Enable@1323";
			 const char _rpc_call_Exit[] = "_rpc_call_Exit@1323";
			 const char _rpc_call_EnableMsgid[] = "_rpc_call_EnableMsgid@1323";
			 const char _rpc_call_GetDisabledMsgids[] = "_rpc_call_GetDisabledMsgids@1323";
		 }
		 namespace Connection
		 {
			 const char _rpc_call_CloseTcp[] = "_rpc_call_CloseTcp@1040";
			 const char _rpc_call_SendMsg[] = "_rpc_call_SendMsg@1040";
			 const char _rpc_call_SendMsgEx[] = "_rpc_call_SendMsgEx@1040";
			 const char _rpc_call_MsgIncomingResult[] = "_rpc_call_MsgIncomingResult@1040";
			 const char _rpc_call_UpdateStatus[] = "_rpc_call_UpdateStatus@1040";
			 const char _rpc_call_CheckStatus[] = "_rpc_call_CheckStatus@1040";
			 const char _rpc_call_ReturnCreateCharacterStage[] = "_rpc_call_ReturnCreateCharacterStage@1040";
		 }
	}
	namespace globalsrv
	{
		 namespace Base
		 {
			 const char _rpc_call_Null[] = "_rpc_call_Null@379";
		 }
		 namespace SImplGlobal
		 {
			 const char _rpc_call_Test[] = "_rpc_call_Test@1078";
			 const char _rpc_call_SendMsg[] = "_rpc_call_SendMsg@1078";
		 }
		 namespace PassportLockMgr
		 {
			 const char _rpc_call_LockAdded[] = "_rpc_call_LockAdded@1547";
			 const char _rpc_call_LockDeled[] = "_rpc_call_LockDeled@1547";
			 const char _rpc_call_LockCheck[] = "_rpc_call_LockCheck@1547";
		 }
		 namespace RanklistMgr
		 {
			 const char _rpc_call_RankUpdate[] = "_rpc_call_RankUpdate@1134";
			 const char _rpc_call_RankQuery[] = "_rpc_call_RankQuery@1134";
			 const char _rpc_call_RankClear[] = "_rpc_call_RankClear@1134";
		 }
	}
}
#endif //_pw_rpc_names_