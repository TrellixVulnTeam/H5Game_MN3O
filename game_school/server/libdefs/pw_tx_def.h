#ifndef _pw_tx_def_
#define _pw_tx_def_

#include <string.h>

namespace pwngs
{
	struct STencentUserInfo
	{
		bool is_blue_vip; // �Ƿ�����
		bool is_blue_year_vip; // �Ƿ��������
		bool is_super_blue_vip; // �Ƿ��������
		int  blue_vip_level; // ����ȼ�

		bool is_yellow_vip; // �Ƿ����
		bool is_yellow_year_vip; // �Ƿ�������
		bool is_super_yellow_vip; // �Ƿ��������
		int  yellow_vip_level; // ����ȼ�

		int tgp_level;	// tgp�ȼ�

		char openid[64];
		char openkey[128];
		char platform[64];
		char platform_key[128];
		int pid; // ��Ѷ����

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