#include "pw_connsrv_node.h"
#include "pw_ngs_def.h"
#include "pw_ngs_utils.h"

namespace pwconnsrv
{
	// 连接服务器id
	sint64 g_nServerId = 0;
	std::string	g_strLoginNode;
	std::string g_strLoginPort;

	Node::Node()
	{
		m_nLastID = 0;
	}

	Node::~Node()
	{
	}

	pwdist::PortBase* Node::GetRandomPort()
	{
		pwdist::PortBase* port = nullptr;
		std::string portName = pwutils::GetSImplAny(pwngs::cst_port_connsrv_fmt,pwngs::max_connsrv_service_port);
		GetPort(portName,&port);
		return port;
	}

	pwdist::int64 Node::MakeConnectionID()
	{
		int64 result = 0;

		m_objLock.lock();
		{
			m_nLastID++;
			result = (g_nServerId << 60) + m_nLastID;
		}
		m_objLock.unlock();

		return result;
	}

}

pwconnsrv::Node g_objConnsrvNode;
