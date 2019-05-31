#include "pw_ngs_common.h"
#ifndef _pw_team_const_
#define _pw_team_const_

namespace pwngs
{

	enum ETeamNotifyCode
	{
		TEAM_NOTIFY_SUCCESS = 0,

		// ͨ�ô���
		TEAM_NOTIFY_COMMON_OFFLINE = 25201,
		TEAM_NOTIFY_COMMON_MEMBER_ADDED,					// ������鲻�ɹ���ϵͳԭ��
		TEAM_NOTIFY_COMMON_MEMBER_DELED,					// �뿪���鲻�ɹ���ϵͳԭ��
		TEAM_NOTIFY_COMMON_MEMBER_NOT_EXIST,				// ���޴��ˣ�ϵͳԭ��
		TEAM_NOTIFY_COMMON_TEAM_NOT_EXIST,					// Ҫ�����Ķ��鲻����
		TEAM_NOTIFY_COMMON_INVALID_TID,						// ��Ч�Ķ���ID
		TEAM_NOTIFY_COMMON_TEAM_CREATING,					// ���ڴ���������
		TEAM_NOTIFY_COMMON_TEAM_JOINING,					// ���ڼ��������
		TEAM_NOTIFY_COMMON_HAS_OTHER_TEAM,					// �Ѿ��ڶ���״̬
		TEAM_NOTIFY_COMMON_INVITE_HAS_OTHER_TEAM = 25210,	// ����ʱ�ڶ���״̬
		TEAM_NOTIFY_COMMON_NOT_CHANGE_TEAM = 25211,			// ����ת������

		// ��������
		TEAM_NOTIFY_CREATE_SUCCESS = 25300,
		TEAM_NOTIFY_CREATE_HAS_TEAM,						// �������Ѽ�����������
		TEAM_NOTIFY_CREATE_LEVEL_LIMIT,						// �����ߵȼ�����
		TEAM_NOTIFY_CREATE_GOLD_LIMIT,						// �����߽������
		TEAM_NOTIFY_CREATE_VIP_LIMIT,						// ������VIP����
		TEAM_NOTIFY_CREATE_NAME_LIMIT,						// �������ֲ����ظ�
		TEAM_NOTIFY_CREATE_MAJOR_CITY_LIMIT,				// �����߱���������

		TEAM_NOTIFY_INVITE_HAD_INVITED,						// �Ѿ��������

		// ��ɢ����
		TEAM_NOTIFY_DISMISS_SUCCESS = 25320,
		TEAM_NOTIFY_DISMISS_TEAM_STATE_LIMIT,				// ����״̬����

		// �������
		TEAM_NOTIFY_JOIN_SUCCESS = 25330,
		TEAM_NOTIFY_JOIN_HAS_TEAM,							// �������Ѽ�����������
		TEAM_NOTIFY_JOIN_LEVEL_LIMIT,						// �����ߵȼ�����
		TEAM_NOTIFY_JOIN_MEMBER_FULL,						// ������Ķ����Ѿ���Ա��
		TEAM_NOTIFY_JOIN_TEAM_STATE_LIMIT,					// ����״̬����
		TEAM_NOTIFY_JOIN_MAJOR_CITY_LIMIT,					// ��Ա����������
		TEAM_NOTIFY_JOIN_CHANGE_TEAM_STATE_LIMIT,			// ����״̬����
		TEAM_NOTIFY_JOIN_ARENA_MAJOR_CITY_LIMIT,			// ��Ա����������
		TEAM_NOTIFY_JOIN_FIGHT_POINT_LIMIT,					// ������ս��������

		// �뿪����
		TEAM_NOTIFY_LEAVE_SUCCESS = 25350,
		TEAM_NOTIFY_LEAVE_COMMANDER_LIMIT,					// �ӳ������뿪
		TEAM_NOTIFY_LEAVE_TEAM_STATE_LIMIT,					// ����״̬����
		TEAM_NOTIFY_LEAVE_TEAM_MDUNGEON_LIMIT,				// ħ���������������˶�

		// �߳�����
		TEAM_NOTIFY_KICKED_SUCCESS = 25360,
		TEAM_NOTIFY_KICKED_OPER_NO_AUTH,					// ������������Ȩ��

		// �����ӳ�
		TEAM_NOTIFY_CHANGE_LEADER_SUCCESS = 25370,
		TEAM_NOTIFY_CHANGE_LEADER_OPER_NO_AUTH,				// �������޲���Ȩ��

		// ��ļ��Ա
		TEAM_NOTIFY_RECRUIT_SUCCESS = 25380,
		TEAM_NOTIFY_RECRUIT_OPER_NO_AUTH,					// ��ļ������ļȨ��
		TEAM_NOTIFY_RECRUIT_OPER_IN_CD,						// ��ļ��CD��

		// �������
		TEAM_NOTIFY_INVITE_SUCCESS = 25390,
		TEAM_NOTIFY_INVITE_HAS_TEAM,						// �������Ѽ�����������
		TEAM_NOTIFY_INVITE_LEVEL_LIMIT,						// �����ߵȼ�����
		TEAM_NOTIFY_INVITE_MEMBER_FULL,						// ������Ķ����Ѿ���Ա��
		TEAM_NOTIFY_INVITE_TEAM_STATE_LIMIT,				// ����״̬����
		TEAM_NOTIFY_INVITE_OPER_NO_AUTH,					// ��������Ȩ��
		TEAM_NOTIFY_INVITE_TARGET_NOT_EXIST ,				// �����˲�����
		TEAM_NOTIFY_INVITE_TEAM_IN_MATCH,					// ����״̬����
	};

	enum ETeamCheckCode
	{
		TEAM_CHECK_SUCCESSFUL = 0,

		TEAM_CHECK_INVITE_TARGET_HAS_TEAM = 25501,		// ����������������������	
		TEAM_CHECK_INVITE_TARGET_NOT_IN_STAGE,			// �������߲��ڱ�����
		TEAM_CHECK_INVITE_TARGET_ARENA_1V1_NOT_OPEN,	// ��������1v1������δ����
		TEAM_CHECK_INVITE_TARGET_ARENA_3V3_NOT_OPEN,	// ��������3v3������δ����
		TEAM_CHECK_INVITE_TARGET_ARENA_5V5_NOT_OPEN,	// ��������5v5������δ����
		TEAM_CHECK_INVITE_TARGET_STAGE_NOT_OPEN,		// ��������û��Ȩ�޽���ó���
		TEAM_CHECK_INVITE_TARGET_REQ_ENTER_TIMES,		// �������߽���ħ��������������
		TEAM_CHECK_INVITE_TARGET_MATCHING,				// ������������ƥ��ħ������

		TEAM_CHECK_JOIN_ARENA_1V1_NOT_OPEN,				// 1v1������δ����
		TEAM_CHECK_JOIN_ARENA_3V3_NOT_OPEN,				// 3v3������δ����
		TEAM_CHECK_JOIN_ARENA_5V5_NOT_OPEN,				// 5v5������δ����
		TEAM_CHECK_NOT_IN_MAJOR_CITY,					// ��������
		TEAM_CHECK_IN_CROSS_SERVER,						// �����ݷ���
		TEAM_CHECK_JOIN_STAGE_NOT_OPEN,					// û��Ȩ�޽���ó���
		TEAM_CHECK_REQ_ENTER_TIMES,						// ���ս���ħ��������������
		TEAM_CHECK_MATCHING,							// ����ƥ��ħ������

		TEAM_CHECK_INVITE_TARGET_IN_ARENA,				// �����������ھ�����������
		TEAM_CHECK_INVITE_TARGET_IN_ADVENTURE,			// ������������̽�ն�����
		TEAM_CHECK_INVITE_TARGET_IN_MD_DEVIL,			// ������������ħ������������

		TEAM_CHECK_JOIN_HAS_TEAM,						// �������Ѽ�����������
		TEAM_CHECK_JOIN_ARENA_NOT_IN_MAJOR_CITY,		// ��������
		TEAM_CHECK_JOIN_MD_DEVIL_REQ_IN_OPEN_SCENE,		// �����в��ܽ���ħ��������
		TEAM_CHECK_JOIN_ARENA_NOT_IN_OPEN_TIME,			// ���ڿ���ʱ��
		TEAM_CHECK_JOIN_ARENA_HAS_ESCAPE_BUFF,			// ��������BUFF
		TEAM_CHECK_INVITE_ARENA_HAS_ESCAPE_BUFF,		// ��������BUFF

		TEAM_CHECK_INVITE_TARGET_IN_MD_WINTER,			// �������������ݶ�������������
		TEAM_CHECK_JOIN_MD_WINTER_REQ_IN_OPEN_SCENE,	// �����в��ܽ����ݶ�����

		TEAM_CHECK_INVITE_TARGET_IN_MD_LONGYU,			// �����������������ػ�������
		TEAM_CHECK_JOIN_MD_LONGYU_REQ_IN_OPEN_SCENE,	// �����в��ܽ��������ػ�����
		TEAM_CHECK_JOIN_BATTLE_NOT_IN_OPEN_TIME,		// ���ڿ���ʱ��
		TEAM_CHECK_JOIN_BATTLE_HAS_ESCAPE_BUFF,			// ��������BUFF
		TEAM_CHECK_INVITE_BATTLE_HAS_ESCAPE_BUFF,		// ��������BUFF

		TEAM_CHECK_JOIN_ARENA_1V1_NOT_IN_OPEN_TIME = 25617,	// 1V1���ڿ���ʱ��
		TEAM_CHECK_JOIN_ARENA_3V3_NOT_IN_OPEN_TIME = 25618,	// 3V3���ڿ���ʱ��

		TEAM_CHECK_CREATE_SCENE_LIMIT			   = 25355, // ��ǰ�����޷����

		TEAM_CHECK_OPER_TEAM_CD					   = 150007, // �������cdʱ��δ��
	};

	enum EUpdateTeamReason
	{
		UPDATE_TEAM_REASON_NONE = 0,		// δ֪ԭ��
		UPDATE_TEAM_REASON_NORMAL = 1,		// ��������
		UPDATE_TEAM_REASON_CREATED = 2,		// �½�����
		UPDATE_TEAM_REASON_DISMISS = 3,		// ��ɢ����
		UPDATE_TEAM_REASON_INVITEE = 4,		// �������
		UPDATE_TEAM_REASON_JOIN = 5,		// ��Ա����
		UPDATE_TEAM_REASON_QUIT = 6,		// ��Ա�뿪
	};

	// ͬ����worldsrv�Ķ�����Ϣ
	struct SHumanTeamInfo
	{
		enum { ENTER = 0x01, LEAVE = 0x02, UPDATE = 0x04, };
		SHumanTeamInfo() { memset(this,0,sizeof(*this)); }

		sint64 tid;				// ����ID
		sint32 flag;			// ��Ա���
		sint64 uids[32];		// ��Ա�б�
		sint32 fp_limit;		// Ҫ��ս��
		char leader_name[max_name_len];		// �ӳ�����
		sint32 leader_lv;		// �ӳ��ȼ�
		bool bAutoJoin;			// �Ƿ������Զ��������
	};
}

#endif // _pw_team_const_
