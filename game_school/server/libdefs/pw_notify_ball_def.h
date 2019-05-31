#ifndef _pw_notify_ball_def_
#define _pw_notify_ball_def_

#include "pw_def.h"
#include "kvorm/pw_orm_notifyball.h"

namespace pwngs
{
	const int cst_notify_ball_expire_time = 7*24*3600;	// 消息球最大存储时间
	const size_t cst_notify_ball_save_max = 50;		// 消息球最大存储数量

	typedef orm::NotifyBall SNotifyBall;

	//const int cst_NotifyBall_Strid_InviteTeamCommon	= 1;
	const int cst_NotifyBall_Strid_InviteGuild		= 2;
	const int cst_NotifyBall_Strid_InviteTeamDevil	= 3;
	const int cst_NotifyBall_Strid_InviteTeamWinter	= 5;

	const int cst_NotifyBall_Strid_RequestFollow	= 11;
	const int cst_NotifyBall_Strid_FollowYou		= 12;

	const int cst_NotifyBall_Strid_Warlord_ChangeRank = 13;	// 武神挑战成功 排名变化

	const int cst_NotifyBall_Strid_GetVigorTime		= 16;
	const int cst_NotifyBall_Strid_GetVigorLevelup	= 17;

	//const int cst_NotifyBall_Strid_Ranklist_OnList	= 18;
	const int cst_NotifyBall_Strid_Ranklist_OutList	= 19;

	const int cst_NotifyBall_Strid_VigorExceedLimit	= 20;
	const int cst_NotifyBall_Strid_InviteTeamLongYu	= 21;
	const int cst_NotifyBall_Strid_DTSCloseSubstutite = 22;// 关闭大逃杀替身功能

	const int cst_NotifyBall_Strid_GuildWar_Start	= 100; // 你的联盟活跃度排名xx，获得了联盟会战的资格，请在xx时间参加
	const int cst_NotifyBall_Strid_GuildWar_Bye		= 101; // 联盟战轮空，直接进入下一轮
	const int cst_NotifyBall_Strid_GuildWar_Next	= 102; // 你的联盟获胜，获得了下一轮联盟会战的资格，请在xx时间参加

	const int cst_NotifyBall_Strid_Guild_Levelup		= 103;
	const int cst_NotifyBall_Strid_GuildStatue_Levelup	= 104;
	const int cst_NotifyBall_Strid_GuildShop_Levelup	= 105;
	const int cst_NotifyBall_Strid_GuildFruiter_Levelup	= 106;
	const int cst_NotifyBall_Strid_Function_Open_DTS = 107;

	const int cst_NotifyBall_Strid_Function_Open_Dragon_Delve = 110;
	const int cst_NotifyBall_Strid_Function_Open_Dragon_Savey = 111;
	const int cst_NotifyBall_Strid_Function_Open_Dragon_Guard = 112;
	const int cst_NotifyBall_Strid_Function_Open_Crystal_Cube = 113;
	const int cst_NotifyBall_Strid_Function_Open_Devil_Tree = 114;
	const int cst_NotifyBall_Strid_Function_Open_Home_Quest = 115;
	const int cst_NotifyBall_Strid_Function_Open_Tarot = 116;

	const int cst_NotifyBall_Strid_Activity_Join_NJTZ = 117;
	const int cst_NotifyBall_Strid_Activity_Join_DTS = 118;

	const int cst_NotifyBall_Strid_Function_Open_Babel = 119;

	const int cst_NotifyBall_Strid_Shop_Auto_Buy_Successed = 120;
	const int cst_NotifyBall_Strid_Shop_Auto_Buy_Failed_Req_Item = 121;
	const int cst_NotifyBall_Strid_Shop_Auto_Buy_Failed_Req_Bag = 122;

	const int cst_NotifyBall_Strid_Open_Auction_Return = 123;
	const int cst_NotifyBall_Strid_Open_Auction_Finish = 124;

	const int cst_NotifyBall_Strid_Babel_Open_Level = 125;

	const int cst_NotifyBall_Strid_Activity_Join_LGKJ = 126;
	const int cst_NotifyBall_Strid_GuildFunc_Open = 127;

	const int cst_NotifyBall_Strid_Award_Bag_Full = 200;
	const int cst_NotifyBall_Strid_Award_Finished = 201;

	const int cst_NotifyBall_Strid_FollowHuman	= 202;
	const int cst_NotifyBall_Strid_TeamInvite_MD_Friend = 203;
	const int cst_NotifyBall_Strid_TeamInvite_MD_Guild	= 204;
	const int cst_NotifyBall_Strid_AskFriend = 300 ;
	const int cst_NotifyBall_Strid_Mail = 301;
	const int cst_NotifyBall_Strid_ApplyJoinTeam = 302;
	const int cst_NotifyBall_Strid_InviteTeamCommon = 303;
	const int cst_NotifyBall_Strid_Ranklist_OnList = 304;
	const int cst_NotifyBall_Strid_Invite_NewTeam = 305;
	const int cst_NotifyBall_Strid_InviteTeamBattle = 306;
	const int cst_NotifyBall_Strid_InviteTeamArena = 307;
	const int cst_NotifyBall_Strid_WildBoss_Created = 404; // 野外boss创建
	const int cst_NotifyBall_Strid_Arena_1v1_Open = 405; // 单人竞技
	const int cst_NotifyBall_Strid_Arena_3v3_Open = 406; // 组队竞技
	const int cst_NotifyBall_Strid_PVE_Open = 407; // 守襄阳
	const int cst_NotifyBall_Strid_Battle_Open = 408; //跨服战场

	const int cst_NotifyBall_Strid_RedEnvelope = 410;//红包
}

#endif // _pw_notify_ball_def_
