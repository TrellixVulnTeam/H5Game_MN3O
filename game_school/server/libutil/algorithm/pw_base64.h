#ifndef _pw_base64_
#define _pw_base64_

#include <string>

namespace pwutils
{
	extern std::string base64_encode(const char* buf,int len);
	extern std::string base64_decode(const char* buf,int len);

	extern std::string EncodeB64(char const* bytes_to_encode, unsigned int in_len);
	extern std::string DecodeB64(std::string const& encoded_string);
}

#endif // _pw_base64_