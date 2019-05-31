#ifndef _pw_pve_def_h
#define _pw_pve_def_h

#include "pw_def.h"
#include "pw_ngs_common.h"

namespace pwngs
{
	// 副本模式
	enum EPVEMode
	{
		PVE_MODE_NONE = 0,
		PVE_MODE_LEVEL_1,			//等级80~119
		PVE_MODE_LEVEL_2,			//等级120~159
		PVE_MODE_LEVEL_3,			//等级160~199
		PVE_MODE_LEVEL_4,			//等级200~239
		PVE_MODE_LEVEL_5,			//等级240~279
		PVE_MODE_LEVEL_6,			//等级>280

		PVE_MODE_NUM,
	};

	// 副本队伍状态
	enum EPVEState
	{
		PVE_STATE_IDLE = 0,		// 空闲中
		PVE_STATE_MERGE,		// 匹配组队中
		PVE_STATE_ENTER,		// 准备进入中
		PVE_STATE_COMPETE,		// 竞技比赛中
		PVE_STATE_FREEZE,		// 队伍冻结，不再匹配
	};

	// 副本开始最小人数
	const int cst_pve_min_team_member = 2;
	//队伍中最大人数
	const int cst_pve_max_team = 20;
	
}

#endif //_pw_pve_def_h