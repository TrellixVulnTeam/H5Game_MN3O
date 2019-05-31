
#ifndef _pw_logger_
#define _pw_logger_

/*
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/TimeStamp.hh>
#include <log4cpp/FileAppender.hh>

#define gDebugStream pwutils::logger::Get("debug")
#define gErrorStream pwutils::logger::Get("error")
#define gWarniStream pwutils::logger::Get("warni")
#define gItemStream pwutils::logger::Get("item")
#define gCashStream pwutils::logger::Get("cash")
#define gClientStream pwutils::logger::Get("client")

namespace pwutils
{
	namespace logger
	{
		extern log4cpp::CategoryStream Get(const std::string& name,log4cpp::Priority::Value priority = log4cpp::Priority::WARN);

		extern void Create(const std::string& name,const std::string& file);
		extern void Initial(const char* prefix);
		extern void ShutDown();
	}
}
*/

#include "log4cplus/logger.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/loggingmacros.h"

namespace pwutils
{
	namespace logger
	{
		extern char g_szLogDefaultDirectory[128];
		extern char g_szXiYouLogDefaultDirectory[128];
		extern char g_szWLogDirectory[128];
		extern log4cplus::Logger gobj_LoggerNetwork;
		extern log4cplus::Logger gobj_LoggerCheat;
		extern log4cplus::Logger gobj_LoggerDebug;
		extern log4cplus::Logger gobj_LoggerError;
		extern log4cplus::Logger gobj_LoggerWarni;
		extern log4cplus::Logger gobj_LoggerCash;
		extern log4cplus::Logger gobj_LoggerClient;

		extern log4cplus::Logger gobj_LoggerNetworkXiYou;
		extern log4cplus::Logger gobj_LoggerCheatXiYou;
		extern log4cplus::Logger gobj_LoggerDebugXiYou;
		extern log4cplus::Logger gobj_LoggerErrorXiYou;
		extern log4cplus::Logger gobj_LoggerWarniXiYou;
		extern log4cplus::Logger gobj_LoggerCashXiYou;
		extern log4cplus::Logger gobj_LoggerClientXiYou;
		extern log4cplus::Logger gobj_LoggerUUIDXiYou;
		extern log4cplus::Logger gobj_LoggerLoginXiYou;
		extern log4cplus::Logger gobj_LoggerMailXiYou;
		extern log4cplus::Logger gobj_LogggerGuildXiYou;

		extern log4cplus::Logger gobj_LoggerUUID;

		extern log4cplus::Logger gobj_LogBabel;
		extern log4cplus::Logger gobj_LogCommonActivity;
		extern log4cplus::Logger gobj_LogHotActivity;

		extern log4cplus::Logger gobj_LogSrvRanklist;
		extern log4cplus::Logger gobj_LogSrvCommonActivity;

		extern log4cplus::Logger gobj_LoggerDragon;
		extern log4cplus::Logger gobj_LoggerLogin;
		extern log4cplus::Logger gobj_LoggerMail;

		extern log4cplus::Logger gobj_LogggerWLog;

		extern void Initial(const char* prefix);
		extern void ModLogInitial();
		extern void ServiceLogInitial();
		extern void XiYouInitial(const char* prefix);
		extern void ShutDown();
	}
}

#ifdef _DEBUG_NETWORK_
	#define gNetworkStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerNetwork,x)
#else
	#define gNetworkStream(x)
#endif

#define gCheatStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerCheat,x)
#define gDebugStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerDebug,x)
#define gErrorStream(x) {std::cout << x << std::endl; LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerError,x); }
#define gWarniStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerWarni,x)
#define gCashStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerCash,x)
#define gClientStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerClient,x)
#define gLoginStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerLogin,x)

#define gUuidStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerUUID,x)

#define gLogBabel(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogBabel,x)
#define gLogCommonActivity(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogCommonActivity,x)
#define gLogHotActivity(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogHotActivity,x)

#define gLogSrvRanklist(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogSrvRanklist,x)
#define gLogSrvCommonActivity(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogSrvCommonActivity,x)

#define gDragonStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerDragon,x)
#define gMailStream(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerMail,x)

//西游
#define gGuildStreamXiYou(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogggerGuildXiYou,x)
#define gChatStreamXiYou(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LoggerCheatXiYou,x)

//wlog日志
#define gGameOperationWlog(x) LOG4CPLUS_INFO(pwutils::logger::gobj_LogggerWLog,x)

#endif //_pw_logger_
