#ifndef _pw_gdb_module_
#define _pw_gdb_module_

#include <string>

namespace gdb
{
	class Server;

	typedef int (*_pfn_dbmod_init)(gdb::Server* server);
	typedef int (*_pfn_dbmod_fini)(gdb::Server* server);
	typedef int (*_pfn_dbmod_exec)(gdb::Server* server,const char* data,size_t size,std::string& error);

	struct SModuleDefine
	{
		_pfn_dbmod_init init;
		_pfn_dbmod_fini fini;
		_pfn_dbmod_exec exec;
	};
}
#endif //_pw_gdb_module_