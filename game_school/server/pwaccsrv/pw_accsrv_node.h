#ifndef _pw_accsrv_node_
#define _pw_accsrv_node_

#include "pwdist_node.h"
#include "pw_ngs_def.h"
#include "pw_sync.h"

namespace pwaccsrv
{
	const int max_service_port = pwngs::max_accsrv_service_port;
	
	class Node : public pwdist::Node
	{
	public:
		Node();
		virtual ~Node();
	};
}

typedef pwutils::Singleton<pwaccsrv::Node,pwutils::ThreadMutex> pwaccsrv_Node;

#endif //_pw_accsrv_node_