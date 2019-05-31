#include "pw_gdb_messaged_thread.h"

namespace gdb
{
	void MessagedThread::HandleMessages()
	{
		ThreadMessage* msg = NULL;
		while(m_vMessages.try_pop(msg))
		{
			HandleMessage(msg);
			delete msg;
		}
	}

	void MessagedThread::HandleMessage( ThreadMessage* msg )
	{

	}

	void MessagedThread::Post( ThreadMessage* msg )
	{
		m_vMessages.push(msg);
	}

}