#ifndef _pwdist_common_
#define _pwdist_common_

#include "pwdist_def.h"
#include "pwdist_parameter.h"
#include <algorithm>
#include <cassert>

namespace pwdist
{

	class Node;
	class PortBase;
	class ICallableObject;
	class RemoteNode;

	// ------------------------------------------------------

	const size_t cst_max_def_len = 40;
	const size_t cst_max_name_len = 60;
	const size_t cst_max_addr_len = 60;
	const size_t cst_max_method_len = 60;

	const size_t cst_max_hierarchies = 3;

	// ------------------------------------------------------

	const size_t cst_max_buf_len = ::cst_tmp_buf_size;

	// ------------------------------------------------------

	const int32 msgid_ping = 10000;
	const int32 msgid_rpc = 30000;
	const int32 msgid_rpc_return = 40000;

	// ------------------------------------------------------

	struct CallEndpoint
	{
		char node[cst_max_name_len];
		char port[cst_max_name_len];
		int64 hierarchies[cst_max_hierarchies];
		int32 hierarchiesNum;

		void initial(const char* _node,const char* _port,int64* _hierarchies,int32 num);
	};

	// ------------------------------------------------------

	struct MsgCall
	{
		int32 msgid;
		int32 msglen;
		int32 flags;
		int64 callid;
		char def[cst_max_def_len];
		char method[cst_max_method_len];
		CallEndpoint sender;
		CallEndpoint target;
		Parameters params;

		size_t Bytes();

		// 从连续的内存块中载入
		size_t Load(char* buf,size_t len);
		// 保存到连的内存块
		size_t Save(char* buf,size_t len);
	};
	
	// ------------------------------------------------------

	struct MethodImpl;

	// ------------------------------------------------------

	struct MethodCall
	{
		PortBase* port;
		MsgCall* call;
		MethodImpl* method;
		ICallableObject* obj;
	};

	// ------------------------------------------------------

	typedef void (*pfnMethodImpl)(MethodCall* ctx);

	// ------------------------------------------------------

	enum 
	{
		METHOD_TYPE_NORMAL,
		METHOD_TYPE_STATIC,
		METHOD_TYPE_OBJECT,
	};

	struct MethodImpl
	{
		char type;
		char name[cst_max_method_len];
		char mdef[cst_max_def_len];
		bool enabled;
		pfnMethodImpl pfn;
	};

	template<class FN> struct StaticMethodImpl : public MethodImpl
	{
		FN fun;
	};

	template<class T,class FN> struct ObjectMethodImpl : public MethodImpl
	{
		T* obj;
		FN fun;
	};

	class INodeListener
	{
	public:
		~INodeListener() {}

	public:
		virtual int OnNodeUp(RemoteNode* node,bool reconnected) { return 0; }
		virtual int OnNodeReconnecting(RemoteNode* node) { return 0; }
		virtual int OnNodeDown(RemoteNode* node)  { return 0; }
	};

	// ------------------------------------------------------

	// ------------------------------------------------------

}

#endif