#include <iostream>
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_def.h"
#include "pw_gdb_server.h"
#include "pw_gdb_master.h"
#include "pw_gdb_client.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_error_handler.h"
#include "pw_gdb_slave.h"
#include "json/json.h"
#include <fstream>
#include "pw_logger.h"
#ifdef _TCMALLOC_USED
	#include <google/malloc_extension.h>
#endif

using namespace gdb;


int main_slave(Json::Value& root)
{
	std::string directory = root.get("slave_dir","./slave_db/").asCString();
	std::string baks_directory = root.get("slave_baks_dir","./slave_db_baks/").asCString();
	std::string masteraddr = root.get("master_addr","127.0.0.1").asCString();
	std::string login_user = root.get("login_user","test").asCString();
	std::string login_pswd = root.get("login_pswd","test").asCString();
	int masterport = root.get("master_port","8600").asInt();
	int slaveport = root.get("slave_port","8650").asInt();
	int backup_interval = root.get("backup_interval","3600").asInt();

	Json::Value databases = root.get("databases","[]");
	if(!databases.isArray())
	{
		std::cerr << "invalid conf: databases not array" << std::endl;
		return 1;
	}

	if(databases.size() == 0)
	{
		std::cerr << "invalid conf: databases not contain name" << std::endl;
		return 2;
	}

	if(directory[directory.length() - 1] != '/')
		directory = directory + "/";

	Json::Value emptyJson;
	gdb::Environment g_mEnv("",emptyJson);
 	gdb::Slave g_mSlave;
 	g_mSlave.Initial(directory,baks_directory,backup_interval,masteraddr,masterport,login_user,login_pswd,slaveport);

 	for(size_t i = 0; i < databases.size(); ++i)
		g_mSlave.Create(databases[i].asString());

	while(!pwngs::gClosed)
	{
		pwutils::time::sleep(0);
		g_mSlave.Update();
	}

	return 0;
}

int main_server(Json::Value& root)
{
	std::string directory = root.get("dir","./db/").asCString();
	std::string backupdirectory = root.get("backup_dir","./db_backups/").asCString();
	std::string bind = root.get("bind","").asCString();
	std::string masterbind = root.get("master_bind","").asCString();
	int port = root.get("port","8600").asInt();
	int masterport = root.get("master_port","8601").asInt();
	int authmode = root.get("auth_mode","0").asInt();
	Json::Value leveldbConfig = root.get("dbconf",Json::Value());

	gdb::g_bEnableIndices = root.get("global_enable_index","true").asString() == "true";

	if(directory[directory.length() - 1] != '/')
		directory = directory + "/";
	if(backupdirectory[backupdirectory.length() - 1] != '/')
		backupdirectory = backupdirectory + "/";

	gdb::Server g_mServer(directory,backupdirectory,authmode,leveldbConfig);
	gdb::Master g_mMaster;

	g_mServer.Startup(bind.c_str(),port);
	g_mMaster.Startup(masterbind.c_str(),masterport);

	std::cout << "pwgdbserver ListenOn:" << port << " bind:" << bind << std::endl;
	std::cout << "pwgdbmaster ListenOn:" << masterport << " bind:" << masterbind << std::endl;
	std::cout << "database directory:" << directory << std::endl;
	std::cout << "backup directory:" << backupdirectory << std::endl;
	std::cout << "auth_mode:" << authmode << std::endl;

	int count = 0;

	while(!pwngs::gClosed)
	{
		++count;
		pwutils::time::sleep(1000);

#ifdef _TCMALLOC_USED
		if((count % 20) == 0)
		{
			count = 0;
			MallocExtension::instance()->ReleaseFreeMemory();		
		}
#endif


// 		std::cout << "chunk size=" << gdb::g_chunk_size << std::endl;
	}

	g_mServer.Cleanup();
	g_mMaster.Cleanup();

	return 0;
}

int main(int argc, char** argv)
{
#ifdef _MSC_VER
	platform::init();
#endif
	pwngs::MySigHandler_Init();
	pwutils::logger::Initial("gdb_");

	std::string defaultConf = "./gdb.conf";

	if(argc > 1)
		defaultConf = argv[1];

	std::fstream fs;
	fs.open(defaultConf.c_str(),std::ios_base::in);
	if(!fs.good())
	{
		std::cerr << "Open Configure File " << defaultConf << " Failed" << std::endl;
		return 1;
	}
	Json::Value root;
	Json::Reader reader;
	if(!reader.parse(fs,root))
	{
		std::cerr << "Parse Configure File Failed:" << reader.getFormatedErrorMessages() << std::endl;
		return 1;
	}
	fs.close();

	int r = 1;

	std::string mode = root.get("mode","server").asCString();
	if(mode == "server")
		r = main_server(root);
	else if(mode == "slave")
		r = main_slave(root);
	else
		std::cerr << "invalid mode:" << mode << std::endl;

#ifdef _MSC_VER
	platform::fini();
#endif

	return r;
}