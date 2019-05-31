#ifndef _pwdist_node_
#define _pwdist_node_

#include "pwdist_def.h"
#include "pwdist_utils.h"
#include "pwdist_zmq.h"
#include "pwdist_common.h"
#include "pw_tick_timer.h"
#include "pw_xml.h"

namespace pwdist
{	
	class RemoteNode;

	const char cst_BroadcastPortName[] = "#ports#";
	const char cst_BroadcastCallableName[] = "#objects#";

	class Node : protected pwdist::Communicator
	{
		friend class RemoteNode;
	public:
		Node();
		virtual ~Node();
	public:
		const const_char_ptr GetName()
		{
			return m_szName;
		}

		void SetUseSendQueue(bool value)
		{
			m_bQueueSendMsg = value;
		}
	public:
		virtual const_char_ptr GetListenAddr()
		{
			return pwdist::Communicator::GetListenAddr();
		}
	public:
		bool IsRemoteActive(const_char_ptr name);
		bool IsRemoteActive(const std::string& name)
		{
			return IsRemoteActive(name.c_str());
		}
	public:
		int GetRemoteNodes(const std::string& pattern,std::vector<std::string>& results);
	public:
		int Startup(const_char_ptr listen_addr,const_char_ptr name = NULL);
		int Startup(const std::string& configure);
		int Cleanup();
	public:
		int Update();
	public:
		int SendMsg(MsgCall* call);
		int SendMsg(const char* node,char* buf,size_t len);
	public:
		int AddPort(PortBase* port);
		int DelPort(PortBase* port);
		int GetPort(const_char_ptr name,PortBase** port);
		int GetPort(const std::string& name,PortBase** port)
		{
			return GetPort(name.c_str(),port);
		}
	public:
		PortBase* GetAnyPort();
	public:
		int AddNode(RemoteNode* node);
		int AddNode(const_char_ptr name,const_char_ptr addr,const_char_ptr customNodeName = NULL);
// 		int DelNode(RemoteNode* node);
	public:
		int Ping(const_char_ptr name,const_char_ptr addr)
		{
			return AddNode(name,addr);
		}
	public:
		int AddListener(INodeListener* l);
		int DelListener(INodeListener* l);
	protected:
		int fireNodeUp(RemoteNode* node,bool reconnect);
		int fireNodeReconnecting(RemoteNode* node);
		int fireNodeDown(RemoteNode* node);
	protected:
		int LoadNodes(pwutils::Xml& xml);
	protected:
		int UpdateMsgs();
		int UpdateNodes();
	protected:
		int HandleMsg(char* buf,size_t len);
	protected:
		// typedef tbb::concurrent_unordered_map<std::string,PortBase*> CollectionPortsT;
		typedef std_unordered_map<std::string,PortBase*> CollectionPortsT;
		typedef std_unordered_map<std::string,RemoteNode*> CollectionRemoteNodesT;
		typedef std::deque<INodeListener*> CollectionListenersT;
	protected:
		pwdist_utils::mutex m_objListenersLock;
	protected:
		CollectionListenersT m_vtListeners;
	protected:
		pwdist_utils::rwlock m_objPortsLock;
		pwdist_utils::rwlock m_objNodesLock;
	protected:
		CollectionPortsT m_mapPorts;
		CollectionRemoteNodesT m_mapRemoteNodes;
	protected:
		int64 m_nCurrentTick; // 与Port不同,随时会更新
		char m_szName[cst_max_name_len];
	protected:
		pwutils::TickTimer m_objUpdateNodeTimer;
		pwutils::TickTimer m_objFreeMemoryTimer;
		bool m_bQueueSendMsg;
	};
}

#endif // 