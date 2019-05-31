#include "pw_backtrace.h"

#ifdef _MSC_VER
	#include <iostream>
	#include "pw_stack_walker_win32.h"

	std::string get_stack_trace(int depth)
	{
		std::string result;

		CStackWalker walker;
		std::vector<std::string> stacks;
		walker.GetCallstack(stacks,0,depth);

		for(size_t i = 0; i < stacks.size(); ++i)
		{
			result = result + stacks[i];
		}

		return result;
	}

	void stack_trace()
	{
		std::cout << get_stack_trace() << std::endl;
	}
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <execinfo.h>
	#include <stdlib.h>

	std::string get_stack_trace(int depth)
	{
		std::string result = "";
		
		void* buffer[1000];
		int n = backtrace(buffer,sizeof(buffer)/sizeof(buffer[0]));
		char** symbols = backtrace_symbols(buffer,n);
		for(int i = 0; i < n && i < depth; ++i)
		{
			result = result + std::string(symbols[i]) + "\n";
		}
		free(symbols);
		return result;
	}

	void stack_trace()
	{
		void* buffer[100];
		int n = backtrace(buffer,sizeof(buffer)/sizeof(buffer[0]));
		char** symbols = backtrace_symbols(buffer,n);

		printf("stack trace:\n");
		for(int i = 0; i < n; ++i)
		{
			printf("\t%s\n",symbols[i]);
		}
		free(symbols);
	}

#endif
