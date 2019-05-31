#include "pw_heronew_dataset.h"
#include "pw_logger.h"
#include "pw_heronew_def.h"

namespace pwngs
{
	HeroNewDataset g_objHeroNewDataset;

	int HeroNewDataset::Load(const std::string& path)
	{
		pwconf::Hero heroNewData;

		if (!heroNewData.LoadFrom(path + "pwconf_Hero.csv"))
		{
			gErrorStream("Error LoadHeroNewData " << path + "pwconf_Hero.csv");
			pwassertn(false && "Error,LoadHeroNewData");
			return -1;
		}

		for (size_t i = 0; i < heroNewData.Count(); ++i)
		{
			SHeroNewData& type = heroNewData.Get(i);
			pwassertop(m_mapHeroPublicData.insert(std::make_pair(type.id, type)).second, continue);
			m_vecHeroIds.push_back(type.id);

			CollectionHeroNewAttrT vtAttr;
			vtAttr.push_back(type.attr_star1);
			vtAttr.push_back(type.attr_star2);
			vtAttr.push_back(type.attr_star3);
			vtAttr.push_back(type.attr_star4);
			vtAttr.push_back(type.attr_star5);
			for (size_t j = 0; j < vtAttr.size(); ++j)
			{
				pwassertn(vtAttr[j].size() % 2 == 0 && "Error,LoadHeroNewStarup stat num is odd");
			}
			m_mapHeroNewAttrSet.insert(std::make_pair(type.id, vtAttr));
		}

		LoadHeroNewRank(path);

		return 0;
	}

	SHeroNewData* HeroNewDataset::GetHeroNewData(sint32 id)
	{
		CollectionHeroNewDataT::iterator iter = m_mapHeroPublicData.find(id);
		if (iter != m_mapHeroPublicData.end())
			return &iter->second;
		return NULL;
	}

	SHeroNewData* HeroNewDataset::GetHeroNewbyDebrisId(sint32 nDebrisId)
	{
		for (CollectionHeroNewDataT::iterator iter = m_mapHeroPublicData.begin(); iter != m_mapHeroPublicData.end(); ++iter)
		{
			if (iter->second.hero_pieces == nDebrisId)
			{
				return &iter->second;
			}
		}
		return NULL;
	}

	int HeroNewDataset::GetActivatedHeroNewDebrisNum(sint32 id)
	{
		SHeroNewData* pData = GetHeroNewData(id);
		if (NULL == pData)
		{
			return -1;
		}
		else
		{
			return pData->pieces_req[0];
		}
	}

	int HeroNewDataset::CollectHeroIds(std::vector<sint32>& vtHeroIds)
	{
		vtHeroIds = m_vecHeroIds;
		return 0;
	}

	int HeroNewDataset::CollectHeroAttr(std::vector<sint32>& vtAttr, int32 nId, int32 nStar)
	{
		CollectionHeroNewAttrSetT::iterator iter = m_mapHeroNewAttrSet.find(nId);
		pwassertf(iter != m_mapHeroNewAttrSet.end());

		CollectionHeroNewAttrT& vtHeroNewAttr = iter->second;
		nStar = nStar - 1;
		pwassertf(nStar >= 0 && nStar < vtHeroNewAttr.size());

		vtAttr = vtHeroNewAttr[nStar];
		return 0;
	}

	int HeroNewDataset::LoadHeroNewRank(const std::string& path)
	{
		pwconf::HeroAssistance heroNewRank;

		if (!heroNewRank.LoadFrom(path + "pwconf_HeroAssistance.csv"))
		{
			gErrorStream("Error LoadHeroNewRank " << path + "pwconf_HeroAssistance.csv");
			pwassertn(false && "Error,LoadHeroNewRank");
			return -1;
		}

		for (size_t ii = 0; ii < heroNewRank.Count(); ++ii)
		{
			SHeroNewRank& rData = heroNewRank.Get(ii);
			pwassertn(0 == rData.item_attr.size() % 2 && "Error,LoadHeroNewRank item_attr num is odd");

			CollectionHeroNewRankTableIDT::iterator iterHeroNew = m_mapHeroNewRankTableIDs.find(rData.hero_id);
			if (m_mapHeroNewRankTableIDs.end() == iterHeroNew)
			{
				CollectionRankTableIDT collectionRankTableID;
				m_mapHeroNewRankTableIDs.insert(std::make_pair(rData.hero_id, collectionRankTableID));
			}
			iterHeroNew = m_mapHeroNewRankTableIDs.find(rData.hero_id);
			CollectionRankTableIDT& rCollectionRankTableID = iterHeroNew->second;

			CollectionRankTableIDT::iterator iterRank = rCollectionRankTableID.find(rData.item_rank);
			if (rCollectionRankTableID.end() == iterRank)
			{
				CollectionSoltTableIDT collectionSoltTableID;
				rCollectionRankTableID.insert(std::make_pair(rData.item_rank, collectionSoltTableID));
			}
			iterRank = rCollectionRankTableID.find(rData.item_rank);
			CollectionSoltTableIDT& rCollectionSoltTableID = iterRank->second;

			CollectionSoltTableIDT::iterator iterSolt = rCollectionSoltTableID.find(rData.item_slot);
			pwassertn(rCollectionSoltTableID.end() == iterSolt && "Error,LoadHeroNewRank item_attr exist!");
			rCollectionSoltTableID.insert(std::make_pair(rData.item_slot, rData.id));

			pwassertop(m_mapHeroNewRankDatas.insert(std::make_pair(rData.id, rData)).second, continue);
		}
		return 0;
	}

	SHeroNewRank* HeroNewDataset::GetSHeroNewRankData(sint32 nID)
	{
		CollectionHeroNewRankDataT::iterator iter = m_mapHeroNewRankDatas.find(nID);
		if (m_mapHeroNewRankDatas.end() != iter)
			return &iter->second;
		return NULL;
	}

	int HeroNewDataset::CollectHeroCurrRankAttr(std::vector<sint32>& vtAttr, int32 nHeroNewDID, int16 nCurrRank, int16 nItemSoltFlag)
	{
		CollectionHeroNewRankTableIDT::iterator iterHeroNew = m_mapHeroNewRankTableIDs.find(nHeroNewDID);
		if (m_mapHeroNewRankTableIDs.end() == iterHeroNew)
		{
			gErrorStream("HeroNewDataset::CollectHeroCurrRankAttr HeroNewDID=" << nHeroNewDID + "is not exist");
			return -1;
		}
		CollectionRankTableIDT& rCollectionRankTableID = iterHeroNew->second;

		CollectionRankTableIDT::iterator iterRank = rCollectionRankTableID.find(nCurrRank);
		if (rCollectionRankTableID.end() == iterRank)
		{
			gErrorStream("HeroNewDataset::CollectHeroCurrRankAttr HeroNewRank=" << nCurrRank + "is not exist");
			return -1;
		}
		CollectionSoltTableIDT& rCollectionSoltTableID = iterRank->second;

		for (int32 ii = HERONEW_RANK_SOLT_1; ii < HERONEW_RANK_SOLT_MAX; ++ii)
		{
			if (nItemSoltFlag & (1 << (ii - 1)))
			{
				pwassertf(0 < rCollectionSoltTableID[ii]);
				SHeroNewRank* pData = GetSHeroNewRankData(rCollectionSoltTableID[ii]);
				pwassertf(NULL != pData);
				vtAttr.insert(vtAttr.end(), pData->item_attr.begin(), pData->item_attr.end());
			}
		}
		return 0;
	}

	int HeroNewDataset::CollectHeroTotalRankAttr(std::vector<sint32>& vtAttr, int32 nHeroNewDID, int16 nTotalRank, int16 nItemSoltFlag)
	{
		CollectionHeroNewRankTableIDT::iterator iterHeroNew = m_mapHeroNewRankTableIDs.find(nHeroNewDID);
		if (m_mapHeroNewRankTableIDs.end() == iterHeroNew)
		{
			gErrorStream("HeroNewDataset::CollectHeroTotalRankAttr HeroNewDID=" << nHeroNewDID + "is not exist");
			return -1;
		}
		CollectionRankTableIDT& rCollectionRankTableID = iterHeroNew->second;

		for (CollectionRankTableIDT::iterator iterRank = rCollectionRankTableID.begin(); iterRank != rCollectionRankTableID.end(); ++iterRank)
		{
			if (iterRank->first > nTotalRank)
			{
				continue;
			}
			else if (iterRank->first == nTotalRank)
			{
				CollectHeroCurrRankAttr(vtAttr, nHeroNewDID, nTotalRank, nItemSoltFlag);
			}
			else
			{
				CollectionSoltTableIDT& rCollectionSoltTableID = iterRank->second;
				for (CollectionSoltTableIDT::iterator iterSolt = rCollectionSoltTableID.begin(); iterSolt != rCollectionSoltTableID.end(); ++iterSolt)
				{
					pwassertf(0 < iterSolt->second);
					SHeroNewRank* pData = GetSHeroNewRankData(iterSolt->second);
					pwassertf(NULL != pData);
					vtAttr.insert(vtAttr.end(), pData->item_attr.begin(), pData->item_attr.end());
				}
			}
		}
		return 0;
	}

	int HeroNewDataset::CollectRankUpPackItems(int32 nHeroNewDID, int16 nCurrRank, int16 nAddItemSoltFlag, CollectionPackItemsT& vtPackItems)
	{
		CollectionHeroNewRankTableIDT::iterator iterHeroNew = m_mapHeroNewRankTableIDs.find(nHeroNewDID);
		if (m_mapHeroNewRankTableIDs.end() == iterHeroNew)
		{
			gErrorStream("HeroNewDataset::CollectRankUpPackItems HeroNewDID=" << nHeroNewDID + "is not exist");
			return -1;
		}
		CollectionRankTableIDT& rCollectionRankTableID = iterHeroNew->second;

		CollectionRankTableIDT::iterator iterRank = rCollectionRankTableID.find(nCurrRank);
		if (rCollectionRankTableID.end() == iterRank)
		{
			gErrorStream("HeroNewDataset::CollectRankUpPackItems HeroNewRank=" << nCurrRank + "is not exist");
			return -1;
		}
		CollectionSoltTableIDT& rCollectionSoltTableID = iterRank->second;

		for (int32 ii = HERONEW_RANK_SOLT_1; ii < HERONEW_RANK_SOLT_MAX; ++ii)
		{
			if (nAddItemSoltFlag & (1 << (ii - 1)))
			{
				pwassertf(0 < rCollectionSoltTableID[ii]);
				SHeroNewRank* pData = GetSHeroNewRankData(rCollectionSoltTableID[ii]);
				pwassertf(NULL != pData);
				SPackItem item = { pData->item_id, 1 };
				vtPackItems.push_back(item);
			}
		}
		return 0;
	}

	int16	 HeroNewDataset::GetHeroMaxRank(int32 nHeroNewDID)
	{
		CollectionHeroNewRankTableIDT::iterator iterHeroNew = m_mapHeroNewRankTableIDs.find(nHeroNewDID);
		if (m_mapHeroNewRankTableIDs.end() == iterHeroNew)
		{
			gErrorStream("HeroNewDataset::GetHeroMaxRank HeroNewDID=" << nHeroNewDID + "is not exist");
			return 0;
		}
		CollectionRankTableIDT& rCollectionRankTableID = iterHeroNew->second;
		pwassertn(0 < rCollectionRankTableID.size());
		return (int16)(rCollectionRankTableID.size() - 1);
	}

	int HeroNewDataset::CollectSynthesisPackItems(int32 nTableID, CollectionPackItemsT& vtGrantItems, CollectionPackItemsT& vtSpendItems)
	{
		SHeroNewRank* pData = GetSHeroNewRankData(nTableID);
		pwassertf(NULL != pData);
		pwassertf(0 < pData->item_id);
		SPackItem item = { pData->item_id, 1 };
		vtGrantItems.push_back(item);

		if (0 < pData->req_item1[0] && 0 < pData->req_item1[1])
		{
			SPackItem item1 = { pData->req_item1[0], pData->req_item1[1] };
			vtSpendItems.push_back(item1);
		}
		if (0 < pData->req_item2[0] && 0 < pData->req_item2[1])
		{
			SPackItem item2 = { pData->req_item2[0], pData->req_item2[1] };
			vtSpendItems.push_back(item2);
		}
		if (0 < pData->req_item3[0] && 0 < pData->req_item3[1])
		{
			SPackItem item3 = { pData->req_item3[0], pData->req_item3[1] };
			vtSpendItems.push_back(item3);
		}
		return 0;
	}
}