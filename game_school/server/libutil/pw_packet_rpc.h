#ifndef _pw_packet_rpc_
#define _pw_packet_rpc_

#include "pw_def.h"
#include "pw_packet_def.h"
#include "pw_destroyer.h"
#include "pw_memory.h"

namespace pwutils
{
	class SocketConnection;
	class PacketRPCListener;

	typedef void (*pfnPacketRpcCallback)(PacketRPCListener* listener,MsgRpcCommon* ret,void* ctx);

	class PacketRPCListener : public DependsObjects,public pwutils::memory::ObjectInThread<PacketRPCListener>
	{
	public:
		PacketRPCListener(pfnPacketRpcCallback pfn,void* ctx,int64 timeoutTick);
	public:
		void OnTimeout();
		void OnComplete(MsgRpcCommon* ret);
	public:
		inline bool IsTimeout(int64 tick)
		{
			return tick >= m_nTimeoutTick;
		}
	protected:
		pfnPacketRpcCallback m_pfn;
		void* m_pContext;
		int64 m_nTimeoutTick;
	};

	class PacketRPC
	{
	public:
		PacketRPC();
		virtual ~PacketRPC();
	public:
		virtual int HandleCall(SocketConnection* connection, MsgRpcCommon* msg) = 0;
		virtual int HandleMessage(SocketConnection* connection, SPacketHeader* msg);
	public:
		virtual int UpdatePer1Sec(int64 tick);
	public:
		inline PacketRPCListener* GetLastListener()
		{
			return m_pLastListener;
		}
	public:
		int Call(SocketConnection* connection,void* ctx,MsgRpcCommon* msg)
		{
			return i_Call(msgid_packet_rpc,connection,ctx,msg);
		}

		int Return(SocketConnection* connection,void* ctx,MsgRpcCommon* msg)
		{
			return i_Call(msgid_packet_rpc_result,connection,ctx,msg);
		}

		int AsyncReturn(int64 callid,SocketConnection* connection,void* ctx,MsgRpcCommon* msg);
	public:
		int i_Call(int msgid,SocketConnection* connection,void* ctx,MsgRpcCommon* msg);
	public:
		PacketRPCListener* ListenResult(pfnPacketRpcCallback pfn,void* ctx,int64 timeMs = 15000);
	public:
		inline int64 MakeCallId()
		{
			m_nCallId++;
			return m_nCallId;
		}

		inline int64 AsyncPrepare()
		{
			return m_nIncomingCallId;
		}
	private:
		int i_HandleCall(SocketConnection* connection, MsgRpcCommon* msg);
		int i_HandleCallResult(SocketConnection* connection, MsgRpcCommon* msg);
	protected:
		virtual int SendCall(SocketConnection* connection,void* ctx,SPacketHeader* packet) = 0;
	protected:
		typedef std_unordered_map<int64,PacketRPCListener*> CollectionListenersT;
	protected:
		int64 m_nCallId;
		int64 m_nIncomingCallId;
		CollectionListenersT m_mapListeners;
		PacketRPCListener* m_pLastListener;
	};
}

#endif // _pw_packet_rpc_