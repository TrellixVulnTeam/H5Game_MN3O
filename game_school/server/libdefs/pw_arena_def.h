#ifndef _pw_arena_def_h
#define _pw_arena_def_h

#include "pw_def.h"
#include "pw_ngs_common.h"

namespace pwngs
{

	// 准备比赛倒计时时间（单位秒）
	const int cst_arena_team_enter_time = 10;

	const int cst_arena_bet2_need_gold = 2;
	const int cst_arena_bet5_need_gold = 10;
	const int cst_arena_today_bet_num = 3;

	const int cst_arena_stageid = 3000;

	// 竞技场逃跑BUFF
	const int cst_arena_escape_buff = 60900;	

	// 竞技队伍状态
	enum EArenaState
	{
		ARENA_STATE_IDLE = 0,		// 空闲中
		ARENA_STATE_MERGE,			// 匹配组队中
		ARENA_STATE_MATCH,			// 匹配对手中
		ARENA_STATE_ENTER,			// 准备进入中
		ARENA_STATE_COMPETE,		// 竞技比赛中
	};

	// 竞技队伍标记
	enum EArenaFlag
	{
		ARENA_FLAG_ACKED = 0x01,	// 确认参加比赛
	};

	// 竞技保存标记
	enum EArenaSaveFlag
	{
		ARENA_SAVE_FLAG_ESCAPE = 0x01,
	};

	// 竞技模式
	enum EArenaMode
	{
		ARENA_MODE_1V1 = 0,			// 单人模式
		ARENA_MODE_3V3 = 1,			// 三人模式
		ARENA_MODE_5V5 = 2,			// 五人模式

		ARENA_MODE_NUM,			
	};

	// 竞技结果
	enum EArenaResult
	{
		ARENA_RESULT_W = 0,
		ARENA_RESULT_D = 1,
		ARENA_RESULT_L = 2,
	};

	// 竞技场排行榜类型
	enum EArenaRankType
	{
		ARENA_RANK_1V1 = 1,
		ARENA_RANK_3V3 = 2,
	};

#pragma pack(push,1)
	
	// CtrlSrv上的竞技信息
	struct SHumanArenaInfo
	{
		sint32 nPoint;				// 竞技积分
		sint32 nCount;				// 竞技场数
		sint32 nWinCount;			// 竞技获胜场数
		sint32 nTodayCount;			// 当日参加场数
		sint32 nTodayWinCount;		// 当日获胜场数
		bool bFuncOpen;				// 功能是否开放 
	};

#pragma pack(pop)

	enum EArenaNotifyCode
	{
		ARENA_NOTIFY_BET_NOT_ENOUGH_NUM			= 15610,
		ARENA_NOTIFY_NOT_RANK_REWARD_MATCHING	= 134001,
		ARENA_NOTIFY_NOT_RANK_REWARD_HAD		= 134002,
		ARENA_NOTIFY_RANK_REWARD_SUCC			= 134003,
	};
}

#endif //_pw_arena_def_h