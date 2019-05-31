#ifndef _pw_open_auction_def_
#define _pw_open_auction_def_

#include "kvorm/pw_orm_openauctionitem.h"
#include "pw_timer_queue.h"

namespace pwngs
{
	const int cst_open_auction_broadcast_before_end_time = 2*60;

	const int cst_one_day_seconds = 24 * 60 * 60;

	enum EOpenAuctionItemStatus
	{
		OPEN_AUCTION_ITEM_STATUS_NONE = 0,

		OPEN_AUCTION_ITEM_STATUS_ONSALE,		// 上架状态
		OPEN_AUCTION_ITEM_STATUS_HAMMER,		// 落锤状态
		OPEN_AUCTION_ITEM_STATUS_COMPLETED,		// 结束状态(未结算)
		OPEN_AUCTION_ITEM_STATUS_FINISHED,		// 结算状态

		OPEN_AUCTION_ITEM_STATUS_MAX,
	};

	enum EOpenAuctionBidType
	{
		OPEN_AUCTION_BID_TYPE_RAISE_OTHER,		// 他人开价
		OPEN_AUCTION_BID_TYPE_RAISE_SELF,		// 自己加价
	};

	enum EOpenAuctionOper
	{
		OPEN_AUCTION_OPER_RETURN_GOLD = 0,		// 返还竞拍金币
		OPEN_AUCTION_OPER_GRANT_ITEM,			// 发放竞拍物品
	};

	enum EOpenAuctionBroadcastType
	{
		OPEN_AUCTION_BROADCAST_TYPE_NONE = 0,

		OPEN_AUCTION_BROADCAST_TYPE_BEFORE_END,		// 落锤前广播
		OPEN_AUCTION_BROADCAST_TYPE_END,			// 落锤广播
		OPEN_AUCTION_BROADCAST_TYPE_FINISHED,		// 结束广播
		OPEN_AUCTION_BROADCAST_TYPE_RESET_HAMMER,	// 落锤重置广播
		OPEN_AUCTION_BROADCAST_TYPE_START,			// 上架广播

		OPEN_AUCTION_BROADCAST_TYPE_MAX,
	};

	enum EOpenAuctionType
	{
		OPEN_AUCTION_TYPE_KAIFU = 1,				// 开服拍卖
		OPEN_AUCTION_TYPE_HEFU,						// 合服拍卖
	};

	enum EOpenAuctionOperCode
	{
		OPEN_AUCTION_OPER_SUCCESS = 0,

		OPEN_AUCTION_OPER_BID_ERR_STATUS = 15301,			// 物品状态错误
		OPEN_AUCTION_OPER_BID_ERR_TYPE,						// 竞拍类型错误
		OPEN_AUCTION_OPER_BID_NOT_ENOUGH_GOLD,				// 竞拍金币不足

		OPEN_AUCTION_OPER_BID_ITEM_CFG_NOT_EXIST,			// 物品配置不存在
		OPEN_AUCTION_OPER_BID_ITEM_CFG_CLOSED,				// 物品配置已关闭
		OPEN_AUCTION_OPER_BID_ITEM_NOT_EXIST,				// 竞拍物品不存在
		OPEN_AUCTION_OPER_BID_ITEM_LOCK,					// 竞拍物品被锁定
		OPEN_AUCTION_OPER_BID_RAISE_SELF_LIMIT,				// 非最高竞价者
		OPEN_AUCTION_OPER_BID_STATUS_MODIFIED,				// 竞拍状态已改变
		OPEN_AUCTION_OPER_BID_BASE_PRICE_MODIFIED,			// 基础价格已改变
		OPEN_AUCTION_OPER_BID_RAISE_PRICE_LIMIT,			// 小于最低加价
		OPEN_AUCTION_OPER_BID_CD_LIMIT,						// CD时间内

		OPEN_AUCTION_OPER_BROADCAST_BEFORE_END = 15340,		// 落锤前广播
		OPEN_AUCTION_OPER_BROADCAST_END,					// 落锤广播
		OPEN_AUCTION_OPER_BROADCAST_FINISHED,				// 竞拍结束广播
		OPEN_AUCTION_OPER_BROADCAST_RESET_HAMMER,			// 落锤重置广播
		OPEN_AUCTION_OPER_BROADCAST_START,					// 上架广播

	};

	typedef orm::OpenAuctionItem SOrmAuctionItem;

	struct SOpenAuctionItem
	{
		SOrmAuctionItem ormitem;
		pwutils::Timer::TRef tref;
		bool bLock;					// 锁定状态
		
		SOpenAuctionItem()
		{
			bLock = false;
		}

		bool IsUnSale()
		{
			return ormitem.status == OPEN_AUCTION_ITEM_STATUS_NONE;
		}

		bool IsOnSale()
		{
			return ormitem.status == OPEN_AUCTION_ITEM_STATUS_ONSALE;
		}

		bool IsInHammer()
		{
			return ormitem.status == OPEN_AUCTION_ITEM_STATUS_HAMMER;
		}

		bool IsCompleted()
		{
			return ormitem.status == OPEN_AUCTION_ITEM_STATUS_COMPLETED;
		}

		bool IsFinished()
		{
			return ormitem.status == OPEN_AUCTION_ITEM_STATUS_FINISHED;
		}
	};

	struct SOpenAuctionBidContext
	{
		int64 nHid;
		int32 nCfgID;
		int64 nBasePrice;
		int64 nRaisePrice;
		int32 nBidStatus;
		int32 nBidType;

		SOpenAuctionBidContext()
		{
			memset(this,0,sizeof(*this));
		}
	};

	struct SOpenAuctionBroadcastContext
	{
		int32 nCfgID;
		EOpenAuctionBroadcastType nType;

		SOpenAuctionBroadcastContext()
		{
			memset(this,0,sizeof(*this));
		}
	};
}

#endif // _pw_open_auction_def_