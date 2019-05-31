#ifndef _pw_iconv_
#define _pw_iconv_

#include "iconv.h"
#include <string>

namespace pwutils
{
	std::string  utf8_to_mbs(const std::string* input);
	std::string  utf8_to_mbs(const std::string& input);
	std::string  utf8_from_mbs(const std::string* input);
	std::string  utf8_from_mbs(const std::string& input);
}

#endif // _pw_iconv_