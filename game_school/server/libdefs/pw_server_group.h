#ifndef _pw_server_group_
#define _pw_server_group_

#include "pw_types.h"
#include <string>
#include "pw_wlog_def.h"

extern std::string g_strVersion;
extern uint32 g_nBuildNO;

namespace pwngs
{
	enum
	{
		LIANYUN_MASK_PUSH_HUMAN = 0x0001,
		LIANYUN_MASK_PUSH_CHATMSG = 0x0002,
		LIANYUN_MASK_SERVERINFO = 0x0100,
	};

	extern int64 g_nServerGroup;
	extern bool g_bLadderServer;
	extern bool g_bLadderTest;
	extern bool g_bBISend;
	extern bool g_bReportSend;

	extern uint64 g_nLianYunMask;
	extern bool g_bLianYunGiftCard;
	extern bool g_bIsTencentPlatform;

	extern int32 g_nMajorCityStageId;
	extern char g_szSecretKey[128];
	extern int32 g_nFatigueSwitch;
	extern int32 g_nZoneId;
	extern int32 g_nKaifuDate;
	extern int64 g_nKaifuTime;

	extern bool g_bNetMsgCheckSeq;	//验证消息包顺序
	
	extern char g_szQlogDirectory[128];
	extern char g_szWlogDirectory[128];

	extern int32 g_nGameId;

	extern char g_sz173TokenAppId[128];
	extern char g_sz173TokenSecret[128];

	extern int32 g_nDawnHour;
	extern int32 g_nCurrencyRatio; // 充值转换比
	extern bool g_bEnableUuidRecycle; // 允许uuid回收
	extern int32 g_nCheatDetectLevel; // 打开作弊检查
	extern bool g_bOpenPingCheck; // 打开ping检查
	extern bool g_bEnableWMlog; // 允许输出完美log
	
	extern uint64 g_nDisableSnspay; // 金券屏蔽掩码
	extern uint64 g_nDisableSnspayPf;	// 金券屏蔽平台
	extern int32 g_nDailyRechargeGroup; // 每日累冲开关 0默认 -1关闭
	extern int32 g_nDailyFirstRechargeGroup;// 每日首次充值开关 0默认 -1关闭

	extern bool g_bAutofixServerInfo;
	extern int32 g_nAutofixServerStart;

	extern int32 g_nHumanLevelLimit; // 等级限制
	extern bool g_bActivityOpenTimeLimit; // 活动是否受开启时间限制

	extern char g_sAllowEnterWorld[128]; // 允许进入地图的时间

	extern std::string g_strDefaultAgent; // 默认agent

	extern unsigned int g_nTencentAppId;
	extern bool g_bTencentDebug;
	extern bool g_bTencentCompassEnable;
	extern bool g_bCustomerServiceCheckSign;
	extern std::string g_strTencentAppKey;
	extern std::string g_strTencentUrl;
	extern std::string g_strTencentPfkeyUrl;
	extern std::string g_strTencentGoldUrl;
	extern std::string g_strTencentCompassUrl;
	extern std::string g_strTencentUnionUrl;
	extern std::string g_strTencentClogUrl;

	extern std::string g_strLocalServerIP;
	extern uint32 g_nLocalServerIP;

	extern int32 g_nArcGameId;
	extern std::string g_strArcGameUrl; // arcgame 调用URL
	extern std::string g_strArcGameAbbr; // arcgame 游戏缩写
	extern std::string g_strArcGameSecret; // arcgame 游戏Secret

	extern int32 g_nLadderLevelMoWang;
	extern int32 g_nLadderLevelArena;
	extern int32 g_nLadderLevelBattle;
	extern int32 g_nLadderLevelPVE;


	extern std::string g_szLogKey;	//第三方写logKey

	extern std::string g_szLoginKey; // 游戏登陆Secret
	extern std::string g_szChargeKey;//支付Secret
	extern std::string g_szGameKey;//gamekey
	extern int32 g_nLadderLevelKFMZ;
	extern int32 g_nWarZoneId;	//战区Id
	extern bool g_bSYRunning;	//神佑试炼状态[开启|关闭]
	extern bool g_bClosedKFMZ;
	extern bool g_bClosedKFMZ_Ladder;

	// 控制wlog的输出
	extern uint64 g_nWlogMask0;
	extern uint64 g_nWlogMask1;

	extern std::string g_strGiftcardUrl;
	extern std::string g_strGiftcardLianYunUrl;

	extern int InitialServerGroup(const char* filename = 0);
	extern bool CheckLianYunMask(uint64 mask);
	extern int GetKaifuDays(sint64 clibtime);

	extern int GetTencentDomain(const char* pf);
}

#endif // _pw_server_group_
