#include "pw_time.h"
#include "pw_client_logger.h"
#include "pw_platform.h"

namespace pwutils
{
	namespace clientlog
	{
		char g_szLogDefaultDirectory[128] = "./clogs/";
		log4cplus::Logger gobj_LoggerMoniter;


		log4cplus::Logger Create( const std::string& name )
		{
			std::string file = std::string(g_szLogDefaultDirectory) + name + ".log";

			//log4cplus::SharedAppenderPtr appender(new log4cplus::FileAppender(file.c_str(),std::ios_base::app,true));
			log4cplus::SharedAppenderPtr appender(new log4cplus::DailyRollingFileAppender(file.c_str(),log4cplus::DAILY,true,100));
			//log4cplus::SharedAppenderPtr appender(new log4cplus::RollingFileAppender(file.c_str(), 100*1024*1024,1000,true)); //100M
			
			
			appender->setName(LOG4CPLUS_TEXT("1"));
			appender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(LOG4CPLUS_TEXT("%D{%Y-%m-%d %H:%M:%S} %m %n"))));

			log4cplus::Logger logger = log4cplus::Logger::getInstance(name.c_str());
			logger.addAppender(appender);
			return logger;
		}

		void InitClientLog( )
		{
			log4cplus::initialize();
			gobj_LoggerMoniter = Create("client");
			gMoniterStream("Logger::Initial");
		}

		void ShutDownLog()
		{
		}
	}
}
