#ifndef _pw_client_logger_
#define _pw_client_logger_

#include "log4cplus/logger.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/loggingmacros.h"

namespace pwutils
{
	namespace clientlog
	{
		extern char g_szLogDefaultDirectory[128];
		extern log4cplus::Logger gobj_LoggerMoniter;


		extern void InitClientLog();
		extern void ShutDownLog();
	}
}

#define gMoniterStream(x) LOG4CPLUS_INFO(pwutils::clientlog::gobj_LoggerMoniter,x)

#endif //_pw_client_logger_
