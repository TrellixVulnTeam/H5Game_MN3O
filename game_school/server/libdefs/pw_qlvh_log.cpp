#include "pw_qlvh_log.h"
#include "pw_server_group.h"

namespace pwngs
{
/*
	static const char* cst_GameNamePY = "BH";

	static const char* g_szLogName[] = 
	{
		"COST",
		"LOGIN",
		"LOGOUT",
		"ONLINE",
		"RECHARGE",
		"REGISTER",
		"UPGRADE",
		"QUEST",
	};
*/

	int InitialQlvhLog(const char* path,const char* tmppath,int serverid)
	{
/*
		if(path == NULL)
			path = g_szQlogDirectory;
		if(tmppath == NULL)
			tmppath = g_szQlogDirectoryTmp;

		pwutils::g_pLogCollectorMgr = new pwutils::LogCollectorMgr(cst_GameNamePY,g_szServerName,QLOG_TYPE_MAX);
		for(int i = 0; i < QLOG_TYPE_MAX;++i)
			pwutils::g_pLogCollectorMgr->Get(i)->Start(g_szLogName[i],tmppath,path);
		// pwutils::g_pLogCollectorMgr->Startup();
*/
		return 0;
	}

	extern int CleanupQlvhLog()
	{
// 		pwutils::g_pLogCollectorMgr->Cleanup();
// 		_safe_delete(pwutils::g_pLogCollectorMgr);
		return 0;
	}

}