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

	const int32 const_team_max_search_radius = 50;	// ���������������뾶����λ����
	const int32 const_team_max_event_radius = 5;	// ��Ա�ڰ뾶��Ч��Χ�ڹ��������¼�����λ����
	const int32 const_team_max_member = 3;			// Ұ������������
	const int32 const_team_max_drop_radius = 20;	// ��Ա��������뾶����λ����
	const int32 const_team_max_aura = 3;			// �������ӳ�buff����
	const int32 const_team_oper_cd = 60;			// �������CDʱ�䣬��λ����

	const int32 cst_team_aura = 90010003;		// ��Ӽӳ�buff

	// ��������
	enum ETeamType
	{
		TEAM_TYPE_UNKNOWN = 0,
		TEAM_TYPE_ARENA,		// ����������
		TEAM_TYPE_ADVENTURE,	// ̽�ն���
		TEAM_TYPE_MD_DEVIL,		// ħ����������
		TEAM_TYPE_MD_WINTER,	// �ݶ�����
		TEAM_TYPE_MD_LONGYU,	// �������
		TEAM_TYPE_BATTLE,		// ս������
		TEAM_TYPE_MD_SPANDEVIL, // ���ħ����
		TEAM_TYPE_WILD,			// Ұ�����
		TEAM_TYPE_PVE,			// ��������PVE

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
		TEAM_AUTH_NONE = 0x00,				// ��Ȩ��
		TEAM_AUTH_INVITE = 0x01,			// ����Ȩ��
		TEAM_AUTH_AGREE_JOIN = 0x02,		// ͬ�����Ȩ��

		TEAM_AUTH_ALL = 0xFF,				// ����Ȩ�� 
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
		TEAM_RECRUIT_WORLD = 0,	// ȫ������ 
		TEAM_RECRUIT_FRIEND,	// ��������
		TEAM_RECRUIT_GUILD,		// ��������
	
		TEAM_RECRUIT_NUM,
	};

	enum ETeamInjectEvent
	{
		TEAM_INJECT_EVENT_KILL_MONSTER, // ����ɱ�ּ���
		TEAM_INJECT_EVENT_DROP,			// �������
		TEAM_INJECT_EVENT_EXP,			// ������

		TEAM_INJECT_MAX,
	};

	enum ETeamOperType
	{
		TEAM_OPER_CHANG_FP,				// �ı�ս��
		TEAM_OPER_MEMBER_INVITE,		// �����Ա�������
		TEAM_OPER_AUTO_JOIN,			// �Ƿ������Զ����

		TEAM_OPER_MAX,
	};

	enum ETeamNearInfoType
	{
		TEAM_NEAR_TEAM,					// ����������Ϣ
		TEAM_NEAR_PLAYER,				// ���������Ϣ
		TEAM_VIEW_TEAM,					// ͬ����Ұ�ڶ�����Ϣ

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
	// �����Ա
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

		// ���ڿ���淨
		sint64 server_group;	// ԭ��ID
		sint64 server_tid;		// ԭ������ID
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

	// ������ӳ�Ա
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