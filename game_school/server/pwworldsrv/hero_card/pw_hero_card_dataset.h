#ifndef _pw_hero_card_dataset_
#define _pw_hero_card_dataset_

#include "pwconf_HeroCard.h"
#include "pwconf_HeroCardLevelUp.h"
#include "pw_item_package.h"

namespace pwngs
{
	typedef pwconf::SHeroCard SHeroCardData ;
	typedef pwconf::SHeroCardLevelUp SHeroCardLevelUp;

	class HeroCardDataset
	{
	public:
		int					Load(const std::string& path) ;

	private:
		int					LoadHeroCardLevelUp(const std::string& path);

	public:
		SHeroCardData*		GetHeroCardData(sint32 id) ;
		int					CollectHeroCardIds(std::vector<sint32>& vtHeroCardIds) ;

		int					CollectLevelUpPackItems(sint32 nLevel, CollectionPackItemsT& vtPackItems); // 获取升级英雄卡牌技能等级所需材料
	private:
		typedef std_unordered_map<int,SHeroCardData> CollectionHeroCardDataT;
		typedef std::vector<sint32> CollectionHeroIdsT;

		typedef std_unordered_map<int, SHeroCardLevelUp> CollectionHeroCardLevelUpDataT;
		
	private:
		CollectionHeroCardDataT m_mapHeroCardPublicData;
		CollectionHeroIdsT		m_vecHeroCardIds;

		CollectionHeroCardLevelUpDataT m_mapHeroCardLevelUpData;

	};

	extern HeroCardDataset g_objHeroCardDataset ;
}


#endif