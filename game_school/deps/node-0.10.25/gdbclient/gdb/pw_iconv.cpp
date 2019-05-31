#include "pw_iconv.h"

namespace pwutils
{

	class Encoding
	{
	public:
		Encoding()
		{
			m_hIconvToUtf8 = iconv_open("UTF-8","GBK");
			m_hIconvToGbk = iconv_open("GBK","UTF-8");
		}
	public:
		std::string toUTF8(const std::string& input)
		{
			return convert(m_hIconvToUtf8,input);
		}

		std::string toGBK(const std::string& input)
		{
			return convert(m_hIconvToGbk,input);
		}
	private:
		std::string convert(iconv_t ic,const std::string& input)
		{
			if(input.empty())
				return std::string();

			size_t ilen = input.length();
			const char* ibuf = input.c_str();

			size_t olen = (ilen + 1) * 4;
			size_t nlen = olen;
			char* obuf = (char*)alloca(olen);//&buf[0];
			char* obuf2 = obuf;

#ifdef _MSC_VER
			iconv(ic,&ibuf,&ilen,&obuf2,&olen);
#else
			iconv(ic,(char**)&ibuf,&ilen,&obuf2,&olen);
#endif

			return std::string(obuf,nlen - olen);
		}
	private:
		iconv_t m_hIconvToUtf8;
		iconv_t m_hIconvToGbk;
	};

	// ----------------------------------------------------------

	static Encoding g_objEncoding;

	// ----------------------------------------------------------

	Encoding* GetCurrentEncoding() 
	{
		return &g_objEncoding;
	}

	std::string utf8_from_mbs( const std::string& input )
	{
		Encoding* encoding = GetCurrentEncoding();
		return encoding->toUTF8(input);
	}

	std::string utf8_from_mbs( const std::string* input )
	{
		Encoding* encoding = GetCurrentEncoding();
		return encoding->toUTF8(*input);
	}

	std::string utf8_to_mbs( const std::string& input )
	{
		Encoding* encoding = GetCurrentEncoding();
		return encoding->toGBK(input);
	}

	std::string utf8_to_mbs( const std::string* input )
	{
		Encoding* encoding = GetCurrentEncoding();
		return encoding->toGBK(*input);
	}

}