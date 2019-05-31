#ifndef _pw_misc_consts_
#define _pw_misc_consts_

#include "pw_def.h"

namespace pwngs
{
	// �ӻ��̹߳���ľ���Ĺ�����
	enum EMiscType
	{
		MISC_TYPE_SHOP_MGR		= 1,			// �̵������
		MISC_TYPE_BROADCAST_MGR = 2,			// ��Ӫ�㲥������
		MISC_TYPE_AWARD_SERVER_MGR = 3,			// ȫ������������
		MISC_TYPE_WARLORD_MGR = 4,				// ��������������
		MISC_TYPE_MALL_MGR = 5,					// �̳ǹ�����
		MISC_TYPE_GAMESELLER_MGR = 6,			// �й�����
		MISC_TYPE_OPEN_AUCTION_MGR = 7,			// ��������������
		MISC_TYPE_LOTTERY_MGR = 8,				// �齱������
		MISC_TYPE_CHEST_MGR = 9,				// ���������
		MISC_TYPE_LOTTERY_PRIZE_MGR = 10,		// �����ֹ�����
	};

	// ȫ���̹߳���ľ���Ĺ�����
	enum EGlobalType
	{
		GLOBAL_TYPE_PASSPORTLOCK_MGR = 1,		// �ʺ�����������
		GLOBAL_TYPE_GLOBALRANK_MGR = 2,			// ȫ�����й�����
	};

	enum
	{
		STAGE_MISC_OBJECT = 1,					// ��SImplStageMgr�ϵ�misc����
	};

	// �̵���ش�����
	enum EShopOperCode
	{
		SHOP_FAILED_SUCCESS		= 0,
		SHOP_FAILED_UNKNOWN_ITEM = 10506,		// �̵겻���ڸ���Ʒ
		SHOP_FAILED_REQ_ITEM,					// ���߲���
		SHOP_FAILED_BAG_FULL,					// �����ռ䲻��
		SHOP_FAILED_EXCEED_GLOBAL_COUNT,		// ���������޹�����
		SHOP_FAILED_UNKNOWN_SHOP,				// δ֪�̵�
		SHOP_FAILED_NOT_FOR_SALE,				// ����Ʒ���ɳ���
		SHOP_FAILED_HONOR_NOT_ENOUGH,			// ��������
		SHOP_FAILED_INVALID_ARGS,				// ��������
		SHOP_FAILED_ITEM_NOT_ENOUGH,			// ���߲���
		SHOP_FAILED_SELL_ITEM_NOT_EXIST,		// �̵겻���ڸ���Ʒ
		SHOP_FAILED_CONDITION_TRIAL_LAND_LIMIT,	// ����֮����֮��δͨ��
	};

	// �̳ǿɹ��������ֵ(������ʾ���޹������)
	const int32 cst_shop_count_infinite = -1;

	// �̳���ش�����
	enum EMallOperCode
	{
		MALL_FAILED_SUCCESS		= 0,
		MALL_FAILED_NOT_ON_SALE			= 70007, // ��Ʒ���¼�
		MALL_FAILED_EXCEED_PERSON_COUNT	= 70008, // ���������޹�����
		MALL_FAILED_EXCEED_GLOBAL_COUNT	= 70009, // ���������޹�����
		MALL_FAILED_REQ_GOLD			= 70010, // ��Ҳ���
		MALL_FAILED_REQ_BAG				= 70011, // �����ռ䲻��
		MALL_FAILED_REQ_CHARGE_GOLD		= 102012,// ��ֵ��Ҳ���
		MALL_FAILED_EXCEED_RIDE_COUNT	= 104020,// ������������
		MALL_FAILED_EXCEED_VIP_LEVEL	= 106200,// ��������ȼ�
	};

	// �̳Ǳ�ǩҳ����
	const int32 cst_mall_label_count = 8;

	// �̳ǿɹ��������ֵ(������ʾ���޹������)
	const int32 cst_mall_count_infinite = -1;

	const int cst_sec_of_a_day = 24 * 3600;

	// ����ս��ش�����
	enum ENJTZOperCode
	{
		NJTZ_ERROR_SUCCESSFUL	= 0,
		NJTZ_ERROR_SUPPORT_TEAM_NOT_EXIST, // �������鲻����
		NJTZ_ERROR_SUPPORT_ALREADY_SUPPORTED, // �Ѿ��������ö���
		NJTZ_ERROR_SUPPORT_TEAM_LOST, // ������������̭
		NJTZ_ERROR_SUPPORT_TEAM_REQ_NOT_SYSTEM, // ����������ϵͳ����
		NJTZ_ERROR_SUPPORT_TEAM_IS_BYE, // �������鱻�ֿ�(�޶���)

		NJTZ_ERROR_SUPPORT_REQ_NOT_START		= 51200, // ��ʼ��������
	};

	// С��Ь��ƷID
	const int cst_easy_go_item_id = 6100000;
}

#endif // _pw_misc_consts_