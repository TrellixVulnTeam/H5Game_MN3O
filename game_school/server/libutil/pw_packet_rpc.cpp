#include "pw_packet_rpc.h"
#include "pw_time.h"

namespace pwutils
{
	PacketRPCListener::PacketRPCListener( pfnPacketRpcCallback pfn,void* ctx,int64 timeoutTick )
		: m_pfn(pfn)
		, m_pContext(ctx)
		, m_nTimeoutTick(timeoutTick)
	{
	}

	void PacketRPCListener::OnTimeout()
	{
		m_pfn(this,NULL,m_pContext);
	}

	void PacketRPCListener::OnComplete( MsgRpcCommon* ret )
	{
		m_pfn(this,ret,m_pContext);
	}

	PacketRPC::PacketRPC()
		: m_nCallId(0)
		, m_pLastListener(NULL)
	{

	}

	PacketRPC::~PacketRPC()
	{
		for(CollectionListenersT::iterator iter = m_mapListeners.begin(); iter != m_mapListeners.end(); ++iter)
		{
			PacketRPCListener* l = iter->second;
			_safe_delete(l);
		}
		m_mapListeners.clear();
	}

	int PacketRPC::AsyncReturn(int64 callid,SocketConnection* connection,void* ctx,MsgRpcCommon* msg)
	{
		msg->msgid = msgid_packet_rpc_result;
		msg->cid = callid;
		msg->flags = 0;
		return SendCall(connection,ctx,msg);
	}

	int PacketRPC::i_Call( int msgid,SocketConnection* connection,void* ctx,MsgRpcCommon* msg)
	{
		msg->msgid = msgid;
		if(msgid == msgid_packet_rpc)
			msg->cid = this->MakeCallId();
		else
			msg->cid = m_nIncomingCallId;
		
		return SendCall(connection,ctx,msg);
	}

	PacketRPCListener* PacketRPC::ListenResult( pfnPacketRpcCallback pfn,void* ctx,int64 timeMs /*= 15000*/ )
	{
		PacketRPCListener* listener = new PacketRPCListener(pfn,ctx,pwutils::time::Msec(timeMs) + pwutils::time::get());
		bool result = m_mapListeners.insert(std::make_pair(m_nCallId,listener)).second;
		if( !result )
		{
			delete listener;
			return NULL;
		}
		m_pLastListener = listener;
		return listener;
	}

	int PacketRPC::UpdatePer1Sec( int64 tick )
	{
		std::vector<int64> vtinvalids;
		for(CollectionListenersT::iterator iter = m_mapListeners.begin(); iter != m_mapListeners.end(); ++iter)
		{
			PacketRPCListener* l = iter->second;
			if(l && l->IsTimeout(tick))
			{
				l->OnTimeout();
				_safe_delete(l);
				vtinvalids.push_back(iter->first);
			}
		}

		if(vtinvalids.size() > 0)
		{
			for(size_t i = 0; i < vtinvalids.size(); ++i)
				m_mapListeners.erase(vtinvalids[i]);
		}

		return 0;
	}

	int PacketRPC::i_HandleCallResult( SocketConnection* connection, MsgRpcCommon* msg )
	{
		CollectionListenersT::iterator iter = m_mapListeners.find(msg->cid);
		if(iter == m_mapListeners.end())
			return -1;
		
		PacketRPCListener* l = iter->second;
		l->OnComplete(msg);
		_safe_delete(l);
		m_mapListeners.erase(iter);

		return 0;
	}

	int PacketRPC::i_HandleCall( SocketConnection* connection, MsgRpcCommon* msg )
	{
		m_nIncomingCallId = msg->cid;

		return this->HandleCall(connection,msg);
	}

	int PacketRPC::HandleMessage( SocketConnection* connection, SPacketHeader* msg )
	{
		switch(msg->msgid)
		{
		case msgid_packet_rpc:
			return this->i_HandleCall(connection,(MsgRpcCommon*)msg);
		case msgid_packet_rpc_result:
			return this->i_HandleCallResult(connection,(MsgRpcCommon*)msg);
		}
		return -1;
	}

}