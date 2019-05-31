#ifndef _pw_notify_def_
#define _pw_notify_def_

namespace pwngs
{
	const int cst_Notify_Strid_LevelUp = 1000;
	const int cst_Notify_Strid_EliteDungeon_Times = 2000;
	const int cst_Notify_Strid_EliteDungeon_Money = 2001;

	const int cst_Notify_Strid_MagicUpgrade_Money = 2002;
	const int cst_Notify_Strid_MagicUpgrade_LevelLimit = 2003;
	//const int cst_Notify_Strid_MagicUpgrade_OK = 2004; //TT1952 策划需求，技能升级成功不发送serverstr信息
	const int cst_Notify_Strid_MagicUpgrade_NoFound = 2005;
	const int cst_Notify_Strid_MagicUpgrade_MagciPoint = 2006;
	const int cst_Notify_Strid_MagicUpgradeOneKey_NotAllSuccess = 2007;
	const int cst_Notify_Strid_MagicUpgradeOneKey_AllSuccess = 2008;

	const int cst_Notify_Strid_MagicReplace_Err_Loc = 2010;
	const int cst_Notify_Strid_MagicReplace_NoFound_ByID = 2011;
	const int cst_Notify_Strid_MagicReplace_NoFound_ByLoc = 2012;
	const int cst_Notify_Strid_MagicReplace_LocLimit = 2013;
	const int cst_Notify_Strid_MagicReplace_OK = 2014;
	const int cst_Notify_Strid_MagicReplace_SameMagic = 2015;
	const int cst_Notify_Strid_MagicAdvance_OK = 2018;

	const int cst_Notify_Strid_Recruit_Arena_TeamMember = 6000;
	const int cst_Notify_Strid_Dismiss_Team = 6001;
	const int cst_Notify_Strid_Leave_Team = 6002;
	const int cst_Notify_Strid_Kick_Team = 6003;
	const int cst_Notify_Strid_Leave_Match_Queue = 6004;
	const int cst_Notify_Strid_Invite_Team = 6005;
	const int cst_Notify_Strid_Join_Team = 6006;
	const int cst_Notify_Strid_Change_Team_Leader = 6007;
	const int cst_Notify_Strid_Levelup_Guild = 6008;
	const int cst_Notify_Strid_Join_Guild = 6009;
	const int cst_Notify_Strid_Leave_Guild = 6010;
	const int cst_Notify_Strid_Add_Guild_Devotion = 6011;
	const int cst_Notify_Strid_Arena_Cancel_Enter = 6012;
	const int cst_Notify_Strid_Invite_Team_Ret = 6014;

	const int cst_Notify_MD_Devil_Recruit = 12601;
	const int cst_Notify_MD_Winter_Recruit = 12602;

	const int cst_Notify_Strid_Team_Full = 12605;
	const int cst_Notify_Strid_Team_Kickout = 12606;

	const int cst_Notify_Strid_Get_Vigor_Use_Item = 12710;
	const int cst_Notify_Strid_Get_Vigor_Buy = 12711;
	const int cst_Notify_Strid_Get_Vigor_Timing = 12712;
	const int cst_Notify_Strid_Get_Vigor_Levelup = 12713;
	const int cst_Notify_Strid_Get_Vigor_Overflow = 12714;

	const int cst_Notify_Babel_Rank_First_Pass = 50318;

	const int cst_Notify_Activity_DTS_Close = 51100;
	const int cst_Notify_Activity_Ready = 51150; // 活动未开启
	const int cst_Notify_Activity_Quit = 51151; // 活动已结束
	const int cst_Notify_Activity_NJTZ_Closed = 51201;

	const int cst_Notify_Dark_Arena_Completed_Gold = 51450;

	const int cst_Notify_Strid_EquipRune_Success = 51517;
	const int cst_Notify_Strid_EquipRune_Replace = 51518;

	const int cst_Notify_Strid_Player_QueryInfo_NotExist = 52100;
	const int cst_Notify_Strid_Player_QueryInfo_Self = 52101;
	const int cst_Notify_Strid_Player_QueryInfo_From = 52102;

	const int cst_Notify_Strid_PingCheck_Timeout = 56000;
	const int cst_Notify_Strid_QueryItem_NotFound = 56001;

	const int cst_Notify_Strid_Target_Not_Online = 56100;
	const int cst_Notify_Strid_Chat_World_CD = 56101;

	const int cst_Notify_Strid_Dungeon_Reward_Bag_Full = 60000;

	const int cst_Notify_Strid_Exit_Meditation_No_Reward = 60100;
	const int cst_Notify_Strid_Exit_Meditation_Reward = 60101;

	const int cst_Notify_Strid_Chat_Horn_Req_Gold = 70014;
	
	const int cst_Notify_Strid_Function_LGKJ_NotOpen = 101014;
	const int cst_Notify_Strid_Function_NJTZ_JOIN_BUFF = 103226;

	const int cst_Notify_Strid_Recruit_Devil_TeamMember = 12601;

	const int cst_Notify_Strid_Rename = 134012;

	const int cst_Notify_Strid_Fire_Mail = 60001;
	const int cst_Notify_Strid_Fire_Count_Down = 108008;
	const int cst_Notify_Strid_Fire_Begin = 108009;
	const int cst_Notify_Strid_Fire_End = 108016;
}

#endif // _pw_notify_def_