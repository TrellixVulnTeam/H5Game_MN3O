#ifndef _pw_devil_def_h
#define _pw_devil_def_h

#include "pw_def.h"
#include "pw_ngs_common.h"

namespace pwngs
{
	// 副本队伍状态
	enum EDevilState
	{
		DEVIL_STATE_IDLE = 0,		// 空闲中
		DEVIL_STATE_MERGE,			// 匹配组队中
		DEVIL_STATE_ENTER,			// 准备进入中
		DEVIL_STATE_COMPETE,		// 竞技比赛中
	};

	// 准备比赛倒计时时间（单位秒）
	const int cst_devil_team_enter_time = 10;

	//队伍中最大人数
	const int cst_devil_max_team = 3 ;

	//离开副本时间限制 sec
	const int cst_devil_leave_time = 15 ;
}

#endif //_pw_arena_def_h