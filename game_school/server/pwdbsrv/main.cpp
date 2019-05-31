#include <cstdio>

#include "pw_def.h"
#include "pw_logger.h"
#include "pw_dbsrv_node.h"
#include "pw_dbsrv_kv_service.h"
#include "pw_dbsrv_kv_service_loader.h"
#include "pw_dbsrv_service.h"
#include "pw_dbsrv_service_sql.h"
#include "pw_dbsrv_service_loader.h"
#include "pwdist_remote_node.h"
#include "pw_ngs_def.h"
#include "CppMysql_FieldDefs.h"
#include "pw_error_handler.h"
#include "pw_server_group.h"
#include "pw_dbsrv_synchronizer.h"
#include "pw_kvorm_uuid_pool.h"
#include <ace/OS_NS_sys_stat.h>

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

#include "pw_kvorm_uuid_pool.h"

void fnErrorHandleFunc(int signo)
{
	std::cout << "fnErrorHandleFunc Called:" << signo << std::endl;

	if(pwutils::g_pUUIDPool != NULL)
		pwutils::g_pUUIDPool->Sync();

	pwngs::MySigHandler_Fini();

	return ;
}

/*
#include "algorithm/pw_base64.h"
#include "pw_utils.h"
*/

int main(int argc, char **argv)
{

/*
	char testbuf[13131];
	for(int i = 0; i < 13131; ++i)
		testbuf[i] = (char)pwutils::random(0,255);
	std::string v1 = pwutils::base64_encode(testbuf,_countof(testbuf));
	std::string v2 = pwutils::base64_decode(v1.c_str(),v1.length());
	assert(memcmp(v2.c_str(),testbuf,_countof(testbuf)) == 0);
*/

	platform::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwdbsrv_");
	pwngs::MySigHandler_Init(&fnErrorHandleFunc);

	{
		std::string uuidbase("./uuids");
		std::string uuidpath(uuidbase);
		uuidpath.append("/");
		uuidpath.append("dbsrv");
		uuidpath.append("/");

		ACE_OS::mkdir(uuidbase.c_str());
		ACE_OS::mkdir(uuidpath.c_str());
		pwutils::InitialUUIDPool(uuidpath);
	}

	{
		pwutils::Xml xml;

		if(xml.LoadFromFile("./pwdbsrv.xml") != 0)
		{
			gErrorStream( "invalid configure file:" << "./pwdbsrv.xml");
			return 1;
		}

// 		if(!pwdbsrv::SynchronizeDatabaseScheme(xml,"./sql/"))
// 		{
// 			gErrorStream( "SynchronizeDatabaseScheme failed");
// 			return 1;
// 		}

		if(pwdbsrv_Node::instance()->Startup(std::string("./pwdbsrv.xml")) != 0)
		{
			gErrorStream( "invalid configure file:" << "./pwdbsrv.xml");
			return 1;
		}

		pwdbsrv_Node::instance()->AddListener(new NodeListener);

		//kv服务线程
		pwdbsrv::SImplKVDBLoader* kvservice_lodder = new pwdbsrv::SImplKVDBLoader();
		if(kvservice_lodder->Startup(pwngs::cst_port_dbsrv_kv_service_loader,pwdbsrv_Node::instance(),xml) != 0)
		{
			gErrorStream( "start kv lodder service failed 2");
			return 2;
		}

		//kv服务线程
		pwdbsrv::SImplKVDB* kvservice = new pwdbsrv::SImplKVDB();
		if(kvservice->Startup(pwngs::cst_port_dbsrv_kv_service,pwdbsrv_Node::instance(),xml) != 0)
		{
			gErrorStream( "start kv service failed 2");
			return 2;
		}

/*
		//服务线程
		pwdbsrv::SImplDB* service = new pwdbsrv::SImplDB();
		if(service->Startup(pwngs::cst_port_dbsrv_service,pwdbsrv_Node::instance(),xml) != 0)
		{
			gErrorStream( "start service failed 2");
			return 2;
		}

		//sql线程
		pwdbsrv::SImplSqlExecutor* serviceSql = new pwdbsrv::SImplSqlExecutor();
		if(serviceSql->Startup(pwngs::cst_port_dbsrv_service_sql,pwdbsrv_Node::instance(),xml) != 0)
		{
			gErrorStream( "start sql service failed 3");
			return 3;
		}

		// loader线程
		pwdbsrv::SImplDBLoader* serviceLoader = new pwdbsrv::SImplDBLoader();
		if(serviceLoader->Startup(pwngs::cst_port_dbsrv_service_loader,pwdbsrv_Node::instance(),xml) != 0)
		{
			gErrorStream( "start sql loader failed 3");
			return 4;
		}
*/
		

		std::cout << "pwdbsrv started." << std::endl;
		std::cout << "Listen:" << pwdbsrv_Node::instance()->GetListenAddr() << std::endl;

		while(!pwngs::gClosed)
		{
			pwutils::time::sleep(1);
			pwdbsrv_Node::instance()->Update();
		}

		pwdbsrv_Node::instance()->Cleanup();
	}
	pwutils::logger::ShutDown();
	platform::fini();
	return 0;
}
