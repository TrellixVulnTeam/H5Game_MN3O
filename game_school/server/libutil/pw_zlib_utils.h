#ifndef _pw_zlib_utils_
#define _pw_zlib_utils_

namespace pwutils
{
	extern int __compress(char* dest,int* destLen,const char* src,int srcLen);
	extern int __compressWithLen(char* dest,int* destLen,const char* src,int srcLen);
	extern int __uncompress(char* dest,int* destLen,const char* src,int srcLen);
	extern int __uncompressWithLen(char* dest,int* destLen,const char* src,int srcLen);
	extern int __uncompressWithLenAuto(const char* src,int srcLen,char*& outbuf,int& outlen);
}

#endif // _pw_zlib_utils_