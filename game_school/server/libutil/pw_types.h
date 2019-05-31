#ifndef _pw_types_
#define _pw_types_

#ifndef nullptr	
#if _MSC_VER <= 1500
	#define nullptr 0L
#endif
#endif

#ifdef __linux
	#include <inttypes.h>
	#pragma GCC diagnostic ignored "-Winvalid-offsetof"
	#pragma G++ diagnostic ignored "-Winvalid-offsetof"
#endif

#ifdef _MSC_VER
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef __int32 sint32;
	typedef unsigned __int32 uint32;
	typedef __int64 sint64;
	typedef unsigned __int64 uint64;
#else
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef int32_t sint32;
	typedef uint32_t uint32;
	typedef long long sint64;
	typedef unsigned long long uint64;
#endif

	typedef sint32 int32;
	typedef sint64 int64;
	typedef sint16 int16;

	typedef int sint;
	typedef unsigned int uint;

	typedef char* char_ptr;
	typedef const char* const_char_ptr;
	typedef unsigned char* byte_ptr;
	typedef const unsigned char* const_byte_ptr;

	typedef sint64 OBJID;
	typedef sint64 hrtime_t;

	const uint32 cst_max_uint32 = (uint32)-1;
	const uint64 cst_max_uint64 = (uint64)-1;

#define _safe_delete(x) if(x != 0) { delete x; x = 0; }
#define _safe_delete_array(x) if(x != 0) { delete [] x; x = 0; }
#define _safe_unref(x) if(x != 0) { x->unref(); x = 0; }

#ifndef _MSC_VER
#define _countof(X) (sizeof(X)/sizeof(X[0]))

#endif

#ifdef _MSC_VER
	#define _offsetof(s,m)   (size_t)( (ptrdiff_t)&(((s *)0)->m) )
#else
	#define _offsetof(s,m)   __builtin_offsetof(s,m)
#endif
#define _abs(x)  ((x) < 0 ? (-(x)) : (x))

#endif // _pw_types_

