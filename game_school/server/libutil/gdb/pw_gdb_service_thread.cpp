#include "pw_gdb_service_thread.h"

namespace gdb
{
	static const int MSGID_REPLY = -1000;

	struct SMessageReply : public ServiceThread::Message
	{
		ServiceThread::Message* reply;
		ServiceThread::fnMsgCallback callback;
	};

	ServiceThread::Message::Message( int _msgid )
		: msgid(_msgid)
		, deleteWhenSignal(1)
		, reply(0)
	{
		sender = (ServiceThread*)Thread::Self();
	}

	ServiceThread::Message::~Message()
	{
		delete reply;
	}

	void ServiceThread::Message::Signal()
	{
		if(callback != 0)
		{
			SMessageReply* msgreply = new SMessageReply();
			msgreply->msgid = MSGID_REPLY;
			msgreply->callback = callback;
			msgreply->reply = reply;
			sender->Post(msgreply);
			reply = 0;
		}
		if(deleteWhenSignal)
			delete this;
	}

	ServiceThread::MessageWaitable::MessageWaitable( int _msgid )
		: Message(_msgid)
	{
		pthread_cond_init(&cond,0);
		pthread_mutex_init(&mutex,0);
	}

	ServiceThread::MessageWaitable::~MessageWaitable()
	{
		pthread_cond_destroy(&cond);
		pthread_mutex_destroy(&mutex);
	}

	bool ServiceThread::MessageWaitable::Wait( int timeMS /*= 1000*/ )
	{
		struct timespec t;
		t.tv_nsec = timeMS * 1000000;
		t.tv_sec = 0;

		pthread_mutex_lock(&mutex);
		int rc = pthread_cond_timedwait(&cond,&mutex,&t);
		pthread_mutex_unlock(&mutex);

		return rc != ETIMEDOUT;
	}

	void ServiceThread::MessageWaitable::Signal()
	{
		pthread_cond_signal(&cond);
		Message::Signal();
	}

	void ServiceThread::HandleMessages()
	{
		Message* msg = 0;
		while(m_vMessages.try_pop(msg))
		{
			if(msg->msgid < 0)
				i_HandleMessage(msg);
			else
				HandleMessage(msg);
			msg->Signal();
		}
	}

	void ServiceThread::HandleMessage( Message* msg )
	{

	}

	void ServiceThread::i_HandleMessage( Message* msg )
	{
		switch(msg->msgid)
		{
		case MSGID_REPLY:
			{
				SMessageReply* acutalmsg = (SMessageReply*)msg;
				(acutalmsg->callback)(acutalmsg->reply);
				delete acutalmsg->reply;
				acutalmsg->reply = 0;
			}
			break;
		}
	}

	void ServiceThread::Post( Message* msg,fnMsgCallback cb )
	{
		msg->callback = cb;
		m_vMessages.push(msg);
	}

	bool ServiceThread::Send( MessageWaitable* msg,Message* & reply,int timeMS /*= 1000*/ )
	{
		msg->deleteWhenSignal = 0;
		m_vMessages.push(msg);
		bool result = msg->Wait(timeMS);
		if(result)
			std::swap(reply,msg->reply);
		delete msg;
		return result;
	}

}