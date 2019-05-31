#ifndef _pw_gdb_stdint_
#define _pw_gdb_stdint_

//#include "pw_types.h"

#ifndef _MSC_VER
	#define __max(a,b)  (((a) > (b)) ? (a) : (b))
	#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

	typedef long long int64;
	typedef unsigned long long uint64;
	typedef long long sint64;
	typedef int int32;
	typedef unsigned int uint32;
	typedef unsigned int uint;
	typedef short int16;
	typedef unsigned short uint16;
	typedef char sint8;
	typedef unsigned char uint8;

#endif // _pw_gdb_stdint_