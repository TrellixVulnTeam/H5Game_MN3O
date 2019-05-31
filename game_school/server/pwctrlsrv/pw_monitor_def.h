#ifndef _pw_monitor_def_
#define _pw_monitor_def_

#include "pw_def.h"

namespace pwngs
{
	namespace monitor
	{
		struct SStagePayload
		{
			int64 map;
			int64 basemap;
			int64 humans;
			int64 objects;
			char  node[64];
			char  port[64];
		};

		struct SThreadPayload
		{
			char  node[64];
			char  port[64];
			float diff;
			float diffAvg;
			int64 humans;
			int64 objects;
			int64 scriptMemoryUsed;
			int64 lastReportTime;
		};

		struct SNormalServer
		{
			int64 server_group;
		};

		struct SCharge
		{
			int64 date;
			float rmb;
			float pubacct_rmb;
		};

		extern volatile int64 g_nStageCount;
		extern volatile int64 g_nHumanCount;
		extern volatile int64 g_nHumanOnlineMax; // service common 管理
		extern volatile int64 g_nHumanRegisterCount; // service common 管理
		extern volatile int64 g_nThreadCount;
		extern volatile int64 g_nNormalServerCount;

		extern SStagePayload g_nStageInfos[20000];
		extern SThreadPayload g_nThreadInfos[1000];
		extern SNormalServer g_vNormalServers[2000];
		extern SCharge g_vCharge[15];
	}
}

#endif // _pw_monitor_def_