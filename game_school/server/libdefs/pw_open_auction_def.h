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

		OPEN_AUCTION_ITEM_STATUS_ONSALE,		// �ϼ�״̬
		OPEN_AUCTION_ITEM_STATUS_HAMMER,		// �䴸״̬
		OPEN_AUCTION_ITEM_STATUS_COMPLETED,		// ����״̬(δ����)
		OPEN_AUCTION_ITEM_STATUS_FINISHED,		// ����״̬

		OPEN_AUCTION_ITEM_STATUS_MAX,
	};

	enum EOpenAuctionBidType
	{
		OPEN_AUCTION_BID_TYPE_RAISE_OTHER,		// ���˿���
		OPEN_AUCTION_BID_TYPE_RAISE_SELF,		// �Լ��Ӽ�
	};

	enum EOpenAuctionOper
	{
		OPEN_AUCTION_OPER_RETURN_GOLD = 0,		// �������Ľ��
		OPEN_AUCTION_OPER_GRANT_ITEM,			// ���ž�����Ʒ
	};

	enum EOpenAuctionBroadcastType
	{
		OPEN_AUCTION_BROADCAST_TYPE_NONE = 0,

		OPEN_AUCTION_BROADCAST_TYPE_BEFORE_END,		// �䴸ǰ�㲥
		OPEN_AUCTION_BROADCAST_TYPE_END,			// �䴸�㲥
		OPEN_AUCTION_BROADCAST_TYPE_FINISHED,		// �����㲥
		OPEN_AUCTION_BROADCAST_TYPE_RESET_HAMMER,	// �䴸���ù㲥
		OPEN_AUCTION_BROADCAST_TYPE_START,			// �ϼܹ㲥

		OPEN_AUCTION_BROADCAST_TYPE_MAX,
	};

	enum EOpenAuctionType
	{
		OPEN_AUCTION_TYPE_KAIFU = 1,				// ��������
		OPEN_AUCTION_TYPE_HEFU,						// �Ϸ�����
	};

	enum EOpenAuctionOperCode
	{
		OPEN_AUCTION_OPER_SUCCESS = 0,

		OPEN_AUCTION_OPER_BID_ERR_STATUS = 15301,			// ��Ʒ״̬����
		OPEN_AUCTION_OPER_BID_ERR_TYPE,						// �������ʹ���
		OPEN_AUCTION_OPER_BID_NOT_ENOUGH_GOLD,				// ���Ľ�Ҳ���

		OPEN_AUCTION_OPER_BID_ITEM_CFG_NOT_EXIST,			// ��Ʒ���ò�����
		OPEN_AUCTION_OPER_BID_ITEM_CFG_CLOSED,				// ��Ʒ�����ѹر�
		OPEN_AUCTION_OPER_BID_ITEM_NOT_EXIST,				// ������Ʒ������
		OPEN_AUCTION_OPER_BID_ITEM_LOCK,					// ������Ʒ������
		OPEN_AUCTION_OPER_BID_RAISE_SELF_LIMIT,				// ����߾�����
		OPEN_AUCTION_OPER_BID_STATUS_MODIFIED,				// ����״̬�Ѹı�
		OPEN_AUCTION_OPER_BID_BASE_PRICE_MODIFIED,			// �����۸��Ѹı�
		OPEN_AUCTION_OPER_BID_RAISE_PRICE_LIMIT,			// С����ͼӼ�
		OPEN_AUCTION_OPER_BID_CD_LIMIT,						// CDʱ����

		OPEN_AUCTION_OPER_BROADCAST_BEFORE_END = 15340,		// �䴸ǰ�㲥
		OPEN_AUCTION_OPER_BROADCAST_END,					// �䴸�㲥
		OPEN_AUCTION_OPER_BROADCAST_FINISHED,				// ���Ľ����㲥
		OPEN_AUCTION_OPER_BROADCAST_RESET_HAMMER,			// �䴸���ù㲥
		OPEN_AUCTION_OPER_BROADCAST_START,					// �ϼܹ㲥

	};

	typedef orm::OpenAuctionItem SOrmAuctionItem;

	struct SOpenAuctionItem
	{
		SOrmAuctionItem ormitem;
		pwutils::Timer::TRef tref;
		bool bLock;					// ����״̬
		
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