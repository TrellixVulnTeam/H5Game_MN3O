#include "pw_iconv.h"
#include "pw_logger.h"
#include "pw_tss.h"
#include "pw_memory.h"

namespace pwutils
{

	std::string g_sDefaultEncoding("GBK");

	class Encoding
	{
	public:
		Encoding()
		{
			m_hIconvToUtf8 = iconv_open("UTF-8",g_sDefaultEncoding.c_str());
			assert(m_hIconvToUtf8 != (iconv_t)-1);

			m_hIconvToGbk = iconv_open(g_sDefaultEncoding.c_str(),"UTF-8");
			assert(m_hIconvToGbk != (iconv_t)-1);
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

	static ThreadSpecific<Encoding> g_objEncoding;

	// ----------------------------------------------------------

	extern void __CleanupThreadEncoding()
	{
		if(Encoding* result = g_objEncoding.get())
		{
			delete result;
			g_objEncoding.set(NULL);
		}
	}

	Encoding* GetCurrentEncoding() 
	{
		Encoding* result = g_objEncoding.get();
		if(result != NULL)
			return result;
		result = new Encoding();
		g_objEncoding.set(result);

		pwutils::memory::atthreadexit(&__CleanupThreadEncoding);
		return result;
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