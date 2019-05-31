#ifndef _pw_strptime_
#define _pw_strptime_

#ifndef __linux
	char *strptime(const char *buf, const char *format, struct tm *tm);
#endif

#endif // _pw_strptime_