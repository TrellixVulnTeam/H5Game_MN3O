#ifndef _pw_heronew_dataset_
#define _pw_heronew_dataset_

#include "pwconf_Hero.h"
#include "pwconf_HeroAssistance.h"
#include "pw_item_package.h"

namespace pwngs
{
	typedef pwconf::SHero SHeroNewData;
	typedef pwconf::SHeroAssistance SHeroNewRank;

	class HeroNewDataset
	{
	public:
		int					Load(const std::string& path) ;
		int					LoadHeroNewRank(const std::string& path);

	public:
		SHeroNewData*		GetHeroNewData(sint32 id) ;
		SHeroNewData*		GetHeroNewbyDebrisId(sint32 nDebrisId); // 根据英雄碎片获取对应的英雄
		int					GetActivatedHeroNewDebrisNum(sint32 id); // 激活英雄所需的碎片数量
		int					CollectHeroIds(std::vector<sint32>& vtHeroIds) ;
		int					CollectHeroAttr(std::vector<sint32>& vtAttr, int32 nId, int32 nStar);

		SHeroNewRank*		GetSHeroNewRankData(sint32 nID);
		int					CollectHeroCurrRankAttr(std::vector<sint32>& vtAttr, int32 nHeroNewDID, int16 nCurrRank, int16 nItemSoltFlag); // 只吸收当前阶对应物品获取的属性
		int					CollectHeroTotalRankAttr(std::vector<sint32>& vtAttr, int32 nHeroNewDID, int16 nTotalRank, int16 nItemSoltFlag); // 吸收全部阶对应物品获取的属性
		int					CollectRankUpPackItems(int32 nHeroNewDID, int16 nCurrRank, int16 nAddItemSoltFlag, CollectionPackItemsT& vtPackItems); // 获取英雄升阶镶嵌所需材料
		int16					GetHeroMaxRank(int32 nHeroNewDID); // 获取英雄最高阶
		int					CollectSynthesisPackItems(int32 nTableID, CollectionPackItemsT& vtGrantItems, CollectionPackItemsT& vtSpendItems); // 获取要合成的英雄镶嵌物和所需材料
	private:
		typedef std_unordered_map<int,SHeroNewData> CollectionHeroNewDataT;
		typedef std::vector<sint32> CollectionHeroIdsT;

		typedef std::vector<std::vector<sint32> > CollectionHeroNewAttrT;
		typedef std_unordered_map<int,CollectionHeroNewAttrT > CollectionHeroNewAttrSetT;

		typedef std_unordered_map<int, int> CollectionSoltTableIDT; // map<slot, tableID>
		typedef std_unordered_map<int, CollectionSoltTableIDT > CollectionRankTableIDT; // map<rank, map<slot, tableID>>
		typedef std_unordered_map<int, CollectionRankTableIDT > CollectionHeroNewRankTableIDT; // map<HeroNewDID, map<rank, map<slot, tableID>>>
		typedef std_unordered_map<int, SHeroNewRank> CollectionHeroNewRankDataT; // map<tableID, SHeroNewRank>
		
	private:
		CollectionHeroNewDataT m_mapHeroPublicData;
		CollectionHeroIdsT		m_vecHeroIds;

		CollectionHeroNewAttrSetT m_mapHeroNewAttrSet ;

		CollectionHeroNewRankTableIDT m_mapHeroNewRankTableIDs;
		CollectionHeroNewRankDataT m_mapHeroNewRankDatas;
	};

	extern HeroNewDataset g_objHeroNewDataset ;
}


#endif