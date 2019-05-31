#include "pw_time.h"
#include "pw_logger.h"
#include "pw_platform.h"
#include <memory>

namespace pwutils
{
	namespace logger
	{
		/*

		log4cpp::CategoryStream Get(const std::string& name,log4cpp::Priority::Value priority)
		{
			log4cpp::Category& logger = log4cpp::Category::getInstance(name);
			return logger.getStream(priority);
		}

		void Create(const std::string& name,const std::string& file)
		{
			// 1实例化一个layout 对象
			log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
			layout->setConversionPattern("%d [%t] %p - %m%n");
			// 2. 初始化一个appender 对象
			log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender",file.c_str(),true,00644);
			// 3. 把layout对象附着在appender对象上
			appender->setLayout(layout);
			// 4. 实例化一个category对象
			log4cpp::Category& logger = log4cpp::Category::getInstance(name);
			// 5. 设置additivity为false，替换已有的appender
			logger.setAdditivity(false);
			// 5. 把appender对象附到category上
			logger.setAppender(appender);
			// 6. 设置category的优先级，低于此优先级的日志不被记录
			logger.setPriority(log4cpp::Priority::INFO);
		}

		void Initial(const char* prefix)
		{
			std::string date = pwutils::time::date();

			date = std::string("./logs/") + std::string(prefix) + date;


#ifdef _MSC_VER
			::CreateDirectory("./logs",NULL);
#else
			::mkdir("./logs",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
#endif

			Create("debug",date + "_debug.log");
			Create("error",date + "_error.log");
			Create("warni",date + "_warni.log");
			Create("item",date + "_item.log");
			Create("cash",date + "_cash.log");
			Create("client",date + "_client.log");
		}

		void ShutDown()
		{
			log4cpp::Category::shutdown();
		}

		*/

		char g_szLogDefaultDirectory[128] = "./logs/";
		char g_szXiYouLogDefaultDirectory[128] = "./data/logs/";
		char g_szWLogDirectory[128] = "./wlogs/";
		log4cplus::Logger gobj_LoggerNetwork;
		log4cplus::Logger gobj_LoggerCheat;
		log4cplus::Logger gobj_LoggerDebug;
		log4cplus::Logger gobj_LoggerError;
		log4cplus::Logger gobj_LoggerWarni;
		log4cplus::Logger gobj_LoggerCash;
		log4cplus::Logger gobj_LoggerClient;

		log4cplus::Logger gobj_LoggerUUID;

		log4cplus::Logger gobj_LogBabel;
		log4cplus::Logger gobj_LogCommonActivity;
		log4cplus::Logger gobj_LogHotActivity;

		log4cplus::Logger gobj_LogSrvRanklist;
		log4cplus::Logger gobj_LogSrvCommonActivity;

		log4cplus::Logger gobj_LoggerDragon;
		log4cplus::Logger gobj_LoggerLogin;
		log4cplus::Logger gobj_LoggerMail;

		//log4cplus::Logger gobj_LoggerNetworkXiYou;
		log4cplus::Logger gobj_LoggerCheatXiYou;
		/*log4cplus::Logger gobj_LoggerDebugXiYou;
		log4cplus::Logger gobj_LoggerErrorXiYou;
		log4cplus::Logger gobj_LoggerWarniXiYou;
		log4cplus::Logger gobj_LoggerCashXiYou;
		log4cplus::Logger gobj_LoggerClientXiYou;
		log4cplus::Logger gobj_LoggerUUIDXiYou;
		log4cplus::Logger gobj_LoggerLoginXiYou;
		log4cplus::Logger gobj_LoggerMailXiYou;*/
		log4cplus::Logger gobj_LogggerGuildXiYou;

		log4cplus::Logger gobj_LogggerWLog;

		log4cplus::Logger Create( const std::string& prefix,const std::string& name )
		{
			std::string file = std::string(g_szLogDefaultDirectory) + prefix + name + ".log";

			log4cplus::SharedAppenderPtr appender(new log4cplus::DailyRollingFileAppender(file.c_str(),log4cplus::DAILY,true,100));
			appender->setName(LOG4CPLUS_TEXT("1"));
			appender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(LOG4CPLUS_TEXT("%D{%Y-%m-%d %H:%M:%S,%q} %m %n"))));

			log4cplus::Logger logger = log4cplus::Logger::getInstance(name.c_str());
			logger.addAppender(appender);
			return logger;
		}

		log4cplus::Logger CreateXiYou(const std::string& prefix, const std::string& name)
		{
			
			time_t timer;
			std::time(&timer);
			tm* t_tm = localtime(&timer);
			char t[20];
			sprintf(t, "%04d%02d%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1, t_tm->tm_mday);
			std::string file = std::string(g_szXiYouLogDefaultDirectory) + prefix + name + "_" + t + ".log";

			log4cplus::SharedAppenderPtr appender(new log4cplus::DailyRollingFileAppender(file.c_str(), log4cplus::DAILY, true, 100));
			std::string pattern = "%m%n";
			std::auto_ptr<log4cplus::Layout> _layout(new log4cplus::PatternLayout(pattern));
			appender->setName(LOG4CPLUS_TEXT("1"));
			appender->setLayout(_layout);

			log4cplus::Logger logger = log4cplus::Logger::getInstance(name.c_str());
			logger.addAppender(appender);
			return logger;
		}

		log4cplus::Logger CreateWlog(const std::string& name)
		{
			std::string file = std::string(g_szWLogDirectory) + name + ".log";

			log4cplus::SharedAppenderPtr appender(new log4cplus::DailyRollingFileAppender(file.c_str(), log4cplus::DAILY, true, 100));
			std::string pattern = "%m%n";
			std::auto_ptr<log4cplus::Layout> _layout(new log4cplus::PatternLayout(pattern));
			appender->setName(LOG4CPLUS_TEXT("1"));
			appender->setLayout(_layout);

			log4cplus::Logger logger = log4cplus::Logger::getInstance(name.c_str());
			logger.addAppender(appender);
			return logger;
		}

		void Initial( const char* prefix )
		{
			log4cplus::initialize();

			gobj_LoggerNetwork = Create(prefix,"network");
			gobj_LoggerCheat = Create(prefix,"cheat");
			gobj_LoggerDebug = Create(prefix,"debug"); 			
			gobj_LoggerError = Create(prefix,"error");
			gobj_LoggerWarni = Create(prefix,"warni");
			gobj_LoggerCash = Create(prefix,"cash");
			gobj_LoggerClient = Create(prefix,"client");
			gobj_LoggerUUID = Create(prefix,"uuid");
			gobj_LoggerLogin = Create(prefix,"login");
			gobj_LoggerMail = Create(prefix,"mail");


			gCashStream("Logger::Initial " << pwutils::time::str());
			gDebugStream("Logger::Initial " << pwutils::time::str());
			gErrorStream("Logger::Initial " << pwutils::time::str());
			gWarniStream("Logger::Initial " << pwutils::time::str());
			gCashStream("Logger::Initial " << pwutils::time::str());
			gClientStream("Logger::Initial " << pwutils::time::str());
			gLoginStream("Logger::Initial " << pwutils::time::str());
			gMailStream("Logger::Initial " << pwutils::time::str());
		}

		void XiYouInitial(const char* prefix)
		{
			log4cplus::initialize();

			//gobj_LoggerNetworkXiYou = CreateXiYou(prefix, "network");
			gobj_LoggerCheatXiYou = CreateXiYou(prefix, "chat");
			/*gobj_LoggerDebugXiYou = CreateXiYou(prefix, "debug");
			gobj_LoggerErrorXiYou = CreateXiYou(prefix, "error");
			gobj_LoggerWarniXiYou = CreateXiYou(prefix, "warni");
			gobj_LoggerCashXiYou = CreateXiYou(prefix, "cash");
			gobj_LoggerClientXiYou = CreateXiYou(prefix, "client");
			gobj_LoggerUUIDXiYou = CreateXiYou(prefix, "uuid");
			gobj_LoggerLoginXiYou = CreateXiYou(prefix, "login");
			gobj_LoggerMailXiYou = CreateXiYou(prefix, "mail");*/
			gobj_LogggerGuildXiYou = CreateXiYou(prefix, "guild");


			//gCashStream("XiYou Logger::Initial " << pwutils::time::str());
			//gDebugStream("XiYou Logger::Initial " << pwutils::time::str());
			//gErrorStream("XiYou Logger::Initial " << pwutils::time::str());
			////gWarniStream("XiYou Logger::Initial " << pwutils::time::str());
			//gCashStream("XiYou Logger::Initial " << pwutils::time::str());
			//gClientStream("XiYou Logger::Initial " << pwutils::time::str());
			//gLoginStream("XiYou Logger::Initial " << pwutils::time::str());
			//gMailStream("XiYou Logger::Initial " << pwutils::time::str());
			//gGuildStreamXiYou("");
			//gChatStreamXiYou("");
		}

		void ModLogInitial()
		{
			log4cplus::initialize();

			gobj_LogBabel = Create("","babel"); 
			gLogBabel("Logger::Initial");

			gobj_LogCommonActivity = Create("","common_activity"); 
			gLogCommonActivity("Logger::Initial");

			gobj_LogHotActivity = Create("","hot_activity"); 
			gLogHotActivity("Logger::Initial");

			gobj_LoggerDragon = Create("module_","dragon");
			gDragonStream("Logger::Initial");
		}

		void ServiceLogInitial()
		{
			log4cplus::initialize();

			gobj_LogSrvRanklist = Create("service_","ranklist"); 
			gLogSrvRanklist("Logger::Initial");

			gobj_LogSrvCommonActivity = Create("service_","commonactivity"); 
			gLogSrvCommonActivity("Logger::Initial");

			gobj_LogggerWLog = CreateWlog("act");

		}

		void ShutDown()
		{
			log4cplus::Logger::shutdown();
		}
	}
}
