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

		// 天梯服需要同步给本地服的角色信息
		enum ESyncLadderHumanFlags
		{
			LADDER_SYNC_HUMAN_ARENA_ENTER,			// 进入场景
			LADDER_SYNC_HUMAN_ARENA_BEGAN,			// 开始比赛
			LADDER_SYNC_HUMAN_ARENA_ENDED,			// 结束比赛
			LADDER_SYNC_HUMAN_ARENA_ABORT,			// 中止比赛
			LADDER_SYNC_HUMAN_ARENA_LEAVE,			// 离开比赛

			LADDER_SYNC_HUMAN_BATTLE_ENTER,			// 进入场景
			LADDER_SYNC_HUMAN_BATTLE_ENDED,			// 战场结束
			LADDER_SYNC_HUMAN_BATTLE_LEAVE,			// 离开战场

			LADDER_SYNC_HUMAN_DEVIL_ENTER,			// 进入魔王本
			LADDER_SYNC_HUMAN_DEVIL_ENDED,			// 结束比赛
			LADDER_SYNC_HUMAN_DEVIL_LEAVE,			// 离开魔王本

			LADDER_SYNC_HUMAN_PVE_ENTER,			// 进入PVE襄阳守卫
			LADDER_SYNC_HUMAN_PVE_ENDED,			// 结束PVE襄阳守卫
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

		// 天梯服需要同步给本地服的队伍信息
		enum ESyncLadderTeamFlags
		{
			LADDER_SYNC_TEAM_ARENA_ACKBEG,			// 开始确认
			LADDER_SYNC_TEAM_ARENA_ACKEND,			// 结束确认
			LADDER_SYNC_TEAM_ARENA_ACKNUM,			// 确认数量

			LADDER_SYNC_TEAM_BATTLE_ACKBEG,			// 开始确认
			LADDER_SYNC_TEAM_BATTLE_ACKEND,			// 结束确认

			LADDER_SYNC_TEAM_DEVIL_ACKBEG,			// 开始确认
			LADDER_SYNC_TEAM_DEVIL_ACKEND,			// 结束确认

			LADDER_SYNC_TEAM_PVE_ACKBEG,			// 开始确认
			LADDER_SYNC_TEAM_PVE_ACKEND,			// 结束确认
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

		// 本地服需要同步给天梯服的角色信息
		enum ESyncNormalHumanFlags
		{
			NORMAL_SYNC_HUMAN_TEST,
		};

		struct SSyncNormalHumanInfo
		{
			sint32 test;
		};

		// 本地服需要同步给天梯服的队伍信息
		enum ESyncNormalTeamFlags
		{
			NORMAL_SYNC_TEAM_RESTORE_TEAMS,			// 上传队伍
			NORMAL_SYNC_TEAM_ARENA_FLAGS,			// 同步标记
			NORMAL_SYNC_TEAM_LEAVE,					// 离开队伍
			NORMAL_SYNC_TEAM_DEVIL_START,			// 天梯魔王本开始
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

		// 神佑排行数据
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

			int32 nWarZoneId;	//战区
			int64 nGuildId;	//联盟id
			char szGuildName[max_name_len];	//联盟名称
			int64 nTotalDamage;	//伤害总值
			int32 nTotalFight;	//总战力
		};

		// 淘汰赛数据
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

			int32 nWarZoneId;	//战区
			int64 nGuildId;	//联盟id
			char szGuildName[max_name_len];	//联盟名称
			int32 nRound;	//轮数
			int64 nBaseMapId;
			int64 nGameMapId;
			int32 nRanking;	//名次
			int32 nTotalFight;	//总战力
		};

		// 淘汰赛数据列表
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