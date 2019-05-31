#ifndef _pw_error_handler_
#define _pw_error_handler_


namespace pwngs
{
	typedef void (*pfnErrorHandleFunc)(int signo);

	extern volatile bool gClosed;
	extern volatile pfnErrorHandleFunc gErrorHandleFunc;

	extern void MySigHandler(int signo);
	extern void MySigHandler_Init(pfnErrorHandleFunc pfn = NULL);
	extern void MySigHandler_Fini();
}

#endif //_pw_error_handler_
