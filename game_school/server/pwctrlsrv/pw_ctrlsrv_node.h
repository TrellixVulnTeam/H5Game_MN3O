#ifndef _pw_ctrlsrv_node_
#define _pw_ctrlsrv_node_

#include "pw_def.h"
#include "pwdist_node.h"
#include "pw_sync.h"

namespace pwctrlsrv
{
	class Node : public pwdist::Node
	{
		
	};
}

typedef pwutils::Singleton<pwctrlsrv::Node,pwutils::ThreadMutex> pwctrlsrv_Node;

#endif //_pw_ctrlsrv_node_