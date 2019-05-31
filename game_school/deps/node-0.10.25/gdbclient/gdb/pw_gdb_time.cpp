#include "pw_gdb_time.h"
#include "pw_gdb_platform.h"
#include <time.h>

#ifdef __linux
	#include <sys/time.h>
#endif

// #undef localtime_r

namespace pwutils
{
	void mylocaltime_r(time_t* t,tm* tt)
	{
#ifdef __linux
		::localtime_r(t,tt);
#else
		::localtime_s(tt,t);
#endif
	}

	namespace time
	{
#ifdef _MSC_VER
		static int64 g_nTimeScaleFactor = 0LL;

		int64 time_scale_factor()
		{
			if(g_nTimeScaleFactor == 0LL)
				::QueryPerformanceFrequency((LARGE_INTEGER*)&g_nTimeScaleFactor);
			return g_nTimeScaleFactor;
		}

		int64 get()
		{
			int64 result = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&result);
			return result;
		}
#else

		int64 time_scale_factor()
		{
			return 1000;
		}

		int64 get()
		{
			timespec t;
			::clock_gettime(CLOCK_MONOTONIC,&t);
			return (int64)t.tv_sec * 1000 + t.tv_nsec / 1000000;
		}
#endif

		// -----------------------------------------------------------------------------

		int64 Usec(sint64 n)
		{
			return n * time_scale_factor() / (1000 * 1000);
		}
		int64 Msec(sint64 n)
		{
			return n * time_scale_factor() / 1000;
		}
		int64 Second(sint64 n)
		{
			return n * time_scale_factor();
		}

		std::string str()
		{
			char buf[100] = "";
			pwutils::time::str(buf,sizeof(buf));
			return std::string(buf);
		}

		std::string str( int64 t )
		{
			char buf[100] = "";
			pwutils::time::str(t,buf,sizeof(buf));
			return std::string(buf);
		}

		void str(char* buf,size_t len)
		{
			time_t curr;
			::time(&curr);
			return pwutils::time::str(curr,buf,len);
		}

/*

		void strYYYYMMDD( char* buf,size_t len,bool hasSplit )
		{
			time_t curr;
			::time(&curr);
			return pwutils::time::strYYYYMMDD(curr,buf,len,hasSplit);
		}

		void strYYYYMMDD( int64 t,char* buf,size_t len,bool hasSplit )
		{
			time_t curr;
			struct tm tmcurr = {0};

			curr = (time_t)t;
			mylocaltime_r(&curr,&tmcurr);
			if(hasSplit)
				strftime(buf,len,"%Y-%m-%d",&tmcurr);
			else
				strftime(buf,len,"%Y%m%d",&tmcurr);
		}
*/

		void str( int64 t,char* buf,size_t len )
		{
			time_t curr;
			struct tm tmcurr = {0};

			curr = (time_t)t;
			mylocaltime_r(&curr,&tmcurr);
			strftime(buf,len,"%Y-%m-%d %H:%M:%S",&tmcurr);
		}

		std::string date()
		{
			char buf[100] = "";
			pwutils::time::date(buf,sizeof(buf));
			return std::string(buf);
		}

		void datetime( SDateTime& out )
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr,&tmcurr);

			out.year = tmcurr.tm_year + 1900;
			out.month = tmcurr.tm_mon + 1;
			out.day = tmcurr.tm_mday;
			out.hour = tmcurr.tm_hour;
			out.minute = tmcurr.tm_min;
			out.second = tmcurr.tm_sec;
		}

		void date( char* buf,size_t len )
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr,&tmcurr);
			strftime(buf,len,"%Y-%m-%d",&tmcurr);
		}


		int64 diff_us(sint64 n1,sint64 n2)
		{
			return (n1 - n2) * 1000 * 1000 / time_scale_factor();
		}

		int64 diff_ms(sint64 n1,sint64 n2)
		{
			return (n1 - n2) * 1000 / time_scale_factor();
		}

		int64 diff_sec(sint64 n1,sint64 n2)
		{
			return (n1 - n2) / time_scale_factor();
		}

		float tick2second( sint64 tick )
		{
			return (float)((double)tick / (double)time_scale_factor());
		}

		sint64 clib_time()
		{
			time_t result = 0;
			::time(&result);
			return result;
		}

		sint64 clib_time_diff_sec(sint64 _new,sint64 _old)
		{
			if(_new < 0)
				_new = clib_time();
			return _new - _old;
		}

		sint64 clib_time_diff_minute(sint64 _new,sint64 _old)
		{
			sint64 diff = _new - _old;
			return diff / 60;
		}

		sint64 clib_time_diff_hour(sint64 _new,sint64 _old)
		{
			sint64 diff = _new - _old;
			return diff / 3600;
		}

		sint64 clib_time_diff_day(sint64 _new,sint64 _old)
		{
			sint64 diff = _new - _old;
			return diff / (3600 * 24);
		}

		sint64 clib_time_diff_week(sint64 _new,sint64 _old)
		{
			sint64 diff = _new - _old;
			return diff / (3600 * 24 * 7);
		}

		bool clib_is_same_day( sint64 n1,sint64 n2 )
		{
			struct tm tm1 = {0};
			struct tm tm2 = {0};
		
			time_t t1 = n1;
			time_t t2 = n2;
			mylocaltime_r(&t1,&tm1);
			mylocaltime_r(&t2,&tm2);
		
			return tm1.tm_mday == tm2.tm_mday && tm1.tm_mon == tm2.tm_mon && tm1.tm_year == tm2.tm_year;
		}

		bool clib_is_new_day(sint64 t,int32 splithour,int32 splitminute,int32 splitsecond)
		{
			int64 today_begin = pwutils::time::mktimeofthisday(splithour,splitminute,splitsecond);
			
			return t < today_begin;
		}

		void sleep(unsigned int Millsec)
		{
#ifdef _MSC_VER
			::Sleep(Millsec);
#else
			long sec = Millsec / 1000;
			long nsec = (Millsec % 1000) * 1000000L;
			struct timespec rqtp;
			rqtp.tv_sec = sec;
			rqtp.tv_nsec = nsec;
			::nanosleep (&rqtp, 0);
#endif
		}

/*
		int64 ptime( const char* text,const char* fmt / *= "%Y-%m-%d %H:%M:%S"* / )
		{
			struct tm t = {0};
			strptime(text,fmt,&t);
			return mktime(&t);
		}

*/
		int64 getintervaltomorrow()
		{
			return mktimeofthisday(23,59,59) + 1 - clib_time();
		}

		int64 mktimeofthisday( const char* hhmmss )
		{
			int hour,minute,second;

			if(sscanf(hhmmss,"%d:%d:%d",&hour,&minute,&second) != 3)
				return -1;

			return mktimeofthisday(hour,minute,second);
		}

		int64 mktimeofthisday( int hour,int minute,int second )
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr,&tmcurr);

			tmcurr.tm_hour = hour;
			tmcurr.tm_min = minute;
			tmcurr.tm_sec = second;

			return mktime(&tmcurr);
		}

		int64 mktimeofoneday( int64 n,const char* hhmmss )
		{
			int hour,minute,second;

			if(sscanf(hhmmss,"%d:%d:%d",&hour,&minute,&second) != 3)
				return -1;

			return mktimeofoneday(n,hour,minute,second);
		}

		int64 mktimeofoneday( int64 n,int hour,int minute,int second )
		{
			time_t ntime = n;
			struct tm tmcurr = {0};

			mylocaltime_r(&ntime,&tmcurr);

			tmcurr.tm_hour = hour;
			tmcurr.tm_min = minute;
			tmcurr.tm_sec = second;

			return mktime(&tmcurr);
		}

		int64 mktimeofday(int month, int day)
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr, &tmcurr);

			tmcurr.tm_mon = month;
			tmcurr.tm_mday = day;
			tmcurr.tm_hour = 0;
			tmcurr.tm_min = 0;
			tmcurr.tm_sec = 0;

			return mktime(&tmcurr);
		}

		int64 mktimeofday(int year, int month, int day)
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr, &tmcurr);

			tmcurr.tm_year = year - 1900;
			tmcurr.tm_mon = month - 1;
			tmcurr.tm_mday = day;
			tmcurr.tm_hour = 0;
			tmcurr.tm_min = 0;
			tmcurr.tm_sec = 0;

			return mktime(&tmcurr);
		}

		int64 mktimeYYMMDD()
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr, &tmcurr);

			int64 yy = tmcurr.tm_year + 1900;
			int64 mm = tmcurr.tm_mon + 1;
			int64 dd = tmcurr.tm_mday;

			return yy * 10000 + mm * 100 + dd;
		}

		tm tmdate()
		{
			time_t curr;
			struct tm tmcurr = {0};

			::time(&curr);
			mylocaltime_r(&curr,&tmcurr);
			return tmcurr;
		}

		extern sint64 clib_timestamp()
		{
#ifdef _MSC_VER
			return clib_time() * 1000 + GetTickCount() % 1000;
#else
			struct timeval t;
			gettimeofday(&t,NULL);
			return clib_time() * 1000 + (t.tv_usec / 1000);
#endif
		}

		extern sint64 timestamp_diff_ms( int64 n1,int64 n2 )
		{
			int64 nseconds1 = n1 / 1000;
			int32 nmillsec1 = n1 % 1000;
			int64 nseconds2 = n2 / 1000;
			int32 nmillsec2 = n2 % 1000;

			return (nseconds1 - nseconds2) * 1000 + nmillsec1 - nmillsec2;
		}
	}

}
