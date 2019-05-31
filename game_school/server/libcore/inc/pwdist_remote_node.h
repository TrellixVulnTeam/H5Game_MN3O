#ifndef _pwdist_remote_node_
#define _pwdist_remote_node_

#include "pwdist_def.h"
#include "pwdist_common.h"
#include "pwdist_zmq.h"

namespace pwdist
{
	class Node;

	class RemoteNode : protected pwdist::Connection
	{
		friend class Node;
	public:
		RemoteNode(const_char_ptr name, const_char_ptr addr, const_char_ptr customNodeName = NULL, bool queueSend = false);
	public:
		inline const_char_ptr GetName()
		{
			return m_szName;
		}

		inline const_char_ptr GetAddr()
		{
			return m_szAddr;
		}
	public:
		int Startup(Node* node);
		int Cleanup();
	public:
		virtual int Update();
		virtual int HandleHeartBeatMsg();
	public:
		int SendPing();
		int SendHeartBeat();
	public:
		virtual int SendMsg(const char* buf,size_t len);
	public:
		inline bool IsLosed()
		{
			return m_bLosted;
		}

		inline bool IsActive()
		{
			return !m_bLosted && m_nLastRecvHB != 0;
		}
	protected:
		char m_szName[cst_max_name_len];
		char m_szAddr[cst_max_addr_len];
		char m_szCustomName[cst_max_name_len];
	protected:
		Node* m_pNode;
		int64 m_nLastSendHB;
		int64 m_nLastRecvHB;
		int64 m_nLastReconnectTick;
		bool m_bLosted;
	};

}

#endif // _pwdist_remote_node_