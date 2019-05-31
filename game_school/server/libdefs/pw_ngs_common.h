#ifndef _pwngs_def_
#define _pwngs_def_

#include "pw_def.h"
#include "pwdist_def.h"
#include "pw_tx_def.h"

namespace pwngs
{

	// 开场动画英雄id
	const OBJID cst_hero_character_id = -1;


	// ------------------------------------------------
	// 连接对象的状态
	// ------------------------------------------------

	namespace connection
	{
		
		const int _StateLogin = 0; // 验证中
		
		const int _StateGate = 1; // 登录界面中
		
		const int _StatePlaying = 2; // 游戏中
		
		const int _StateLosted = 3; // 连接丢失/关闭
	}

	// ------------------------------------------------

	const int max_date_len = 32;
	const int max_name_len = pwdist::max_name_len;
	const int max_account_len = 64;

	// ------------------------------------------------

	enum
	{
		FATIGUE_STATUS_UNSET = 0,	// 未填写信息
		FATIGUE_STATUS_CHECK,		// 需要处理沉迷的账号
		FATIGUE_STATUS_LOOSE,		// 已验证,不需要沉迷
	};

	enum
	{
		FATIGUE_SWITCH_NORMAL = 0,		// 标准
		FATIGUE_SWITCH_ONLY_BEIJING,	// 仅对北京地区生效
		FATIGUE_SWITCH_CLOSE,			// 关闭防沉迷系统
	};

	struct ConnectionStatus
	{
		int  nState;
		char szAccount[max_account_len];
		char szWorldNode[max_name_len];
		char szWorldPort[max_name_len];
		char szSocketIP[max_name_len];
		sint16 nSocketPort;
		sint64 nWorldStage;
		sint64 nWorldObjid;
		sint32 nFatigue;
		sint32 nClientType;
		char szAgent[max_name_len];
		char szDeviceId[64];
		char szAdid[128];
		sint32 nZoneId;
		char exts[max_account_len];//西游网登陆传递的参数

		STencentUserInfo vTencentUserInfo;

		ConnectionStatus()
		{
			memset(this,0,sizeof(ConnectionStatus));
		}
	};

	//登陆信息
	struct SLoginToStage
	{
		sint64 id;
		sint64 socketId;
		char socketNode[64];
		char socketPort[64];
		char socketIp[max_name_len];
		sint32 flags;
		sint32 fatigue;

		float loc[3]; // 进入的位置
		float dir[3]; // 进入的方向
		char mac[max_name_len];
		int32 clientType;
		char device_id[64];
		char adid[64];

		STencentUserInfo vTencentUserInfo;
	};

	// 地图线程负载报告
	struct SStageThreadReport
	{
		sint32 updateDiff;
		sint32 stageCount;
		sint32 objectCount;
		sint32 humanCount;
		sint64 scriptMemoryUsed;
	};

	enum EStageFlags
	{
		STAGE_FLAG_DUNGEON	= 0x0001,
		STAGE_FLAG_SUBLINE	= 0x0002,
		STAGE_FLAG_ACTIVITY = 0x0004,
		STAGE_FLAG_VAIN = 0x0008,
	};

	enum EStageType
	{
		STAGE_TYPE_NORMAL,
		STAGE_TYPE_DUNGEON,
		STAGE_TYPE_SUBLINE,
		STAGE_TYPE_ACTIVITY,
	};
	
	enum EStageSchemeType
	{
		STAGE_SCHEME_TYPE_DUNGEON = 0,		// 副本
		STAGE_SCHEME_TYPE_NORMAL = 1,		// 野外
		STAGE_SCHEME_TYPE_MAJOR_CITY = 2,	// 主城
	};

	enum ESwitchStageType
	{
		SWITCH_TYPE_TRANSPORT,
		SWITCH_TYPE_ENTER_DUNGEON,
		SWITCH_TYPE_LEAVE_DUNGEON,
	};

	// CtrlSrv中SImplCommon线程内的管理器类型
	enum EImplCommonMgrType
	{
		SIMPL_COMMON_MGR_TYPE_CHAT = 1,	// 聊天管理器
		SIMPL_COMMON_MGR_TYPE_MAIL = 2,	// 邮件管理器
		SIMPL_COMMON_MGR_TYPE_QUEUE= 3, // 登陆排队管理器
		SIMPL_COMMON_MGR_TYPE_OPERATIONS = 4, // 操作列表
		SIMPL_COMMON_MGR_TYPE_NAME = 5, // 唯一名管理
		SIMPL_COMMON_MGR_TYPE_PASSPORT_OPERATIONS = 6, // 账号操作列表
		SIMPL_COMMON_MGR_TYPE_NOTIFY_BALL = 7,	// 消息球管理器
	};

	// 关系类型
	enum ERelation
	{
		RELATION_NONE = 0,
		RELATION_FOLLOW,		// 关注
		RELATION_FANS,			// 粉丝
		RELATION_BLOCK,			// 屏蔽

		RELATION_NUM,
	};

	// 关系成员状态
	enum ERelationMemberState
	{
		RELATION_MEMBER_STATE_OFFLINE,
		RELATION_MEMBER_STATE_IDLE,
		RELATION_MEMBER_STATE_BUSY,
	};

	// 魔王本匹配结果
	enum EMDMatchResult
	{
		MD_MATCH_RESULT_SUCCESSFUL = 0,		// 匹配成功
		MD_MATCH_RESULT_TIMEOUT,			// 匹配超时
		MD_MATCH_RESULT_INTERUPT,			// 匹配被中断
	};

	// 商店物品信息
	struct SShopItem
	{
		int32 cfgid;		//物品ID
		int32 count;		//物品数量
	};

	// 商城物品信息
	typedef struct SShopItem SMallItem;

	// 玩家名字查找表结构
	struct SHumanQuery
	{
		OBJID id;
		char name[max_name_len];
		char last_login[max_date_len];
		char profession;
		char sex;
		char passport[max_name_len];
		sint16 level;
	};
	//360GM用
	struct SHumanInfo360
	{
		OBJID id;
		char passport[max_name_len];
		char name[max_name_len];
		char last_login[max_date_len];
		char last_logout[max_date_len];
		int64 online_total_time;
		char   profession[max_name_len];
		uint8   sex;
		int16   level;
		int64   curExp;
		int64   levelNeedExp;
		int64   giftGold;//绑定元宝
		int64   gold;//元宝
		int64   silver;//银币
		int64   chargeMoney;
		int32   gmStatus;
		int32   loc_stage;
		float   loc_x;
		float   loc_y;
		int64   locked_time;
		int64   locked_chat_time;
		int32   zoneid;
		int64	create_ctime;
		int32	viplevel;
		int64	last_fightpoint;//战力
		char	last_login_ip[max_name_len];
	};

	struct SCreateCharacter
	{
		char account[max_name_len];
		char name[max_name_len];
		char profession;
		char sex;
		int32 stage;
		float loc[3];
		float dir[3];
		char agent[max_name_len];
		int32 zoneid;
		int64 last_program_id;
		char exts[max_name_len];//西游网附加参数
	};
#pragma pack(push,1)
	// 跨服传送数据角色信息
	struct SEntranceHumanInformation
	{
		int64 id;
		int32 server_group;
		char server_name[max_name_len];
		char account[max_name_len];
		char name[max_name_len];
		char profession;
		char sex;

		// 角色在队伍中的权限与标记
		int32 team_auth;
		int32 team_flag;
	};
#pragma pack(pop)

	struct SEntranceServerConfig
	{
		char name[max_name_len];
		char addr[max_name_len];
		int  port;
	};

	struct SEntranceRestoringTeamMember
	{
		enum { FLAGS_RESTORE_SENT = 0x01 };

		int64 id;
		int32 flags;
		int32 server_group;

		// 权限与标记
		int32 team_auth;
		int32 team_flag;
	};

	struct SEntranceRestoringTeam
	{
		int64 leader;
		int32 teamMgrId;
		int32 membersNum;
		SEntranceRestoringTeamMember members[40];
		int64 timeout;
	};

	struct SServerInfo
	{
// 		int64 id;
		int64 zoneid;
		char szPerfixName[128]; // 前缀名字
		char szServerName[128]; // 服务器名字
	};

	enum EGlobalRankType
	{
		GLOBAL_RANK_TYPE_YZSL = 1,			// 勇者试炼排行榜
		GLOBAL_RANK_TYPE_HASCORE = 2,		// 活动积分排行榜
		GLOBAL_RANK_TYPE_HELL_TRIAL = 3,	// 地狱试炼排行榜

		GLOBAL_RANK_TYPE_NUM,
	};
 
	const int cst_global_rank_count = 500;
}
#endif //_pwngs_def_
