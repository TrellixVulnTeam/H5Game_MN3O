
#ifndef _pw_db_node
#define _pw_db_node

#include "pwdist_node.h"
#include "pw_ngs_def.h"
#include "pw_sync.h"

namespace pwdbsrv
{	
	class Node : public pwdist::Node
	{
	public:
		Node();
		virtual ~Node();
	};
}

typedef pwutils::Singleton<pwdbsrv::Node,pwutils::ThreadMutex> pwdbsrv_Node;

#endif

