#include "pw_zlib_utils.h"
#include "zlib.h"
#include <stdlib.h>

namespace pwutils
{
	int __compress( char* dest,int* destLen,const char* src,int srcLen )
	{
		Bytef* outbuf = (Bytef*)dest;
		uLongf outlen = *destLen;

		int result = compress(outbuf,&outlen,(Bytef*)src,(uLongf)srcLen);
		*destLen = outlen;
		return result;
	}

	int __uncompress( char* dest,int* destLen,const char* src,int srcLen )
	{
		Bytef* outbuf = (Bytef*)dest;
		uLongf outlen = *destLen;

		int result = uncompress(outbuf,&outlen,(Bytef*)src,(uLongf)srcLen);
		*destLen = outlen;
		return result;
	}

	int __compressWithLen( char* dest,int* destLen,const char* src,int srcLen )
	{
		const int cst_prefix_size = sizeof(int);

		*destLen -= cst_prefix_size;

		int result = __compress(&dest[cst_prefix_size],destLen,src,srcLen);
		if( result == Z_OK)
		{
			*(int*)dest = srcLen;
			*destLen += cst_prefix_size;
		}
		return result;
	}

	int __uncompressWithLen( char* dest,int* destLen,const char* src,int srcLen )
	{
		const int cst_prefix_size = sizeof(int);

		if(src == 0 || srcLen < cst_prefix_size)
			return Z_STREAM_ERROR;

		int len = *((int*)src);

		if(*destLen < len)
		{
			*destLen = len;
			return Z_BUF_ERROR;
		}
		return __uncompress(dest,destLen,&src[cst_prefix_size],srcLen - cst_prefix_size);
	}

	int __uncompressWithLenAuto( const char* src,int srcLen,char*& outbuf,int& outlen )
	{
		outlen = 0;
		__uncompressWithLen(0,&outlen,src,srcLen);
		outbuf = (char*)malloc(outlen);
		return __uncompressWithLen(outbuf,&outlen,src,srcLen);
	}

}