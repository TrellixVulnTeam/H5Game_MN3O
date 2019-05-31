#ifndef _pw_team_def_h_
#define _pw_team_def_h_

#include "pw_def.h"
#include "pw_ngs_common.h"
#include "pw_arena_def.h"
#include "pw_human_status.h"
#include "pw_ngs_def.h"

namespace pwngs
{
	class Team;
	class TeamMgr;

	const int32 const_team_max_search_radius = 50;	// 搜索附近区域队伍半径，单位：米
	const int32 const_team_max_event_radius = 5;	// 队员在半径有效范围内共享数据事件，单位：米
	const int32 const_team_max_member = 3;			// 野外队伍最多人数
	const int32 const_team_max_drop_radius = 20;	// 队员最大共享掉落半径，单位：米
	const int32 const_team_max_aura = 3;			// 队伍最大加成buff数量
	const int32 const_team_oper_cd = 60;			// 队伍操作CD时间，单位：秒

	const int32 cst_team_aura = 90010003;		// 组队加成buff

	// 队伍类型
	enum ETeamType
	{
		TEAM_TYPE_UNKNOWN = 0,
		TEAM_TYPE_ARENA,		// 竞技场队伍
		TEAM_TYPE_ADVENTURE,	// 探险队伍
		TEAM_TYPE_MD_DEVIL,		// 魔王本本队伍
		TEAM_TYPE_MD_WINTER,	// 凛冬队伍
		TEAM_TYPE_MD_LONGYU,	// 龙域队伍
		TEAM_TYPE_BATTLE,		// 战场队伍
		TEAM_TYPE_MD_SPANDEVIL, // 跨服魔王本
		TEAM_TYPE_WILD,			// 野外队伍
		TEAM_TYPE_PVE,			// 襄阳守卫PVE

		TEAM_TYPE_NUM,
	};

	enum ETeamOper
	{
		TEAM_OPER_CREATE = 0,
		TEAM_OPER_JOIN,
		TEAM_OPER_INVITE,
		TEAM_OPER_INVITE_RETURN,
		TEAM_OPER_LEAVE,

		TEAM_OPER_NUM,
	};

	enum ETeamAuth
	{
		TEAM_AUTH_NONE = 0x00,				// 无权限
		TEAM_AUTH_INVITE = 0x01,			// 邀请权限
		TEAM_AUTH_AGREE_JOIN = 0x02,		// 同意加入权限

		TEAM_AUTH_ALL = 0xFF,				// 所有权限 
	};

	enum ETeamInviteeState
	{
		TEAM_INVITEE_STATE_WAIT = 0,
	};

	enum ETeamInviteeReturn
	{
		TEAM_INVITEE_RETURN_REFUSE = 0,
		TEAM_INVITEE_RETURN_ACCEPT,
	};

	enum ETeamRecruitType
	{
		TEAM_RECRUIT_WORLD = 0,	// 全服邀请 
		TEAM_RECRUIT_FRIEND,	// 好友邀请
		TEAM_RECRUIT_GUILD,		// 公会邀请
	
		TEAM_RECRUIT_NUM,
	};

	enum ETeamInjectEvent
	{
		TEAM_INJECT_EVENT_KILL_MONSTER, // 共享杀怪计数
		TEAM_INJECT_EVENT_DROP,			// 共享掉落
		TEAM_INJECT_EVENT_EXP,			// 共享经验

		TEAM_INJECT_MAX,
	};

	enum ETeamOperType
	{
		TEAM_OPER_CHANG_FP,				// 改变战力
		TEAM_OPER_MEMBER_INVITE,		// 允许成员邀请入队
		TEAM_OPER_AUTO_JOIN,			// 是否允许自动入队

		TEAM_OPER_MAX,
	};

	enum ETeamNearInfoType
	{
		TEAM_NEAR_TEAM,					// 附近队伍信息
		TEAM_NEAR_PLAYER,				// 附近玩家信息
		TEAM_VIEW_TEAM,					// 同步视野内队伍信息

		TEAM_NEAR_MAX,
	};

	enum ETeamLeaveOperType
	{
		TEAM_LEAVE_INVITE,
		TEAM_LEAVE_JOIN,
	};

	#define make_team_mgrid(tid)				((tid) >> 32)
	#define make_team_type(tid)					((tid >> 56) & 0xFF)
	#define make_team_mode(tid)					((tid >> 48) & 0xFF)
	#define make_team_reserved(tid)				((tid >> 32) & 0xFFFF)

	#define make_team_type_by_mgrid(mgrid)		((mgrid) >> 24)
	#define make_team_mode_by_mgrid(mgrid)		((mgrid >> 16) & 0xFF)
	#define make_team_reserved_by_mgrid(mgrid)	((mgrid) & 0xFFFF)

#pragma pack(push,1)
	// 队伍成员
	struct STeamMember
	{
		sint64 uid;
		char uname[max_name_len];
		sint16 level;
		sint16 sex;
		sint16 pro;
		sint32 fight_point;
		sint32 flag;
		sint32 auth;
		bool inworld;
		sint64 context;
		sint32 max_hp;
		sint32 cur_hp;

		// 用于跨服玩法
		sint64 server_group;	// 原服ID
		sint64 server_tid;		// 原服队伍ID
		SHumanArenaInfo arena[ARENA_MODE_NUM];

		STeamMember()
		{
			memset(this,0,sizeof(*this));
		}

		STeamMember(const HumanStatus& status,sint64 tid)
		{
			uid = status.nId;
			memcpy(uname,status.szName,sizeof(uname));
			level = status.nLevel;
			sex = status.nSex;
			pro = status.nProfession;
			fight_point = status.nFightPoint;
			flag = 0;
			auth = 0;
			inworld = status.InWorld;
			context = 0;
			memcpy(arena,status.szArenaInfo,sizeof(arena));
			server_group = status.nServerGroup;
			server_tid = tid;
		}
	};
#pragma pack(pop)

	// 被邀入队成员
	struct STeamInvitee
	{
		sint64 uid;
		char uname[max_name_len];
		sint64 operid;
		sint32 state;
	};

	struct SArenaMatchParams
	{
		sint32 minMatchPoint;
		sint32 maxMatchPoint;
		sint32 minMatchLevel;
		sint32 maxMatchLevel;
	};

	typedef std_unordered_map<sint64,std::vector<sint64> > CollectionNormalTeamsT;

}

#endif //_pw_team_def_h_