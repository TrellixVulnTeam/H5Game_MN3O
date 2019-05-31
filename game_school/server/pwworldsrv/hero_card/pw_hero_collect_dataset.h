#ifndef _pw_hero_collect_dataset_
#define _pw_hero_collect_dataset_

#include "pwconf_HeroGet.h"
#include "pwconf_HeroGetSpecial.h"
#include "pw_hero_collect_def.h"

namespace pwngs
{
	typedef pwconf::SHeroGet SHeroGet;
	typedef std_unordered_map<int, SHeroGet> CollectionHeroCollectDataT;

	typedef pwconf::SHeroGetSpecial SHeroGetSpecial;
	typedef std_unordered_map<int, SHeroGetSpecial> CollectionHeroCollectConditionDataT;

	class HeroCollectDataset
	{
	public:
		int Load(const std::string& sCSVPath);

	public:
		SHeroGet* GetHeroCollect(int nID);
		bool CheckHeroCollectOpen(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType); // 配置表格中抽取级别是否开启抽取方式
		sint32 FindRandomIDByCondition(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, sint32 nCurrCollectCount, sint32 nTotalCollectCount); // 遍历查询是否存在特殊抽取条件

	private:
		int LoadHeroCollect(const std::string& sCSVPath);
		int LoadHeroCollectCondition(const std::string& sCSVPath);
		
	private:
		CollectionHeroCollectDataT m_mapHeroCollectData;
		CollectionHeroCollectConditionDataT m_mapHeroCollectConditionData;
	};

	extern HeroCollectDataset g_objHeroCollectDataset;
}


#endif // _pw_hero_collect_dataset_