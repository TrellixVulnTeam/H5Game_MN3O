﻿#ifndef _pw_guild_const_
#define _pw_guild_const_

#include "pw_ngs_common.h"

namespace pwngs
{
	// 角色允许创建公会的最低限制
	const int cst_guild_name_max_len = 16;
	const int cst_guild_notice_max_len = 130;

	// 角色加入联盟保护时间
	const int cst_guild_join_limit_time = 24*3600;
	const int cst_guild_join_njtz_limit_time = 48*3600;

	// 新加入联盟BUFF保护
	const int cst_guild_join_buff = 60911;

	// 联盟踢人人数上限
	const int cst_guild_kick_limit_member = 15;

	enum EGuildLog
	{
		GUILD_LOG_NONE = 0,							// 未知类型
		GUILD_LOG_CREATE,							// 创建帮会
		GUILD_LOG_MEMBER_ADDED,						// 成员加入
		GUILD_LOG_MEMBER_LEAVE,						// 成员离开
		GUILD_LOG_MEMBER_KICKED,					// 开除成员
		GUILD_LOG_COMMANDER_CHANGED,				// 转让统帅
		GUILD_LOG_VICE_COMMANDER_CHANGED,			// 任命副统帅
		GUILD_LOG_ELITE_CHANGED,					// 任命精英
		GUILD_LOG_DISMISS_OPENED,					// 解散倒计时开启
		GUILD_LOG_DISMISS_CLOSED,					// 解散倒计时结束

		GUILD_LOG_BUILDING_LEVELUP = 20,			// 升级控制中心
		GUILD_LOG_FRUITER,							// 果树
		GUILD_LOG_LEVELUP,							// 联盟升级
		GUILD_LOG_DEPOT,							// 仓库分配
		GUILD_LOG_STATUE,							// 瞻仰
		GUILD_LOG_DRAGON_HUNT,						// 试炼之地

		GUILD_LOG_NJTZ,								// 军团战
	};

	enum EGuildLogStrId
	{
		GUILD_LOG_STRID_CREATE = 1230,
		GUILD_LOG_STRID_DISMISS_OPENED = 1231,
		GUILD_LOG_STRID_MEMBER_ADDED,
		GUILD_LOG_STRID_MEMBER_LEAVE,
		GUILD_LOG_STRID_MEMBER_KICKED,
		GUILD_LOG_STRID_VICE_COMMANDER_CHANGED,
		GUILD_LOG_STRID_ELITE_CHANGED,
		GUILD_LOG_STRID_COMMANDER_CHANGED,
		GUILD_LOG_STRID_LEVELUP,
		GUILD_LOG_STRID_DEVOTION_COIN,
		GUILD_LOG_STRID_DEVOTION_YUANBAO,
		GUILD_LOG_STRID_DISMISS_CLOSED,
		GUILD_LOG_STRID_BUILDING_LEVELUP,

		GUILD_LOG_STRID_NJTZ_WIN = 43417,
		GUILD_LOG_STRID_NJTZ_LOST = 43418,
		GUILD_LOG_STRID_FRUITER = 50874,
		GUILD_LOG_STRID_DEPOT = 50876,
		GUILD_LOG_STRID_STATUE = 50877,
		GUILD_LOG_STRID_DRAGON_HUNT = 50878,

	};

	enum EUpdateGuildInfo
	{
		UPDATE_GUILD_INFO_LOGIN = 0x0001,		// 角色登录更新
		UPDATE_GUILD_INFO_ENTER = 0x0002,		// 加入公会更新
		UPDATE_GUILD_INFO_LEAVE = 0x0004,		// 离开公会更新
		UPDATE_GUILD_INFO_LEVEL = 0x0008,		// 公会等级更新
	};

	// 需要同步给worldsrv的公会信息
	struct SHumanGuildInfo
	{
		SHumanGuildInfo() { memset(this,0,sizeof(*this)); }

		sint64 gid;				// 公会ID
		sint16 level;			// 公会等级
		sint32 devotion;		// 可用贡献度
		sint16 shop_level;		// 商店等级
		sint16 statue_level;	// 雕像等级
		sint16 fruiter_level;	// 果树等级
		bool hunt_doubled;		// 猎龙奖励双倍
		bool hunt_started;		// 猎龙副本是否开启
		sint64 hunt_game_mapid; // 开启的猎龙副本id
		char name[max_name_len];// 公会名称
		sint32 trial_land_passed_max; // 试炼之地已通过最大ID
		sint32 total_devotion;//历史贡献度
	};

	// 玩法功能开放
	enum EGuildFuncType
	{
		GUILD_FUNC_STATUE		= 0x01,	// 雕像
		GUILD_FUNC_FRUITER		= 0x02,	// 果树
		GUILD_FUNC_SHOP			= 0x04, // 商店
		GUILD_FUNC_DEPOT		= 0x08,	// 仓库
		GUILD_FUNC_LEVELUP		= 0x10,	// 升级
		GUILD_FUNC_DRAGON_HUNT	= 0x20,	// 猎龙
		GUILD_FUNC_TOWER		= 0x40,	// 灯塔
		GUILD_FUNC_TRIAL_LAND	= 0x80,	// 试炼之地

		GUILD_FUNC_NUM = 8,
	};

	enum EGuildBuildingType
	{
		GUILD_BUILDING_TYPE_NONE = 0,
		GUILD_BUILDING_TYPE_FRUITER,	// 果树
		GUILD_BUILDING_TYPE_SHOP,		// 商店
		GUILD_BUILDING_TYPE_STATUE,		// 雕像

		GUILD_BUILDING_NUM,
	};

	enum EGuildNotifyCode
	{
		GUILD_NOTIFY_SUCCESS = 0,

		GUILD_NOTIFY_FUNC_NOT_OPEN = 16001,
		GUILD_NOTIFY_NOT_ENOUGH_BAG_SPACE = 16002,
		GUILD_NOTIFY_BUILDING_MAX_LEVEL_LIMIT = 16003,
		GUILD_NOTIFY_BUILDING_NOT_ENOUGH_DEVELOPMENT = 16004,
		GUILD_NOTIFY_BUILDING_LEVEL_GTEATER_THAN_GUILD_LEVEL = 16005,
		GUILD_NOTIFY_FRUITER_PICKUP_NONE = 16036,
		GUILD_NOTIFY_BUILDING_LEVELUP_OPER_LIMIT = 16037,
		GUILD_NOTIFY_FRUITER_NOT_MATURED = 16038,
		GUILD_NOTIFY_FRUITER_PICKUP_COUNT_LIMIT = 16039,
		GUILD_NOTIFY_CREATE_GUILD = 16040,
		GUILD_NOTIFY_RECRUIT_MEMBER = 16041,
		GUILD_NOTIFY_STATUE_DONATE_COUNT_LIMIT = 16042,
		GUILD_NOTIFY_STATUE_COST_LIMIT = 16043,
		GUILD_NOTIFY_RECRUIT_OPER_NO_AUTH = 16044,
		GUILD_NOTIFY_RECRUIT_OPER_IN_CD = 16045,
		GUILD_NOTIFY_DEPOT_ALLOT_SUCCESS = 16046,
		GUILD_NOTIFY_HUMAN_OFFLINE = 16047,
		GUILD_NOTIFY_GET_DBDATA_TIMEOUT = 16048,
		GUILD_NOTIFY_MEMBER_NOT_EXIST = 16049,
		GUILD_NOTIFY_MEMBER_ADDED_FAILED = 16050,
		GUILD_NOTIFY_MEMBER_DELED_FAILED = 16051,
		GUILD_NOTIFY_GUILD_NOT_EXIST = 16052,
		GUILD_NOTIFY_NOTICE_OPER_NO_AUTH = 16053,
		GUILD_NOTIFY_NOTICE_LEN_LIMIT = 16054,
		GUILD_NOTIFY_FRUITER_PICKUP_TIME_LIMIT = 16055,
		GUILD_NOTIFY_CHANGE_NOTICE_OPER_IN_CD = 16056,
		GUILD_NOTIFY_STATUE_DONATE_SUCCESS = 16057,
		GUILD_NOTIFY_CHANGE_NOTICE_CONTENT = 16058,
		GUILD_NOTIFY_AUTO_APPLY = 16170,

		// 创建联盟
		GUILD_NOTIFY_CREATE_SUCCESS = 16100,
		GUILD_NOTIFY_CREATE_HAS_GUILD,	
		GUILD_NOTIFY_CREATE_LEVEL_LIMIT,
		GUILD_NOTIFY_CREATE_CASH_LIMIT,	
		GUILD_NOTIFY_CREATE_VIP_LIMIT,
		GUILD_NOTIFY_CREATE_NAME_LIMIT,
		GUILD_NOTIFY_CREATE_NAME_LEN_LIMIT,
		GUILD_NOTIFY_CREATE_TIMEOUT,
		GUILD_NOTIFY_CREATE_WRITEDB_FAILED,
		GUILD_NOTIFY_CREATE_NUM_LIMIT = 16302,

		// 离开联盟
		GUILD_NOTIFY_LEAVE_SUCCESS = 16120,
		GUILD_NOTIFY_LEAVE_COMMANDER_LIMIT,

		// 踢出联盟
		GUILD_NOTIFY_KICKED_SUCCESS = 16130,
		GUILD_NOTIFY_KICKED_OPER_NO_AUTH,
		GUILD_NOTIFY_KICKED_NUM_LIMIT = 16301,
		GUILD_NOTIFY_KICKED_NUM_NOTIFY = 16303,

		// 申请入盟
		GUILD_NOTIFY_APPLY_SUCCESS = 16140,
		GUILD_NOTIFY_APPLY_HAS_GUILD,
		GUILD_NOTIFY_APPLY_LEVEL_LIMIT,
		GUILD_NOTIFY_APPLY_GUILD_FULL,
		GUILD_NOTIFY_APPLY_MEMBER_FULL,
		GUILD_NOTIFY_APPLY_APPLY_MEMBER_FULL,
		GUILD_NOTIFY_APPLY_HAVE_APPLIED,
		GUILD_NOTIFY_APPLY_OPER_NO_AUTH,
		GUILD_NOTIFY_APPLY_TIMEOUT,	
		GUILD_NOTIFY_APPLY_LAST_LEAVE_TIME_LIMIT,

		GUILD_NOTIFY_APPLY_RESULT_SUCCESS = 16150,

		// 邀请入盟
		GUILD_NOTIFY_INVITE_SUCCESS = 16160,
		GUILD_NOTIFY_INVITE_LEVEL_LIMIT,
		GUILD_NOTIFY_INVITE_MEMBER_FULL,
		GUILD_NOTIFY_INVITE_NOT_SELF,
		GUILD_NOTIFY_INVITE_OPER_NO_AUTH,
		GUILD_NOTIFY_INVITE_HAS_GUILD,
		GUILD_NOTIFY_INVITE_TIMEOUT,
		GUILD_NOTIFY_INVITE_HAVE_APPLIED,

		GUILD_NOTIFY_JOIN_SUCCESS = 16170,

		// 联盟商店
		GUILD_NOTIFY_SHOP_SUCCESS = 16180,
		GUILD_NOTIFY_SHOP_NOT_EXIST_ITEM,
		GUILD_NOTIFY_SHOP_COST_LIMIT,
		GUILD_NOTIFY_SHOP_NOT_ENOUGH_DEVOTION,
		GUILD_NOTIFY_SHOP_REFRESH_ITEMS,
		GUILD_NOTIFY_SHOP_BUY_SUCCESS,

		// 更改联盟职务
		GUILD_NOTIFY_TITLE_SUCCESS = 16200,
		GUILD_NOTIFY_TITLE_NO_CANDIDATE,
		GUILD_NOTIFY_TITLE_CHANGED,
		GUILD_NOTIFY_TITLE_INVAILD_CANDIDATE,
		GUILD_NOTIFY_TITLE_OPER_NO_AUTH,
		GUILD_NOTIFY_TITLE_TOO_MANY_CANDIDATES,
		GUILD_NOTIFY_TITLE_WITH_NAME_SUCCESS,
		GUILD_NOTIFY_TITLE_TOO_MANY_ELITES,
		GUILD_NOTIFY_TITLE_TOO_MANY_VICE_COMMANDER = 16308,

	};

	enum EDragonHuntUpdateReason
	{
		DRAGON_HUNT_UPDATE_REASON_PERSONAL = 0,
		DRAGON_HUNT_UPDATE_REASON_GUILD,
	};

	enum EDragonHuntError
	{
		DRAGON_HUNT_ERROR_SUCCESSFUL		= 0,

		DRAGON_HUNT_ERROR_REQ_GOLD			= 16006,	// 金币不足
		DRAGON_HUNT_ERROR_REQ_FREE_TIMES	= 16007,	// 无免费猎龙次数
		DRAGON_HUNT_ERROR_REQ_GOLD_TIMES	= 16008,	// 无金币猎龙次数
		DRAGON_HUNT_ERROR_FREE_HUNT_FAILED	= 16009,	// 免费猎龙失败
		DRAGON_HUNT_ERROR_HAS_DOUBLED		= 16010,	// 猎龙已双倍
		DRAGON_HUNT_ERROR_HAS_STARTED		= 16011,	// 猎龙副本已开启
		DRAGON_HUNT_ERROR_REQ_COMMANDER		= 16012,	// 只有会长可以开启
		DRAGON_HUNT_ERROR_REQ_OPEN_TIMES	= 16013,	// 无开启次数
		DRAGON_HUNT_ERROR_REQ_DRAGON		= 16014,	// 没有龙，不可开启
		DRAGON_HUNT_ERROR_REQ_STARTED		= 16015,	// 猎龙副本未开启
		DRAGON_HUNT_ERROR_JOIN_FAILED		= 16016,	// 进入猎龙副本失败
	};

	const int cst_hunt_max_dragon_num = 9;
	const sint64 cst_hunt_base_map = 2010;

	// 神佑试炼--副本
	const int64 cst_sy_base_map = 6002;

	struct SHuntContext
	{
		int64 gid;
		int32 dragons[cst_hunt_max_dragon_num];
		bool bDoubleReward;

		SHuntContext()
		{
			memset(this,0,sizeof(*this));
		}
	};

	// 用于通知离线成员的公会操作定义
	enum EGuildOpers
	{
		GUILD_OPER_BUILDING_LEVELUP = 1,
		GUILD_OPER_BUILDING_FUNOPEN = 2,
		GUILD_OPER_GUILD_ADDED = 3,
	};

	const int32 cst_guild_trial_land_max_cnt = 1;

	enum ETrialLandOperCode
	{
		TRIAL_LAND_OPER_SUCCESS = 0,

		TRIAL_LAND_OPER_COMMON_ERR_TID = 61402,			// 通用-试炼ID错误
		TRIAL_LAND_OPER_COMMON_NOT_OPEN,				// 通用-未激活

		TRIAL_LAND_OPER_START_PERM_LIMIT = 61410,		// 开启-权限不足
		TRIAL_LAND_OPER_START_BLOCKING,					// 开启-阻塞中
		TRIAL_LAND_OPER_START_TRIALING,					// 开启-试炼中
		TRIAL_LAND_OPER_START_CNT_LIMIT,				// 开启-次数不足

		TRIAL_LAND_OPER_ENTER_NOT_TRIALING = 61420,		// 进入-未开启试炼
		TRIAL_LAND_OPER_ENTER_BUFF_LIMIT,				// 进入-新人buff限制

		TRIAL_LAND_OPER_BROADCAST_START = 61430,		// 广播-开启
		TRIAL_LAND_OPER_BROADCAST_SUCCESS,				// 广播-成功
		TRIAL_LAND_OPER_BROADCAST_FAIL,					// 广播-失败
		TRIAL_LAND_OPER_BROADCAST_SERVER_FIRST,			// 广播-全服首杀	
		TRIAL_LAND_OPER_BROADCAST_SERVER_FAST,			// 广播-全服最快
		TRIAL_LAND_OPER_BROADCAST_SELF_FAST,			// 广播-本盟最快
		TRIAL_LAND_OPER_BROADCAST_SUCCESS_SERVER,		// 广播-全服击杀广播

		TRIAL_LAND_OPER_GAIN_SCENE_LIMIT = 61440,		// 增益-非试炼场景
		TRIAL_LAND_OPER_GAIN_CNT_LIMIT,					// 增益-次数不足
		TRIAL_LAND_OPER_GAIN_NOT_ENOUGH_GOLD,			// 增益-金币不足
	};

	enum ETrialLandFlag
	{
		TRIAL_LAND_FLAG_SERVER_FIRST = 0x0001,
		TRIAL_LAND_FLAG_SERVER_FAST = 0x0002,
		TRIAL_LAND_FLAG_SELF_FAST = 0x0004,
	};

	enum ETrialLandBroadcastType
	{
		TRIAL_LAND_BROADCAST_TYPE_SERVER = 0,
		TRIAL_LAND_BROADCAST_TYPE_GUILD,
	};

	enum EGuildCreateSpendType
	{
		GUILD_CREATE_YUANBAO,						// 元宝
		GUILD_CREATE_COIN,							// 铜钱
	};

	enum EGuildDonateType
	{
		GUILD_DONATE_TYPE_NONE = 0,
		GUILD_DONATE_TYPE_SILVER,				// 银币捐献
		GUILD_DONATE_TYPE_GOLD,					// 金币捐献
		GUILD_DONATE_TYPE_PRIME,				// 至尊捐献

		GUILD_DONATE_TYPE_NUM,
	};
}

#endif // _pw_guild_const_