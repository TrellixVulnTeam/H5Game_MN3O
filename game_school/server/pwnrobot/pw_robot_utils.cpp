#include "pw_robot_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void print_response( const char* fmt,... )
{
	char buf[4096] = "";
	va_list vl;
	va_start(vl,fmt);
	vsprintf(buf,fmt,vl);
	va_end(vl);

	printf("\t %s\n>",buf);
}
