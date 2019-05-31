#include "pw_ngs_common.h"
#ifndef _pw_team_const_
#define _pw_team_const_

namespace pwngs
{

	enum ETeamNotifyCode
	{
		TEAM_NOTIFY_SUCCESS = 0,

		// 通用错误
		TEAM_NOTIFY_COMMON_OFFLINE = 25201,
		TEAM_NOTIFY_COMMON_MEMBER_ADDED,					// 加入队伍不成功，系统原因
		TEAM_NOTIFY_COMMON_MEMBER_DELED,					// 离开队伍不成功，系统原因
		TEAM_NOTIFY_COMMON_MEMBER_NOT_EXIST,				// 查无此人，系统原因
		TEAM_NOTIFY_COMMON_TEAM_NOT_EXIST,					// 要操作的队伍不存在
		TEAM_NOTIFY_COMMON_INVALID_TID,						// 无效的队伍ID
		TEAM_NOTIFY_COMMON_TEAM_CREATING,					// 正在创建队伍中
		TEAM_NOTIFY_COMMON_TEAM_JOINING,					// 正在加入队伍中
		TEAM_NOTIFY_COMMON_HAS_OTHER_TEAM,					// 已经在队伍状态
		TEAM_NOTIFY_COMMON_INVITE_HAS_OTHER_TEAM = 25210,	// 邀请时在队伍状态
		TEAM_NOTIFY_COMMON_NOT_CHANGE_TEAM = 25211,			// 不能转换队伍

		// 创建队伍
		TEAM_NOTIFY_CREATE_SUCCESS = 25300,
		TEAM_NOTIFY_CREATE_HAS_TEAM,						// 创建者已加入其他队伍
		TEAM_NOTIFY_CREATE_LEVEL_LIMIT,						// 创建者等级限制
		TEAM_NOTIFY_CREATE_GOLD_LIMIT,						// 创建者金币限制
		TEAM_NOTIFY_CREATE_VIP_LIMIT,						// 创建者VIP限制
		TEAM_NOTIFY_CREATE_NAME_LIMIT,						// 队伍名字不能重复
		TEAM_NOTIFY_CREATE_MAJOR_CITY_LIMIT,				// 创建者必须在主城

		TEAM_NOTIFY_INVITE_HAD_INVITED,						// 已经邀请过了

		// 解散队伍
		TEAM_NOTIFY_DISMISS_SUCCESS = 25320,
		TEAM_NOTIFY_DISMISS_TEAM_STATE_LIMIT,				// 队伍状态限制

		// 加入队伍
		TEAM_NOTIFY_JOIN_SUCCESS = 25330,
		TEAM_NOTIFY_JOIN_HAS_TEAM,							// 申请者已加入其他队伍
		TEAM_NOTIFY_JOIN_LEVEL_LIMIT,						// 申请者等级限制
		TEAM_NOTIFY_JOIN_MEMBER_FULL,						// 所申请的队伍已经满员了
		TEAM_NOTIFY_JOIN_TEAM_STATE_LIMIT,					// 队伍状态限制
		TEAM_NOTIFY_JOIN_MAJOR_CITY_LIMIT,					// 队员必须在主城
		TEAM_NOTIFY_JOIN_CHANGE_TEAM_STATE_LIMIT,			// 队伍状态限制
		TEAM_NOTIFY_JOIN_ARENA_MAJOR_CITY_LIMIT,			// 队员必须在主城
		TEAM_NOTIFY_JOIN_FIGHT_POINT_LIMIT,					// 申请者战斗力限制

		// 离开队伍
		TEAM_NOTIFY_LEAVE_SUCCESS = 25350,
		TEAM_NOTIFY_LEAVE_COMMANDER_LIMIT,					// 队长不能离开
		TEAM_NOTIFY_LEAVE_TEAM_STATE_LIMIT,					// 队伍状态限制
		TEAM_NOTIFY_LEAVE_TEAM_MDUNGEON_LIMIT,				// 魔王本不允许主动退队

		// 踢出队伍
		TEAM_NOTIFY_KICKED_SUCCESS = 25360,
		TEAM_NOTIFY_KICKED_OPER_NO_AUTH,					// 踢人者无踢人权限

		// 提升队长
		TEAM_NOTIFY_CHANGE_LEADER_SUCCESS = 25370,
		TEAM_NOTIFY_CHANGE_LEADER_OPER_NO_AUTH,				// 任命者无操作权限

		// 招募队员
		TEAM_NOTIFY_RECRUIT_SUCCESS = 25380,
		TEAM_NOTIFY_RECRUIT_OPER_NO_AUTH,					// 招募者无招募权限
		TEAM_NOTIFY_RECRUIT_OPER_IN_CD,						// 招募在CD中

		// 邀请入队
		TEAM_NOTIFY_INVITE_SUCCESS = 25390,
		TEAM_NOTIFY_INVITE_HAS_TEAM,						// 申请者已加入其他队伍
		TEAM_NOTIFY_INVITE_LEVEL_LIMIT,						// 申请者等级限制
		TEAM_NOTIFY_INVITE_MEMBER_FULL,						// 所申请的队伍已经满员了
		TEAM_NOTIFY_INVITE_TEAM_STATE_LIMIT,				// 队伍状态限制
		TEAM_NOTIFY_INVITE_OPER_NO_AUTH,					// 邀请人无权限
		TEAM_NOTIFY_INVITE_TARGET_NOT_EXIST ,				// 被邀人不存在
		TEAM_NOTIFY_INVITE_TEAM_IN_MATCH,					// 队伍状态限制
	};

	enum ETeamCheckCode
	{
		TEAM_CHECK_SUCCESSFUL = 0,

		TEAM_CHECK_INVITE_TARGET_HAS_TEAM = 25501,		// 被邀请者已在其他队伍中	
		TEAM_CHECK_INVITE_TARGET_NOT_IN_STAGE,			// 被邀请者不在本场景
		TEAM_CHECK_INVITE_TARGET_ARENA_1V1_NOT_OPEN,	// 被邀请者1v1竞技场未开放
		TEAM_CHECK_INVITE_TARGET_ARENA_3V3_NOT_OPEN,	// 被邀请者3v3竞技场未开放
		TEAM_CHECK_INVITE_TARGET_ARENA_5V5_NOT_OPEN,	// 被邀请者5v5竞技场未开放
		TEAM_CHECK_INVITE_TARGET_STAGE_NOT_OPEN,		// 被邀请者没有权限进入该场景
		TEAM_CHECK_INVITE_TARGET_REQ_ENTER_TIMES,		// 被邀请者进入魔王魂狱次数用完
		TEAM_CHECK_INVITE_TARGET_MATCHING,				// 被邀请者正在匹配魔王魂狱

		TEAM_CHECK_JOIN_ARENA_1V1_NOT_OPEN,				// 1v1竞技场未开放
		TEAM_CHECK_JOIN_ARENA_3V3_NOT_OPEN,				// 3v3竞技场未开放
		TEAM_CHECK_JOIN_ARENA_5V5_NOT_OPEN,				// 5v5竞技场未开放
		TEAM_CHECK_NOT_IN_MAJOR_CITY,					// 不在主城
		TEAM_CHECK_IN_CROSS_SERVER,						// 在天梯服中
		TEAM_CHECK_JOIN_STAGE_NOT_OPEN,					// 没有权限进入该场景
		TEAM_CHECK_REQ_ENTER_TIMES,						// 今日进入魔王魂狱次数用完
		TEAM_CHECK_MATCHING,							// 正在匹配魔王魂狱

		TEAM_CHECK_INVITE_TARGET_IN_ARENA,				// 被邀请者正在竞技场队伍中
		TEAM_CHECK_INVITE_TARGET_IN_ADVENTURE,			// 被邀请者正在探险队伍中
		TEAM_CHECK_INVITE_TARGET_IN_MD_DEVIL,			// 被邀请者正在魔王魂狱队伍中

		TEAM_CHECK_JOIN_HAS_TEAM,						// 申请者已加入其他队伍
		TEAM_CHECK_JOIN_ARENA_NOT_IN_MAJOR_CITY,		// 不在主城
		TEAM_CHECK_JOIN_MD_DEVIL_REQ_IN_OPEN_SCENE,		// 副本中不能进入魔王本队伍
		TEAM_CHECK_JOIN_ARENA_NOT_IN_OPEN_TIME,			// 不在开启时间
		TEAM_CHECK_JOIN_ARENA_HAS_ESCAPE_BUFF,			// 存在逃跑BUFF
		TEAM_CHECK_INVITE_ARENA_HAS_ESCAPE_BUFF,		// 存在逃跑BUFF

		TEAM_CHECK_INVITE_TARGET_IN_MD_WINTER,			// 被邀请者正在凛冬修练场队伍中
		TEAM_CHECK_JOIN_MD_WINTER_REQ_IN_OPEN_SCENE,	// 副本中不能进入凛冬队伍

		TEAM_CHECK_INVITE_TARGET_IN_MD_LONGYU,			// 被邀请者正在龙域守护队伍中
		TEAM_CHECK_JOIN_MD_LONGYU_REQ_IN_OPEN_SCENE,	// 副本中不能进入龙域守护队伍
		TEAM_CHECK_JOIN_BATTLE_NOT_IN_OPEN_TIME,		// 不在开启时间
		TEAM_CHECK_JOIN_BATTLE_HAS_ESCAPE_BUFF,			// 存在逃跑BUFF
		TEAM_CHECK_INVITE_BATTLE_HAS_ESCAPE_BUFF,		// 存在逃跑BUFF

		TEAM_CHECK_JOIN_ARENA_1V1_NOT_IN_OPEN_TIME = 25617,	// 1V1不在开启时间
		TEAM_CHECK_JOIN_ARENA_3V3_NOT_IN_OPEN_TIME = 25618,	// 3V3不在开启时间

		TEAM_CHECK_CREATE_SCENE_LIMIT			   = 25355, // 当前场景无法组队

		TEAM_CHECK_OPER_TEAM_CD					   = 150007, // 队伍操作cd时间未到
	};

	enum EUpdateTeamReason
	{
		UPDATE_TEAM_REASON_NONE = 0,		// 未知原因
		UPDATE_TEAM_REASON_NORMAL = 1,		// 正常更新
		UPDATE_TEAM_REASON_CREATED = 2,		// 新建队伍
		UPDATE_TEAM_REASON_DISMISS = 3,		// 解散队伍
		UPDATE_TEAM_REASON_INVITEE = 4,		// 邀请更新
		UPDATE_TEAM_REASON_JOIN = 5,		// 队员加入
		UPDATE_TEAM_REASON_QUIT = 6,		// 队员离开
	};

	// 同步给worldsrv的队伍信息
	struct SHumanTeamInfo
	{
		enum { ENTER = 0x01, LEAVE = 0x02, UPDATE = 0x04, };
		SHumanTeamInfo() { memset(this,0,sizeof(*this)); }

		sint64 tid;				// 队伍ID
		sint32 flag;			// 队员标记
		sint64 uids[32];		// 队员列表
		sint32 fp_limit;		// 要求战力
		char leader_name[max_name_len];		// 队长名字
		sint32 leader_lv;		// 队长等级
		bool bAutoJoin;			// 是否允许自动加入队伍
	};
}

#endif // _pw_team_const_
