#ifndef _pw_hero_collect_def_
#define _pw_hero_collect_def_

namespace pwngs
{
	const int32 CST_HERO_DEBRIS_DEFAULT = 20; // 碎片默认数量
	const int32 CST_HERO_COLLECT_TEN = 10; // 十连抽次数
	const int32 CST_HERO_COLLECT_HIGH_PERCENT = 20; // 高级抽取开启概率（百分比）

	// 抽取级别
	enum EHeroCollectLevel
	{
		COLLECT_LEVEL_LOW = 0,		// 初级抽取
		COLLECT_LEVEL_MIDDLE,		// 中级抽取
		COLLECT_LEVEL_HIGH,		// 高级抽取

		COLLECT_LEVEL_MAX,
	};

	// 抽取方式
	enum EHeroCollectType
	{
		COLLECT_TYPE_FREE = 0,		// 免费抽取
		COLLECT_TYPE_COST,		// 付费抽取
		COLLECT_TYPE_MULTICOST,		// 连抽

		COLLECT_TYPE_MAX,
	};

	enum EHeroCollectOperCode
	{
		HERO_COLLECT_SUCCESS = 0,

		HERO_COLLECT_FAILED_COST = 5101,		// 抽取-资源不足
		HERO_COLLECT_FAILED_LEVEL = 5102,		// 抽取-高级抽取未开启
		HERO_COLLECT_FAILED_BAG_NOT_ENOUGH = 5103,		// 抽取-背包剩余格数不足
	};
}

#endif // _pw_hero_collect_def_