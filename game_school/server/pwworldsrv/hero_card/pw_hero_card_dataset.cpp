#include "pw_hero_card_dataset.h"
#include "pw_logger.h"
#include "pw_hero_card_def.h"

namespace pwngs
{
	HeroCardDataset g_objHeroCardDataset;

	int HeroCardDataset::Load(const std::string& path)
	{
		pwconf::HeroCard heroCardData;

		if (!heroCardData.LoadFrom(path + "pwconf_HeroCard.csv"))
		{
			gErrorStream("Error LoadHeroCardData " << path + "pwconf_HeroCard.csv");
			pwassertn(false && "Error,LoadHeroCardData");
			return -1;
		}

		for (size_t i = 0; i < heroCardData.Count(); ++i)
		{
			SHeroCardData& type = heroCardData.Get(i);
			pwassertop(m_mapHeroCardPublicData.insert(std::make_pair(type.id, type)).second, continue);
			m_vecHeroCardIds.push_back(type.id);
		}

		LoadHeroCardLevelUp(path);

		return 0;
	}

	SHeroCardData* HeroCardDataset::GetHeroCardData(sint32 id)
	{
		CollectionHeroCardDataT::iterator iter = m_mapHeroCardPublicData.find(id);
		if (iter != m_mapHeroCardPublicData.end())
			return &iter->second;
		return NULL;
	}

	int HeroCardDataset::CollectHeroCardIds(std::vector<sint32>& vtHeroCardIds)
	{
		vtHeroCardIds = m_vecHeroCardIds;
		return 0;
	}

	int HeroCardDataset::LoadHeroCardLevelUp(const std::string& path)
	{
		pwconf::HeroCardLevelUp heroCardLevelUp;

		if (!heroCardLevelUp.LoadFrom(path + "pwconf_HeroCardLevelUp.csv"))
		{
			gErrorStream("Error LoadHeroCardLevelUpData " << path + "pwconf_HeroCardLevelUp.csv");
			pwassertn(false && "Error,LoadHeroCardLevelUpData");
			return -1;
		}

		for (size_t i = 0; i < heroCardLevelUp.Count(); ++i)
		{
			SHeroCardLevelUp& type = heroCardLevelUp.Get(i);
			pwassertop(m_mapHeroCardLevelUpData.insert(std::make_pair(type.id, type)).second, continue);
		}

		return 0;
	}

	int HeroCardDataset::CollectLevelUpPackItems(sint32 nLevel, CollectionPackItemsT& vtPackItems)
	{
		for (CollectionHeroCardLevelUpDataT::iterator iter = m_mapHeroCardLevelUpData.begin(); iter != m_mapHeroCardLevelUpData.end(); ++iter)
		{
			const SHeroCardLevelUp& rLevelUpConfig = iter->second;
			if (rLevelUpConfig.skill_level[0] <= nLevel && rLevelUpConfig.skill_level[1] >= nLevel)
			{
				if (0 < rLevelUpConfig.lvlup_item_1[0] && 0 < rLevelUpConfig.lvlup_item_1[1])
				{
					SPackItem item1 = { rLevelUpConfig.lvlup_item_1[0], rLevelUpConfig.lvlup_item_1[1] };
					vtPackItems.push_back(item1);
				}
				if (0 < rLevelUpConfig.lvlup_item_2[0] && 0 < rLevelUpConfig.lvlup_item_2[1])
				{
					SPackItem item2 = { rLevelUpConfig.lvlup_item_2[0], rLevelUpConfig.lvlup_item_2[1] };
					vtPackItems.push_back(item2);
				}
				if (0 < rLevelUpConfig.lvlup_item_3[0] && 0 < rLevelUpConfig.lvlup_item_3[1])
				{
					SPackItem item3 = { rLevelUpConfig.lvlup_item_3[0], rLevelUpConfig.lvlup_item_3[1] };
					vtPackItems.push_back(item3);
				}
				return 0;
			}
		}
		return -1;
	}
}