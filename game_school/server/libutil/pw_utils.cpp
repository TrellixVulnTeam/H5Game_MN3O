#include "pw_utils.h"
#ifdef _MSC_VER
	#include <string.h>
#else
	#include <cstring>
#endif
#include <sstream>
#include "pw_random.h"
#include "pw_logger.h"

#ifdef _MSC_VER
	#include <ObjBase.h>
#else
	#include <uuid/uuid.h>
#endif

#include "tokenizer.h"
#include <stdlib.h>
#include "cityhash/city.h"

#ifdef _MSC_VER
	#include <process.h>
#endif

namespace pwutils
{
	int strcmp(const char* str1,const char* str2)
	{
		return ::strcmp(str1,str2);
	}

	int stricmp(const char* str1,const char* str2)
	{
#ifdef __linux__
		return ::strcasecmp(str1,str2);
#else
		return ::stricmp(str1,str2);
#endif
	}

	sint64 	atoi(const char* str,int base)
	{
		if(str == NULL)
			return 0LL;
#ifdef _MSC_VER
		return (sint64)::_strtoi64(str,NULL,base);
#else
		return (sint64)::strtoll(str,NULL,base);
#endif
	}

	sint64 atoi(const char* str)
	{
		if(str == NULL)
			return 0LL;

#ifdef _MSC_VER
		return _atoi64(str);
#else
		return ::atoll(str);
#endif
	}

	double atof(const char* str)
	{
		return ::atof(str);
	}

	std::string itoa2( sint64 val )
	{
		char buf[100] = "";
		itoa(buf,val);
		return std::string(buf);
	}

	void itoa(char* str,sint64 val)
	{
#ifdef _MSC_VER
		_i64toa(val,str,10);
#else
		sprintf(str,"%lld",val);
#endif
	}

	void ftoa(char* str,double val)
	{
		sprintf(str,"%f",val);
	}

	char* strncpy(char* dst,const char* src,size_t len)
	{
#ifdef _MSC_VER
		return ::strncpy(dst,src,len);
#else
		return ::strncpy(dst,src,len);
#endif
	}

	char* strncat( char* dest,const char* src,size_t destlen )
	{
		return ::strncat(dest,src,destlen);
	}

	int floatcmp(float value1,float value2)
	{
		const float fEpsilon = 0.000001f;
		float fDelta = fabs(value1-value2);

		if (fDelta > fEpsilon)
			return 1;
		else
			return 0;
	}

	void substr( const char* src, const char* dest, char* result, int32 len )
	{
		std::string strSrc(src);
		std::string strDest(dest);
		int pos = strSrc.find( strDest );
		if( std::string::npos == pos )
		{
			::strncpy(result, src, len );
		}
		else
		{
			std::string newSrc = strSrc.substr( strDest.length(), strSrc.length() );
			::strncpy(result,newSrc.c_str(), len );
		}
	}
 
	sint64 rdtsc()
	{
#ifdef _MSC_VER
		_asm rdtsc;
		// 		LARGE_INTEGER result = {0};
		// 		if(!QueryPerformanceCounter(&result))
		// 			assert(false && "System NoSupport QueryPerformanceCounter");
		// 		return result.LowPart;
		// return (int)GetTickCount();
#else
		unsigned int lo;
		unsigned int hi;
		__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
		return (((sint64)hi) << 32) + lo;
#endif

	}

	sint64 random()
	{
		return g_objRandomGenerator.Gen();
	}

	int random(int start,int end)
	{
		if(start == end)
			return start;
		unsigned int r = random() % 0xffffffff;
		return (r % (end - start)) + start;
	}

	float random(float start,float end)
	{
		unsigned int r = random() % 0xffffffff;
		double d = (double)r / (double)0xffffffff;
		return (float)(start + (end - start) * d);
	}
	
	char* strlower(char* str)
	{
		std::locale loc;

		for(size_t i = 0; ;++i)
		{
			if(str[i] == 0)
				break;
#ifdef _MSC_VER
			str[i] = ::tolower(str[i]);
#else
			str[i] = std::tolower(str[i],loc);
#endif
		}
		return str;
	}
	
	char* strupper(char* str)
	{
		std::locale loc;

		for(size_t i = 0; ;++i)
		{
			if(str[i] == 0)
				break;
#ifdef _MSC_VER
			str[i] = ::toupper(str[i]);
#else
			str[i] = std::toupper(str[i],loc);
#endif
		}
		return str;
	}

	bool is_between( float start,float end,float value )
	{
		if(start > end)
			std::swap(start,end);
		return value >= start && value <= end;
	}

	bool is_between( int64 start,int64 end,int64 value )
	{
		if(start > end)
			std::swap(start,end);
		return value >= start && value <= end;
	}

	bool is_between( int32 start,int32 end,int32 value )
	{
		if(start > end)
			std::swap(start,end);
		return value >= start && value <= end;
	}

	float clamp( float ho,float lo,float value )
	{
		if(value < lo)
			return lo;
		else if(value >= ho)
			return ho;
		return value;
	}

	int clamp( int ho,int lo,int value )
	{
		if(value < lo)
			return lo;
		else if(value >= ho)
			return ho;
		return value;
	}

	bool strtobool( const char* text )
	{
		if(stricmp(text,"true") == 0)
			return true;
		if(stricmp(text,"false") == 0)
			return false;
		if(stricmp(text,"1") == 0)
			return true;
		if(stricmp(text,"0") == 0)
			return false;
		return atoi(text) != 0;
	}

	bool isNumber( const char* text )
	{
		size_t len = strlen(text);
		for(size_t i = 0; i < len; ++i)
		{
			if(!(text[i] >= '0' && text[i] <= '9'))
			{
				return false;
			}
		}
		return true;
	}

	const char __HEX[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
	};


	void tohex( int64 val,char* obuf,size_t len )
	{
		std::stringstream ss;
		ss << std::hex << val << std::dec;
		strncpy(obuf,ss.str().c_str(),len);
	}

	void tohex( const char* ibuf,size_t ilen,char* obuf,size_t& olen )
	{
		size_t outlen = 0;
		for (size_t i = 0; i < ilen && outlen < olen; ++i) {
			int t = (unsigned char)ibuf[i];
			int a = t / 16;
			int b = t % 16;
			obuf[outlen] = __HEX[a];
			++outlen;
			obuf[outlen] = __HEX[b];
			++outlen;
		}
		obuf[outlen] = 0;
		olen = outlen;
	}

	void create_token(char* buf,size_t len)
	{
		static const char s_objTokenPool[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()-=+_";

		for(size_t i = 0; i < (len - 1); ++i)
		{
			int r = pwutils::random(0,_countof(s_objTokenPool));
			buf[i] = s_objTokenPool[r];
		}
		buf[len - 1] = '\0';
	}

	
// 	long long make_id(long long group,long long incrid)
// 	{
// 		if(group > 8191LL)
// 		{
// 			long long group_48 = group >> 13;
// 			long long group_50 = group % 0x2000;
// 			return (group_50 << 50) + (group_48 << 48) + incrid;
// 		}
// 		return (group << 50) + incrid;
// 	}

	int64	make_global_id(int64 server_group,int64 incr_id)
	{
		return (server_group << 50) + incr_id;
	}

	int64	make_global_id(int64 server_group,int64 server,int64 incr_id)
	{
		return (server_group << 50) + (server << 46) + incr_id;
	}

	int64	extract_global_incrid(int64 server_group,int64 id)
	{
		if(server_group == 0)
			return id;
		return id % (server_group << 50);
	}

	void bits_copy(const void* _src,int srcStart,int srcCount,void* _dst,int dstStart)
	{
		const unsigned char* src = (unsigned char*)_src;
		unsigned char* dst = (unsigned char*)_dst;
		for(int i = 0; i < srcCount; ++i)
		{
			int startIndex = (srcStart + i) / 8;
			int startBit = (srcStart + i) % 8;

			int dstIndex = (dstStart + i) / 8;
			int dstBit = (dstStart + i) % 8;

			unsigned char tmps = 1 << startBit;
			unsigned char tmpd = 1 << dstBit;

			dst[dstIndex] &= ~tmpd;

			if(src[startIndex] & tmps)
				dst[dstIndex] |= tmpd;
		}
	}


	static long g_passwords_num = 0;
	static char g_passwords[100] = {0};

	int initpswd()
	{
		if(g_passwords_num != 0)
			return 0;

		for(char c = 'a'; c <= 'z'; ++c)
		{
			g_passwords[g_passwords_num] = c;
			++g_passwords_num;
		}

		for(char c = '0'; c <= '9'; ++c)
		{
			g_passwords[g_passwords_num] = c;
			++g_passwords_num;
		}
		return 0;
	}

	extern void make_random_pswd( char* buf,size_t pswd_len )
	{
		if(g_passwords_num == 0)
			initpswd();

		for(size_t i = 0; i < pswd_len; ++i)
		{
			int n = (int)pwutils::random(0,g_passwords_num);
			buf[i] = g_passwords[n];
		}
	}

#ifdef _MSC_VER

	static void GetStringFromGUID(GUID& FilterCLSID, char* lpszString)
	{
		sprintf(lpszString, "%08X_%04X_%04X_%02X%02X_%02X%02X%02X%02X%02X%02X",
			FilterCLSID.Data1, FilterCLSID.Data2, FilterCLSID.Data3,
			FilterCLSID.Data4[0], FilterCLSID.Data4[1], FilterCLSID.Data4[2], FilterCLSID.Data4[3], 
			FilterCLSID.Data4[4], FilterCLSID.Data4[5], FilterCLSID.Data4[6], FilterCLSID.Data4[7]
		);
	}
#endif

	extern void uuidgen( char* buf )
	{
/*
#ifdef _MSC_VER
		GUID guid;
		CoCreateGuid(&guid);
		GetStringFromGUID(guid,buf);
#else
		uuid_t uid;
		uuid_generate(uid);
		uuid_unparse(uid,buf);
#endif
*/
	}

	extern void unlink( const char* filename )
	{
#ifdef _MSC_VER
		DeleteFile(filename);
#else
		::unlink(filename);
#endif
	}

	extern int32 bkdr_hash( const char* str )
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
		unsigned int hash = 0;

		while (*str)
		{
			hash = hash * seed + (*str++);
		}

		return (hash & 0x7FFFFFFF);
	}

	extern int64 bkdr_hash_and_sum( const char* str )
	{
		int64 sum = 0;
		unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
		unsigned int hash = 0;

		while (*str)
		{
			sum += *str;
			hash = hash * seed + (*str++);
		}

		return (sum << 32) + (hash & 0x7FFFFFFF);
	}

	extern float ushort2float( uint16 v )
	{
		return v / 65535.0f;
	}

	extern uint16 float2ushort( float v )
	{
		return uint16(v * 65535.0f);
	}

	extern int64 city_hash( const void* buf,size_t len,int64 seed )
	{
		return (int64)cityhash::CityHash64WithSeed((const char*)buf,len,seed);
	}

	extern void valist_to_stringlist(const char* format,va_list argptr,std::vector<std::string>& vtString)
	{
		int len = strlen(format);
		for(int i = 0; i < len; ++i)
		{
			std::stringstream str;
			switch(format[i])
			{
			case 'i':
				str << va_arg(argptr,int32);
				break;
			case 'I':
				str << va_arg(argptr,int64);
				break;
			case 's':
				str << va_arg(argptr,const_char_ptr);
				break;
			default:
				pwassert(false && "invalid param type");
			}

			vtString.push_back(str.str());
		}
	}

#ifdef _MSC_VER

	const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)

	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

	void SetThreadName( DWORD dwThreadID, char* threadName)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}

	extern void set_thread_name( const char* name )
	{
		SetThreadName(GetCurrentThreadId(),strdup(name));
	}
#else

	#include <sys/prctl.h>
	
	extern void set_thread_name( const char* name )
	{
		prctl(PR_SET_NAME,strdup(name),0,0,0);
	}

#endif

	extern void string_trim( std::string& s )
	{
		if(s.empty())
			return;
		s.erase(0,s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}

	extern bool read_file_to_string( const char* filename,std::string& content )
	{
		FILE* f = fopen(filename,"r");
		if(f == NULL)
		{
			content = "open file failed";
			return false;
		}

		fseek(f,0,SEEK_END);
		size_t fsize = ftell(f);
		fseek(f,0,SEEK_SET);
		
		content.resize(fsize);
		fread(&content[0],fsize,1,f);
		fclose(f);

		return true;
	}

	static int64 ipaddrToLong(const char* ip) {   
		std::vector<std::string> strs;
		::tokenize(ip,strs,".");

		if(strs.size() != 4)
			return 0;

		int64 a = atoi(strs[0].c_str());
		int64 b = atoi(strs[1].c_str());
		int64 c = atoi(strs[2].c_str());
		int64 d = atoi(strs[3].c_str());

		return a * 256 * 256 * 256 + b * 256 * 256 + c * 256 + d;
	}

	extern bool is_localip( const char* ip )
	{
        int64 ipval = ipaddrToLong(ip);   
		if(ipval == 0)
			return false;

        /**  
        私有IP：
				A类  10.0.0.0-10.255.255.255  
				B类  172.16.0.0-172.31.255.255  
				C类  192.168.0.0-192.168.255.255  
				回环 127.0.0.1
        **/
		static int64 sPrivateIpadressVals[][2] = 
		{
			{ ipaddrToLong("10.0.0.0"),		ipaddrToLong("10.255.255.255"), },
			{ ipaddrToLong("172.16.0.0"),	ipaddrToLong("172.31.255.255"), },
			{ ipaddrToLong("192.168.0.0"),	ipaddrToLong("192.168.255.255"), },
			{ ipaddrToLong("127.0.0.1"),		ipaddrToLong("127.0.0.1"), },
		};

		for(size_t i = 0; i < _countof(sPrivateIpadressVals); ++i)
		{
			const int64* vals = sPrivateIpadressVals[i];

			if(is_between(vals[0],vals[1],ipval))
				return true;
		}
        return false;
	}

	extern void make_temp_filename( std::string& filename )
	{
		int pid = getpid();
		char prefix[64] = "";
		sprintf(prefix,"%d_",pid);

		char* name = tempnam(NULL,prefix);
		if(name != NULL)
		{
			filename = name;
			free(name);
		}
	}

}