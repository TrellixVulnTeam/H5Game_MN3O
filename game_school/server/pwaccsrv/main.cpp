#include <cstdio>

#include "pw_def.h"
#include "pw_logger.h"
#include "pw_accsrv_node.h"
#include "pw_accsrv_service_port.h"
#include "pw_service_wallow.h"
#include "pw_ngs_def.h"
#include "pw_ngs_utils.h"
#include "pw_ngs_vars.h"
#include "pwdist_remote_node.h"
#include "pw_error_handler.h"
#include "pw_server_group.h"
#include "pw_accsrv_whitelist.h"
#include "pw_laohu_auth.h"
#include "curl/curl.h"

// -------------------------------------------------------------------

pwaccsrv::SImplAcc* StartupPort(int n,pwutils::Xml& xml)
{
	pwaccsrv::SImplAcc* port = new pwaccsrv::SImplAcc();
	if(port->Startup(pwutils::GetSImplAcc(n),pwaccsrv_Node::instance(),xml) < 0)
	{
		exit(1);
	}
	return port;
}

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

#include "tx_platform/pw_tx_openapi_v3.h"

int main(int argc, char **argv)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	platform::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwaccs_");
	pwngs::MySigHandler_Init();

// 	{
// 		std::string url;
// 		tx::InterfaceV3 v(15499,"56abfbcd12fe46f5ad85ad9f2faf36d7");
// 		tx::InterfaceV3::CollectionParametersT params;
// 
// 		v.Initial();
// 
// 		params["openid"] = "00000000000000000000000014BDF6E4";
// 		params["openkey"] = "8A590068198AA8F91EADDCC408215AD6";
// 		params["pf"] = "qzone";
// 		params["amt"]="4";
// 		params["billno"]="-APPDJT18700-20120210-1428215572";
// 		params["payamt_coins"]="2";
// 		params["payitem"]="5005*4*1";
// 		params["provide_errno"]="0";
// 		params["providetype"]="0";
// 
// 		params["pubacct_payamt_coins"]="1";
// 		params["token_id"]="70CA63F0AD33AD19FD376DDC4792337A04621";
// 		params["ts"]="1339409927";
// 		params["version"]="v3";
// 		params["zoneid"]="0";
// 		
// 		v.BuildInvokeUrl(url,"/v3/pay/confirm_delivery",params,tx::InterfaceV3::ENCODE_METHOD_CONFIRM_DELIVERY);
// 
// 		std::cout << url << std::endl;
// 	}


	{
		const std::string configure("./pwaccsrv.xml");

		pwngs::ReloadWhiteList("./pwaccsrv_whitelist.json");

		if(pwaccsrv_Node::instance()->Startup(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			std::cerr << "invalid configure file:" << configure << std::endl;
			return 1;
		}

		pwaccsrv_Node::instance()->AddListener(new NodeListener);

		pwutils::Xml xml;
		if(xml.LoadFromFile(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			std::cerr << "invalid configure file:" << configure << std::endl;
			return 2;
		}

		pwutils::time::sleep(1000);
		
		// 创建服务端口
		for(int i = 0; i < pwaccsrv::max_service_port; ++i)
			StartupPort(i,xml);
		
		pwutils::time::sleep(1000);
		
		//防沉迷线程	
// 		pwaccsrv::SImplWallow* port = new pwaccsrv::SImplWallow();
// 		if (port->Startup(pwngs::cst_port_accsrv_wallow,pwaccsrv_Node::instance(),xml) != 0)
// 		{
// 			gErrorStream( "start wallow service failed");
// 			return 3;
// 		}

		// 载入全局配置信息
		// pwngs::g_objSavedConfigures.LoadFromDbsrv(pwaccsrv_Node::instance());

		std::cout << "pwaccsrv started." << std::endl;
		std::cout << "Listen:" << pwaccsrv_Node::instance()->GetListenAddr() << std::endl;

		while(!pwngs::gClosed)
		{
			pwutils::time::sleep(1);
			pwaccsrv_Node::instance()->Update();
		}

		pwaccsrv_Node::instance()->Cleanup();
	}
	pwutils::logger::ShutDown();
	platform::fini();
	return 0;
}
