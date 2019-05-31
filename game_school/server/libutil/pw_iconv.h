#ifndef _pw_iconv_
#define _pw_iconv_

#include "pw_def.h"
#include "iconv.h"

namespace pwutils
{
	std::string  utf8_to_mbs(const std::string* input);
	std::string  utf8_to_mbs(const std::string& input);
	std::string  utf8_from_mbs(const std::string* input);
	std::string  utf8_from_mbs(const std::string& input);

	extern void __CleanupThreadEncoding();

	extern std::string g_sDefaultEncoding;
}

#endif // _pw_iconv_