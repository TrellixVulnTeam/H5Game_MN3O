#ifndef _pw_module_hero_collect_
#define _pw_module_hero_collect_

#include "pw_types.h"
#include "pw_random_pool_dataset.h"
#include "pw_hero_collect_dataset.h"
#include "pw_hero_collect_def.h"
#include "pw_module.h"
#include "pw_memory.h"
#include "kvorm/pw_orm_humanherocollect.h"

namespace pwngs
{
	class Human;

	class ModHeroCollect : public Module<Human>, public pwutils::memory::ObjectInThread<ModHeroCollect>
	{
	public:
		ModHeroCollect(Module<Human>::TOwnerPtr ptr);
		~ModHeroCollect();

	public:
		sint32 OrmLoad();
		sint32 OrmSave();

	public:
		const orm::HumanHeroCollect* GetOrmHeroCollect() { return m_pOrmHeroCollect; }
		sint32 Query(); // 查询英雄抽取信息
		sint32 DoCollect(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 进行抽取

	private:
		sint32 CheckCollect(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 抽取条件判断，并扣除花费
		sint32 GetRandomItem(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, SRandomItem& rRandomItem); // 生成随机包，并执行能量值的消耗和积累
		sint32 ObtainItem(const CollectionPackItemsT& vtPackItems); // 获取随机包结果

	public:
		// 抽取级别
		bool CheckCollectLevelHigh(); // 是否开启高级抽取（处理每天20%概率开启的逻辑）
		// 抽取方式
		EHeroCollectType GetCollectType(EHeroCollectLevel nCollectLevel); // 根据CD，获取当前使用的抽取方式（仅仅限于免费抽取和付费抽取，不包含十连抽）
		sint32 GenerateCurrCollectCount(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 生成本次抽取的计数信息（比如：第几次中级免费抽取）

		// 抽取条件
	private:
		sint32 GetCost(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, SItemPackage& rPackage); // 获取资源消耗
		bool CheckPriorEnergy(EHeroCollectLevel nCollectLevel); // 检测优先能量值
		bool CheckFullEnergy(EHeroCollectLevel nCollectLevel); // 检测满能量值
		sint32 ObtainEnergy(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 获取抽取能量
		sint32 CostPriorEnergy(EHeroCollectLevel nCollectLevel); // 消耗优先能量值
		sint32 CostFullEnergy(EHeroCollectLevel nCollectLevel); // 消耗满能量值
		sint32 CalcEnergy(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 计算抽取积累能量值
		sint32 AlterEnergy(EHeroCollectLevel nCollectLevel, sint32 nModifyEnergy); // 增减能量值
		sint32 AddRecord(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 添加抽取记录
		sint32 GetFreeCollectCount(EHeroCollectLevel nCollectLevel) const; // 获取免费抽取次数
		sint32 GetCostCollectCount(EHeroCollectLevel nCollectLevel) const; // 获取付费抽取次数（将连续抽取分解成独立的付费抽取）
		sint32 GetTotalCollectCount(EHeroCollectLevel nCollectLevel) const; // 获取总抽取次数

		// 抽取结果
	private:
		// 优先英雄池其实和随机池无必然联系，随机池只是提供一个英雄列表用于挑选
		sint32 CollectPriorHero(sint32 nRandomID, CollectionRandomItemsT& vtRandomItemList); // 生成优先英雄池
		sint32 GetPriorHeroID(sint32 nRandomID); // 从优先英雄池随机出英雄

	private:
		sint32 GetWholeHeroCollectNum(sint32 nHeroID) const; // 计算完整英雄所需碎片数量
		sint32 ConvertRandomItemToPackItem(const SRandomItem& rRandomItem, SPackItem& rPackItem); // 随机道具转换为物品道具
		sint32 GetReplaceHeroID(sint32 nRandomID) const; // 获取替换英雄id，用于十连抽
		sint32 GenerateRandomItem(sint32 nRandomID, SRandomItem& rRandomItem); // 生成英雄抽取的随机包
		sint32 ReplaceRandomItemWithHero(CollectionRandomItemsT& vtRandomItemList, sint32 nFullRandomID); // 将随机包的最后一个替换为完整英雄（若替换随机池中无英雄则不替换）

	private:
		sint32 InitialLastFreeTime(); // 初始化上次免费抽取时间，处理创建新角色的默认CD
		sint32 InitialEnergy(); // 初始化能量值，处理创建新角色的默认能量值

	private:
		orm::HumanHeroCollect* m_pOrmHeroCollect;

	};
}

#endif // _pw_module_hero_collect_
