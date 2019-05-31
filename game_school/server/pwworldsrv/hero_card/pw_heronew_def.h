#ifndef _pw_heronew_def_
#define _pw_heronew_def_

namespace pwngs
{
	const int32 cst_heronew_star_max = 5;
	const int32 cst_heronew_card_max = 3;

	enum EHeroNewState
	{
		HERONEW_STATE_NONE = 0,

		HERONEW_STATE_IDLE,		// 空闲态
		HERONEW_STATE_ASSISTANCE,		// 助战态

		HERONEW_STATE_MAX,
	};

	enum EHeroNewRankSolt
	{
		HERONEW_RANK_SOLT_NONE = 0,

		HERONEW_RANK_SOLT_1,
		HERONEW_RANK_SOLT_2,
		HERONEW_RANK_SOLT_3,
		HERONEW_RANK_SOLT_4,
		HERONEW_RANK_SOLT_5,
		HERONEW_RANK_SOLT_6,

		HERONEW_RANK_SOLT_MAX
	};

	enum EHeroNewOperCode
	{
		HERONEW_SUCCESS = 0,

		HERONEW_EMBED_FAILED_SOLT = -1,											// 镶嵌-镶嵌位错误
		HERONEW_EMBED_FAILED_ITEM_NOT_ENOUGH = -1,					// 镶嵌-材料不足

		HERONEW_RANKUP_FAILED_NOT_FULL = -1,								// 升阶-未镶嵌满不可升阶

		HERONEW_SYNTHESIS_FAILED_BAG_FULL = -1,							// 合成-背包已满
		HERONEW_SYNTHESIS_FAILED_ITEM_NOT_ENOUGH = -1,			// 合成-材料不足
	};
}

#endif