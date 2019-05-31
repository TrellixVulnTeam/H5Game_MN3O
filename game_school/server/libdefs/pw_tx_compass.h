#ifndef _pw_tx_compass_
#define _pw_tx_compass_

#include "pw_def.h"

namespace tx
{
	enum EDisableSnspay
	{
		TX_DISABLE_SNSPAY_GIFT = 0,	// 赠送 
		TX_DISABLE_SNSPAY_GIVE,		// 索要
		TX_DISABLE_SNSPAY_DEDU,		// 抵扣
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
		DOMAIN_QZONE = 1,			// qq空间
		DOMAIN_PENGYOU = 2,			// 腾讯朋友网
		DOMAIN_WEIBO = 3,			// 腾讯weibo
		DOMAIN_QPLUS = 4,			// Q+平台
		DOMAIN_MOBILE_QZONE = 5,	// 手机qq空间
		DOMAIN_MOBILE_PENGYOU = 6,	// 手机朋友网
		DOMAIN_MOBILE_QZONE2 = 8,	// 手机qq空间
		DOMAIN_MOBILE_PENGYOU2 = 9,	// 手机朋友网
		DOMAIN_QQGAME = 10,			// qqgame
		DOMAIN_3366 = 11,			// 3366平台
		DOMAIN_QQGAME_WEBSITE = 12,	// qqgame官网
		DOMAIN_IOS = 13,			// iOS
		DOMAIN_ANDROID = 14,		// Android
		DOMAIN_MANYOU = 15,			// 漫游
		DOMAIN_YOUXI_RENSHENG = 16,	// 游戏人生
		DOMAIN_YOUXI_LIANMENG = 17,	// 游戏联盟
		DOMAIN_YOUXI_BOX = 23,		// 游戏盒子
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

			sint64 modifyfee; // 变化金币
			sint64 totalfee;  // 当前金币

			sint64 modifycoin; // 变化绑金
			sint64 totalcoin; // 当前绑金
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

			sint64 modifyfee; // 变化金币
			sint64 totalfee;  // 当前金币

			sint64 modifycoin; // 变化绑金
			sint64 totalcoin; // 当前绑金
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