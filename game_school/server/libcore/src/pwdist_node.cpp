#include "pwdist_node.h"
#include "pwdist_port_generic.h"
#include "pwdist_remote_node.h"
#include "pw_time.h"
#include "pw_logger.h"
#include "pw_utils.h"

#ifdef _TCMALLOC_USED
	#include <google/malloc_extension.h>
#endif

namespace pwdist
{

	bool IsValidNodeAddr(const char* addr)
	{
		if(strstr(addr,"tcp://") != addr)
			return false;
		addr += 6;

		for(size_t i = 0; i < strlen(addr); ++i)
		{
			if(!(addr[i] == '.' || addr[i] == ':' || (addr[i] >= '0' && addr[i] <= '9')))
				return false;
		}
		return true;
	}

	Node::Node()
	{
		m_szName[0] = '\0';
		m_bQueueSendMsg = false;
		m_objUpdateNodeTimer.Startup(pwutils::time::Second(1));
		m_objFreeMemoryTimer.Startup(pwutils::time::Second(15));
	}

	Node::~Node()
	{
		Cleanup();
	}

	int Node::Startup( const_char_ptr listen_addr,const_char_ptr name/* = NULL*/ )
	{
		if(pwdist::Communicator::Startup(listen_addr) != 0)
			return -1;

		for(CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.begin(); iter != m_mapRemoteNodes.end(); ++iter)
			iter->second->Startup(this);

		for(CollectionPortsT::iterator iter = m_mapPorts.begin(); iter != m_mapPorts.end(); ++iter)
			iter->second->i_DoNodeStarted();

		UpdateNodes();

		if(name != NULL)
			strncpy(m_szName,name,_countof(m_szName));

		return 0;
	}

	int Node::Startup( const std::string& configure )
	{
		pwutils::Xml xml;

		if_fail(xml.LoadFromFile(configure))
		{
			return -1;
		}

		std::string name = xml.GetValue("/pwdist/name");
		if(name.length() == 0)
		{
			return -2;
		}

		strncpy(m_szName,name.c_str(),_countof(m_szName));

		std::string listenAddr = xml.GetValue("/pwdist/communicator/listen_addr");

		if_fail(Communicator::Startup(listenAddr.c_str()))
		{
			return -3;
		}

		if_fail(LoadNodes(xml))
		{
			return -4;
		}

		return 0;
	}

	int Node::GetRemoteNodes(const std::string& pattern,std::vector<std::string>& results)
	{
		m_objNodesLock.rlock();

		for(CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.begin(); iter != m_mapRemoteNodes.end(); ++iter)
		{
			RemoteNode* node = iter->second;
			const std::string& name = node->GetName();
			if(::strstr(name.c_str(),pattern.c_str()) != NULL)
				results.push_back(name);
		}

		m_objNodesLock.runlock();
		return 0;
	}

	int Node::LoadNodes(pwutils::Xml& xml)
	{
		int nodeCount = (int)pwutils::atoi(xml.GetValue("/pwdist/nodes/count").c_str());
		if(nodeCount == 0)
			return 0;

		for(int i = 1; i < (nodeCount+1); ++i)
		{
			char bufName[200] = "";
			char bufAddr[200] = "";
			char bufCustomName[200] = "";

			sprintf(bufName,"/pwdist/nodes/node%d/name",i);
			sprintf(bufAddr,"/pwdist/nodes/node%d/addr",i);
			sprintf(bufCustomName,"/pwdist/nodes/node%d/custom_name",i);

			std::string nodeName = xml.GetValue(bufName);
			std::string nodeAddr = xml.GetValue(bufAddr);
			std::string nodeCustomName = xml.GetValue(bufCustomName);

			if(!IsValidNodeAddr(nodeAddr.c_str()))
			{
				std::cout << __FUNCTION__ << " " << nodeName << " addr invalid,skiped " << nodeAddr << std::endl;
				continue;
			}

			if(nodeName.length() > 0 && nodeAddr.length())
			{
				RemoteNode* node = new RemoteNode(nodeName.c_str(),nodeAddr.c_str(),nodeCustomName.c_str());
				node->Startup(this);
				AddNode(node);
			}
		}
		return 0;
	}

	int Node::Cleanup()
	{
		std::vector<PortBase*> ports;

		// m_objPortsLock.wlock();
		{
			for(CollectionPortsT::iterator iter = m_mapPorts.begin(); iter != m_mapPorts.end(); ++iter)
				ports.push_back(iter->second);
		}
		// m_objPortsLock.wunlock();

		for(size_t i = 0; i < ports.size(); ++i)
		{
			ports[i]->Cleanup();
			delete ports[i];
		}
		m_mapPorts.clear();

		m_objNodesLock.wlock();
		{
			for(CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.begin(); iter != m_mapRemoteNodes.end(); ++iter)
			{
				iter->second->Cleanup();
				delete iter->second;
			}
			m_mapRemoteNodes.clear();
		}
		m_objNodesLock.wunlock();		

		if(pwdist::Communicator::Cleanup() != 0)
			return -1;

		return 0;
	}

	int Node::Update()
	{
		m_nCurrentTick = pwutils::time::get();
		
		UpdateMsgs();

		if(m_objUpdateNodeTimer.IsPeriodExpired(m_nCurrentTick))
			UpdateNodes();

#ifdef _TCMALLOC_USED
		if(m_objFreeMemoryTimer.IsPeriodExpired(m_nCurrentTick))
			MallocExtension::instance()->ReleaseFreeMemory();		
#endif
		m_objNodesLock.rlock();
		for(CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.begin(); iter != m_mapRemoteNodes.end(); ++iter)
			iter->second->Tick();
		m_objNodesLock.runlock();

		return 0;
	}

	int Node::UpdateMsgs()
	{
		zmq::message_t msg;
		
		while(Communicator::GetMsg(msg) == 0)
		{
			HandleMsg((char*)msg.data(),msg.size());
		}

		return 0;
	}

	int Node::UpdateNodes()
	{
 		m_objNodesLock.rlock();

		for(CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.begin(); iter != m_mapRemoteNodes.end(); ++iter)
			iter->second->Update();

 		m_objNodesLock.runlock();

		return 0;
	}


	int Node::AddPort( PortBase* port )
	{
		
		m_objPortsLock.wlock();
		{
			if(m_mapPorts.insert(std::make_pair(port->GetName(),port)).second)
			{
				AddListener(port);
			}
		}
		m_objPortsLock.wunlock();
		return 0;
	}

	int Node::DelPort( PortBase* port )
	{
		m_objPortsLock.wlock();
		{
			CollectionPortsT::iterator iter = m_mapPorts.find(port->GetName());
			if(iter != m_mapPorts.end())
			{
				DelListener(port);
				m_mapPorts.erase(iter);
			}
		}
		m_objPortsLock.wunlock();
		return 0;
	}

	int Node::GetPort( const_char_ptr name,PortBase** port )
	{
		int result = 1;

		m_objPortsLock.rlock();
		{
			CollectionPortsT::iterator iter = m_mapPorts.find(name);
			if(iter != m_mapPorts.end())
			{
				*port = iter->second;
				result = 0;
			}
		}
		m_objPortsLock.runlock();
		return result;
	}

	int Node::AddNode( RemoteNode* node )
	{
 		m_objNodesLock.wlock();
 		{
			m_mapRemoteNodes.insert(std::make_pair(node->GetName(),node));
 		}
 		m_objNodesLock.wunlock();
 		return 0;
//	}
	}

	int Node::AddNode( const_char_ptr name,const_char_ptr addr,const_char_ptr customNodeName/* = NULL*/ )
	{
		RemoteNode* node = new RemoteNode(name,addr,customNodeName);
		node->Startup(this);
		// node->SendPing();
		
		return AddNode(node);
	}

// 	int Node::DelNode( RemoteNode* node )
// 	{
// 		m_objNodesLock.wlock();
// 		{
// 			CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.find(node->GetName());
// 			if(iter != m_mapRemoteNodes.end())
// 				m_mapRemoteNodes.erase(iter);
// 		}
// 		m_objNodesLock.wunlock();
// 		return 0;
// 	}


	struct SHandleMessageCache
	{
		int portSum;
		char portName[100];
		ManagedMsgCallMulti* multiCalls;
		ManagedMsgCallMulti* multiCallResults;
		pwdist::PortBase* port;
	};

	/*
	 @class SHandleMessageCaches
	 @author cbh
	 @date 2013/3/29 12:07:04
	 @file pwdist_node.cpp
	 @brief 减少lock,加速
	*/
	struct SHandleMessageCaches
	{
		int count;
		SHandleMessageCache caches[200];

		static int strsum(const_char_ptr portname,size_t len)
		{
			int result = 0;
			for(size_t i = 0; i < len; ++i)
				result += portname[i];
			return result;
		}

		SHandleMessageCache* Get(const_char_ptr portname,bool createIfNonExists = false,pwdist::PortBase* port = NULL)
		{
			size_t len = strlen(portname);
			int sum = strsum(portname,len);
			for(int i = 0; i < count; ++i)
			{
				if(caches[i].portSum == sum && pwutils::stricmp(caches[i].portName,portname) == 0)
				{
					return &caches[i];
				}
			}

			if(!createIfNonExists)
				return NULL;
			pwassertn(port);

			caches[count].portSum = sum;
			caches[count].multiCalls = new ManagedMsgCallMulti(port->GetFrameTime());
			caches[count].multiCallResults = new ManagedMsgCallMulti(port->GetFrameTime());
			caches[count].port = port;
			pwutils::strncpy(caches[count].portName,portname,sizeof(caches[count].portName));
			++count;
			return &caches[count - 1];
		}

		void Commit()
		{
			for(int i = 0; i < count; ++i)
			{
				SHandleMessageCache& r = caches[i];
				
				if(r.multiCalls && r.multiCalls->Count() > 0)
					r.port->i_HandleMultiCall(r.multiCalls);
				else
					_safe_delete(r.multiCalls);

				if(r.multiCallResults && r.multiCallResults->Count() > 0)
					r.port->i_HandleMultiCallResult(r.multiCallResults);
				else
					_safe_delete(r.multiCallResults)
			}
		}
	};

	int Node::HandleMsg( char* buf,size_t len )
	{
		// 一个消息,一定来自同一个remoteNode
		RemoteNode* node = NULL;

		SHandleMessageCaches caches = {0};

		while(len > 0)
		{
			MsgCall* call = (MsgCall*)buf;
			size_t n = call->params.LoadPtr(buf + sizeof(MsgCall),call->msglen - sizeof(MsgCall));
			
			buf = buf + n + sizeof(MsgCall);
			len = len - n - sizeof(MsgCall);

			if(node == NULL)
			{
				m_objNodesLock.rlock();
				{
					CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.find(call->sender.node);
					if(iter != m_mapRemoteNodes.end())
						node = iter->second;
				}
				m_objNodesLock.runlock();
			}

			switch(call->msgid)
			{
			case msgid_ping:
				{
					if(node != NULL)
					{
						node->HandleHeartBeatMsg();
					}
					else
					{
						pwassertn(call->params.paramsNum == 1);
						pwassertn(call->params.params[0].type == PARAMETER_TYPE_STR);

						node = new RemoteNode(call->sender.node,call->params.params[0].valbuf,NULL,m_bQueueSendMsg);
						node->Startup(this);
						node->HandleHeartBeatMsg();
						this->AddNode(node);
					}
				}
				break;
			case msgid_rpc:
			case msgid_rpc_return:
				{
					if(node != NULL)
						node->HandleHeartBeatMsg();

					SHandleMessageCache* cache = caches.Get(call->target.port);
					if(cache == NULL)
					{
						PortBase* port = NULL;
						m_objPortsLock.rlock();
						{
							CollectionPortsT::iterator iter = m_mapPorts.find(call->target.port);
							if(iter != m_mapPorts.end())
								port = iter->second;
						}
						m_objPortsLock.runlock();
						
						if(port != NULL)
							cache = caches.Get(call->target.port,true,port);
					}					

					if(cache != NULL)
					{
						if(call->msgid == msgid_rpc)
							cache->multiCalls->Add(call);
						else
							cache->multiCallResults->Add(call);
					}
					else if( (call->flags & PortBase::FLAGS_BROADCAST) || (call->flags & PortBase::FLAGS_OBJECT_BROADCAST) )
					{
						m_objPortsLock.rlock();
						{
							for(CollectionPortsT::iterator iter = m_mapPorts.begin(); iter != m_mapPorts.end(); ++iter)
							{
								iter->second->i_HandleCall(call);
							}
						}
						m_objPortsLock.runlock();
					}
					else
					{
						gWarniStream( "port not exists!! " << " msgid = " << call->msgid 
							<< " sender = (" << call->sender.node << "," << call->sender.port << ")"
							<< " target = (" << call->target.node << "," << call->target.port << ")"
							<< " method = " << call->method);
					}
				}
				break;
			default:
				{
					gErrorStream( "pwdist_node unexpected msgid = " << call->msgid);
				}
				break;
			}
		}

		caches.Commit();

		return 0;
	}

	int Node::AddListener( INodeListener* l )
	{
		m_objListenersLock.lock();
		m_vtListeners.push_back(l);
		m_objListenersLock.unlock();
		return 0;
	}

	int Node::DelListener( INodeListener* l )
	{
		m_objListenersLock.lock();
		m_vtListeners.erase(std::remove(m_vtListeners.begin(),m_vtListeners.end(),l),m_vtListeners.end());
		m_objListenersLock.unlock();
		return 0;
	}

	int Node::fireNodeUp( RemoteNode* node,bool reconnect )
	{
// 		std::cout << "this=" << m_szName << " nodeup=" << node->GetName() << std::endl;

		for(CollectionListenersT::iterator iter = m_vtListeners.begin(); iter != m_vtListeners.end(); ++iter)
		{
			(*iter)->OnNodeUp(node,reconnect);
		}
		return 0;
	}

	int Node::fireNodeReconnecting( RemoteNode* node )
	{
		std::cout << "this=" << m_szName << " fireNodeReconnecting=" << node->GetName() << ", curTime=" << pwutils::time::clib_time() << std::endl;

		for(CollectionListenersT::iterator iter = m_vtListeners.begin(); iter != m_vtListeners.end(); ++iter)
		{
			(*iter)->OnNodeReconnecting(node);
		}
		return 0;
	}

	int Node::fireNodeDown( RemoteNode* node )
	{
		std::cout << "this=" << m_szName << " fireNodeDown=" << node->GetName() << ", curTime=" << pwutils::time::clib_time() << std::endl;

		for(CollectionListenersT::iterator iter = m_vtListeners.begin(); iter != m_vtListeners.end(); ++iter)
		{
			(*iter)->OnNodeDown(node);
		}
		return 0;
	}

	int Node::SendMsg(const char* _node,char* buf,size_t len)
	{
		if(len <= 0)
			return 0;

		// Í¬½Úµã
		if(strcmp(_node,m_szName) == 0)
		{
			return this->HandleMsg(buf,len);
		}

		RemoteNode* node = NULL;

		m_objNodesLock.rlock();
		{
			CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.find(_node);
			if(iter != m_mapRemoteNodes.end())
				node = iter->second;
		}
		m_objNodesLock.runlock();

		if(node != NULL)
		{
			return node->SendMsg(buf,len);
		}
		return -1;
	}

	int Node::SendMsg( MsgCall* call )
	{
		// Í¬½Úµã
		if(strcmp(call->target.node,m_szName) == 0)
		{
			PortBase* port = NULL;

			m_objPortsLock.rlock();
			{
				CollectionPortsT::iterator iter = m_mapPorts.find(call->target.port);
				if(iter != m_mapPorts.end())
					port = iter->second;
			}
			m_objPortsLock.runlock();

			if(port != NULL)
			{
				port->i_HandleCall(call);
			}
		}
		else
		{
			RemoteNode* node = NULL;

			m_objNodesLock.rlock();
			{
				CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.find(call->target.node);
				if(iter != m_mapRemoteNodes.end())
					node = iter->second;
			}
			m_objNodesLock.runlock();

			if(node != NULL)
			{
				void* msgptr = NULL;
				char* buffer = node->AllocateSendBuffer(call->msglen,&msgptr);
				call->Save(buffer,call->msglen);
				node->SendAllocatedMsgAndFree(msgptr);
			}
			else
			{
				gWarniStream( "RemoteNode NoFound node=" << call->target.node
					<< " port=" << call->target.port
					<< " method=" << call->method);
			}
		}
		return 0;
	}

	bool Node::IsRemoteActive( const_char_ptr name )
	{
		RemoteNode* node = NULL;

		m_objNodesLock.rlock();
		{
			CollectionRemoteNodesT::iterator iter = m_mapRemoteNodes.find(name);
			if(iter != m_mapRemoteNodes.end())
				node = iter->second;
		}
		m_objNodesLock.runlock();

		if(node != NULL)
			return node->IsActive();
		return false;
		
	}

	PortBase* Node::GetAnyPort()
	{
		if(m_mapPorts.size() == 0)
			return NULL;
		return m_mapPorts.begin()->second;
	}

}