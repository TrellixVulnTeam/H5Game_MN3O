#ifndef _pw_chunk_
#define _pw_chunk_

#include "pw_types.h"
#include <string>

namespace pwngs
{
	struct Chunk
	{
		char* buf;
		int32 len;

		Chunk()
			: buf(NULL)
			, len(0)
		{
		}

		Chunk(const void* b,int32 l)
			: buf((char*)b)
			, len(l)
		{

		}

		Chunk(std::string& str)
			: buf((char*)str.c_str())
			, len(str.length())
		{

		}
	};
}


#endif // _pw_chunk_