#include "pw_ctrlsrv.h"


#include "pw_kvorm_uuid_pool.h"
#include <ace/OS_NS_sys_stat.h>



namespace pwngs
{
	//extern void InitialHmodules();
}

namespace pwngs
{

#ifndef _MSC_VER
	static std::string g_strHModuleDirectory("./hmodules/c/");

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

	int InitialCtrlsrv()
	{
		//pwngs::InitialHmodules();
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
		std::string path("./data/csv/");
		//g_objPublicDataset.Load(path);
		
		{
			std::string uuidbase("./uuids");
			std::string uuidpath(uuidbase);
			uuidpath.append("/");
			uuidpath.append("ctrlsrv");
			uuidpath.append("/");

			ACE_OS::mkdir(uuidbase.c_str());
			ACE_OS::mkdir(uuidpath.c_str());
			pwutils::InitialUUIDPool(uuidpath);
		}

		return 0;
	}

	int CleanupCtrlsrv()
	{
		return 0;
	}

	int UpdateCtrlsrv()
	{
#ifndef _MSC_VER
		g_objHModuleWatcher.Update();
#endif
		//pwutils::GetMainHModuleMgr()->Tick(pwutils::time::get());

		return 0;
	}


}