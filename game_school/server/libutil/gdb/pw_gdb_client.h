#ifndef _pw_gdb_client_
#define _pw_gdb_client_

#include "pw_gdb_socket_client.h"
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_protocol.h"
#include "pw_destroyer.h"
#include "pw_functional.h"

#ifndef _NODEJS_CLIENT
	#include "pw_tick_timer.h"
#else
	#include <unordered_map>
#endif


#define GMDB_FOREACH_PACKETS(inc,future) for(size_t inc = gdb::Client::PKT_INDEX_DATA0; inc < future->Num(); ++inc)

namespace gdb
{
	/*
	 @class 游戏数据库客户端
	 @author cbh
	 @date 2014/2/24 10:25:51
	 @file pw_gdb_client.h
	 @brief 
	*/
	class Client : protected gdb::SocketClient
	{
	public:
		/*
		 @class 配置信息
		 @author cbh
		 @date 2014/2/24 10:25:42
		 @file pw_gdb_client.h
		 @brief 
		*/
		struct Configure
		{
			std::string addr;
			int port;
			std::string user;
			std::string pswd;
			std::string dbname;
			Configure() : port(0) { }
		};
	public:
		typedef std::vector<gdb::SProtocolPacket*> CollectionPacketsT;
	public:
		class Future;
		class FutureEx;
	public:
		/*
		 @class 请求类
		 @author cbh
		 @date 2014/2/24 10:26:02
		 @file pw_gdb_client.h
		 @brief 
		*/
		class Request
		{
			friend class Client;
		public:
			Request();
		public:
			inline gdb::ProtocolWriter* GetWriter()
			{
				return &writer;
			}
		public:
			inline void Reset()
			{
				actualWriter.Clear();
			}
		public:
			int64 cmd;
			int64 requestId;
		private:
			gdb::ProtocolWriter writer;
			gdb::ChunksWriter actualWriter;
		};

		/*
		 @class 请求的返回值
		 @author cbh
		 @date 2014/2/24 10:26:11
		 @file pw_gdb_client.h
		 @brief 
		*/
		class Response
		{
		public:
			bool IsSuccessful();
			bool IsSuccessfulButNoFound();
		public:
			int64 GetErrorCode();
			const char* GetErrorString();
		public:
			int64 CheckedInteger(size_t i);
			const char* CheckedString(size_t i);
			double CheckedDecimal(size_t i);
			void CheckedBuffer(size_t i,char** data,size_t* size);
			void CheckedBuffer(size_t i,std::string& rdata);
		public:
			void ToArray(std::vector<std::string>& array);
			void ToArray(std::vector<gdb::SProtocolPacket*>& array);
		public:
			inline size_t Num()
			{
				return this->packets.size();
			}
		public:
			SProtocolPacket* Get(size_t i);
		public:
			CollectionPacketsT packets;
		};
	public:
		typedef pwutils::function2<void,Future*,int> fnFutureCallback;
	public:
		enum
		{
			PKT_INDEX_CTX = 0,
			PKT_INDEX_RET = 1,
			PKT_INDEX_ERR = 2,
			PKT_INDEX_DATA0 = 3,
		};
		enum
		{
			MODE_FINISHED,
			MODE_TIMEOUT,
		};
	public:
		/*
		 @class 异步获取返回值基类Future
		 @author cbh
		 @date 2014/2/24 10:26:30
		 @file pw_gdb_client.h
		 @brief 
		*/
		class Future : public Response,public pwutils::DependsObjects
		{
			friend class Client;
		public:
			Future();
			virtual ~Future();
		public:
			void OnExpired();
			void OnFinished();
		public:
			virtual void Destroy();
		public:
			virtual bool IsAllowRebuildStream();
		public:
			inline bool IsExpired()
			{
				return _expired;
			}
			inline bool IsFinished()
			{
				return _finished;
			}
		public:
			void*	context1;
			void*	context2;
		protected:
			int64	_timeoutTick;
			int64	_requestId;
			bool	_expired;
			bool	_finished;
			fnFutureCallback _callback;
		};

		/*
		 @class 栈上的future
		 @author cbh
		 @date 2014/2/24 10:26:30
		 @file pw_gdb_client.h
		 @brief 
		*/
		class StackFuture : public Future
		{
		public:
			virtual bool IsAllowRebuildStream();
		public:
			virtual void Destroy();
		};
	public:
		Client();
	public:
		inline bool IsConnected()
		{
			return gdb::SocketClient::IsConnected();
		}
	public:
		int Connect(const char* addr,int port);
		int Connect(const Configure& conf);
	public:
		int Authentication(const char* user,const char* pswd);
	public:
		int CreateDatabase(const char* dbname);
		int DeleteDatabase(const char* dbname);
		int SelectDatabase(const char* dbname);

		int LoadDatabase(const char* dbname);
		int UnloadDatabase(const char* dbname);
		int CopyDatabase(const char* srcdbname,const char* dstdbname);
	public:
		int SetClientFlags(int64 flags);
	public:
		int AddUser(const std::string& user,const std::string& pswd,bool sys);
		int ModUser(const std::string& user,const std::string& pswd,bool sys);
		int DelUser(const std::string& user);
	public:
		int ListDatabases(std::vector<std::string>& list);
	public:
		int Update(int64 currTick);
		int CheckAndReconnect();
		int Reconnect();
	public:
		inline const char* LastErrorString()
		{
			return m_sLastError.c_str();
		}
	public:
		virtual int OnConnected();
		virtual int OnDataIncoming();
		virtual int OnClose();
	public:
		virtual int doref() { return 0; }
		virtual int unref() { return 0; }
	public:
		void CreateRequest(Request& req,int64 cmd);
		void CommitRequest(Request& req,Response* res = 0);
	public:
		Future* ListenFuture(fnFutureCallback cb,void* context1 = NULL,void* context2 = NULL);
	public:
		void FetchResponse(int64 requestId,Response* res);
	protected:
		int64 MakeRequestId();
	protected:
		int HandlePackets(gdb::SProtocolPacket** packets,size_t count);
	protected:
		void CheckExpiredFuture(int64 currTick);
	protected:
#ifndef _NODEJS_CLIENT
		typedef std_unordered_map<int64,Future*> CollectionFuturesT;
#else
		typedef std::unordered_map<int64,Future*> CollectionFuturesT;
#endif
	protected:
		CollectionPacketsT m_vPackets;
		CollectionFuturesT m_vFutures;
		gdb::SocketReactorDefaultImpl m_mReactor;
	protected:
		int64 m_nLastRequestId;
		int64 m_nLastReconnectTime;
		int64 m_nClientFlags;
	protected:
		Configure m_mConf;
	protected:
		std::string m_sLastError;
#ifndef _NODEJS_CLIENT
	protected:
		pwutils::TickTimer m_objLazyTimer;
#endif
	};
}

#endif // _pw_gdb_client_