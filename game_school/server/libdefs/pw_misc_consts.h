#ifndef _pw_misc_consts_
#define _pw_misc_consts_

#include "pw_def.h"

namespace pwngs
{
	// 杂货线程管理的具体的管理器
	enum EMiscType
	{
		MISC_TYPE_SHOP_MGR		= 1,			// 商店管理器
		MISC_TYPE_BROADCAST_MGR = 2,			// 运营广播管理器
		MISC_TYPE_AWARD_SERVER_MGR = 3,			// 全服发奖管理器
		MISC_TYPE_WARLORD_MGR = 4,				// 武神排名管理器
		MISC_TYPE_MALL_MGR = 5,					// 商城管理器
		MISC_TYPE_GAMESELLER_MGR = 6,			// 托管理器
		MISC_TYPE_OPEN_AUCTION_MGR = 7,			// 开服拍卖管理器
		MISC_TYPE_LOTTERY_MGR = 8,				// 抽奖管理器
		MISC_TYPE_CHEST_MGR = 9,				// 宝箱管理器
		MISC_TYPE_LOTTERY_PRIZE_MGR = 10,		// 命运轮管理器
	};

	// 全局线程管理的具体的管理器
	enum EGlobalType
	{
		GLOBAL_TYPE_PASSPORTLOCK_MGR = 1,		// 帐号锁定管理器
		GLOBAL_TYPE_GLOBALRANK_MGR = 2,			// 全局排行管理器
	};

	enum
	{
		STAGE_MISC_OBJECT = 1,					// 在SImplStageMgr上的misc对象
	};

	// 商店相关错误码
	enum EShopOperCode
	{
		SHOP_FAILED_SUCCESS		= 0,
		SHOP_FAILED_UNKNOWN_ITEM = 10506,		// 商店不存在该物品
		SHOP_FAILED_REQ_ITEM,					// 道具不够
		SHOP_FAILED_BAG_FULL,					// 背包空间不够
		SHOP_FAILED_EXCEED_GLOBAL_COUNT,		// 超出本服限购数量
		SHOP_FAILED_UNKNOWN_SHOP,				// 未知商店
		SHOP_FAILED_NOT_FOR_SALE,				// 该物品不可出售
		SHOP_FAILED_HONOR_NOT_ENOUGH,			// 荣誉不够
		SHOP_FAILED_INVALID_ARGS,				// 参数错误
		SHOP_FAILED_ITEM_NOT_ENOUGH,			// 道具不够
		SHOP_FAILED_SELL_ITEM_NOT_EXIST,		// 商店不存在该物品
		SHOP_FAILED_CONDITION_TRIAL_LAND_LIMIT,	// 条件之试炼之地未通关
	};

	// 商城可购数量最大值(用来表示不限购的情况)
	const int32 cst_shop_count_infinite = -1;

	// 商城相关错误码
	enum EMallOperCode
	{
		MALL_FAILED_SUCCESS		= 0,
		MALL_FAILED_NOT_ON_SALE			= 70007, // 商品已下架
		MALL_FAILED_EXCEED_PERSON_COUNT	= 70008, // 超出个人限购数量
		MALL_FAILED_EXCEED_GLOBAL_COUNT	= 70009, // 超出本服限购数量
		MALL_FAILED_REQ_GOLD			= 70010, // 金币不足
		MALL_FAILED_REQ_BAG				= 70011, // 背包空间不足
		MALL_FAILED_REQ_CHARGE_GOLD		= 102012,// 充值金币不足
		MALL_FAILED_EXCEED_RIDE_COUNT	= 104020,// 超出坐骑数量
		MALL_FAILED_EXCEED_VIP_LEVEL	= 106200,// 超出尊爵等级
	};

	// 商城标签页数量
	const int32 cst_mall_label_count = 8;

	// 商城可购数量最大值(用来表示不限购的情况)
	const int32 cst_mall_count_infinite = -1;

	const int cst_sec_of_a_day = 24 * 3600;

	// 公会战相关错误码
	enum ENJTZOperCode
	{
		NJTZ_ERROR_SUCCESSFUL	= 0,
		NJTZ_ERROR_SUPPORT_TEAM_NOT_EXIST, // 助威队伍不存在
		NJTZ_ERROR_SUPPORT_ALREADY_SUPPORTED, // 已经助威过该队伍
		NJTZ_ERROR_SUPPORT_TEAM_LOST, // 助威队伍已淘汰
		NJTZ_ERROR_SUPPORT_TEAM_REQ_NOT_SYSTEM, // 助威队伍是系统队伍
		NJTZ_ERROR_SUPPORT_TEAM_IS_BYE, // 助威队伍被轮空(无对手)

		NJTZ_ERROR_SUPPORT_REQ_NOT_START		= 51200, // 开始后不能助威
	};

	// 小飞鞋物品ID
	const int cst_easy_go_item_id = 6100000;
}

#endif // _pw_misc_consts_