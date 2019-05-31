#ifndef _pw_file_watcher_
#define _pw_file_watcher_

#ifndef _MSC_VER

#include "pw_platform.h"
#include <vector>
#include <string>

namespace pwutils
{
	class FileWatcher
	{
	public:
		enum 
		{
			MASK_CREATE = IN_CREATE,
			MASK_MOVED_TO = IN_MOVED_TO,
		};
	public:
		FileWatcher();
		virtual ~FileWatcher();
	public:
		int Add(const std::string& path,unsigned mask);
		int Del(const std::string& path);
		int Del(int wd);
		int Update();
	public:
		virtual int HandleEvent(unsigned mask,const char* filename) = 0;
	private:
		struct SWatchInfo
		{
			int wd;
			std::string path;
		};
	private:
		typedef std::vector<SWatchInfo> CollectionWatchInfosT;
	private:
		int m_fd;
		CollectionWatchInfosT m_vInfos;
	};
}

#endif

#endif // _pw_file_watcher_