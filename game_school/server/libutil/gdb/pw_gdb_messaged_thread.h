#ifndef _pw_gdb_messaged_thread_
#define _pw_gdb_messaged_thread_

#include "pw_gdb_thread.h"
#include <tbb/concurrent_queue.h>

namespace gdb
{
	class ThreadMessage
	{
	public:
		int mid;
	public:
		virtual ~ThreadMessage() {}
	};

	template<class T> class ThreadMessageT : public ThreadMessage
	{
	public:
		T value;
	};

	class MessagedThread : public gdb::Thread
	{
	public:
		void Post(ThreadMessage* msg);
	protected:
		virtual void HandleMessages();
		virtual void HandleMessage(ThreadMessage* msg);
	protected:
		typedef tbb::concurrent_queue<ThreadMessage*> CollectionMessagesT;
	protected:
		CollectionMessagesT m_vMessages;
	};
}

#endif // _pw_gdb_messaged_thread_