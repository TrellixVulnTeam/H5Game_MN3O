#ifndef _pw_syscfg_def_
#define _pw_syscfg_def_

#include "pw_types.h"

namespace pwngs
{

	const int cst_syscfgid_servergroup = 0;
 	const int cst_syscfgid_zoneid = 1;
	const int cst_syscfgid_lastjtz_refresh = 2; // �ϴξ���սˢ��ʱ��
	const int cst_syscfgid_sql_version = 3; // ���ݿ�汾
	const int cst_syscfgid_sum_charge_lastday = 4; // ���մ����ֵ data1=date data2=sum
	const int cst_syscfgid_njtz_next_round = 5;	// ����ս��һ�ֵ�����(��0��ʼ)
	const int cst_syscfgid_last_merge_date = 6;	// ���Ϸ�����(0 | ��������Ϊû�Ϲ���)
	const int cst_syscfgid_last_zero_event = 7; // �������¼�ʱ��
	const int cst_syscfgid_360set_openserveractivitytime = 8;	//360���ÿ����ʱ��

// 	struct SSystemConfigure
// 	{
// 		int32 id;
// 		int64 ivar1; 
// 		int64 ivar2;
// 		char  svar[100];
// 	};
}

#endif // 