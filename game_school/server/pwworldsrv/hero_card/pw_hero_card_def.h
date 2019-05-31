#ifndef _pw_hero_card_def_
#define _pw_hero_card_def_

namespace pwngs
{
	const int32 cst_hero_card_equip_max = 3;
	const int32 cst_hero_card_guard_max = 3;
	const int32 cst_hero_card_star_max = 5 ;

	const int32 cst_hero_card_equip_loc_open_succ_notify = 140001;
	const int32 cst_hero_card_equip_loc_already_open_notify = 140002;

	struct SHeroCardStats
	{
		int32 id;
		int32 value;

		SHeroCardStats()
		{
			memset(this,0,sizeof(*this));
		}
	};

	enum EHeroCardState
	{
		HERO_CARD_STATE_NONE = 0,

		HERO_CARD_STATE_IDLE,		// 空闲态
		HERO_CARD_STATE_GUARD,		// 守护态
		HERO_CARD_STATE_EQUIP,		// 装备态

		HERO_CARD_STATE_MAX,
	};

	enum EHeroCardOperFlag
	{
		HERO_CARD_OPER_CHANGE_STATE = 0x01,
	};

	enum EHeroCardOperCode
	{
		HERO_CARD_SUCCESS = 0,

		HERO_CARD_LEVELUP_FAILED_ITEM_NOT_ENOUGH = 5201,				// 升级-材料不足
		HERO_CARD_LEVELUP_FAILED_MAX_LEVEL = 5202,							// 升级-技能当前最高级
	};
}

#endif