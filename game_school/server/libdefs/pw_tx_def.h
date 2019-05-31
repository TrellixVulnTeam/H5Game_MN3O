#ifndef _pw_tx_def_
#define _pw_tx_def_

#include <string.h>

namespace pwngs
{
	struct STencentUserInfo
	{
		bool is_blue_vip; // 是否蓝钻
		bool is_blue_year_vip; // 是否蓝钻年费
		bool is_super_blue_vip; // 是否豪华蓝钻
		int  blue_vip_level; // 蓝钻等级

		bool is_yellow_vip; // 是否黄钻
		bool is_yellow_year_vip; // 是否黄钻年费
		bool is_super_yellow_vip; // 是否豪华黄钻
		int  yellow_vip_level; // 黄钻等级

		int tgp_level;	// tgp等级

		char openid[64];
		char openkey[128];
		char platform[64];
		char platform_key[128];
		int pid; // 腾讯渠道

		bool pfkey_valid() const
		{
			return strlen(platform_key) > 0;
		}

		bool valid() const
		{
			return strlen(openid) > 0;
		}

		STencentUserInfo()
		{
			memset(this,0,sizeof(STencentUserInfo));
		}
	};
}

#endif // 