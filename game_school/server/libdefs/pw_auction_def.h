#ifndef _pw_auction_def_
#define _pw_auction_def_

#include "pw_def.h"
#include "pw_ngs_common.h"
#include "pw_item_def.h"
#include "kvorm/pw_orm_dauctioninfo.h"
#include "kvorm/pw_orm_auctionitem.h"

namespace pwngs
{

	const size_t cst_auction_item_chunk_capacity = 5000;
	const size_t cst_auction_max_itemsinsell_count = 5;

	const size_t cst_auction_max_list_item_num = 50;
	const size_t cst_auction_max_query_item_num = 100;
	const size_t cst_auction_max_search_item_num = 2000;

	const size_t cst_auction_min_floor_price = 50;

	struct SAuctionSearch
	{
	public:
		SAuctionSearch()
		{
			memset(this,0,sizeof(*this));
		
			memset(attr1,-1,sizeof(attr1));
			memset(attr2,-1,sizeof(attr2));
			memset(attr3,-1,sizeof(attr3));
		}
	public:
		char  name[pwngs::max_name_len];	// 物品名称
		int32 type[16];						// 物品类型
		int32 color;						// 物品品质
		int32 min_level;					// 物品最低等级
		int32 max_level;					// 物品最高等级

		int32 attr1[16];					// 物品包含属性
		int32 attr2[16];					// 物品包含属性
		int32 attr3[16];					// 物品包含属性
	};

#pragma pack(push,1)

	struct SAuctionIdx
	{
		int64 nAuctionId;
		int32 nAuctionPosition;
	};

#pragma pack(pop)

	typedef std::vector<SAuctionIdx> CollectionAuctionIdxsT;

	struct SAuctionBuy
	{
		int64 uid;
		char  uname[pwngs::max_name_len];
		int32 position;
		int64 auctionId;
		int32 priceGold;
	};

	struct SAuctionInfomation : public orm::DAuctionInfo
	{
		SAuctionInfomation()
		{

		}
		SAuctionInfomation(const orm::DAuctionInfo& v)
		{
			static_cast<orm::DAuctionInfo&>(*this) = v;
		}

	};

	class SAuctionItem : public orm::AuctionItem
	{
	public:
		SAuctionItem()
			: m_pTimerPointer(NULL)
		{
			this->Clear();
		}

		inline void Clear()
		{
			this->id = 0;
		}

		inline bool IsNil()
		{
			return id == 0;
		}
	public:
		void* m_pTimerPointer;
	};	

	struct SAuctionItemRef
	{
	public:
		SAuctionItemRef()
		{
			memset(this,0,sizeof(*this));
		}

		SAuctionItemRef(SAuctionItem& item,int32 position = -1)
		{
			m_nAuctionId = item.id;
			m_nAuctionPosition = position;
			m_nLevel = item.info.item_level;
			m_nItemColor = item.info.item_color;
			m_nItemClass = item.info.item_class;
		}
	public:
		int64 m_nAuctionId;
		int32 m_nAuctionPosition;
		int32 m_nLevel;
		uint8 m_nItemColor;
		uint8 m_nItemClass;
	};

	typedef std::deque<SAuctionItemRef> CollectionOrderedRefsT;

	struct SAuctionItemClientRef
	{
		int64 nAuctionId;
		int32 nAuctionPosition;
		SAuctionInfomation info;
	};
}


#endif // _pw_auction_def_