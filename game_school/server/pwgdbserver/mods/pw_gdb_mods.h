#ifndef _pw_gdb_mods_
#define _pw_gdb_mods_

#include "pw_gdb_module.h"

namespace dbmod_fixpassportitems
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

namespace dbmod_convert_passport
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

namespace dbmod_remove_futile
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

namespace dbmod_merge
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

namespace dbmod_fix_names
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

namespace dbmod_fix_names2
{
	extern int init(gdb::Server* server);
	extern int fini(gdb::Server* server);
	extern int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result);
}

#define _DBMOD_ERROR_(bson_result,error) \
	mongo::BSONObjBuilder error_builder;\
	error_builder.append("code",0 - __LINE__);\
	error_builder.append("info",error);\
	mongo::BSONObj error_bson = error_builder.obj();\
	bson_result = std::string(error_bson.objdata(),error_bson.objsize());


#ifndef _MSC_VER
	#define _GDB_DEFINE_MOD_(__ns) extern "C" void dbmod_entry(gdb::SModuleDefine* define,std::string* name)\
	{\
		*name = #__ns;\
		define->init = &__ns::init;\
		define->fini = &__ns::fini;\
		define->exec = &__ns::exec;\
	}
#else
	#define _GDB_DEFINE_MOD_(__ns)
#endif


#endif // _pw_gdb_mods_