#include "pw_monitor_def.h"

namespace pwngs
{
	namespace monitor
	{
		volatile int64 g_nStageCount = 0;
		volatile int64 g_nHumanCount = 0;
		volatile int64 g_nHumanOnlineMax = 0;
		volatile int64 g_nHumanRegisterCount = 0;
		volatile int64 g_nThreadCount = 0;
		volatile int64 g_nNormalServerCount = 0;

		SStagePayload g_nStageInfos[20000];
		SThreadPayload g_nThreadInfos[1000];
		SNormalServer g_vNormalServers[2000];
		SCharge g_vCharge[15] = {0};
	}
}