#ifndef _pw_random_pool_dataset_
#define _pw_random_pool_dataset_

#include "pw_def.h"
// #include "pw_unit.h"
#include "pw_ngs_common.h"
#include "pw_item_package.h"
#include "pwconf_RandomPool.h"
#include "pw_pro_def.h"

namespace pwngs
{
	typedef pwconf::SRandomPool SRandomPool;

	enum ERandomType
	{
		RANDOM_TYPE_NONE = 0,

		RANDOM_TYPE_ITEM = 1, // 随机物品
		RANDOM_TYPE_UNDEFINED = 2, // 随机英雄装备（暂时无定义）
		RANDOM_TYPE_HERO = 3, // 随机英雄（完整英雄）
		RANDOM_TYPE_PACKAGE = 4, // 嵌套随机

		RANDOM_TYPE_MAX
	};

	struct SRandomItem
	{
	public: 
		SRandomItem()
			: nType(RANDOM_TYPE_NONE), nTID(0), nCount(0), nWeight(0)
		{}

		SRandomItem(int32 type, int32 id, int32 count, int32 weight)
			: nType(type), nTID(id), nCount(count), nWeight(weight)
		{}

		bool IsDefault()
		{
			return 0 == nTID && 0 == nCount && 0 == nWeight;
		}

		int32 nType;
		int32 nTID;
		int32 nCount;
		int32 nWeight;
	};

	class RandomItemConfig;
	typedef std::vector<SRandomItem> CollectionRandomItemsT;
	typedef std::vector<RandomItemConfig*> CollectionRandomItemConfigsT;

	class RandomItemConfig
	{
	public:
		RandomItemConfig(const SRandomPool& rRawConfig);
	private:
		void InitialWithRawConfig(const SRandomPool& rRawConfig);

	public:
		bool RandomGenerateItems(CollectionRandomItemsT& vtItems);
		inline int32 GetRandomNum() { return m_nRandomNum; }
		inline const CollectionRandomItemsT& GetRandomItems() { return m_vtItems; }

	public:
		CollectionRandomItemsT m_vtItems;
		CollectionRandomItemConfigsT m_vRandomConfigs;
		int32 m_nRandomNum;
		int32 m_nPoolID;
	};

	class RandomPoolDataset
	{
	public:
		int Load(const std::string& sPath);
	public:
		int CollectRandomList(int nRandomID, int nRandomCount, CollectionRandomItemsT& vtRandomItemList);
		int CollectRandomList(int nRandomID, CollectionRandomItemsT& vtRandomItemList);
		bool IsContainHero(const CollectionRandomItemsT& vtRandomItemList);

	public:
		RandomItemConfig* GetRandomItemConfig(int nID);

	private:
		int LoadRandomPoolConfig(const std::string& sFileName);
		void CheckDataset();
	private:
		typedef std_unordered_map<int, RandomItemConfig> CollectionRandomPoolConfigsT;

		CollectionRandomPoolConfigsT m_mapRandomPools;

	};
	extern RandomPoolDataset g_objRandomPoolDataset;
}

#endif //_pw_random_pool_dataset_