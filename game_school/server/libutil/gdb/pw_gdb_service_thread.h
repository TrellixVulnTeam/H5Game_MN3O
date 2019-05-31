#ifndef _pw_pw_gdb_service_thread_
#define _pw_pw_gdb_service_thread_

#include "pw_gdb_thread.h"
#include <tbb/concurrent_queue.h>

namespace gdb
{
	class ServiceThread : public Thread
	{
	public:
		class Message;
	public:
		typedef void (*fnMsgCallback)(const Message* reply);
	public:
		class Message
		{
		public:
			Message(int _msgid = 0);
			virtual ~Message();
		public:
			virtual void Signal();
		public:
			ServiceThread* sender;
		public:
			int msgid;
			int deleteWhenSignal;
			fnMsgCallback callback;
			Message* reply;
		};

		template<class T> class MessageT : public Message
		{
		public:
			T value;
		};

		class MessageWaitable : public Message
		{
		public:
			MessageWaitable(int _msgid = 0);
			virtual ~MessageWaitable();
		public:
			virtual bool Wait(int timeMS = 1000);
			virtual void Signal();
		private:
			pthread_cond_t cond;
			pthread_mutex_t mutex;
		};

		template<class T> class MessageWaitableT : public MessageWaitable
		{
		public:
			T value;
		};
	public:
		void Post(Message* msg,fnMsgCallback cb = 0);
		bool Send(MessageWaitable* msg,Message* & reply,int timeMS = 1000);
	protected:
		virtual void HandleMessages();
	protected:
		virtual void HandleMessage(Message* msg);
		virtual void i_HandleMessage(Message* msg);
	protected:
		typedef tbb::concurrent_queue<Message*> CollectionMessagesT;
	protected:
		CollectionMessagesT m_vMessages;
	};
}


#endif // _pw_pw_gdb_service_thread_