#ifndef _pw_multiplayer_dungeon_def_
#define _pw_multiplayer_dungeon_def_

#include "pw_def.h"

namespace pwngs
{
	// 魔王本每天免费进入次数
	const int cst_multiplayer_dungeon_enter_times_per_day = 3;
	// 魔王本扫荡vip等级限制
	const int cst_multiplayer_dungeon_sweep_vip_level = 4 ;
	// 魔王本扫荡等级限制
	const int cst_multiplayer_dungeon_sweep_level = 15 ;

	// 多人副本队伍状态
	enum EMultiplayerDungeonState
	{
		MULTIPLAYER_DUNGEON_TEAM_STATE_WAITING = 0,	// 组队中
		MULTIPLAYER_DUNGEON_TEAM_STATE_STARTED,		// 副本开始
	};

	enum EMultiplayerDungeonType
	{
		MULTIPLAYER_DUNGEON_TYPE_DEVIL = 0,	// 魔王本
		MULTIPLAYER_DUNGEON_TYPE_WINTER,	// 凛冬
		MULTIPLAYER_DUNGEON_TYPE_LONGYU,	// 龙域

		MULTIPLAYER_DUNGEON_TYPE_MAX,
	};

	enum EMDErrorCode
	{
		MD_ERROR_SUCCESSFUL = 0,
		MD_ERROR_DEVIL_REQ_VIP_LEVEL			= 25600, // 超过当前vip等级的最大可购买次数
		MD_ERROR_DEVIL_REQ_GOLD					= 25601, // 金币不足，无法购买魔王本进入次数
		MD_ERROR_WINTER_ALREADY_FINISH			= 25602, // 今天已完成凛冬修炼
		MD_ERROR_WINTER_REQ_GOLD				= 25603, // 金币不足，无法完成凛冬修炼
		MD_ERROR_LONGYU_REQ_REWARD_TIMES		= 25604, // 今天已完成龙域守护
		MD_ERROR_LONGYU_REQ_GOLD				= 25605, // 金币不足，无法完成龙域守护
		MD_ERROR_LONGYU_BUY_COUNT_REQ_VIP_LEVEL	= 25611, // 升级VIP可获得更多龙域守护购买次数
		MD_ERROR_LONGYU_BUY_COUNT_REQ_GOLD		= 25612, // 金币不足，无法完成龙域守护奖励次数
	};

	// 跨服魔王本离开副本时间限制提示
	const int cst_notify_md_leave_timelimit = 107002 ;
}
#endif // _pw_multiplayer_dungeon_def_
