
#ifndef _pw_connsrv_node_
#define _pw_connsrv_node_

#include "pwdist_node.h"
#include "pwdist_port_generic.h"
#include "pw_ngs_def.h"
#include "pw_sync.h"

namespace pwconnsrv
{
	const int max_service_port = pwngs::max_connsrv_service_port;
	
	// 连接服务器id
	extern sint64 g_nServerId;
	extern std::string g_strLoginNode;
	extern std::string g_strLoginPort;
	
	class Node : public pwdist::Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		pwdist::PortBase* GetRandomPort();
	public:
		pwdist::int64 MakeConnectionID();
	private:
		pwutils::ThreadMutex m_objLock;
	private:
		int64 m_nLastID;
	};
}

extern pwconnsrv::Node g_objConnsrvNode;

#endif //_pw_connsrv_node_