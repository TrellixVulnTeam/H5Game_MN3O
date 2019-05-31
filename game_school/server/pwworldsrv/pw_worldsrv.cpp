#include "pw_worldsrv.h"
#include "pw_utils.h"
#include "pw_file_system.h"
#include "pw_ngs_utils.h"

#include "pw_kvorm_uuid_pool.h"
#include "pw_operations_def.h"
#include <ace/OS_NS_sys_stat.h>


namespace pwngs
{
	//extern int InitialHuman();
	//extern int InitialCooldownDefs();

	static pwutils::ThreadSpecific<std::string> g_szLuaContext;

	//extern const char* fnLuaContextInformation(lua_State* L)
	//{
	//	std::string* buf = g_szLuaContext.get();
	//	if(buf == NULL)
	//	{
	//		buf = new std::string();
	//		buf->reserve(2048);
	//		g_szLuaContext.set(buf);
	//	}

	//	pwdist::Port* port = pwdist::Port::self();
	//	if(port == NULL)
	//		return "Port=Null";

	//	/*SImplStage* stagePort = dynamic_cast<SImplStage*>(port);
	//	if(stagePort == NULL)
	//		return "StagePort=Null";

	//	Stage* stage = stagePort->GetCurrentStage();
	//	if(stage == NULL)
	//		return "Stage=Null";*/

	//	/*std::stringstream ss;
	//	ss << " Stage " << stage->GetBaseMapID() << " Stack \n" << get_stack_trace(20);*/

	//	//*buf = ss.str();

	//	return buf->c_str();
	//}
}


namespace pwngs
{
	//extern void InitialHmodules();
}

namespace pwworldsrv
{
#ifndef _MSC_VER
	static std::string g_strHModuleDirectory("./hmodules/w/");

	class HModuleWatcher : public pwutils::FileWatcher
	{
	public:
		virtual int HandleEvent(unsigned mask,const char* filename)
		{
			std::string actualFile = g_strHModuleDirectory + filename;

			std::cout << __FUNCTION__ << " tryload:" << actualFile << std::endl;

			pwutils::GetMainHModuleMgr()->LoadModuleDelay(actualFile.c_str());
			return 0;
		}
	};

	HModuleWatcher g_objHModuleWatcher;

#endif

	int g_nServerId = 0;
	int g_nServerMode = 0;
	std::string g_strServerName = "unset";

	int InitialWorld(pwutils::Xml& params)
	{
		//pwngs::InitialHmodules();

		// 检查长度,以免溢出
		g_nServerId = (int)pwutils::atoi(params.GetValue("/pwdist/pwworldsrv/id").c_str());
		g_nServerMode = (int)pwutils::atoi(params.GetValue("/pwdist/pwworldsrv/mode","0").c_str());
		g_strServerName = params.GetValue("/pwdist/name");
		pwasserte(g_nServerId < 0xff);

#ifndef _MSC_VER
		{
			std::vector<std::string> hmoduels;
			pwutils::list_files(g_strHModuleDirectory.c_str(),hmoduels);
			std::sort(hmoduels.begin(),hmoduels.end());

			for(size_t i = 0; i < hmoduels.size(); ++i)
			{
				std::string filename = hmoduels[i];
				std::cout << __FUNCTION__ << " tryload:" << filename << std::endl;
				pwutils::GetMainHModuleMgr()->LoadModule(filename.c_str());
			}

			g_objHModuleWatcher.Add(g_strHModuleDirectory,pwutils::FileWatcher::MASK_CREATE | pwutils::FileWatcher::MASK_MOVED_TO);
		}
#endif

		// 配置文件路径
		std::string csvpath = params.GetValue("/pwdist/pwworldsrv/csv_path");
		if(csvpath.length() == 0)
			return -1;
		if(csvpath[csvpath.length()-1] != '/')
			csvpath = csvpath + "/";

		// 初始化
		//pwngs::g_objItemDataset.Load(csvpath);
		
		//pwngs::InitialHuman();
		//pwngs::InitialCooldownDefs();
		//pwngs::GlobalFunctionEnableInit();
		//pwngs::InitialChallengeBoss();

		//pwlua::g_pfnContextInformation = &pwngs::fnLuaContextInformation;

		{
			char myuuiddir[256] = {0};
			sprintf(myuuiddir,"worldsrv_%d",(int)g_nServerId);

			std::string uuidbase("./uuids");
			std::string uuidpath(uuidbase);
			uuidpath.append("/");
			uuidpath.append(myuuiddir);
			uuidpath.append("/");

			ACE_OS::mkdir(uuidbase.c_str());
			ACE_OS::mkdir(uuidpath.c_str());
			pwutils::InitialUUIDPool(uuidpath);
		}

		return 0;
	}

	int StartupWorld(pwdist::Node* node,pwutils::Xml& xml, int threadNum)
	{
		int start = 1;
		int ended = threadNum;
		
		if(pwworldsrv::g_nServerId == 0)
		{
			//pwngs::g_objStageSchemeMgr.CreateNormalMaps(node,start,ended,pwworldsrv::g_nServerId * 100);
		}

		return 0;
	}

	int CleanupWorld()
	{
		return 0;
	}

	int UpdateWorld()
	{
#ifndef _MSC_VER
		g_objHModuleWatcher.Update();
#endif
		//pwutils::GetMainHModuleMgr()->Tick(pwutils::time::get());
		//pwngs::UpdateChallengeBoss();
		return 0;
	}

}



// ----------------------------------------------------------------------------------
// 测试用例
// ---------------------------------------------------------------------------------

/*#ifndef _DEBUG

#include <unittest++/UnitTest++.h>
#include "pw_ordered_vector.h"

TEST(TestCommon)
{
	using namespace pwngs;
	using namespace pwutils;

	pwutils::ordered_vector<int> vt;


	vt.push_back(10200);
	vt.push_back(10201);
	vt.push_back(10202);
	vt.push_back(10203);

	pwutils::ordered_vector<int>::iterator iter = vt.find(10202);
	CHECK(iter != vt.end());

	vt.erase(iter);
}

#endif
*/