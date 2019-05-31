#include <iostream>
#include "pwdist_node.h"
#include "pwdist_port.h"
#include "pw_error_handler.h"
#include "pw_time.h"
#include "pw_service_global.h"
#include "pw_globalsrv_node.h"
#include "pwdist_remote_node.h"
#include "pw_service_global.h"
#include "pw_server_group.h"

// -------------------------------------------------------------------

#ifdef _MSC_VER
	#include "vld.h"
#endif

class NodeListener : public pwdist::INodeListener
{
public:
	static void pfnPullGlobal(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplGlobal* service = (pwngs::SImplGlobal*)port;
		service->Pull();
	}

public:
	virtual int OnNodeUp(pwdist::RemoteNode* node,bool reconnect)
	{

		if(!reconnect)
			std::cout << pwutils::time::str() << " node up:" << node->GetName() << " " << node->GetAddr() << std::endl;
		else
			std::cout << pwutils::time::str() << " node up(reconnected):" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;

	}

	virtual int OnNodeDown(pwdist::RemoteNode* node)
	{
		std::cout << pwutils::time::str() << " node down:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}

	virtual int OnNodeReconnecting(pwdist::RemoteNode* node)
	{
		std::cout << pwutils::time::str() << " node reconnecting:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}
};

// -------------------------------------------------------------------


int main(int argc,char** argv)
{
	platform::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwglobal_");
	pwngs::MySigHandler_Init();

	pwutils::Xml xml;
	const std::string configure("./pwglobalsrv.xml");

	if(xml.LoadFromFile(configure) != 0)
	{
		gErrorStream( "invalid configure file:" << configure);
		return 1;
	}

	pwglobalsrv_Node::instance()->SetUseSendQueue(true);

	if(pwglobalsrv_Node::instance()->Startup(configure) != 0)
	{
		gErrorStream( "invalid configure file:" << configure);
		std::cerr << "invalid configure file:" << configure << std::endl;
		return 1;
	}

	pwglobalsrv_Node::instance()->AddListener(new NodeListener);

	pwngs::SImplGlobal* implGlobal = new pwngs::SImplGlobal();
	if(implGlobal->Startup(pwngs::cst_port_globalsrv_service,pwglobalsrv_Node::instance(),xml) != 0)
	{
		std::cout << "error start port,invalid database information" << std::endl;
		return 2;
	}
	
	// 拉取通用数据
	implGlobal->PostProc(&NodeListener::pfnPullGlobal,NULL);

	// 等待相关线程拉取数据
	while(!implGlobal->IsPullCompleted())
	{
		pwutils::time::sleep(1);
		pwglobalsrv_Node::instance()->Update();
	}

	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "pwglobalsrv started." << std::endl;
	std::cout << "ListenOn:" << pwglobalsrv_Node::instance()->GetListenAddr() << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

	while(!pwngs::gClosed)
	{
		pwglobalsrv_Node::instance()->Update();
		pwutils::time::sleep(1);
	}

	pwglobalsrv_Node::instance()->Cleanup();

	pwutils::logger::ShutDown();
	platform::fini();
	return 0;
};