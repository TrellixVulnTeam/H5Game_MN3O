#ifndef _pw_worldsrv_node_
#define _pw_worldsrv_node_

#include "pwdist_node.h"
#include "pw_sync.h"

namespace pwworldsrv
{
	// --------------------------------------------------------
	
	class Node : public pwdist::Node
	{
	public:
		Node();
		virtual ~Node();
	};
}

typedef pwutils::Singleton<pwworldsrv::Node,pwutils::ThreadMutex> pwworldsrv_Node;

#endif //_pw_worldsrv_node_