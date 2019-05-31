#include <cstdio>

#include "pw_def.h"
#include "pw_lua_ext.h"
#include "pw_logger.h"
#include "pw_worldsrv_node.h"
#include "pw_ngs_def.h"
#include "pw_ngs_vars.h"
#include "pw_ngs_utils.h"
#include "pw_utils.h"
#include "pwdist_remote_node.h"
#include "pw_worldsrv.h"
#include "pw_error_handler.h"
#include "main_test.h"
#include "ace/Init_ACE.h"
#include "pw_scripts.h"
#include "pw_server_group.h"
#include "pw_iconv.h"
#include "google/protobuf/stubs/common.h"

#ifdef _MSC_VER
	#include "vld.h"
#endif

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

void pfnPortRoutineRunTests(pwdist::PortBase* port,void* context)
{
	main_test();
}

// -------------------------------------------------------------------

// -------------------------------------------------------------------

#include "pw_kvorm_uuid_pool.h"

void fnErrorHandleFunc(int signo)
{
	std::cout << "fnErrorHandleFunc Called:" << signo << std::endl;

	if(pwutils::g_pUUIDPool != NULL)
		pwutils::g_pUUIDPool->Sync();

	pwngs::MySigHandler_Fini();

	return ;
}

int main(int argc, char **argv)
{
//	test_lua_int64();

	platform::init();
	ACE::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwgame_");
	char temp[20];
	sprintf(temp, "%d_6_", pwngs::g_nZoneId);
	//pwutils::logger::XiYouInitial(temp);
	pwutils::logger::ModLogInitial();
	pwngs::MySigHandler_Init(&fnErrorHandleFunc);

	{
		if(argc != 2)
		{
			std::cout << "Useage: ./pwworldsrv config_file" << std::endl;
			return 1;
		}

		const std::string configure(argv[1]);

		pwutils::Xml xml;
		if(xml.LoadFromFile(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			return 2;
		}

		if(pwworldsrv::InitialWorld(xml) != 0)
		{
			gErrorStream( "world_init failed :" << configure);
			return 3;
		}

		// 启动节点
		if(pwworldsrv_Node::instance()->Startup(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			return 4;
		}

		pwworldsrv_Node::instance()->AddListener(new NodeListener);


		// --------------------------------------------------------------------------------------------------
		std::string strLaunchWorld = xml.GetValue("/pwdist/pwworldsrv/thread_world/enable","false");
		std::string strLaunchLogin = xml.GetValue("/pwdist/pwworldsrv/thread_login/enable","false");
		std::string strLaunchSupport = xml.GetValue("/pwdist/pwworldsrv/thread_support/enable","false");

		//std::string strLoginPort = xml.GetValue("/pwdist/pwworldsrv/thread_login/port");
		std::string strSupportPort = xml.GetValue("/pwdist/pwworldsrv/thread_support/port");
		std::string strWorldThreadNum = xml.GetValue("/pwdist/pwworldsrv/thread_world/thread_num","5");

		bool launchWorld = pwutils::strtobool(strLaunchWorld.c_str());
		bool launchLogin = pwutils::strtobool(strLaunchLogin.c_str());
		bool launchSupport = pwutils::strtobool(strLaunchSupport.c_str());

		std::cout << "strLaunchSupport=" << strLaunchSupport << " launchLogin="  << launchLogin<< std::endl;

		int32 nWorldThreadNum = pwutils::atoi(strWorldThreadNum.c_str());
		pwasserte(nWorldThreadNum > 1 && nWorldThreadNum < 100);

		// --------------------------------------------------------------------------------------------------


		// --------------------------------------------------------------------------------------------------
		// 等待控制服务器,数据服务器上线
		// --------------------------------------------------------------------------------------------------

		std::cout << "Wait dbsrv Node..." << std::endl;
		while(!pwngs::gClosed && !pwworldsrv_Node::instance()->IsRemoteActive(pwngs::cst_node_db))
		{
			pwworldsrv_Node::instance()->Update();
			pwutils::time::sleep(100);
		}

		std::cout << "Wait ctrlsrv Node..." << std::endl;
		while(!pwngs::gClosed && !pwworldsrv_Node::instance()->IsRemoteActive(pwngs::cst_node_ctrl))
		{
			pwworldsrv_Node::instance()->Update();
			pwutils::time::sleep(100);
		}
		
		// --------------------------------------------------------------------------------------------------
		// 启动拉取线程
		// --------------------------------------------------------------------------------------------------
		if(!pwngs::gClosed)
		{
			// 启动login
			if(launchLogin)
			{
				/*pwngs::SImplLogin* port = new pwngs::SImplLogin();
				if(port->Startup(pwngs::cst_port_worldsrv_login,pwworldsrv_Node::instance(),xml) != 0)
				{
					gErrorStream( "gate port start failed");
					return 5;
				}*/
			}

			// --------------------------------------------------------------------------------------------------
			// 启动游戏服务器
			// --------------------------------------------------------------------------------------------------
			if(launchWorld)
			{
				int result = pwworldsrv::StartupWorld(pwworldsrv_Node::instance(),xml,nWorldThreadNum);
				if( result != 0)
				{
					gErrorStream( "startup world failed:"  << result);
					return 6;
				}
			}

			// TODO:: support Thread

			if(launchSupport)
			{
				/*pwngs::SImplSupport* port = new pwngs::SImplSupport();
				if(port->Startup(strSupportPort,pwworldsrv_Node::instance()) != 0)
				{
					gErrorStream( "SImplSupport port start failed");
					return 7;
				}*/
			}

			// --------------------------------------------------------------------------------------------------
			// 启动测试用例
			// --------------------------------------------------------------------------------------------------
// 			pwdist::PortBase* port = NULL;
// 			pwworldsrv_Node::instance()->GetPort("wsrv_1",&port); // TODO::测试
// 			pwassertn(port);
// 
// 			port->PostProc(&pfnPortRoutineRunTests,NULL);

			// 载入全局配置信息
			//pwngs::g_objSavedConfigures.LoadFromDbsrv(pwworldsrv_Node::instance());

			// --------------------------------------------------------------------------------------------------
			// 节点更新循环
			// --------------------------------------------------------------------------------------------------		

			std::cout << "----------------------------------------------------------------" << std::endl;
			std::cout << "pwworldsrv started." << std::endl;
			std::cout << "ServerID:" << pwworldsrv::g_nServerId << std::endl;
			std::cout << "ServerGroup:" << pwngs::g_nServerGroup << std::endl;
			
			std::cout << "LaunchWorld:" << launchWorld << std::endl;
			std::cout << "LaunchLogin:" << launchLogin << std::endl;
			std::cout << "LaunchSupport:" << launchSupport << std::endl;

			std::cout << "ListenOn:" << pwworldsrv_Node::instance()->GetListenAddr() << std::endl;
			std::cout << "----------------------------------------------------------------" << std::endl;

			while(!pwngs::gClosed)
			{
				pwutils::time::sleep(1);
				pwworldsrv::UpdateWorld();
				pwworldsrv_Node::instance()->Update();
			}
		}

		pwworldsrv_Node::instance()->Cleanup();
		pwworldsrv_Node::close_instance();
		pwworldsrv::CleanupWorld();
	}
	pwutils::logger::ShutDown();
	platform::fini();
	ACE::fini();

	google::protobuf::ShutdownProtobufLibrary();
	pwutils::__CleanupThreadEncoding();

#ifdef _MSC_VER
	printf("pwutils::g_ref_count = %d\r\n",pwutils::g_ref_count);
#endif

	return 0;
}
