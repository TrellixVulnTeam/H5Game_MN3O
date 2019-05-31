#ifndef _pwdist_zmq_
#define _pwdist_zmq_

#include "pwdist_def.h"
#include "pwdist_utils.h"
#include <memory>

namespace pwdist
{

	class Communicator;

	class Connection
	{
	public:
		Connection(bool queueSend);
		virtual ~Connection();
	public:
		virtual int Startup(Communicator* communicator,const char* addr);
		virtual int Cleanup();
	public:
		virtual int Connect(const std::string& addr);
	public:
		virtual char* AllocateSendBuffer(size_t len,void** obj);
		virtual int SendMsg(const char* buf,size_t len);
		virtual int SendAllocatedMsgAndFree(void* obj);
		virtual int Tick();
	public:
		std::auto_ptr<zmq::socket_t> mSocket;
		std::auto_ptr<zmq::context_t> mContext;
		pwdist_utils::mutex mSendLock;
		bool mQueueSend;
	private:
		typedef tbb::concurrent_queue<zmq::message_t*> CollectionSendMsgsT;

		CollectionSendMsgsT m_vSendMsgs;
	};


	// *******************************************************************************************************

	class Communicator
	{
		friend class Connection;
	public:
		Communicator();
		virtual ~Communicator();
	public:
		virtual int Startup(const_char_ptr listenAddr);
		virtual int Cleanup();
	public:
		virtual int GetMsg(zmq::message_t& msg);
	public:
		virtual const_char_ptr GetListenAddr();

		virtual zmq::context_t* GetZmqContext();
	protected:
		char mListenAddr[100];
	#ifdef _MSC_VER
		std::auto_ptr<zmq::context_t> mContext;
		std::auto_ptr<zmq::socket_t> mListener;
	#else
		std::unique_ptr<zmq::context_t> mContext;
		std::unique_ptr<zmq::socket_t> mListener;
	#endif
	};
}
#endif // _pwdist_zmq_