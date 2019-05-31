#include "pw_ngs_common.h"
#ifndef _pw_stage_def_
#define _pw_stage_def_


namespace pwngs
{
	enum EStageInitCode
	{
		STAGE_INIT_NULL = 0,
		STAGE_INIT_DUNGEON_SCRIPT = 1,
		STAGE_INIT_DARK_ARENA = 2,
		STAGE_INIT_ARENA = 3,
		STAGE_INIT_BATTLE = 4,
		STAGE_INIT_TRIAL_LAND = 5,
		STAGE_INIT_MULTIPLAYER_DUNGEON = 6,
		STAGE_INIT_HELL_TRIAL = 7,
	};

	static const char* cst_stage_init_script_file = "s";
	static const char* cst_stage_init_script_vars = "v";
	static const char* cst_stage_init_script_vars_null = "";

	enum
	{
		DARKARENA_MONSTER_MAXNUM = 3,
	};

	struct SInitStageDarkArena
	{
		int monster_lev;
		int monster_group;
		int monster_types[DARKARENA_MONSTER_MAXNUM];
	};

	struct SInitStageArena
	{
		int32 arena_mode;
		int64 arena_teams[2];
		int64 arena_teammembers[2][5];
	};

	struct SInitStageDevil
	{
		int32 devil_mode;
		int64 devil_teams;
		int64 devil_teammembers[5];
	};

	struct SInitStageBattle
	{
		int32 battle_mode;
		int64 battle_teams[2];
		int64 battle_teammembers[2][32];
	};

	struct SInitStageTrialLand
	{
		int32 trial_id;
		int64 guild_id;
	};

	struct SInitStageMultiplayerDungeon
	{
		int64 team_member_ids[5];
		int32 team_member_levels[5];
	};

	struct SInitStageHellTrial
	{
		bool use_ticket;
		int32 round;
	};

	struct SInitStagePVE
	{
		int64 team_id;
	};

	// …Ò”” ‘¡∂
	struct SInitStageDungeonSY
	{
		int64 nGuildId;
	};

	// Ã‘Ã≠»¸
	struct SInitTTSDungeon
	{
		int64 nRedGuildId;
		char szRedGuildName[max_name_len];
		int64 nBlueGuildId;
		char szBlueGuildName[max_name_len];
	};
}

#endif // _pw_stage_def_