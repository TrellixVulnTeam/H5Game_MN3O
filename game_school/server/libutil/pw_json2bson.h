#ifndef _pw_json2bson_
#define _pw_json2bson_

#include <string>

namespace pwutils
{
	extern bool json2bson(const char* jsonstr,size_t jsonlen,std::string& bson,std::string& error);
}


#endif // _pw_json2bson_