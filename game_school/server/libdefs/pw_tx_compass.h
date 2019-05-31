#ifndef _pw_tx_compass_
#define _pw_tx_compass_

#include "pw_def.h"

namespace tx
{
	enum EDisableSnspay
	{
		TX_DISABLE_SNSPAY_GIFT = 0,	// ���� 
		TX_DISABLE_SNSPAY_GIVE,		// ��Ҫ
		TX_DISABLE_SNSPAY_DEDU,		// �ֿ�
	};

	enum EDisableSnspayPf
	{
		TX_DISABLE_SNSPAY_PF_QQGAME = 0, 
		TX_DISABLE_SNSPAY_PF_QZONE,
		TX_DISABLE_SNSPAY_PF_TGP,
		TX_DISABLE_SNSPAY_PF_IDIP,
	};

	const int cst_disable_snspay_gift = (1 << TX_DISABLE_SNSPAY_GIFT);
	const int cst_disable_snspay_give = (1 << TX_DISABLE_SNSPAY_GIVE);
	const int cst_disable_snspay_dedu = (1 << TX_DISABLE_SNSPAY_DEDU);

	const int cst_disable_snspay_pf_qqgame = (1 << TX_DISABLE_SNSPAY_PF_QQGAME);
	const int cst_disable_snspay_pf_qzone = (1 << TX_DISABLE_SNSPAY_PF_QZONE);
	const int cst_disable_snspay_pf_tgp = (1 << TX_DISABLE_SNSPAY_PF_TGP);
	const int cst_disable_snspay_pf_idip = (1 << TX_DISABLE_SNSPAY_PF_IDIP);

	extern const char* cst_tencent_platform[];

	enum
	{
		DOMAIN_QZONE = 1,			// qq�ռ�
		DOMAIN_PENGYOU = 2,			// ��Ѷ������
		DOMAIN_WEIBO = 3,			// ��Ѷweibo
		DOMAIN_QPLUS = 4,			// Q+ƽ̨
		DOMAIN_MOBILE_QZONE = 5,	// �ֻ�qq�ռ�
		DOMAIN_MOBILE_PENGYOU = 6,	// �ֻ�������
		DOMAIN_MOBILE_QZONE2 = 8,	// �ֻ�qq�ռ�
		DOMAIN_MOBILE_PENGYOU2 = 9,	// �ֻ�������
		DOMAIN_QQGAME = 10,			// qqgame
		DOMAIN_3366 = 11,			// 3366ƽ̨
		DOMAIN_QQGAME_WEBSITE = 12,	// qqgame����
		DOMAIN_IOS = 13,			// iOS
		DOMAIN_ANDROID = 14,		// Android
		DOMAIN_MANYOU = 15,			// ����
		DOMAIN_YOUXI_RENSHENG = 16,	// ��Ϸ����
		DOMAIN_YOUXI_LIANMENG = 17,	// ��Ϸ����
		DOMAIN_YOUXI_BOX = 23,		// ��Ϸ����
	};

	namespace compass
	{
		struct SBase
		{
			int32 domain;
			int32 pid;
			std::string pf;
		};

		struct SLogin : public SBase
		{
			std::string userip;
			sint64 hid;
			std::string openid;
			uint32 level;
		};

		struct SQuit : public SBase
		{
			std::string userip;
			sint64 hid;
			std::string openid;
			uint32 level;
			uint32 online_second;
		};

		struct SRegister : public SBase
		{
			std::string userip;
			sint64 hid;
			std::string openid;
			std::string source;

			std::string openkey;
			std::string pfkey;
		};

		struct SRecharge : public SBase
		{
			std::string userip;
			sint64 hid;
			std::string openid;

			uint32 itemid;
			std::string itemtype;
			uint32 itemcnt;
			uint32 level;

			sint64 modifyfee; // �仯���
			sint64 totalfee;  // ��ǰ���

			sint64 modifycoin; // �仯���
			sint64 totalcoin; // ��ǰ���
		};

		struct SConsume : public SBase
		{
			std::string userip;
			sint64 hid;
			std::string openid;

			uint32 itemid;
			std::string itemtype;
			uint32 itemcnt;
			uint32 level;

			sint64 modifyfee; // �仯���
			sint64 totalfee;  // ��ǰ���

			sint64 modifycoin; // �仯���
			sint64 totalcoin; // ��ǰ���
		};
	}

	class CompassHelper
	{
	public:
		static void Perform(const std::string& url);
		static void PerformUnion(const std::string& url);

		static void DoLogin(compass::SLogin& context);
		static void DoRegister(compass::SRegister& context);
		static void DoRegisterUnion(compass::SRegister& context);
		static void DoQuit(compass::SQuit& context);
		static void DoRecharge(compass::SRecharge& context);
		static void DoConsume(compass::SConsume& context);
	};
}

#endif //_pw_tx_compass_