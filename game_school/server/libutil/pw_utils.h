#ifndef _pw_string_
#define _pw_string_

#include "pw_def.h"

namespace pwutils
{
	extern int		strcmp(const char* str1,const char* str2);
	extern int		stricmp(const char* str1,const char* str2);
	extern sint64 	atoi(const char* str);
	extern sint64 	atoi(const char* str,int base);
	extern double 	atof(const char* str);
	extern void 	itoa(char* str,sint64 val);
	extern std::string itoa2(sint64 val);

	extern void 	ftoa(char* str,double val);
	extern char* 	strncpy(char* dst,const char* src,size_t len);
	extern int		floatcmp(float value1,float value2);
	extern void		substr( const char* src, const char* dest, char* result, int32 len );
	extern sint64 	rdtsc();
	extern sint64 	random();
	extern int 		random(int start,int end);
	extern float 	random(float start,float end);
	extern char* 	strlower(char* str);
	extern char* 	strupper(char* str);
	extern bool		is_between(float start,float end,float value);
	extern bool		is_between(int64 start,int64 end,int64 value);
	extern bool		is_between(int32 start,int32 end,int32 value);
	extern float	clamp(float ho,float lo,float value);
	extern int		clamp(int ho,int lo,int value);
	extern bool		strtobool(const char* text);
	extern bool		isNumber(const char* text);
	extern void		tohex(int64 val,char* obuf,size_t len);
	extern void		tohex(const char* ibuf,size_t ilen,char* obuf,size_t& olen);
	extern void		create_token(char* buf,size_t len);
	extern char*	strncat(char* dest,const char* src,size_t destlen);

	extern int64	make_global_id(int64 server_group,int64 incr_id);
	extern int64	make_global_id(int64 server_group,int64 server,int64 incr_id);
	extern int64	extract_global_incrid(int64 server_group,int64 id);
	extern void		bits_copy(const void* _src,int srcStart,int srcCount,void* _dst,int dstStart);
	extern void		uuidgen(char* buf);
	extern void		unlink(const char* filename);
	extern int32	bkdr_hash(const char* str);
	extern int64	bkdr_hash_and_sum(const char* str);
	extern float	ushort2float(uint16 v);
	extern uint16	float2ushort(float v);
	extern int64	city_hash(const void* buf,size_t len,int64 seed);
	extern void		set_thread_name(const char* name);
	extern void		string_trim(std::string& s);
	extern bool		read_file_to_string(const char* filename,std::string& content);
	extern void		make_temp_filename(std::string& filename);

	extern bool		is_localip(const char* ip);

	extern void	make_random_pswd(char* buf,size_t pswd_len);

	extern void valist_to_stringlist(const char* format,va_list argptr,std::vector<std::string>& vtString);

	template<typename T> T& random_select(T& v1,float odd1,T& v2,float odd2)
	{
		float r = random(0.0f,odd1 + odd2);

		if(odd1 >= odd2)
		{
			if(r < odd2)
				return v2;
			return v1;
		}
		
		if(r < odd1)
			return v1;
		return v2;
	}

	template<typename T> T abs(const T& v)
	{
		if(v < 0)
			return -v;
		return v;
	}

	inline bool is_legal(const float& v)
	{
		return !isinff(v) && !isnanf(v);
	}

	template<typename T> bool is_vector3_legal(const T& v)
	{
		return is_legal(v.x) && is_legal(v.y) && is_legal(v.z);
	}

	struct SRandomer
	{
	public:
		ptrdiff_t operator()(ptrdiff_t max)
		{
			float d = pwutils::random(0.0f,1.0f);
			return static_cast<ptrdiff_t>(d * max);
		}

	};

	struct SStringHasher
	{
		int32 operator()(std::string* str)
		{
			return bkdr_hash(str->c_str());
		}
	};

	struct SIntegerHasher
	{
		int32 operator()(int32* val)
		{
			return *val;
		}
	};

	struct SLongHasher
	{
		int32 operator()(int64* val)
		{
			return (*val) % 0x7fffffff;
		}
	};

	template<class T> struct SObjectIdHasher
	{
		int32 operator()(T* t)
		{
			SIntegerHasher h;
			return h(&t->id);
		}
	};
}

#endif //_pw_string_