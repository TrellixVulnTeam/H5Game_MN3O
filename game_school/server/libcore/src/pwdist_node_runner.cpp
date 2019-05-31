#include "pwdist_node_runner.h"
#include "pwdist_node.h"
#include "pw_time.h"

namespace pwdist
{

	NodeRunner::NodeRunner(Node* node)
		: m_pNode(node)
	{
	}

	NodeRunner::~NodeRunner()
	{
	}

	int NodeRunner::svc()
	{
		while(!pwutils::Runnable::mClosed)
		{
			m_pNode->Update();
			pwutils::time::sleep(1);
		}
		return 0;
	}

	int NodeRunner::Startup(int threads)
	{
		return pwutils::Runnable::Startup(threads);
	}

	int NodeRunner::Cleanup()
	{
		return pwutils::Runnable::Cleanup();
	}
}

