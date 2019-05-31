#include "pw_server_group.h"
#include "pw_xml.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "pw_platform.h"
#include "pw_iconv.h"
#include "pw_time.h"
#include "pw_ngs_utils.h"
#include "json/json.h"
#include <iostream>
#include "pw_socket_utils.h"
#include "pw_byte_order.h"
#include "pw_tx_compass.h"

#ifdef _MSC_VER
	std::string g_strVersion = "MSVC_NoVersion";
	uint32 g_nBuildNO = 0;
#else
	#include "pw_version.inl"
#endif


namespace pwngs
{
	int64 g_nServerGroup = 0;
	bool g_bLadderServer = false;
	// 测试天梯，开启后，本机会同时启动普通和天梯
	bool g_bLadderTest = false;
	bool g_bBISend = true;
	bool g_bReportSend = true;
	uint64 g_nLianYunMask = 0LL;
	bool g_bLianYunGiftCard = false;
	bool g_bIsTencentPlatform = false;

	int32 g_nMajorCityStageId = 0;
	char g_szSecretKey[128] = "";
	int32 g_nFatigueSwitch = 0;
	int32 g_nZoneId = 0;
	int32 g_nKaifuDate;
	int64 g_nKaifuTime;

	bool g_bNetMsgCheckSeq = true;		//验证消息包顺序
	
	char g_szQlogDirectory[128] = "./qlogs/";
	char g_szWlogDirectory[128] = "./wlogs/";
	// char g_szWlogDirectoryTmp[128] = "./tmp_wlogs/";

	int32 g_nGameId = 43;
	char g_sz173TokenAppId[128];
	char g_sz173TokenSecret[128];
	int32 g_nDawnHour = 5;
	int32 g_nCurrencyRatio = 10; // 充值转换比
	bool g_bEnableUuidRecycle = true; // 允许uuid回收
	int32 g_nCheatDetectLevel = 0; // 打开作弊检查
	bool g_bOpenPingCheck = true; // 打开ping检查
	std::string g_strDefaultAgent = "173"; // 默认agent
	bool g_bEnableWMlog = true; // 允许输出完美log

	uint64 g_nDisableSnspay = tx::cst_disable_snspay_dedu;
	uint64 g_nDisableSnspayPf = tx::cst_disable_snspay_pf_qqgame + tx::cst_disable_snspay_pf_qzone + tx::cst_disable_snspay_pf_tgp + tx::cst_disable_snspay_pf_idip;

	int32 g_nDailyFirstRechargeGroup = 0;
	int32 g_nDailyRechargeGroup = 0;

	bool g_bAutofixServerInfo = false;
	int32 g_nAutofixServerStart = 0;

	int32 g_nHumanLevelLimit = 80;	// 等级限制
	bool g_bActivityOpenTimeLimit = true;
	char g_sAllowEnterWorld[128] = {0}; // 允许进入地图的时间

	unsigned int g_nTencentAppId = 0;
	bool g_bTencentDebug = false;
	bool g_bTencentCompassEnable = true;
	bool g_bCustomerServiceCheckSign = true;
	std::string g_strTencentAppKey;
	std::string g_strTencentUrl;
	std::string g_strTencentPfkeyUrl;
	std::string g_strTencentGoldUrl;
	std::string g_strTencentCompassUrl;
	std::string g_strTencentUnionUrl;
	std::string g_strTencentClogUrl;

	std::string g_strLocalServerIP;
	uint32 g_nLocalServerIP = 0;

	uint64 g_nWlogMask0 = (uint64)-1;
	uint64 g_nWlogMask1 = (uint64)-1;

	std::string g_strGiftcardUrl = "http://api.173.com:8181/giftBag/validatekey?";
	std::string g_strGiftcardLianYunUrl = "http://api.173.com:8181/giftBag/validatekey/ly2?";

	int32 g_nArcGameId = 3100;
	std::string g_strArcGameUrl = "pear.arcgames.com";
	std::string g_strArcGameAbbr = "dkl";
	std::string g_strArcGameSecret = "be812da68670b0eecc5602800a4f7d0a";//ad5d32fe47d39094df6d2972015f5188";

	std::string g_szLogKey = "Mj0ZO1gksjScVgsQoC61vUveJJxZ221E";

	std::string g_szLoginKey = "O2aTNQTD7qnOJ4DdD7eAjjd42";
	std::string g_szChargeKey = "7TNMEXn2M7WNQ7RtgnNETNmsx";
	std::string g_szGameKey = "fwcq";
	int32 g_nLadderLevelMoWang = 0;
	int32 g_nLadderLevelArena = 0;
	int32 g_nLadderLevelBattle = 0;
	int32 g_nLadderLevelPVE = 0;

	int32 g_nLadderLevelKFMZ = 0;
	int32 g_nWarZoneId = 0;	//战区Id
	bool g_bSYRunning = false;	//神佑试炼状态[开启|关闭]
	bool g_bClosedKFMZ = false;
	bool g_bClosedKFMZ_Ladder = false;

	pthread_mutex_t g_variables_lock = PTHREAD_MUTEX_INITIALIZER;

	int InitialPlatformConfigures();
	int ExecutePlatformConfigures(const std::string& filename,Json::Value& obj);

	int InitialServerGroup( const char* filename /*= 0*/ )
	{
		pwutils::Xml loader;
		if(filename == 0)
			filename = "./server_group.xml";
		pwassertf(loader.LoadFromFile(filename) == 0);

		std::string key = loader.GetValue("/server_group/secret");
		
		std::string qlogdir = loader.GetValue("/server_group/log_qlvh","./qlogs/");
		std::string mlogdir = loader.GetValue("/server_group/log_self","./logs/");
		std::string wlogdir = loader.GetValue("/server_group/log_wm","./wlogs/");
		std::string xiyoulogdir = loader.GetValue("/server_group/log_platform", "./data/logs");
		
		std::string tmp_qlogdir = loader.GetValue("/server_group/tmp_log_qlvh","./tmp_qlogs/");
// 		std::string tmp_wlogdir = loader.GetValue("/server_group/tmp_log_wm","./tmp_wlogs/");


		std::string defaultTiyanStage = loader.GetValue("/server_group/default_tiyan_stage","1988");
		std::string tokenAppId = loader.GetValue("/server_group/token_appid","10003");
		std::string tokenSecret = loader.GetValue("/server_group/token_secret","DCHUISEnrgXFsGohFpwqOaKr6hAlNqqNbsL");
// 		std::string heroname = loader.GetValue("/server_group/hero_name",pwutils::utf8_from_mbs("伊森"));

		std::string dawnhour = loader.GetValue("/server_group/dawn_hour","5");
		std::string currencyratio = loader.GetValue("/server_group/currency_ratio","10");
		std::string enable_uuid_recycle = loader.GetValue("/server_group/enable_uuid_recycle","1");
		std::string enable_cheat_detect = loader.GetValue("/server_group/enable_cheat_detect","0");

		std::string default_encoding = loader.GetValue("/server_group/default_encoding","");
		if(default_encoding.length() > 0)
		{
			pwutils::g_sDefaultEncoding = default_encoding;
		}

#ifdef _DEBUG
		std::string allow_assert = loader.GetValue("/server_group/allow_assert","1");
#else
		std::string allow_assert = loader.GetValue("/server_group/allow_assert","0");
#endif
		std::string wmlog_enable = loader.GetValue("/server_group/wmlog_enable","1");
		std::string activity_opentime_limit = loader.GetValue("/server_group/activity_opentime_limit","1");

		std::string lianyun =  loader.GetValue("/server_group/lianyun_push","0");
		std::string lianyun_giftcard =  loader.GetValue("/server_group/lianyun_giftcard",lianyun.c_str());

		std::string autofix_server_info =  loader.GetValue("/server_group/autofix_server_info","0");
		 
		g_strDefaultAgent = loader.GetValue("/server_group/default_agent","xiyou");

// 		heroname = pwutils::utf8_to_mbs(heroname);		

		g_nServerGroup = pwutils::atoi(loader.GetValue("/server_group/id","0").c_str());
		g_nZoneId = (int32)pwutils::atoi(loader.GetValue("/server_group/zone_id","0").c_str());
		g_nGameId = (int32)pwutils::atoi(loader.GetValue("/server_group/game_id","43").c_str());
		g_bLadderServer = loader.GetValue("/server_group/ladder-server","false") == "true";
		g_bLadderTest = loader.GetValue("/server_group/laddertest", "false") == "true";
		g_bBISend = loader.GetValue("/server_group/bi_send", "false") == "true";
		g_bReportSend = loader.GetValue("/server_group/report_send", "false") == "true";
		g_nMajorCityStageId = (int)pwutils::atoi(loader.GetValue("/server_group/ladder-server-login-stage","2006").c_str());
		g_nFatigueSwitch = (int)pwutils::atoi(loader.GetValue("/server_group/fatigue","0").c_str());
		g_nKaifuDate = (int32)pwutils::atoi(loader.GetValue("/server_group/kaifudate","0").c_str());
		g_nKaifuTime = pwutils::time::mktimeofday(g_nKaifuDate/10000,(g_nKaifuDate%10000)/100,g_nKaifuDate%100);
		g_nDawnHour = (int32)pwutils::atoi(dawnhour.c_str());
		g_nCurrencyRatio = pwutils::atoi(currencyratio.c_str());
		g_bEnableUuidRecycle = pwutils::atoi(enable_uuid_recycle.c_str()) == 1;
		g_nCheatDetectLevel = pwutils::atoi(enable_cheat_detect.c_str());
		g_bAllowAssert = pwutils::atoi(allow_assert.c_str()) == 1;
		g_bEnableWMlog = pwutils::atoi(wmlog_enable.c_str()) == 1;
		g_bActivityOpenTimeLimit = pwutils::atoi(activity_opentime_limit.c_str()) == 1;

		// 是否为联运,是的话取加上LIANYUN_MASK_SERVERINFO联运掩码
		// 推送部份由各自平台处理
		if(pwutils::atoi(lianyun.c_str()) > 0)
		{
			g_nLianYunMask |= LIANYUN_MASK_SERVERINFO;
		}
		g_bLianYunGiftCard = pwutils::atoi(lianyun_giftcard.c_str()) == 1;

		g_bAutofixServerInfo = pwutils::atoi(autofix_server_info.c_str()) == 1;

		g_bIsTencentPlatform = pwutils::atoi(loader.GetValue("/server_group/tencent-platform").c_str()) > 0;
		g_nTencentAppId = (unsigned int)pwutils::atoi(loader.GetValue("/server_group/tencent-appid").c_str());
		g_bTencentDebug = pwutils::atoi(loader.GetValue("/server_group/tencent-debug").c_str()) > 0;
		g_strTencentAppKey = loader.GetValue("/server_group/tencent-appkey");
		g_strTencentUrl = loader.GetValue("/server_group/tencent-url");
		g_strTencentPfkeyUrl = loader.GetValue("/server_group/tencent-pfkey-url");
		g_strTencentGoldUrl = loader.GetValue("/server_group/tencent-gold-url");
		g_strTencentCompassUrl = loader.GetValue("/server_group/tencent-datacompass-url");
		g_strTencentUnionUrl = loader.GetValue("/server_group/tencent-dataunion-url");
		g_strTencentClogUrl = loader.GetValue("/server_group/tencent-dataclog-url");
		
		//西游网
		g_szLoginKey = loader.GetValue("/server_group/login-key");
		g_szChargeKey = loader.GetValue("/server_group/pay-key");
		g_szGameKey = loader.GetValue("/server_group/game-key");

		g_bNetMsgCheckSeq = loader.GetValue("/server_group/netmsgcheckseq", "true") != "false";

		int64 currdate = pwutils::time::mktimeYYMMDD();
// 		if(g_nKaifuDate > currdate)
// 		{
// 			std::cout << "KaifuDate Great Today,Use:" << currdate << std::endl;
// 			g_nKaifuDate = currdate;
// 		}

		pwutils::strncpy(g_szSecretKey,key.c_str(),_countof(g_szSecretKey));
		
		pwutils::strncpy(g_szQlogDirectory,qlogdir.c_str(),_countof(g_szQlogDirectory));
		pwutils::strncpy(pwutils::logger::g_szLogDefaultDirectory,mlogdir.c_str(),_countof(pwutils::logger::g_szLogDefaultDirectory));		
		pwutils::strncpy(pwutils::logger::g_szXiYouLogDefaultDirectory, xiyoulogdir.c_str(), _countof(pwutils::logger::g_szXiYouLogDefaultDirectory));
		std::string tempPath = "";
		if (g_strDefaultAgent == "360")
		{
			tempPath = wlogdir;
			tempPath += loader.GetValue("/server_group/zone_id", "0").c_str();
			tempPath += "/";
			pwutils::strncpy(pwutils::logger::g_szWLogDirectory, tempPath.c_str(), _countof(pwutils::logger::g_szWLogDirectory));
		}
		else
		{
			pwutils::strncpy(pwutils::logger::g_szWLogDirectory, wlogdir.c_str(), _countof(pwutils::logger::g_szWLogDirectory));
		}
		
		pwutils::strncpy(g_sz173TokenAppId,tokenAppId.c_str(),_countof(g_sz173TokenAppId));		
		pwutils::strncpy(g_sz173TokenSecret,tokenSecret.c_str(),_countof(g_sz173TokenSecret));		
	
		//////////////////////////////////////////////////////////////////////////运营日志初始路径begin
		std::string strServerId = loader.GetValue("/server_group/id", "0");
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf));
		std::string strWLogDir = wlogdir + strServerId + "/" + datebuf + "/";

#ifdef _MSC_VER
		::CreateDirectory(mlogdir.c_str(),NULL);

		//::CreateDirectory(wlogdir.c_str(), NULL);
		//::CreateDirectory((wlogdir + strServerId + "/").c_str(), NULL);
		if (g_strDefaultAgent != "360")
		{
			::CreateDirectory(strWLogDir.c_str(), NULL);
		}
		else
		{
			if (tempPath != "")
			{
				::CreateDirectory(tempPath.c_str(), NULL);
			}
			else
			{
				::CreateDirectory(strWLogDir.c_str(), NULL);
			}
		}
		::CreateDirectory(xiyoulogdir.c_str(),NULL);

#else
		::mkdir(mlogdir.c_str(),755);

		//::mkdir(wlogdir.c_str(), 755);
		//::mkdir((wlogdir + strServerId + "/").c_str(), 755);
		if (g_strDefaultAgent != "360")
		{
			::mkdir(strWLogDir.c_str(), 755);
		}
		else
		{
			if (tempPath != "")
			{
				::mkdir(tempPath.c_str(), NULL);
			}
			else
			{
				::mkdir(strWLogDir.c_str(), 755);
			}
		}
		::mkdir(xiyoulogdir.c_str(), 755);
		
#endif
		pwutils::strncpy(g_szWlogDirectory, wlogdir.append(strServerId).append("/").c_str(), _countof(g_szWlogDirectory));
		//////////////////////////////////////////////////////////////////////////运营日志初始路径end
		{
			std::vector<std::string> addresses;
			
			if(!pwutils::gethostaddresses(addresses))
				assert(false && "gethostname failed");

			for(size_t i = 0; i < addresses.size(); ++i)
			{
				if(addresses[i] == "127.0.0.1")
					continue;

				struct in_addr addr = {0};
				pwutils::inet_aton(addresses[i].c_str(),&addr);

				g_strLocalServerIP = addresses[i];
				unsigned long addrn = addr.s_addr;
				pwutils::Convert<unsigned long>::ToHostOrder(addrn);
				g_nLocalServerIP = addrn;

				break;
			}

			assert(g_strLocalServerIP.length() > 0);
		}			

		InitialPlatformConfigures();

		std::cout << "***************************************************************************" << std::endl;
		std::cout << "zoneid=" << g_nZoneId << std::endl;
		std::cout << "gameid=" << g_nGameId << std::endl;
		std::cout << "servergroup=" << g_nServerGroup << std::endl;
		std::cout << "kaifudate=" << g_nKaifuDate << std::endl;
		std::cout << "dawnhour=" << g_nDawnHour << std::endl;
		std::cout << "ladder=" << g_bLadderServer << std::endl;
		std::cout << "currencyratio=" << g_nCurrencyRatio << std::endl;
		std::cout << "enable_uuid_recycle=" << g_bEnableUuidRecycle << std::endl;
		std::cout << "allow_assert=" << g_bAllowAssert << std::endl;
		std::cout << "activity_opentime_limit=" << g_bActivityOpenTimeLimit << std::endl;
		std::cout << "wmlog_enable=" << g_bEnableWMlog << std::endl;
		std::cout << "cheat_detect_level=" << g_nCheatDetectLevel << std::endl;
		std::cout << "default_agent=" << g_strDefaultAgent << std::endl;
		std::cout << "lianyun_push=" << g_nLianYunMask << std::endl;
		std::cout << "lianyun_giftcard=" << g_bLianYunGiftCard<< std::endl;
		std::cout << "autofix_server_info=" << g_bAutofixServerInfo << std::endl;
		std::cout << "local_ip=" << g_strLocalServerIP << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "tencent_appid=" << g_nTencentAppId << std::endl;
		std::cout << "tencent_url=" << g_strTencentUrl << std::endl;
		
		std::cout << "***************************************************************************" << std::endl;

		return 0;
	}

	int InitialPlatformConfigures()
	{
		std::string filename;
		filename.append("./data/platform/").append(g_strDefaultAgent).append(".json");

		std::fstream fs;
		fs.open(filename.c_str(),std::ios_base::in);
		if(!fs.good())
		{
			std::cout << "*****warning**** platform configure nofound:" << filename << std::endl;
			return 0;
		}

		Json::Reader reader;
		Json::Value values;
		if(!reader.parse(fs,values))
		{
			std::cout << "*****warning**** platform configure not json format:" << filename << std::endl;
			assert(false);
			return 0;
		}

		ExecutePlatformConfigures(filename,values);

		return 0;
	}

	int ExecutePlatformConfigure(const std::string& name,Json::Value& val)
	{
		enum EConfigureValueType
		{
			__TYPE_I32,
			__TYPE_I64,
			__TYPE_DOUBLE,
			__TYPE_STD_STRING,
			__TYPE_INT_AS_BOOL,
			__TYPE_U64_MASK_DISABLE,
			__TYPE_U64_MASK_ENABLE,
			__TYPE_ERROR,
		};

		struct SConfigure
		{
			std::string name;
			EConfigureValueType type;
			void* value_ptr;
		};

		static SConfigure s_SupportedConfigures[] = 
		{
			{  "fatigue",				__TYPE_I32,			&g_nFatigueSwitch },
			{  "currency_ratio",		__TYPE_I32,			&g_nCurrencyRatio },
			{  "lianyun_bits",			__TYPE_U64_MASK_ENABLE,		&g_nLianYunMask},
			{  "lianyun_giftcard",		__TYPE_INT_AS_BOOL,	&g_bLianYunGiftCard},
			{  "tencent_platform",		__TYPE_INT_AS_BOOL,	&g_bIsTencentPlatform},
			{  "tencent_debug",			__TYPE_INT_AS_BOOL,	&g_bTencentDebug},
			{  "http_check_sign",		__TYPE_INT_AS_BOOL,	&g_bCustomerServiceCheckSign},
			{  "humanlevel_limit",		__TYPE_I32,			&g_nHumanLevelLimit},
			{  "autofix_server_info",	__TYPE_INT_AS_BOOL,	&g_bAutofixServerInfo},
			{  "autofix_server_start",	__TYPE_I32,			&g_nAutofixServerStart},
			{  "default_encoding",		__TYPE_STD_STRING,	&pwutils::g_sDefaultEncoding},
			{  "giftcard_url"	,		__TYPE_STD_STRING,	&g_strGiftcardUrl},
			{  "lianyun_giftcard_url",	__TYPE_STD_STRING,	&g_strGiftcardLianYunUrl},
			
			{  "wmlog_disable_mask0",	__TYPE_U64_MASK_DISABLE,	&g_nWlogMask0},
			{  "wmlog_disable_mask1",	__TYPE_U64_MASK_DISABLE,	&g_nWlogMask1},

			{  "arcgames_url",			__TYPE_STD_STRING,	&g_strArcGameUrl},
			{  "arcgames_abbr",			__TYPE_STD_STRING,	&g_strArcGameAbbr},
			{  "arcgames_secret",		__TYPE_STD_STRING,	&g_strArcGameSecret},

			{  "ladder_level_mowang",	__TYPE_I32,			&g_nLadderLevelMoWang},
			{  "ladder_level_arena",	__TYPE_I32,			&g_nLadderLevelArena},
			{  "ladder_level_battle",	__TYPE_I32,			&g_nLadderLevelBattle},
			{  "ladder_level_pve",      __TYPE_I32,			&g_nLadderLevelPVE},

			{  "",						__TYPE_ERROR,		NULL },
		};

		for(size_t i = 0; i < _countof(s_SupportedConfigures); ++i)
		{
			SConfigure& r = s_SupportedConfigures[i];
			if(r.name.length() == 0)
				break;
			if(r.name != name)
				continue;

			switch(r.type)
			{
			case __TYPE_I32:
				{
					int32* ptr = (int32*)r.value_ptr;
					if(!val.isIntegral())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					*ptr = (int32)val.asInt();
				}
				break;
			case __TYPE_I64:
				{
					int64* ptr = (int64*)r.value_ptr;
					if(!val.isIntegral())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					*ptr = (int64)val.asInt();
				}
				break;
			case __TYPE_DOUBLE:
				{
					double* ptr = (double*)r.value_ptr;
					if(!val.isNumeric())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					*ptr = val.asDouble();
				}
				break;
			case __TYPE_STD_STRING:
				{
					std::string* ptr = (std::string*)r.value_ptr;
					if(!val.isString())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					*ptr = val.asString();
				}
				break;
			case __TYPE_INT_AS_BOOL:
				{
					bool* ptr = (bool*)r.value_ptr;
					if(!val.isIntegral())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					*ptr = val.asBool();
				}
				break;
			case __TYPE_U64_MASK_DISABLE:
				{
					uint64& ptr = *((uint64*)r.value_ptr);
					if(!val.isArray())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}
					
					for(Json::UInt i = 0; i < val.size(); ++i)
					{
						assert(val[i].isIntegral());
						Json::Int bit = val[i].asInt();
						ptr &= ~(1ULL << bit);

						std::cout << __FUNCTION__ << " mask " << name << " bit disabled =" << bit << std::endl;
					}
				}
				break;
			case __TYPE_U64_MASK_ENABLE:
				{
					uint64& ptr = *((uint64*)r.value_ptr);
					if(!val.isArray())
					{
						std::cout << __FUNCTION__ << " ***ERROR***type nomatch:" << name << " value=" << val.toStyledString() << std::endl;
						assert(false);
					}

					for(Json::UInt i = 0; i < val.size(); ++i)
					{
						assert(val[i].isIntegral());
						Json::Int bit = val[i].asInt();
						ptr |= (1ULL << bit);

						std::cout << __FUNCTION__ << " mask " << name << " bit enable =" << bit << std::endl;
					}
				}
				break;
			default:
				{
					std::cout << __FUNCTION__ << " ***ERROR***type invalid:" << name << " value=" << val.toStyledString() << std::endl;
					assert(false);
					return -100;
				}
				break;
			}
			return 0;
		}
		return -1;
	}

	int ExecutePlatformConfigures(const std::string& filename,Json::Value& obj)
	{
		Json::Value::Members members = obj.getMemberNames();
		for(size_t i = 0; i < members.size(); ++i)
		{
			Json::Value value = obj[members[i]];
			if(ExecutePlatformConfigure(members[i],value) != 0)
			{
				std::cout << __FUNCTION__ << " ***ERROR***override configure failed,name=" << members[i] << " value=" << value.toStyledString() << std::endl;
			}
			else
			{
				std::cout << __FUNCTION__ << " override configure successful,name=" << members[i] << " value=" << value.toStyledString() << std::endl;
			}
		}
		
		return 0;
	}

	extern bool CheckLianYunMask( uint64 mask )
	{
		return g_nLianYunMask & mask;
	}

	extern int GetKaifuDays(sint64 clibtime)
	{
		if(clibtime == 0)
			clibtime = pwutils::time::clib_time();
		return (clibtime - g_nKaifuTime) / 86400;
	}

	extern int GetTencentDomain( const char* pf )
	{
		std::string strpf(pf);

		if(pwutils::stricmp(pf,"qzone") == 0)
			return tx::DOMAIN_QZONE;
		if(pwutils::stricmp(pf,"pengyou") == 0)
			return tx::DOMAIN_PENGYOU;
		if(pwutils::stricmp(pf,"tapp") == 0)
			return tx::DOMAIN_WEIBO;
		if(pwutils::stricmp(pf,"qplus") == 0)
			return tx::DOMAIN_QPLUS;
		if(pwutils::stricmp(pf,"qzone_m") == 0)
			return tx::DOMAIN_MOBILE_QZONE;
		if(pwutils::stricmp(pf,"pengyou_m") == 0)
			return tx::DOMAIN_MOBILE_PENGYOU;
		if(pwutils::stricmp(pf,"qqgame") == 0)
			return tx::DOMAIN_QQGAME;
		if(pwutils::stricmp(pf,"3366") == 0)
			return tx::DOMAIN_3366;
		if(strpf.find("union") != strpf.npos)
			return tx::DOMAIN_YOUXI_LIANMENG;
		
		gDebugStream(__FUNCTION__ << " unknown pf=" << pf);

		return tx::DOMAIN_QQGAME_WEBSITE;
	}

}