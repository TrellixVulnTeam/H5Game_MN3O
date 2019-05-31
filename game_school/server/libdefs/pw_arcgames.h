#ifndef _pw_arcgames_
#define _pw_arcgames_

#include "pw_def.h"

namespace pwngs
{
	struct ArcGames
	{
		static void MakeSig( std::string& result,const unsigned char* key,size_t keylen,const unsigned char* text,size_t textlen);
		static void PerformRequest(std::string& result,const std::string& request);
	};
}


#endif // _pw_arcgames_