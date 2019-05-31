#ifndef _pw_file_system_
#define _pw_file_system_

#include "pw_def.h"

namespace pwutils
{
	extern void list_files(const char* dir,std::vector<std::string>& filenames);
}

#endif // _pw_file_system_