#ifndef _pw_service_Common_def_
#define _pw_service_Common_def_

#include "pw_def.h"
#include "pw_arena_def.h"
#include "pw_tx_def.h"

namespace pwngs
{
	struct HumanStatus
	{
		enum
		{
			UPDATE_WORLD_NODE = 0x0001,
			UPDATE_WORLD_PORT = 0x0002,
			UPDATE_LEVEL = 0x0004,
			UPDATE_ARENA = 0x0008,
			UPDATE_COMBAT_POINT = 0x0010,
			UPDATE_VIP_LEVEL = 0x0020,
			UPDATE_TITLE = 0x0040,
			UPDATE_ACHIEVEMENT = 0x0080,	
			UPDATE_BLOOD = 0x0100,
			UPDATE_LOGIN = 0x0200,
			UPDATE_LOGOUT = 0x0400,
			UPDATE_TENCENT = 0x0800,
			UPDATE_YZSL = 0x1000,
			UPDATE_HASCORE = 0x2000,
			UPDATE_HELLTRIAL = 0x4000,
			UPDATE_NAME = 0x8000,
			UPDATE_HATIMED = 0x10000,
		};

		enum
		{
			FLAGS_DROPPED	= 0x0001,
			FLAGS_FAKE		= 0x0002, // 假角色
		};
		
		HumanStatus()
		{
			this->Clear();
		}

		void Clear()
		{
			memset(this,0,sizeof(*this));
			nId = -1;
			nSocketId = -1;
		}
		
		//
		// 在worldsrv上的信息  
		//
		sint64 nId;					// 对象id  
		sint64 nStageId;			// 地图Id
		sint32 nBaseStageId;		// 地图配置id
		sint32 nStageSchemeType;	// 地图配置类型
		char szWorldNode[64];		// 对象所在节点  
		char szWorldPort[64];		// 对象所在线程  

		//
		// 在connsrv上的信息  
		// 
		sint64 nSocketId;			// socket id
		char szSocketNode[64];		// 套接字所在节点  
		char szSocketPort[64];		// 套接字所在线程  
		
		sint32 nLevel;				// 等级
		sint32 nSex;				// 性别
		sint16 nProfession;			// 职业
		sint32 nFightPoint;			// 战斗力
		sint32 nGemFightPoint;		// 宝石战力
		sint32 nDragonFightPoint;	// 龙总战力
		sint32 nRideFightPoint;		// 坐骑战力
		sint32 nMagicFightPoint;	// 技能总战力
		sint32 nWingFightPoint;		// 翅膀总战力
		sint32 nEquipFightPoint;		// 装备战力
		sint32 nPetFightPoint;		// 宠物总战力
		sint32 nHeroNewFightPoint;		// 新英雄总战力
		sint64 nTeamId;				// 队伍ID
		sint64 nServerGroup;		// 所在服务器组
		sint32 nTitle;				// 称号
		sint32 nZoneId;				// zoneid
		sint32 nHolyWeaponFightPoint; // 神器总战力
		sint32 nHeroStar;			// 英雄总星级
		sint32 nHeroCard;			// 英雄秘籍个数
		sint32 nLansquenetFightPoint;//侍从最高战力
		sint32 nMagicWeaponFightPoint;//法宝最高战力

		// 竞技场信息
		SHumanArenaInfo szArenaInfo[ARENA_MODE_NUM];
		// 成就信息
		sint32 nAchievementScore;	// 成就得分
		// 身上的血脉之力
		sint32 nBloodExp;			// 血脉之力总和
		
		sint64 nYZSLData;			// 勇者试炼挑战记录
		sint32 nHotActScore;		// 运营活动积分
		sint64 nHellTrialData;		// 地狱试炼挑战记录

		char szName[64];			// 名字
		char szLastLogin[32];		// 最近上线时刻
		char szLastLogout[32];		// 最近下线时刻
		char szAccount[64];
		char szIP[64];				// 登录ip
		int32 nVipLevel;			// vip等级,0=无

		uint32 nFlags;
		uint32 nClientType;
		char szAgent[64];
		bool InWorld;

		STencentUserInfo vTencentUserInfo;
	};
	
	const sint64 NULL_ID = 0;
	
	const int max_send_count = 3;
}

#endif //_pw_service_Common_def_