#ifndef _pw_auction_house_const_
#define _pw_auction_house_const_

namespace pwngs
{

	enum EAuctionNotifyCode
	{
		AUCTION_NOTIFY_SUCCESS = 0,

		AUCTION_NOTIFY_NOT_BID_MYSELF = 52000,	// ���ܶ��Լ����ĵ���Ʒ���о���
		AUCTION_NOTIFY_SELL_SUCCESS,			// �����ɹ�
		AUCTION_NOTIFY_BUY_SUCCESS,				// ����ɹ�����ʹ���ʼ�����
		AUCTION_NOTIFY_BID_SUCCESS,				// ���۳ɹ�
		AUCTION_NOTIFY_NOT_EXIST_ITEM,			// ��Ʒ������
		AUCTION_NOTIFY_BID_PRICE_LOW,			// ���۹���
		AUCTION_NOTIFY_BID_ONCE_PRICE_LOW,		// �Ӽ۹���
		AUCTION_NOTIFY_SELL_NUM_LIMIT,			// ������������
		AUCTION_NOTIFY_SELL_CANT_CANCEL,		// ����ȡ������

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
