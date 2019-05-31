#ifndef _pw_auction_house_const_
#define _pw_auction_house_const_

namespace pwngs
{

	enum EAuctionNotifyCode
	{
		AUCTION_NOTIFY_SUCCESS = 0,

		AUCTION_NOTIFY_NOT_BID_MYSELF = 52000,	// 不能对自己寄拍的物品进行竞价
		AUCTION_NOTIFY_SELL_SUCCESS,			// 寄卖成功
		AUCTION_NOTIFY_BUY_SUCCESS,				// 购买成功，请使用邮件接收
		AUCTION_NOTIFY_BID_SUCCESS,				// 出价成功
		AUCTION_NOTIFY_NOT_EXIST_ITEM,			// 物品不存在
		AUCTION_NOTIFY_BID_PRICE_LOW,			// 出价过低
		AUCTION_NOTIFY_BID_ONCE_PRICE_LOW,		// 加价过低
		AUCTION_NOTIFY_SELL_NUM_LIMIT,			// 寄售数量过多
		AUCTION_NOTIFY_SELL_CANT_CANCEL,		// 不可取消寄售

	};

	enum EAuctionOper
	{
		AUCTION_OPER_BUY,
		AUCTION_OPER_SELL,
	};

	enum EAuctionItemOper
	{
		AUCTION_ITEM_OPER_ADD,
		AUCTION_ITEM_OPER_DEL,
		AUCTION_ITEM_OPER_UPDATE,
	};

}

#endif // _pw_auction_house_const_
