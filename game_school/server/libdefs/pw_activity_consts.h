#ifndef _pw_activity_consts_
#define _pw_activity_consts_

#include "pw_def.h"

namespace pwngs
{
	enum EActivityStatus
	{
		ACTIVITY_STATUS_NONE = 1,
		ACTIVITY_STATUS_READY,
		ACTIVITY_STATUS_START,
		ACTIVITY_STATUS_END,
		ACTIVITY_STATUS_ENTER,
		ACTIVITY_STATUS_QUIT,
	};

	namespace activities
	{
		enum EFailedCode
		{
			FAILED_SUCCESSFUL = 0,
			FAILED_CASH_NOTENOUGHT = 1,
			FAILED_CASH_INVALID = 2,
			FAILED_TIMEOUT = 3,
			FAILED_SIGNUP = 4,
			FAILED_HUMAN_STATUS = 5,
			FAILED_CONDITION = 6,
			FAILED_STAGE_FULL = 7,
		};
	}

	const int cst_activity_dts = 1;
	const int cst_activity_njtz = 2;
	const int cst_activity_lgkj = 3;
	const int cst_activity_worldboss_honglong = 4; // 世界boss-红龙
	const int cst_activity_worldboss_baoyanlong = 5; // 世界boss-爆炎龙
	const int cst_activity_worldboss_jinglinglong = 6; // 世界boss-精灵龙
	const int cst_activity_runcar = 7;	//护送

	const int cst_activity_kfmz = 24;	//跨服盟战[普通服]
	const int cst_activity_kfmz_ladder = 25;	//跨服盟战[天梯服]

	const int LGKJ_ITEM = 400032;
	const int LGKJ_ITEM_GOUYU = 400223;
	const int LGKJ_ITEM_EXCHANGE_MAX = 3000;

	const int DTS_ITEM = 400024;
	const int DTS_COUNT1 = 60;
	const int DTS_COUNT2 = 30;
	const int DTS_BASEMAP1 = 37501;
	const int DTS_BASEMAP2 = 37502;
	const int DTS_BASEMAP3 = 37501;

	const int cst_activity_substitute_cost_worldboss = 30;
	const int cst_activity_substitute_cost_lgkj = 50;

}

#endif // _pw_activity_consts_