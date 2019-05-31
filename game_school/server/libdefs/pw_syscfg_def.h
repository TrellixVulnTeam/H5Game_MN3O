#ifndef _pw_syscfg_def_
#define _pw_syscfg_def_

#include "pw_types.h"

namespace pwngs
{

	const int cst_syscfgid_servergroup = 0;
 	const int cst_syscfgid_zoneid = 1;
	const int cst_syscfgid_lastjtz_refresh = 2; // 上次军团战刷新时间
	const int cst_syscfgid_sql_version = 3; // 数据库版本
	const int cst_syscfgid_sum_charge_lastday = 4; // 当日大最充值 data1=date data2=sum
	const int cst_syscfgid_njtz_next_round = 5;	// 军团战下一轮的轮数(从0开始)
	const int cst_syscfgid_last_merge_date = 6;	// 最后合服日期(0 | 不存在则为没合过服)
	const int cst_syscfgid_last_zero_event = 7; // 最后零点事件时间
	const int cst_syscfgid_360set_openserveractivitytime = 8;	//360设置开服活动时间

// 	struct SSystemConfigure
// 	{
// 		int32 id;
// 		int64 ivar1; 
// 		int64 ivar2;
// 		char  svar[100];
// 	};
}

#endif // 