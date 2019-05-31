#ifndef _pwdist_node_runner_
#define _pwdist_node_runner_

#include "pwdist_def.h"
#include "pw_runnable.h"

namespace pwdist
{

	class Node;

	class NodeRunner : public pwutils::Runnable
	{
	public:
		NodeRunner(Node* node);
		virtual ~NodeRunner();
	public:
		int Startup(int threads = 1);
		int Cleanup();
	protected:
		virtual int svc();
	public:
		Node* m_pNode;
	};

}

#endif // _pwdist_node_runner_