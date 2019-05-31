#ifndef _pw_gdb_client_script_lua_
#define _pw_gdb_client_script_lua_

#include "pw_gdb_client_script.h"
#include "pw_lua.h"

namespace gdb
{
	class ClientScriptLua : public ClientScript
	{
	public:
		ClientScriptLua();
		virtual ~ClientScriptLua();
	public:
		void GC();
	public:
		virtual bool Startup(const gdb::Slice& script,std::string& error);
		virtual void Cleanup();
	public:
		virtual bool Filter(const gdb::Slice& name,const gdb::Slice& key,const gdb::Slice& val);
		virtual bool Execute(DatabaseScriptHelper* helper,const char* func,const char* params,std::string& error);
	public:
		lua_State *L;
		std::string filterFuncName;
	};
}

#endif // _pw_gdb_client_script_lua_