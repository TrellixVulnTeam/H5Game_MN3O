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

	extern bool g_bNetMsgCheckSeq;	//��֤��Ϣ��˳��
	
	extern char g_szQlogDirectory[128];
	extern char g_szWlogDirectory[128];

	extern int32 g_nGameId;

	extern char g_sz173TokenAppId[128];
	extern char g_sz173TokenSecret[128];

	extern int32 g_nDawnHour;
	extern int32 g_nCurrencyRatio; // ��ֵת����
	extern bool g_bEnableUuidRecycle; // ����uuid����
	extern int32 g_nCheatDetectLevel; // �����׼��
	extern bool g_bOpenPingCheck; // ��ping���
	extern bool g_bEnableWMlog; // �����������log
	
	extern uint64 g_nDisableSnspay; // ��ȯ��������
	extern uint64 g_nDisableSnspayPf;	// ��ȯ����ƽ̨
	extern int32 g_nDailyRechargeGroup; // ÿ���۳忪�� 0Ĭ�� -1�ر�
	extern int32 g_nDailyFirstRechargeGroup;// ÿ���״γ�ֵ���� 0Ĭ�� -1�ر�

	extern bool g_bAutofixServerInfo;
	extern int32 g_nAutofixServerStart;

	extern int32 g_nHumanLevelLimit; // �ȼ�����
	extern bool g_bActivityOpenTimeLimit; // ��Ƿ��ܿ���ʱ������

	extern char g_sAllowEnterWorld[128]; // ��������ͼ��ʱ��

	extern std::string g_strDefaultAgent; // Ĭ��agent

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
	extern std::string g_strArcGameUrl; // arcgame ����URL
	extern std::string g_strArcGameAbbr; // arcgame ��Ϸ��д
	extern std::string g_strArcGameSecret; // arcgame ��ϷSecret

	extern int32 g_nLadderLevelMoWang;
	extern int32 g_nLadderLevelArena;
	extern int32 g_nLadderLevelBattle;
	extern int32 g_nLadderLevelPVE;


	extern std::string g_szLogKey;	//������дlogKey

	extern std::string g_szLoginKey; // ��Ϸ��½Secret
	extern std::string g_szChargeKey;//֧��Secret
	extern std::string g_szGameKey;//gamekey
	extern int32 g_nLadderLevelKFMZ;
	extern int32 g_nWarZoneId;	//ս��Id
	extern bool g_bSYRunning;	//��������״̬[����|�ر�]
	extern bool g_bClosedKFMZ;
	extern bool g_bClosedKFMZ_Ladder;

	// ����wlog�����
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
