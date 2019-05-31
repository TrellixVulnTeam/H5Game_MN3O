#ifndef _pw_battle_def_h
#define _pw_battle_def_h

#include "pw_def.h"
#include "pw_ngs_common.h"

namespace pwngs
{

	// 准备比赛倒计时时间（单位秒）
	const int cst_battle_team_enter_time = 30;

	// 战场逃跑BUFF
	const int cst_battle_escape_buff = 60910;

	const int cst_battle_normal_team_num = 3;
	const int cst_battle_ladder_team_num = 15;

	const int cst_battle_ladder_team_merge_low = 3;
	const int cst_battle_ladder_team_merge_min = 3;

	// 战场每日最多参加次数
	const int cst_battle_max_today_count = 3;
	const int cst_battle_max_accum_count = 20;

	// 战场队伍状态
	enum EBattleState
	{
		BATTLE_STATE_IDLE = 0,		// 空闲中
		BATTLE_STATE_MERGE,			// 匹配组队中
		BATTLE_STATE_MATCH,			// 匹配对手中
		BATTLE_STATE_ENTER,			// 准备进入中
		BATTLE_STATE_COMPETE,		// 竞技比赛中
	};

	// 战场队伍标记
	enum EBattleFlag
	{
		BATTLE_FLAG_ACKED = 0x01,	// 确认参加比赛
		BATTLE_FLAG_CANDI = 0x02,	// 可以作为候补 
	};

	// 战场保存标记
	enum EBattleSaveFlag
	{
		BATTLE_SAVE_FLAG_ESCAPE = 0x01,
	};

	// 战场模式
	enum EBattleMode
	{
		BATTLE_MODE_NONE = 0,
		BATTLE_MODE_40,				// 40级模式
		BATTLE_MODE_50,				// 50级模式
		BATTLE_MODE_60,				// 60级模式
		BATTLE_MODE_70,				// 70级模式
		BATTLE_MODE_NUM,			
	};

	struct SBattleLevel
	{
		int nMinLevel;
		int nMaxLevel;
	};

	const SBattleLevel cst_battle_mode_to_level[BATTLE_MODE_NUM] = 
	{
		{999,999},{80,119},{120,159},{160,199},{200,999},		
	};

	// 战场结果
	enum EBattleResult
	{
		BATTLE_RESULT_W = 0,
		BATTLE_RESULT_D = 1,
		BATTLE_RESULT_L = 2,
	};

#pragma pack(push,1)
	
	// CtrlSrv上的战场信息
	struct SHumanBattleInfo
	{

	};

#pragma pack(pop)

	enum EBattleNotifyCode
	{
		BATTLE_NOTIFY_LEVEL_NOT_MATCH = 100514,
		BATTLE_NOTIFY_COUNT_NOT_ENOUGH = 101003,
	};

}

#endif //_pw_battle_def_h