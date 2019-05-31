#ifndef _pwngs_def_123_
#define _pwngs_def_123_

#include <string>
#include "pw_def.h"

namespace pwngs
{
#pragma pack(push,1)
	struct MsgHeader
	{
#ifdef _MSC_VER
		uint32 len;
		uint32 mid;
#else
		uint32_t len;
		uint32_t mid;
#endif
	};

	struct MsgHeaderEx
	{
#ifdef _MSC_VER
		uint32 len;
		uint32 mid;
		uint32 seq;
#else
		uint32_t len;
		uint32_t mid;
		uint32_t seq;
#endif
	};
#pragma pack(pop)

	const size_t cst_tmp_buf_size  = ::cst_tmp_buf_size;

	const size_t cst_max_msg_size = 409600;
	
	const size_t npos = std::string::npos;

	const int64 cst_date_factor = 100000000;
	

// ------------------------------------------------

	const char cst_node_db[] = "dbsrv";
	const char cst_node_acc[] = "accsrv";
	const char cst_node_ctrl[] = "ctrlsrv";
	const char cst_node_conn_pattern[] = "connsrv";
	const char cst_node_login_node[] = "worldsrv0";
	const char cst_node_global[] = "globalsrv";

// ------------------------------------------------

	const char cst_port_worldsrv_pull[] = "worldsrv_pull";
	const char cst_port_worldsrv_login[] = "world_login";
	const char cst_port_ctrlsrv_pull[] = "ctrlsrv_pull";
	const char cst_port_ctrlsrv_guild[] = "ctrlsrv_guild";
	const char cst_port_ctrlsrv_common[] = "ctrlsrv_common";
	const char cst_port_ctrlsrv_relation[] = "ctrlsrv_relation";
	const char cst_port_ctrlsrv_dungeon[] = "ctrlsrv_dungeon";
	const char cst_port_ctrlsrv_activity[] = "ctrlsrv_action";
	const char cst_port_ctrlsrv_misc[] = "ctrlsrv_misc";
	const char cst_port_ctrlsrv_adventure[] = "ctrlsrv_adventure";
	const char cst_port_ctrlsrv_arena[] = "ctrlsrv_arena";
	const char cst_port_ctrlsrv_ranklist[] = "ctrlsrv_ranklist";
	const char cst_port_ctrlsrv_entrance_srv[] = "ctrlsrv_entrance_srv";
	const char cst_port_ctrlsrv_entrance_cli[] = "ctrlsrv_entrance_cli";
	const char cst_port_ctrlsrv_multiplayer_dungeon[] = "ctrlsrv_multiplayer_dungeon";
	const char cst_port_ctrlsrv_qlvh_log[] = "ctrlsrv_qlvh_log";
	const char cst_port_ctrlsrv_173[] = "ctrlsrv_173";
	const char cst_port_ctrlsrv_auction_house[] = "ctrlsrv_auction_house";
	const char cst_port_ctrlsrv_common_activity[] = "ctrlsrv_common_activity";
	const char cst_port_ctrlsrv_hot_activity[] = "ctrlsrv_hot_activity";
	const char cst_port_ctrlsrv_battle[] = "ctrlsrv_battle";
	const char cst_port_ctrlsrv_devil[] = "ctrlsrv_devil";
	const char cst_port_ctrlsrv_team[] = "ctrlsrv_team";
	const char cst_port_ctrlsrv_pve[] = "ctrlsrv_pve";
	const char cst_port_ctrlsrv_xiyou[] = "ctrlsrv_xiyou";
	const char cst_port_ctrlsrv_360[] = "ctrlsrv_360";

	const char cst_port_ctrlsrv_redenvelope[] = "ctrlsrv_redenvelope";
	//const char cst_port_ctrlsrv_memdb = "ctrlsrv_memdb";
	//const char cst_port_accsrv_wallow[] = "accsrv_wallow";

// 	const char cst_port_dbsrv_service[] = "dbsrv_service";
// 	const char cst_port_dbsrv_service_sql[] = "dbsrv_service_sql";
// 	const char cst_port_dbsrv_service_loader[] = "dbsrv_service_loader";

	const char cst_port_dbsrv_kv_service[] = "dbsrv_kv_service";
	const char cst_port_dbsrv_kv_service_loader[] = "dbsrv_kv_service_loader";

	const char cst_port_globalsrv_service[] = "globalsrv_service";

// ------------------------------------------------

	const char cst_node_worldsrv_fmt[] = "worldsrv";
	const char cst_port_worldsrv_fmt[] = "wsrv_";

	const char cst_node_worldsrv_gmstage[] = "worldsrv0";
	const char cst_port_worldsrv_gmstage[] = "wsrv_1";

	const char cst_port_connsrv_listener[] = "listener";
	const char cst_port_connsrv_websocketlistener[] = "websocketlistener";
	const char cst_port_connsrv_fmt[] = "service_";
	const char cst_port_accsrv_fmt[] = "service_";
	const char cst_port_worldsrv_map_fmt[] = "map_";

	// 账号zone分隔符
	const char cst_passport_split_zone[] = "%";
	// 账号agent分隔符
	const char cst_passport_split_agent[] = ";";

// ------------------------------------------------

	//const int max_dbsrv_service_port = 4;
#ifdef _DEBUG
	const int max_accsrv_service_port = 3;
#else
	const int max_accsrv_service_port = 3;
#endif
	const int max_connsrv_service_port = 8;

	const int max_characater_name_len = 12;
	const int min_characater_name_len = 1;

	const int32 cst_gm_stage_id = 99999;
	const int64 cst_dungeon_stage_start = 100*10000; // 副本起始id
	const int64 cst_subline_stage_start =  90*10000; // 分线起始id
	const int64 cst_dynamic_subline_stage_start =  5000*10000; // 动态分线起始id
	const int32 cst_sublineid_incrment_step =  1000; // 分线id增长步数

// ------------------------------------------------
	enum  KILL_CHARACTER_ERROR_CODE
	{
		// 踢人操作
		FAILED_KICK_SAME_CHARACTER_LOGIN = 1,			// 相同角色登陆
		FAILED_KICK_CHARACTER_LOGIN_RESULT1_TIMEOUT,		// 登陆操作1超时
		FAILED_KICK_CHARACTER_LOGIN_RESULT2_TIMEOUT,		// 登陆操作2超时
		FAILED_KICK_CHARACTER_LOGIN_RESULT3_TIMEOUT,		// 登陆操作3超时
		FAILED_KICK_CHARACTER_LOGIN_RESULT3_ERROR,		// 登陆操作3错误
		FAILED_KICK_CHARACTER_STAGE,
		FAILED_KICK_CHARACTER_LOCKED,					// 账号已锁定
		FAILED_KICK_TOOMANY_MESSAGE,
		FAILED_KICK_CHARACTER_NOEXISTS,					// 角色不存在
		KICK_CHARACTER_360,                            //360踢人
	};

	enum
	{
		LOGINTOSTAGE_FLAGS_RECONNECT = 0x0001,
		LOGINTOSTAGE_FLAGS_SWITCH_STAGE = 0x0002,
		LOGINTOSTAGE_FLAGS_DROPED = 0x0004,
		LOGINTOSTAGE_FLAGS_GM = 0x0008,
	};
	enum 
	{
		LEAVE_WORLD_COLLISION_CRASH = 0x0001,

		LEAVE_WORLD_SWITCH_STAGE = 0x0002,
		LEAVE_WORLD_KEEP_OBJECT = 0x0004,
		LEAVE_WORLD_DISCARD_POSTED = 0x0008,
		LEAVE_WORLD_DROPPED = 0x00010,
		LEAVE_WORLD_KILLED_DISAPPEAR = 0x0020,
		LEAVE_WORLD_KEEP_OBJECT_IN_STAGE = 0x0040,
		LEAVE_WORLD_DONTCALL_LEAVE_NOTIFY = 0x0080,
		LEAVE_WORLD_LADDER_PAUSE = 0x100,

		LEAVE_WORLD_CLIENT_MASK = LEAVE_WORLD_COLLISION_CRASH,

	};

	enum
	{
		KICK_FLAGS_PREPARE_REMOVED = 0x01,
	};
// ------------------------------------------------

}

#endif //_pwngs_def_123_
