#include "pwdist_node.h"
#include "pwdist_remote_node.h"
#include "pw_time.h"

namespace pwdist
{
	RemoteNode::RemoteNode(const_char_ptr name, const_char_ptr addr, const_char_ptr customNodeName/* = NULL*/, bool queueSend/* = false*/)
		: Connection(queueSend)
	{
		m_pNode = NULL;
		memset(m_szCustomName,0,sizeof(m_szCustomName));
		strncpy(m_szName,name,_countof(m_szName));
		strncpy(m_szAddr,addr,_countof(m_szAddr));
		if(customNodeName != NULL)
			strncpy(m_szCustomName,customNodeName,_countof(m_szCustomName));
		m_nLastSendHB = 0;
		m_nLastRecvHB = 0;
		m_bLosted = false;
		m_nLastReconnectTick = 0;
	}

	int RemoteNode::Startup(Node* node)
	{
		int result = Connection::Startup(node,m_szAddr);
		if( result != 0 )
			return result;

		m_pNode = node;

		return 0;
	}

	int RemoteNode::Cleanup()
	{
		int result = Connection::Cleanup();
		if( result != 0 )
			return result;


		Connection::Tick();

		return 0;
	}

	int RemoteNode::Update()
	{
		static int64 sf_lost_time = pwutils::time::Second(8);
		static int64 sf_heart_beat_time = pwutils::time::Second(2);
		static int64 sf_reconnect_time = pwutils::time::Second(2);

		if((m_pNode->m_nCurrentTick - m_nLastSendHB) > sf_heart_beat_time)
			this->SendHeartBeat();

		if(!m_bLosted 
			&& m_nLastRecvHB != 0 
			&& (m_pNode->m_nCurrentTick - m_nLastRecvHB) > sf_lost_time)
		{
			m_bLosted = true;
 //			m_pNode->fireNodeDown(this);
		}

		if(m_bLosted)
		{
			m_nLastRecvHB = 0;

			if((m_pNode->m_nCurrentTick - m_nLastReconnectTick) > sf_reconnect_time)
			{
				m_nLastReconnectTick = m_pNode->m_nCurrentTick;
 //				m_pNode->fireNodeReconnecting(this);
			}
		}


		Connection::Tick();

		return 0;
	}

	int RemoteNode::SendHeartBeat()
	{
		m_nLastSendHB = m_pNode->m_nCurrentTick;

//  		std::cout << m_szName << " SendHeartBeat" << std::endl;
		return SendPing();
	}

	struct SMsgPing
	{
		MsgCall call;
		char paramsBuf[1000];
	};

	int RemoteNode::SendPing()
	{
		SMsgPing msgping = {0};

		strncpy(msgping.paramsBuf,m_pNode->GetListenAddr(),sizeof(msgping.paramsBuf));

		msgping.call.msgid = msgid_ping;
		if(m_szCustomName[0] == 0)
			msgping.call.sender.initial(m_pNode->m_szName,NULL,NULL,0);
		else
			msgping.call.sender.initial(m_szCustomName,NULL,NULL,0);
		msgping.call.target.initial(m_szName,NULL,NULL,0);
		msgping.call.params.paramsNum++;
		msgping.call.params.params[0].type = PARAMETER_TYPE_STR;
		msgping.call.params.params[0].valbuf = msgping.paramsBuf;
		msgping.call.params.params[0].size = strlen(msgping.paramsBuf) + 1;
		msgping.call.msglen = msgping.call.Bytes();

		return this->SendMsg((const_char_ptr)&msgping,msgping.call.msglen);
	}

	int RemoteNode::HandleHeartBeatMsg()
	{
		if(m_nLastRecvHB == 0)
		{
			m_pNode->fireNodeUp(this,m_bLosted);
		}
		m_bLosted = false;
		m_nLastRecvHB = m_pNode->m_nCurrentTick;

		return 0;
	}

	int RemoteNode::SendMsg( const char* buf,size_t len )
	{
		m_nLastSendHB = m_pNode->m_nCurrentTick;

		return Connection::SendMsg(buf,len);
	}
}