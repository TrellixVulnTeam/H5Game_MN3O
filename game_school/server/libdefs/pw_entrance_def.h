#ifndef _pw_entrance_def_
#define _pw_entrance_def_

#include "pw_types.h"
#include "pw_socket_stream_pump.h"
#include "pw_ngs_common.h"
#include "pw_team_def.h"

namespace pwngs
{
	namespace entrance
	{
		const int msgid_cs_authorization = 100;

		const int cst_entrance_client_bufsize = 2 * 1024 * 1024;

		const char cst_entrance_secret_key[] = "@$()*&(@@(*#KJ@KJJKas=-dlkak";

		enum
		{
			ERROR_INVALID_RESTORE_ID = 46000,
			ERROR_ENTRANCE_TIMEOUT,
			ERROR_TRANSMIT_TIMEOUT,
			ERROR_RESTORE_TEAM_TIMEOUT,
			ERROR_RESTORE_TEAM_CHECK_TIMEOUT,
			ERROR_LADDER_SERVER_NOT_OPEN,
			ERROR_LADDER_SERVER_CONNECT_FAILED,
			ERROR_LADDER_QUERY_CHARS_FAILED,
			ERROR_LADDER_VERIFY_LOGIN_FAILED,
			ERROR_LADDER_TRANSMIT_NOT_IN_MAJOR_CITY,
		};

		const int max_level = 3;

#pragma pack(push,1)
		struct Msg : public pwutils::SPacketHeader
		{
		};

		struct MsgAuthorization : public Msg
		{
			int64 server_group;
			char  secret_value[max_name_len];
		};

#pragma pack(pop)

		struct SEntranceDesc
		{
			int64 pid;
			int32 level;
			int64 team_leader;
			int32 team_mgrid;
		};

#pragma pack(push,1)

		// ���ݷ���Ҫͬ�������ط��Ľ�ɫ��Ϣ
		enum ESyncLadderHumanFlags
		{
			LADDER_SYNC_HUMAN_ARENA_ENTER,			// ���볡��
			LADDER_SYNC_HUMAN_ARENA_BEGAN,			// ��ʼ����
			LADDER_SYNC_HUMAN_ARENA_ENDED,			// ��������
			LADDER_SYNC_HUMAN_ARENA_ABORT,			// ��ֹ����
			LADDER_SYNC_HUMAN_ARENA_LEAVE,			// �뿪����

			LADDER_SYNC_HUMAN_BATTLE_ENTER,			// ���볡��
			LADDER_SYNC_HUMAN_BATTLE_ENDED,			// ս������
			LADDER_SYNC_HUMAN_BATTLE_LEAVE,			// �뿪ս��

			LADDER_SYNC_HUMAN_DEVIL_ENTER,			// ����ħ����
			LADDER_SYNC_HUMAN_DEVIL_ENDED,			// ��������
			LADDER_SYNC_HUMAN_DEVIL_LEAVE,			// �뿪ħ����

			LADDER_SYNC_HUMAN_PVE_ENTER,			// ����PVE��������
			LADDER_SYNC_HUMAN_PVE_ENDED,			// ����PVE��������
		};

		struct SSyncLadderHumanInfo
		{
			sint32 arena_mode;
			sint32 arena_result;
			sint32 arena_kill_num;
			sint32 arena_dead_num;
			sint32 team_flags;
			sint32 arena_anti_point;

			sint64 ladder_basemap;
			sint64 ladder_gamemap;
			sint32 battle_result;
			sint32 battle_rank;
			sint64 devil_cleartime ;
		};

		// ���ݷ���Ҫͬ�������ط��Ķ�����Ϣ
		enum ESyncLadderTeamFlags
		{
			LADDER_SYNC_TEAM_ARENA_ACKBEG,			// ��ʼȷ��
			LADDER_SYNC_TEAM_ARENA_ACKEND,			// ����ȷ��
			LADDER_SYNC_TEAM_ARENA_ACKNUM,			// ȷ������

			LADDER_SYNC_TEAM_BATTLE_ACKBEG,			// ��ʼȷ��
			LADDER_SYNC_TEAM_BATTLE_ACKEND,			// ����ȷ��

			LADDER_SYNC_TEAM_DEVIL_ACKBEG,			// ��ʼȷ��
			LADDER_SYNC_TEAM_DEVIL_ACKEND,			// ����ȷ��

			LADDER_SYNC_TEAM_PVE_ACKBEG,			// ��ʼȷ��
			LADDER_SYNC_TEAM_PVE_ACKEND,			// ����ȷ��
		};

		struct SSyncLadderTeamInfo
		{
			sint64 team_id;
			sint64 matched_team_id;
			sint32 ack_result;
			sint32 arena_navi_acknum;
			sint32 arena_anti_acknum;
			sint32 arena_navi_profs[3];
			sint32 arena_anti_profs[3];
		};

		struct SSyncLadderTeamReward
		{
			sint64 team_id;
			sint32 rank;
			sint64 hid;
			bool bSucc;
		};

		// ���ط���Ҫͬ�������ݷ��Ľ�ɫ��Ϣ
		enum ESyncNormalHumanFlags
		{
			NORMAL_SYNC_HUMAN_TEST,
		};

		struct SSyncNormalHumanInfo
		{
			sint32 test;
		};

		// ���ط���Ҫͬ�������ݷ��Ķ�����Ϣ
		enum ESyncNormalTeamFlags
		{
			NORMAL_SYNC_TEAM_RESTORE_TEAMS,			// �ϴ�����
			NORMAL_SYNC_TEAM_ARENA_FLAGS,			// ͬ�����
			NORMAL_SYNC_TEAM_LEAVE,					// �뿪����
			NORMAL_SYNC_TEAM_DEVIL_START,			// ����ħ������ʼ
		};

		struct SSyncNormalTeamInfo
		{
			sint64 team_id;
			STeamMember members[5];
			sint64 leavers[5];
			sint32 ladder_level;
		};

		enum ELadderLevel
		{
			LADDER_LEVEL_0,
			LADDER_LEVEL_1,
		};

		// ������������
		struct SYRankInfo
		{
			SYRankInfo()
				: nWarZoneId(0)
				, nGuildId(0)
				, nTotalDamage(0)
				, nTotalFight(0)
			{
				szGuildName[0] = '\0';
			}

			void SetGuildName(const char *pGuildName)
			{
				if (pGuildName)
				{
					memcpy(this->szGuildName, pGuildName, __min(max_name_len, strlen(pGuildName) + 1));
				}
			}

			int32 nWarZoneId;	//ս��
			int64 nGuildId;	//����id
			char szGuildName[max_name_len];	//��������
			int64 nTotalDamage;	//�˺���ֵ
			int32 nTotalFight;	//��ս��
		};

		// ��̭������
		struct STTSInfo
		{
			STTSInfo()
				: nWarZoneId(0)
				, nGuildId(0)
				, nRound(0)
				, nBaseMapId(0)
				, nGameMapId(0)
				, nRanking(0)
				, nTotalFight(0)
			{
				szGuildName[0] = '\0';
			}

			void Clear()
			{
				nWarZoneId = 0;
				nGuildId = 0;
				szGuildName[0] = '\0';
				nRound = 0;
				nBaseMapId = 0;
				nGameMapId = 0;
				nRanking = 0;
				nTotalFight = 0;
			}

			void SetGuildName(const char *pGuildName)
			{
				if (pGuildName)
				{
					memcpy(this->szGuildName, pGuildName, __min(max_name_len, strlen(pGuildName) + 1));
				}
			}

			int32 nWarZoneId;	//ս��
			int64 nGuildId;	//����id
			char szGuildName[max_name_len];	//��������
			int32 nRound;	//����
			int64 nBaseMapId;
			int64 nGameMapId;
			int32 nRanking;	//����
			int32 nTotalFight;	//��ս��
		};

		// ��̭�������б�
		struct STTSInfoList
		{
			STTSInfoList()
				: nUsedCount(0)
			{
			}

			void Clear()
			{
				for (int i = 0; i < STTSInfoList::MaxSize; ++i)
				{
					this->tts[i].Clear();
				}
			}

			static const int32 MaxSize = 16;
			int32 nUsedCount;
			STTSInfo tts[MaxSize];
		};

#pragma pack(pop)

	}
}

#endif // _pw_entrance_def_