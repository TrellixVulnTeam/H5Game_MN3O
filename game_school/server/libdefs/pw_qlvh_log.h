#ifndef _pw_qlvh_log_
#define _pw_qlvh_log_

#include "pw_log_collector.h"

namespace pwngs
{
	enum
	{
		QLOG_TYPE_COST = 0,
		QLOG_TYPE_LOGIN,
		QLOG_TYPE_LOGOUT,
		QLOG_TYPE_ONLINE,
		QLOG_TYPE_RECHARGE,
		QLOG_TYPE_REGISTER,
		QLOG_TYPE_UPGRADE,
		QLOG_TYPE_QUEST,
		QLOG_TYPE_MAX,
	};

	extern int InitialQlvhLog(const char* path = NULL,const char* tmppath = NULL,int serverid = -1);
	extern int CleanupQlvhLog();


}

#endif // _pw_qlvh_log_