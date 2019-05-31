#ifndef _pw_globalsrv_node_
#define _pw_globalsrv_node_

#include "pwdist_node.h"
#include "pw_ngs_def.h"
#include "pw_sync.h"

namespace pwglobalsrv
{	
	class Node : public pwdist::Node
	{
	public:
		Node();
		virtual ~Node();
	};
}

typedef pwutils::Singleton<pwglobalsrv::Node,pwutils::ThreadMutex> pwglobalsrv_Node;

#endif //_pw_globalsrv_node_