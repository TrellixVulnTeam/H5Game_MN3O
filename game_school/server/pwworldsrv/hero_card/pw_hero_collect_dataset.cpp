#include "pw_hero_collect_dataset.h"
#include "pw_logger.h"

namespace pwngs
{
	HeroCollectDataset g_objHeroCollectDataset;

	int HeroCollectDataset::Load(const std::string& sCSVPath)
	{
		LoadHeroCollect(sCSVPath);
		LoadHeroCollectCondition(sCSVPath);
		return 0;
	}

	int HeroCollectDataset::LoadHeroCollect(const std::string& sCSVPath)
	{
		pwconf::HeroGet reader;
		if (!reader.LoadFrom(sCSVPath + "pwconf_HeroGet.csv"))
		{
			pwasserte(false && "HeroCollectDataset::LoadHeroCollect failed");
			return false;
		}

		for (size_t i = 0; i < reader.Count(); ++i)
		{
			pwconf::SHeroGet& rConf = reader.Get(i);
			m_mapHeroCollectData.insert(std::make_pair(rConf.id, rConf));
		}
		return 0;
	}

	int HeroCollectDataset::LoadHeroCollectCondition(const std::string& sCSVPath)
	{
		pwconf::HeroGetSpecial reader;
		if (!reader.LoadFrom(sCSVPath + "pwconf_HeroGetSpecial.csv"))
		{
			pwasserte(false && "HeroCollectDataset::LoadHeroCollectCondition failed");
			return false;
		}

		for (size_t i = 0; i < reader.Count(); ++i)
		{
			pwconf::SHeroGetSpecial& rConf = reader.Get(i);
			m_mapHeroCollectConditionData.insert(std::make_pair(rConf.id, rConf));
		}

		return 0;
	}

	pwconf::SHeroGet* HeroCollectDataset::GetHeroCollect(int nID)
	{
		CollectionHeroCollectDataT::iterator iter = m_mapHeroCollectData.find(nID);
		if (iter != m_mapHeroCollectData.end())
		{
			return &iter->second;
		}
		else
		{
			return NULL;
		}
	}

	bool HeroCollectDataset::CheckHeroCollectOpen(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		const pwconf::SHeroGet* pSHeroGet = GetHeroCollect(nCollectLevel);
		pwassertn(pSHeroGet);
		switch (nCollectType)
		{
		case COLLECT_TYPE_FREE:
			return -1 != pSHeroGet->freeCd;
		case  COLLECT_TYPE_COST:
			return true;
		case COLLECT_TYPE_MULTICOST:
			return -1 != pSHeroGet->tenTimesCost;
		default:
			return false;
		}
		return false;
	}

	sint32 HeroCollectDataset::FindRandomIDByCondition(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, sint32 nCurrCollectCount, sint32 nTotalCollectCount)
	{
		pwassertf(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		pwassertf(COLLECT_TYPE_FREE <= nCollectType && COLLECT_TYPE_MAX > nCollectType);
		for (CollectionHeroCollectConditionDataT::iterator iter = m_mapHeroCollectConditionData.begin(); iter != m_mapHeroCollectConditionData.end(); ++iter)
		{
			const pwconf::SHeroGetSpecial& rSHeroGetSpecial = iter->second;
			// 条件类型 1.第n次抽取	2.第n次元宝抽 3.第n次免费抽
			switch (rSHeroGetSpecial.type)
			{
			case 1:
				{
					  if (rSHeroGetSpecial.npara2 == nCollectLevel && rSHeroGetSpecial.npara1 == nTotalCollectCount)
					  {
						  return rSHeroGetSpecial.randomPool;
					  }
				}
				break;
			case 2:
				{
					  if (COLLECT_TYPE_COST == nCollectType || COLLECT_TYPE_MULTICOST == nCollectType)
					  {
						  if (rSHeroGetSpecial.npara2 == nCollectLevel && rSHeroGetSpecial.npara1 == nCurrCollectCount)
						  {
							  return rSHeroGetSpecial.randomPool;
						  }
					  }
				}
				break;
			case 3:
				{
					  if (COLLECT_TYPE_FREE == nCollectType)
					  {
						  if (rSHeroGetSpecial.npara2 == nCollectLevel && rSHeroGetSpecial.npara1 == nCurrCollectCount)
						  {
							  return rSHeroGetSpecial.randomPool;
						  }
					  }
				}
				break;
			}
		}
		return 0;
	}
}