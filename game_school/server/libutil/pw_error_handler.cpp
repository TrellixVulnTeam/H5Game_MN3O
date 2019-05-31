#include "pw_def.h"
#include "pw_logger.h"
#include "pw_error_handler.h"
#include "pw_backtrace.h"

#include <stdio.h>
#include <signal.h>

namespace pwngs
{
	volatile bool gClosed = false;
	volatile pfnErrorHandleFunc gErrorHandleFunc = NULL;

	void MySigHandler(int signo)
	{
		if(signo == SIGINT)
			gClosed = true;

		if(gErrorHandleFunc != NULL)
			gErrorHandleFunc(signo);
		else
			MySigHandler_Fini();

		std::cout << __FUNCTION__ << " signal:" << signo << std::endl;
	}

	void hook_exit(void)
	{
		printf ("hook_exit now,lasterror= %d \n",errno);
	}

	void MySigHandler_Init(pfnErrorHandleFunc pfn)
	{
		gErrorHandleFunc = pfn;

		atexit(hook_exit);
#ifndef _MSC_VER
		signal(SIGPIPE,SIG_IGN);
		signal(SIGCHLD,SIG_IGN);
#endif
		signal(SIGFPE,SIG_IGN);

		//指定SIGINT信号的处理函数
		::signal (SIGINT,pwngs::MySigHandler);
		::signal (SIGSEGV,pwngs::MySigHandler);
		::signal (SIGABRT,pwngs::MySigHandler);

		::signal (SIGILL,pwngs::MySigHandler);
		::signal (SIGTERM,pwngs::MySigHandler);

#ifndef __linux
		::signal (SIGBREAK,pwngs::MySigHandler);
#else
		::signal (SIGBUS,pwngs::MySigHandler);
		::signal (SIGHUP,pwngs::MySigHandler);
		::signal (SIGALRM,pwngs::MySigHandler);
		::signal (SIGUSR1,pwngs::MySigHandler);
		::signal (SIGUSR2,pwngs::MySigHandler);
		// 		::signal (SIGTSTP,pwngs::MySigHandler);
		// 		::signal (SIGTTIN,pwngs::MySigHandler);
		// 		::signal (SIGTTOU,pwngs::MySigHandler);
		::signal (SIGPOLL,pwngs::MySigHandler);
		::signal (SIGPROF,pwngs::MySigHandler);

		::signal (SIGIO,pwngs::MySigHandler);
		::signal (SIGPWR,pwngs::MySigHandler);
#endif
	}

	void MySigHandler_Fini()
	{
		::signal (SIGINT,NULL);
		::signal (SIGSEGV,NULL);
		::signal (SIGABRT,NULL);

		::signal (SIGILL,NULL);
		::signal (SIGTERM,NULL);

#ifndef __linux
		::signal (SIGBREAK,NULL);
#else
		::signal (SIGBUS,NULL);
		::signal (SIGHUP,NULL);
		::signal (SIGALRM,NULL);
		::signal (SIGUSR1,NULL);
		::signal (SIGUSR2,NULL);
// 		::signal (SIGTSTP,NULL);
// 		::signal (SIGTTIN,NULL);
// 		::signal (SIGTTOU,NULL);
		::signal (SIGPOLL,NULL);
		::signal (SIGPROF,NULL);

		::signal (SIGIO,NULL);
		::signal (SIGPWR,NULL);
#endif
	}

}
