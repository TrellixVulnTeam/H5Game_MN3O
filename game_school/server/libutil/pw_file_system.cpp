#include "pw_file_system.h"
#include "pw_platform.h"
#include "pw_utils.h"

#ifdef __linux
	#include <dirent.h>
#endif

namespace pwutils
{

#ifdef _MSC_VER
	void list_files( const char* dir,std::vector<std::string>& filenames )
	{
		char findname[256] = "";
		snprintf(findname,_countof(findname),"%s*.*",dir);

		_WIN32_FIND_DATAA data = {0};
		HANDLE hFind = FindFirstFileA(findname,&data);
		do
		{
			if(strlen(data.cFileName) <= 0 || stricmp(data.cFileName,".") == 0 || stricmp(data.cFileName,"..") == 0)
				continue;
			filenames.push_back(std::string(dir) + data.cFileName);
		} while(FindNextFileA(hFind,&data));

		FindClose(hFind);
	}
#else

	void list_files( const char* dir,std::vector<std::string>& filenames )
	{
		DIR* d = opendir(dir);
		if(d == NULL)
			return;

		struct dirent* entry = NULL;
		while((entry = readdir(d)))
		{
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0 || strcmp(entry->d_name,"\\") == 0)
				continue;
			filenames.push_back(std::string(dir) + entry->d_name);
		}

		closedir(d);
	}

#endif

}