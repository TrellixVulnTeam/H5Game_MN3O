#ifndef PW_FIXED_STRING_H
#define PW_FIXED_STRING_H

#include <string.h>

#ifndef __min
	#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef __max
	#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

namespace pwutils
{
    struct fixed_string_base
    {
		char* buf;
		size_t len;
    };

	// 这个类内只能有char[],不能加别的任何成员
    template<unsigned LEN> class fixed_string
    {
    public:
		fixed_string(const char* str,size_t len)
		{
			memset(m_szString,0,sizeof(m_szString));
			set(str,len);
		}
		fixed_string(const char* str)
		{
			memset(m_szString,0,sizeof(m_szString));
			set(str,strlen(str));
		}
		fixed_string(const std::string& str)
		{
			memset(m_szString,0,sizeof(m_szString));
			set(str.c_str(),str.length());
		}
		fixed_string()
		{
			memset(m_szString,0,sizeof(m_szString));
		}
        void set(const char* msg,size_t len)
        {
			unsigned size = __min(len,LEN);
			strncpy(m_szString,msg,size);
			m_szString[size] = 0;
        }

		fixed_string<LEN>& operator =(const char* text)
		{
			this->set(text,strlen(text));
			return *this;
		}

		operator const char*() const
		{
			return m_szString;
		}

		operator char*()
		{
			return m_szString;
		}

		operator fixed_string_base ()
		{
			fixed_string_base r;
			r.buf = this->m_szString;
			r.len = LEN;
			return r;
		}

		const char* c_str() const
		{
			return m_szString;
		}

		bool operator<(const fixed_string<LEN>& r) const
		{
			return memcmp(m_szString,r.m_szString,LEN) == -1;
		}

		bool operator==(const fixed_string<LEN>& r) const
		{
			return strcmp(r.m_szString,m_szString) == 0;
		}

		bool operator==(const char* val) const
		{
			return strcmp(val,m_szString) == 0;
		}

		bool operator!=(const char* val) const
		{
			return strcmp(val,m_szString) != 0;
		}

		size_t capacity()
		{
			return LEN;
		}

		size_t length() const
		{
			return strlen(m_szString);
		}
    protected:
        char m_szString[LEN+1];
    };
}

#endif // PW_FIXED_STRING_H
