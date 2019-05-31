#ifndef _pw_time_
#define _pw_time_

#include <string>
#include "pw_gdb_stdint.h"

namespace pwutils
{
	namespace time
	{
		struct SDateTime
		{
			int year;
			int month;
			int day;
			int hour;
			int minute;
			int second;
		};

		extern int64 Usec(sint64 n);
		extern int64 Msec(sint64 n);
		extern int64 Second(sint64 n);

		extern int64 diff_us(sint64 n1,sint64 n2);
		extern int64 diff_ms(sint64 n1,sint64 n2);
		extern int64 diff_sec(sint64 n1,sint64 n2);

		extern float tick2second(sint64 tick);

		extern int64 get();
		extern int64 time_scale_factor();

		extern std::string str();
		extern std::string str(int64 t);
		extern std::string date();

		extern void str(char* buf,size_t len);
		extern void str(int64 t,char* buf,size_t len);

// 		extern void strYYYYMMDD(char* buf,size_t len,bool hasSplit = true);
// 		extern void strYYYYMMDD(int64 t,char* buf,size_t len,bool hasSplit = true);

		extern void date(char* buf,size_t len);
		extern void datetime(SDateTime& out);

//		extern int64 ptime(const char* text,const char* fmt = "%Y-%m-%d %H:%M:%S");
		extern int64 mktimeofthisday(const char* hhmmss);
		extern int64 mktimeofthisday(int hour,int minute,int second);
		extern int64 mktimeofoneday(int64 n,const char* hhmmss);
		extern int64 mktimeofoneday(int64 n,int hour,int minute,int second);
		// 现在到明天0点的秒数
		extern int64 getintervaltomorrow();
		extern int64 mktimeofday(int month, int day);
		extern int64 mktimeofday(int year, int month, int day);
		extern int64 mktimeYYMMDD();

		extern sint64 clib_time();
		extern sint64 clib_timestamp();
		extern sint64 timestamp_diff_ms(int64 n1,int64 n2);

		extern sint64 clib_time_diff_sec(sint64 _new,sint64 _old);
		extern sint64 clib_time_diff_minute(sint64 _new,sint64 _old);
		extern sint64 clib_time_diff_hour(sint64 _new,sint64 _old);
		extern sint64 clib_time_diff_day(sint64 _new,sint64 _old);
		extern sint64 clib_time_diff_week(sint64 _new,sint64 _old);

		extern bool   clib_is_same_day(sint64 n1,sint64 n2);

		// 判断t是否为新一的天(以splithour:splitminute:splitsecond)判断
		// 如 clib_is_new_day(t,6,0,0) t在当天6点之前，都返回true
		extern bool   clib_is_new_day(sint64 t,int32 splithour = 0,int32 splitminute = 0,int32 splitsecond = 0);

		extern void		sleep(unsigned int Millsec);
		extern tm		tmdate();
	}
}

#endif // _pw_time_
