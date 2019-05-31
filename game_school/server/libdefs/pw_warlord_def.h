#ifndef _pw_warlord_def_
#define _pw_warlord_def_

#include "pw_def.h"
#include "pw_ngs_def.h"
#include "kvdb/pw_fixed_string.h"
#include "kvorm/pw_orm_warlordcombatresult.h"

namespace pwngs
{
	const int32 cst_warlord_top_start = 1;
	const int32 cst_warlord_top_end = 3;

	const int32 cst_warlord_rival_max = 3;			// 被挑战者最大数量

	const int32	cst_warlord_broadcast_top = 1;			// 头名广播 
	const int32	cst_warlord_broadcast_win_idx = 5;		// 连胜广播间隔
	const int32	cst_warlord_broadcast_win_start = 10;	// 连胜广播起始
	const int32	cst_warlord_broadcast_worship = 10;		// 膜拜广播

	const int32 cst_warlord_special_rank = 10;	// 低于10的排名特殊处理

	enum EWarlordOperCode
	{
		WARLORD_NOTIFY_SUCCESS = 0,
		
		WARLORD_NOTIFY_ENTER = 56300,					// 进入

		WARLORD_NOTIFY_COMBAT_CANNOT_CHALLENGE	= 56301,	//不能挑战
		WARLORD_NOTIFY_COMBAT_CD_ING			= 56302,	// 挑战-CD中

		WARLORD_NOTIFY_NOT_RESET_CD				= 56303,	//没有重置CD
		WARLORD_NOTIFY_RESET_CD_NOT_GOLD		= 56304,	//没有足够的金币重置CD

		WARLORD_NOTIFY_COMBAT_RIVAL_NOT_EXIST = 56310,	// 挑战-被挑战者不存在
		WARLORD_NOTIFY_COMBAT_SELF,						// 挑战-挑战自己
		WARLORD_NOTIFY_COMBAT_CNT_LIMIT,				// 挑战-免费挑战次数不足
		WARLORD_NOTIFY_COMBAT_ADD_NOT_ENOUGH_GOLD,		// 挑战-增次金币不足
		WARLORD_NOTIFY_COMBAT_ADD_CNT_LIMIT,			// 挑战-金币增次上限
		WARLORD_NOTIFY_COMBAT_TOP_LIMIT,				// 挑战-不能挑战前三名
		
		
		WARLORD_NOTIFY_DRAW_NO_AWARD = 56330,			// 领奖-无可领奖励
		WARLORD_NOTIFY_DRAW_BAG_LIMIT,					// 领奖-背包空间不足

		WARLORD_NOTIFY_BROADCAST_WIN = 56340,			// 广播-连胜
		WARLORD_NOTIFY_BROADCAST_TOP,					// 广播-头名
		WARLORD_NOTIFY_BROADCAST_WORSHIP,				// 广播-膜拜

		WARLORD_NOTIFY_HONOR_INVALID_ARGS = 56350,		// 荣誉-参数错误
		WARLORD_NOTIFY_HONOR_NOT_ENOUGH,				// 荣誉-荣誉不足

		WARLORD_NOTIFY_WORSHIP_NOT_EXIST = 56360,		// 膜拜-玩家不存在
		WARLORD_NOTIFY_WORSHIP_CNT_LIMIT,				// 膜拜-次数限制
		WARLORD_NOTIFY_WORSHIP_SELF,					// 膜拜-膜拜自己
		WARLORD_NOTIFY_WORSHIP_RANK_LIMIT,				// 膜拜-排名限制(非前三名)
	};

	enum EWarlordBroadcastType
	{ 
		WARLORD_BROADCAST_WIN = 0,		// 连胜广播
		WARLORD_BROADCAST_TOP,			// 头名广播
		WARLORD_BROADCAST_WORSHIP,		// 膜拜广播

		WARLORD_BROADCAST_MAX,
	};

	enum EWarlordCombatResultType
	{
		WARLORD_COMBAT_RESULT_ERROR = -1,			// 错误

		WARLORD_COMBAT_SUCC_RANK_NOT_CHANGE = 0,	// 成功排名不变
		WARLORD_COMBAT_SUCC_RANK_CHANGE,			// 成功排名变化
		WARLORD_COMBAT_FAIL,						// 失败
	};

	enum EWarlordModCombatType
	{
		WARLORD_MOD_COMBAT_TYPE_REDUCE = 0,			// 减少次数
		WARLORD_MOD_COMBAT_TYPE_ADD,				// 增加次数
	};

	enum EWarlordGrantRankAwardType
	{
		WARLORD_GRANT_RANK_AWARD_TYPE_CTRL_TIMER = 0,		// ctrl定时发放
		WARLORD_GRANT_RANK_AWARD_TYPE_RPC,					// rpc发放
	};

	typedef orm::WarlordCombatResult SWarlordCombatResult;

	enum
	{
		EType_Human = 1,	//Human
		EType_NPC = 2,	//npc
	};

	struct SWarlordCombatResultData
	{
		int32 type;
		uint8 src_type;
		int64 src_id;
		int64 src_rank;
		pwutils::fixed_string<64> src_name;
		uint8 dst_type;
		int64 dst_id;
		int64 dst_rank;
		pwutils::fixed_string<64> dst_name;
		int64 combat_time;

		SWarlordCombatResultData()
		{
			type = -1;
			src_type = 0;
			src_id = 0;
			src_rank = 0;
			src_name = "";
			dst_type = 0;
			dst_id = 0;
			dst_rank = 0;
			dst_name = "";
			combat_time = 0;
		}
	};

	struct SWarlordData
	{
		int64 id;
		uint8 type;
		int64 hid;
		int64 win_count;
		int64 worship_today;
		int64 worship_total;
		int32 last_worship_date;
		SWarlordCombatResultData results[20];

		SWarlordData()
		{
			id = 0;
			type = 0;
			hid = 0;
			win_count = 0;
			worship_total = 0;
			worship_total = 0;
			last_worship_date = 0;
		}
	};

	// 获取挑战列表参数
	struct SWarlordParam
	{
		SWarlordParam() 
			: bRefresh(false)
			, bFirstCombat(false)
		{}

		bool bRefresh;	//是否随机
		int64 arrRanks[3];
		bool bFirstCombat;	//首次挑战
	};

	struct SChallengeInfo
	{
		SChallengeInfo()
			: rank(0)
			, type(0)
			, hid(0)
		{}

		int64 rank;
		uint8 type;
		int64 hid;
	};

	struct SChallengeWarlordInfo
	{
		SChallengeWarlordInfo()
		{}

		static const int size = 3;

		SChallengeInfo arrChallengeInfo[size];
	};
}

#endif // _pw_warlord_def_