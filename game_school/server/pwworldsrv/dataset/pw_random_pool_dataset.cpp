#include "pw_random_pool_dataset.h"
#include "pw_logger.h"
#include "pw_utils.h"
//#include "pw_stage.h"
//#include "pw_item_character.h"
//#include "pw_item_dataset.h"
//#include "pw_module_statistic.h"
//#include "pw_creature.h"
//#include "pw_stage_scheme.h"
//#include "pw_thread_hotfix.h"
#include "pw_hero_card_dataset.h"

//#include "kvorm/pw_orm_collection_human.h"
//#include "kvorm/pw_orm_humanmisc.h"

namespace pwngs
{
	// 随机项目配置最大数量
	const sint32 cst_random_pool_item_num = 20;

	RandomPoolDataset g_objRandomPoolDataset;

	RandomItemConfig::RandomItemConfig(const SRandomPool& rRawConfig)
	{
		InitialWithRawConfig(rRawConfig);
	}

	void RandomItemConfig::InitialWithRawConfig(const SRandomPool& rRawConfig)
	{
		typedef int (ItemArray)[4];

		// 下面的代码依赖于结构体在内存中的存储结构
		ItemArray* pItem = (ItemArray*)(&rRawConfig.item1);
		for (int ii = 0; ii < cst_random_pool_item_num; ++ii)
		{
			if (0 < pItem[ii][0] && 0 < pItem[ii][1] && 0 < pItem[ii][2] && 0 < pItem[ii][3])
			{
				SRandomItem raw = { pItem[ii][0], pItem[ii][1], pItem[ii][2], pItem[ii][3] };
				m_vtItems.push_back(raw);
			}
		}

		m_nRandomNum = rRawConfig.randNum;
		m_nPoolID = rRawConfig.id;
	}

	bool RandomItemConfig::RandomGenerateItems(CollectionRandomItemsT& vtItems)
	{
		// 初始化配置,不用每次都取
		if (m_vRandomConfigs.size() != m_vtItems.size())
		{
			m_vRandomConfigs.clear();
			m_vRandomConfigs.resize(m_vtItems.size(), (RandomItemConfig*)NULL);

			for(size_t ii = 0; ii < m_vtItems.size(); ++ii)
			{
				SRandomItem& rConfig = m_vtItems[ii];

				if (RANDOM_TYPE_PACKAGE == rConfig.nType)
				{
					m_vRandomConfigs[ii] = g_objRandomPoolDataset.GetRandomItemConfig(rConfig.nTID);
					if (NULL == m_vRandomConfigs[ii])
					{
						gErrorStream("RandomItemConfig::RandomGenerateItems poolid=" << rConfig.nTID << " is not exist");
					}
				}
			}
		}

		sint32 nRandomContainerWeightSum = 0;
		for(size_t jj = 0; jj < m_vtItems.size(); ++jj)
		{
			SRandomItem& rConfig = m_vtItems[jj];
			nRandomContainerWeightSum += rConfig.nWeight;
		}

		bool dropped = false;

		for(int mm = 0; mm < GetRandomNum(); ++mm)
		{
			int32 rnd = pwutils::random(0, nRandomContainerWeightSum);
			int32 thresold = 0;
			bool loopDropped = false;

			for(size_t nn = 0; nn < m_vtItems.size(); ++nn)
			{
				SRandomItem& rConfig = m_vtItems[nn];
				thresold += rConfig.nWeight;

				if(rnd < __max(1,thresold))
				{
					switch(rConfig.nType)
					{
					case RANDOM_TYPE_ITEM:
					case RANDOM_TYPE_HERO:
						{
							// 小等于0表示什么都不掉
							if(0 < rConfig.nTID && 0 < rConfig.nCount)
							{
								SRandomItem item = { rConfig.nType, rConfig.nTID, rConfig.nCount, rConfig.nWeight };
								vtItems.push_back(item);
							}
							// 但还要是阻击下面的掉落
							loopDropped = true;
						}
						break;
					case RANDOM_TYPE_PACKAGE:
						{
							RandomItemConfig* pRandomItemConfig = m_vRandomConfigs[nn];
							pwreportvars(pRandomItemConfig, rConfig.nTID);
							pwassertop(pRandomItemConfig, continue);

							loopDropped = pRandomItemConfig->RandomGenerateItems(vtItems);
						}
						break;
					default:
						pwreportvars("Unknown random type:",rConfig.nType);
						pwassertr(false,dropped);
					}

					if(loopDropped)
						break;

				}
			}
			dropped |= loopDropped;
		}
		return dropped;
	}

	//------------------------------------------------------------------

	int RandomPoolDataset::Load(const std::string& sPath)
	{
		// 载入随机池配置表
		LoadRandomPoolConfig(sPath + "pwconf_RandomPool.csv");

		// 校验id是否存在
		CheckDataset();
		return 0;
	}

	int RandomPoolDataset::CollectRandomList(int nRandomID, int nRandomCount, CollectionRandomItemsT& vtRandomItemList)
	{
		if (0 >= nRandomID)
		{
			return -1;
		}
		pwassertf(0 < nRandomCount);
		for (int32 ii = 0; ii < nRandomCount; ++ii)
		{
			CollectRandomList(nRandomID, vtRandomItemList);
		}
	}

	int RandomPoolDataset::CollectRandomList(int nRandomID, CollectionRandomItemsT& vtRandomItemList)
	{
		pwassertf(0 < nRandomID);
		if (0 < nRandomID)
		{
			RandomItemConfig* pRandomItemConfig = GetRandomItemConfig(nRandomID);
			pwreportvars(pRandomItemConfig, nRandomID);
			pwassertn(pRandomItemConfig);

			pRandomItemConfig->RandomGenerateItems(vtRandomItemList);
			return 0;
		}

		return -1;
	}

	bool RandomPoolDataset::IsContainHero(const CollectionRandomItemsT& vtRandomItemList)
	{
		for (CollectionRandomItemsT::const_iterator iter = vtRandomItemList.begin(); iter != vtRandomItemList.end(); ++iter)
		{
			if (RANDOM_TYPE_HERO == iter->nType)
			{
				return true;
			}
		}
		return false;
	}

	int RandomPoolDataset::LoadRandomPoolConfig(const std::string& sFileName)
	{
		pwconf::RandomPool randomPoolData;

		if (!randomPoolData.LoadFrom(sFileName))
		{
			gErrorStream("Error LoadRandomPools " << sFileName);
			pwassertn(false && "Error,LoadRandomPools");
			return -1;
		}

		for (size_t ii = 0; ii < randomPoolData.Count(); ++ii)
		{
			pwconf::SRandomPool& rConfig = randomPoolData.Get(ii);
			m_mapRandomPools.insert(std::make_pair(rConfig.id, RandomItemConfig(rConfig)));
		}

		return 0;
	}
	
	void RandomPoolDataset::CheckDataset()
	{
		for (CollectionRandomPoolConfigsT::iterator iter = m_mapRandomPools.begin(); iter != m_mapRandomPools.end(); ++iter)
		{
			RandomItemConfig& rConfig = iter->second;

			for(size_t ii = 0; ii < rConfig.m_vtItems.size(); ++ii)
			{
				SRandomItem& rItem = rConfig.m_vtItems[ii];

				if(RANDOM_TYPE_ITEM == rItem.nType)
				{
					if(0 != rItem.nTID)
					{/*
						SItemType* pItemType = g_objItemDataset.Get(rItem.nTID);
						if (NULL == pItemType)
						{
						gErrorStream("RandomPoolDataset::CheckDataset item not exist, configid:" << iter->first << ", index:" << ii + 1 << ", itemid:" << rItem.nTID);
						}

						pwassertop(pItemType,continue);*/
					}
				}
				else if (RANDOM_TYPE_HERO == rItem.nType)
				{
					if (0 != rItem.nTID)
					{
						/*SHeroCardData* pSHeroCardData = g_objHeroCardDataset.GetHeroCardData(rItem.nTID);
						if (NULL == pSHeroCardData)
						{
							gErrorStream("RandomPoolDataset::CheckDataset hero card not exist, configid:" << iter->first << ", index:" << ii + 1 << ", herocardid:" << rItem.nTID);
						}

						pwassertop(pSHeroCardData, continue);*/
					}
				}
				else if(RANDOM_TYPE_PACKAGE == rItem.nType)
				{
					const RandomItemConfig* pConfig = g_objRandomPoolDataset.GetRandomItemConfig(rItem.nTID);
					if (NULL == pConfig)
					{
						gErrorStream("RandomPoolDataset::CheckDataset special id not exist, configid:" << iter->first << ", index" << ii + 1 << ", specialid:" << rItem.nTID);
					}
					pwassertop(pConfig, continue);
				}
			}
		}
	}

	RandomItemConfig* RandomPoolDataset::GetRandomItemConfig(int nID)
	{
		CollectionRandomPoolConfigsT::iterator iter = m_mapRandomPools.find(nID);
		if (m_mapRandomPools.end() != iter)
		{
			return &iter->second;
		}
		else
		{
			return NULL;
		}
	}

}
