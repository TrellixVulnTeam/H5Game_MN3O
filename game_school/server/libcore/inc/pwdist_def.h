#ifndef _pwdist_def_
#define _pwdist_def_

#ifndef pid_t
	typedef int pid_t;
#endif

#include "pw_def.h"
#include "zmq.hpp"
#include "pthread.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_queue.h"


namespace pwdist
{
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

	typedef float float32;
	typedef double float64;

	typedef float dec32;
	typedef double dec64;

	typedef sint16 int16;
	typedef sint32 int32;
	typedef sint64 int64;

	typedef int sint;
	typedef unsigned int uint;

	typedef unsigned char* byte_ptr;
	typedef const unsigned char* const_byte_ptr;
	typedef char* char_ptr;
	typedef const char* const_char_ptr;

	class PortGeneric;
	class PortScripted;

	class ICallableObject;
	class FutureObject;

	class Port;
	class PortEx;

	struct MsgCall;

	const int max_name_len = 64;

}

#endif