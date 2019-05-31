#include "pwdist_zmq.h"

namespace pwdist
{
	int Connection::Cleanup()
	{
		if(mSocket.get())
		{
			// 主动关闭时,不用等那么久
			int linger = 500;
			mSocket->setsockopt(ZMQ_LINGER,&linger,sizeof(int));

			mSocket->close();
			mSocket.reset();
		}
		return 0;
	}

	Connection::Connection(bool queueSend)
	{
		mQueueSend = queueSend;
		if(!mQueueSend)
		{
			mContext.reset(new zmq::context_t(1));
		}
	}

	int Connection::Startup(Communicator* communicator, const char* addr)
	{
		int linger = 3000;

		if(!mQueueSend)
			mSocket.reset(new zmq::socket_t(*mContext,ZMQ_PUSH));
		else
			mSocket.reset(new zmq::socket_t(*communicator->GetZmqContext(),ZMQ_PUSH));
		mSocket->setsockopt(ZMQ_LINGER,&linger,sizeof(int));

		// 重连间隔
		int reconnect_ivl = 2000;
		int reconnect_ivl_max = 5000;
		mSocket->setsockopt(ZMQ_RECONNECT_IVL,&reconnect_ivl,sizeof(int));
		mSocket->setsockopt(ZMQ_RECONNECT_IVL_MAX,&reconnect_ivl_max,sizeof(int));

		mSocket->connect(addr);
		return 0;
	}

	Connection::~Connection()
	{
		Cleanup();
	}

	char* Connection::AllocateSendBuffer(size_t len,void** obj)
	{
		zmq::message_t* msg = new zmq::message_t(len);
		*obj = msg;
		return (char*)msg->data();
	}

	int Connection::SendAllocatedMsgAndFree(void* obj)
	{
		if(!mQueueSend)
		{
			pwdist_utils::thread_mutex_guard<pwdist_utils::mutex> g(mSendLock);
			zmq::message_t* msg = (zmq::message_t*)obj;
			int result = mSocket->send(*msg);
			delete msg;
			return result;
		}
		else
		{
			m_vSendMsgs.push((zmq::message_t*)obj);
		}
		return 0;
	}

	int Connection::SendMsg(const char* buf,size_t len)
	{
		if(!mQueueSend)
		{
			pwdist_utils::thread_mutex_guard<pwdist_utils::mutex> g(mSendLock);

			zmq::message_t msg(len);
			memcpy(msg.data(),buf,len);

			if(!mSocket->send(msg))
			{
				return -1;
			}
		}
		else
		{
			zmq::message_t* msg = new zmq::message_t(len);
			memcpy(msg->data(),buf,len);
			m_vSendMsgs.push((zmq::message_t*)msg);
		}
		return 0;
	}

	int Connection::Connect(const std::string& addr)
	{
		mSocket->connect(addr.c_str());
		return 0;
	}

	int Connection::Tick()
	{
		zmq::message_t* msg = 0;
		while(m_vSendMsgs.try_pop(msg))
		{
			mSocket->send(*msg);
			delete msg;
		}
		return 0;
	}

	// *******************************************************************************************************
	// *******************************************************************************************************
	// *******************************************************************************************************

#ifndef ZMQ_DONTWAIT
#define ZMQ_DONTWAIT ZMQ_NOBLOCK
#endif

	int Communicator::GetMsg( zmq::message_t& msg )
	{
		try
		{
			if(mListener->recv(&msg,ZMQ_DONTWAIT))
				return 0;
		}
		catch(const zmq::error_t& e)
		{
			std::cout << __FUNCTION__ << " catch exception:" << e.what() << std::endl;
			return -1;
		}
		catch(...)
		{
			std::cout << __FUNCTION__ << " catch unknown exception" << std::endl;
			return -1;
		}
		return -1;
	}

	Communicator::Communicator()
	{
		mContext.reset(new zmq::context_t(1));
	}

	Communicator::~Communicator()
	{

	}

// 	void* _pwdist_zmq_msg_alloc_fn(size_t size,void* hint)
// 	{
// 		return lwrpc_ProtocolMemPool::instance()->allocate(size);
// 	}
// 
// 	void  _pwdist_zmq_msg_free_fn(void* ptr,size_t size,void* hint)
// 	{
// 		lwrpc_ProtocolMemPool::instance()->deallocate(ptr,size);
// 	}


	int Communicator::Startup(const_char_ptr listenAddr)
	{
		if(mListener.get())
			return -1;

		strncpy(mListenAddr,listenAddr,_countof(mListenAddr));

		if(strlen(mListenAddr) == 0)
			return -2;

// 		zmq_msg_memory_fn(&_pwdist_zmq_msg_alloc_fn,&_pwdist_zmq_msg_free_fn,NULL);

		int linger = 3000;
		mListener.reset(new zmq::socket_t(*mContext.get(),ZMQ_PULL));
		mListener->setsockopt(ZMQ_LINGER,&linger,sizeof(int));
		mListener->bind(mListenAddr);

		return 0;
	}

	int Communicator::Cleanup()
	{
		if(mListener.get())
		{
			mListener->close();
			mListener.reset();
		}
		return 0;
	}

	const_char_ptr Communicator::GetListenAddr()
	{
		return mListenAddr;
	}

	zmq::context_t* Communicator::GetZmqContext()
	{
		return mContext.get();
	}

}