#ifndef _pw_back_trace_
#define _pw_back_trace_

#include <string>

extern void stack_trace();
extern std::string get_stack_trace(int depth = 50);

#endif //_pw_back_trace_