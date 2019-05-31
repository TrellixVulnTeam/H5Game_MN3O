
#ifndef pwDef_h__
#define pwDef_h__

#ifndef pid_t
	typedef int pid_t;
#endif

#ifdef _MSC_VER

	#pragma warning(disable:4005)

	#ifndef _HAVE_STRUCT_TIMESPEC
		#define HAVE_STRUCT_TIMESPEC
	#endif

	#define HAVE_MODE_T
	#define _CRT_SECURE_NO_WARNINGS
	#pragma warning(disable:4996)
#else
	#define __max(a,b)  (((a) > (b)) ? (a) : (b))
	#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#include "pthread.h"
#include <cassert>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <iostream>
#include <functional>
#include <sstream>
#include <set>

#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_priority_queue.h"
#include "tbb/concurrent_queue.h"
#include "tbb/concurrent_vector.h"


#include <expat.h>

#ifdef _MSC_VER


	#include <float.h>

	#pragma warning(disable:4996)
	#pragma warning(disable:4800)

	#undef std_unordered_map
	#undef std_unordered_set
	#define std_unordered_map std::tr1::unordered_map
	#define std_unordered_set std::tr1::unordered_set
	#define std_unordered_multimap std::tr1::unordered_multimap

	#define isinff(x) (_finite(x) == 0)
	#define isnanf(x) (_isnan(x))

	#define snprintf _snprintf
#else
	#define std_unordered_map std::unordered_map
	#define std_unordered_set std::unordered_set
	#define std_unordered_multimap std::unordered_multimap

	#include <math.h>
#endif

#include "pw_types.h"

extern bool g_bAllowAssert;

#define pwassert(a) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( " ***ASSERT*** " << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); return ; } } 
#define pwassertn(a) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( " ***ASSERT*** "  << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); return 0; } } 
#define pwassertf(a) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( " ***ASSERT*** "  << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); return -1; } } 
#define pwassertr(a,rr) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( " ***ASSERT*** "  << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); return rr; } } 
#define pwasserte(a) { bool abcdefg = (a); if(!abcdefg) {  gErrorStream( " ***ASSERT*** "  << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); } } 
#define pwassertop(a,op) { bool abcdefg = (a); if(!abcdefg) {  gErrorStream( " ***ASSERT*** "  << __FILE__ << "," << __LINE__ << ":" << #a); if(g_bAllowAssert) assert(a); op; } } 

#define stdassert(a) { bool abcdefg = (a); if(!abcdefg) { std::cout << __FILE__ << "," << __LINE__ << ":" << #a; if(g_bAllowAssert) assert(a); return ; } } 
#define stdassertn(a) { bool abcdefg = (a); if(!abcdefg) { std::cout << __FILE__ << "," << __LINE__ << ":" << #a; if(g_bAllowAssert) assert(a); return 0; } } 
#define stdassertr(a,rr) { bool abcdefg = (a); if(!abcdefg) { std::cout << __FILE__ << "," << __LINE__ << ":" << #a; if(g_bAllowAssert) assert(a); return rr; } } 
#define stdasserte(a) { bool abcdefg = (a); if(!abcdefg) { std::cout << __FILE__ << "," << __LINE__ << ":" << #a; if(g_bAllowAssert) assert(a); } } 

#define pwreportvars(a,v1) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( __FILE__ << "," << __LINE__ << ":" << #a << "," << v1); } } 
#define pwreport_vars2(a,v1,v2) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( __FILE__ << "," << __LINE__ << ":" << #a << ",v1=" << v1 << ",v2=" << v2); } } 
#define pwreport_vars3(a,v1,v2,v3) { bool abcdefg = (a); if(!abcdefg) { gErrorStream( __FILE__ << "," << __LINE__ << ":" << #a << ",v1=" << v1 << ",v2=" << v2 << ",v3=" << v3); } } 

#define PWCHECK pwassert
#define PWCHECKF pwassertn
#define PWCHECKR pwassertr
#define PWCHECKN pwasserte


#define if_fail(x) if((x) != 0)
#define if_succ(x) if((x) == 0)

namespace mongo { class BSONObj; class BSONObjBuilder; }

#define PreDefineOrm(x) namespace orm { class x; }
#define PreDefineGoogleMsg() namespace google { namespace protobuf { class Message; } }

#define PreDefineMsgW(x) namespace protocol { namespace worldsrv { class x; } }
#define PreDefineMsgA(x) namespace protocol { namespace accsrv { class x; } }
#define PreDefineMsgC(x) namespace protocol { namespace ctrlsrv { class x; } }
#define PreDefineMsgD(x) namespace protocol { namespace dbsrv { class x; } }

#define MsgW(x) pwngs::protocol::worldsrv::x
#define MsgA(x) pwngs::protocol::accsrv::x
#define MsgC(x) pwngs::protocol::ctrlsrv::x
#define MsgD(x) pwngs::protocol::dbsrv::x

#ifdef _DEBUG
	const size_t cst_tmp_buf_size  = 1*1024*1024;
#else
	const size_t cst_tmp_buf_size  = 3*1024*1024;
#endif
	
#endif // pwDef_h__
