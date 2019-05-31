#include <cstdio>
#include <iostream>

#include "pw_connsrv_listener.h"
#include "pw_connsrv_connection.h"

#include "pw_def.h"
#include "pw_logger.h"
#include "pw_connsrv_node.h"
#include "pw_connsrv_service_port.h"
#include "pw_ngs_def.h"
#include "pw_ngs_utils.h"
#include "pw_xml.h"
#include "pw_utils.h"
#include "pwdist_remote_node.h"
#include "pw_backtrace.h"
#include "pw_error_handler.h"
#include "pw_server_group.h"

// -------------------------------------------------------------------

class NodeListener : public pwdist::INodeListener
{
public:
	virtual int OnNodeUp(pwdist::RemoteNode* node,bool reconnect)
	{
		if(!reconnect)
			std::cout << "node up:" << node->GetName() << " " << node->GetAddr() << std::endl;
		else
			std::cout << "node up(reconnected):" << node->GetName() << " " << node->GetAddr() << std::endl;

		return 0;
		
	}
	
	virtual int OnNodeDown(pwdist::RemoteNode* node)
	{
		std::cout << "node down:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}
	
	virtual int OnNodeReconnecting(pwdist::RemoteNode* node)
	{
		std::cout << "node reconnecting:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}
};

// -------------------------------------------------------------------

pwconnsrv::SImplSend* StartupPort(int n)
{
	pwconnsrv::SImplSend* port = new pwconnsrv::SImplSend();
	port->Startup(pwutils::GetSImplSend(n),&g_objConnsrvNode);
	return port;
}

int main(int argc, char **argv)
{
	platform::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwconn_");
	pwngs::MySigHandler_Init();
	{
		pwutils::Xml xml;
		std::string configure("./pwconnsrv.xml");

		if(argc > 1)
			configure = argv[1];
		
		// 配置文件
		if(xml.LoadFromFile(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			std::cerr << "invalid configure file:" << configure << std::endl;
			return 1;
		}
		
		pwconnsrv::g_nServerId = pwutils::atoi(xml.GetValue("/pwdist/id").c_str());
		pwconnsrv::g_strLoginNode = xml.GetValue("/pwdist/gate/node");
		pwconnsrv::g_strLoginPort = xml.GetValue("/pwdist/gate/port");

		//------------------------------------------------------------------------
		// 启动分布式节点
		//------------------------------------------------------------------------
		if(g_objConnsrvNode.Startup(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			return 1;
		}
		
		g_objConnsrvNode.AddListener(new NodeListener);
		
		//------------------------------------------------------------------------
		// 创建N个分布式服务端口 用于发送数据/为connection提供服务
		// connection在初始化时随机选择一个service用于发送数据
		// connection内部必须同步机制
		//------------------------------------------------------------------------
		for(int i = 0; i < pwconnsrv::max_service_port; ++i)
			StartupPort(i);

		std::cout << "pwconnsrv started." << std::endl;
		std::cout << "ListenOn:" << g_objConnsrvNode.GetListenAddr() << std::endl;
		

		// --------------------------------------------------------------------------
		// 创建listener对象
		// --------------------------------------------------------------------------
		int listenPort = pwutils::atoi(xml.GetValue("/pwdist/game/listen_port").c_str());

		sprintf(pwconnsrv::g_nPolicyResponse,pwconnsrv::unity_policy_response_fmt,listenPort);

		pwconnsrv::SImplListener* simpListener = new pwconnsrv::SImplListener();
		if(simpListener->Startup(pwngs::cst_port_connsrv_listener,&g_objConnsrvNode,listenPort) != 0)
		{
			std::cout << "listen port failed " << listenPort << std::endl;
			delete simpListener;
			return 1;
		}

		std::cout << "ListenOn:" << listenPort << std::endl;

		// --------------------------------------------------------------------------
		// 创建 websokcet listener对象
		// --------------------------------------------------------------------------
		int listenWebsokcetPort = pwutils::atoi(xml.GetValue("/pwdist/game/listen_websocket_port").c_str());

		//sprintf(pwconnsrv::g_nPolicyResponse, pwconnsrv::unity_policy_response_fmt, listenWebsokcetPort);

		/*pwconnsrv::SImplWebsocketListener* simpWebsokcetListener = new pwconnsrv::SImplWebsocketListener();
		if (simpWebsokcetListener->Startup(pwngs::cst_port_connsrv_websocketlistener, &g_objConnsrvNode, listenWebsokcetPort) != 0)
		{
			std::cout << "listen Websokcet port failed " << listenWebsokcetPort << std::endl;
			delete simpWebsokcetListener;
			return 1;
		}

		std::cout << "ListenWebsokcetOn:" << listenWebsokcetPort << std::endl;*/
		
		// 更新节点
		volatile bool& closed = pwngs::gClosed;
		while(!closed)
		{
			pwutils::time::sleep(1);
			g_objConnsrvNode.Update();
		}
		
		g_objConnsrvNode.Cleanup();
	}

	platform::fini();
	return 0;
}
