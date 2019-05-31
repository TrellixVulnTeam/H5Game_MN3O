#include "pw_gdb_client_script_lua.h"
#include "bson/bson.h"
#include "pw_gdb_database_script_helper.h"

namespace gdb
{
	ClientScriptLua::ClientScriptLua()
	{
		L = luaL_newstate();
		luaL_openlibs(L);
		filterFuncName = "";
	}

	ClientScriptLua::~ClientScriptLua()
	{
		lua_close(L);
	}

	bool ClientScriptLua::Startup( const gdb::Slice& script,std::string& error )
	{
		std::string strScript(script.data(),script.size());

		if(luaL_loadstring(L,strScript.c_str()) != 0)
		{
			error = lua_tostring(L,-1);
			return false;
		}
		lua_pcall(L, 0, LUA_MULTRET, 0);
		return true;
	}

	void ClientScriptLua::Cleanup()
	{

	}

	bool ClientScriptLua::Filter( const gdb::Slice& name,const gdb::Slice& key,const gdb::Slice& val )
	{
		if(filterFuncName.empty())
			return true;

		lua_getglobal(L,filterFuncName.c_str());
		if(lua_type(L,-1) != LUA_TFUNCTION)
		{
			lua_pop(L,1);
			std::cout << "ClientScriptLua::Filter nofound lua func" << std::endl;
			return false;
		}
		BsonObject obj(val.data(),val.size());

		lua_pushlstring(L,name.data(),name.size());
		lua_pushlstring(L,key.data(),key.size());
		pwlua::_detail::stack_helper<BsonObject&>::push(L,obj);

		if(lua_pcall(L,3,1,0) != 0)
		{
			std::cout << "ClientScriptLua::Filter script error:" << lua_tostring(L,-1) << std::endl;
			return false;
		}
		bool result = pwlua::_detail::stack_helper<bool>::cast(L,-1);
		lua_pop(L,1);
		return result;
	}

	bool ClientScriptLua::Execute(DatabaseScriptHelper* helper,const char* func,const char* params,std::string& error)
	{
		lua_getglobal(L,func);
		if(lua_type(L,-1) != LUA_TFUNCTION)
		{
			lua_pop(L,1);
			error.append("ClientScriptLua::Execute func nofound :");
			error.append(func);
			return false;
		}

		pwlua::_detail::stack_helper<gdb::DatabaseScriptHelper*>::push(L,helper);
		lua_pushstring(L,params);
		if(lua_pcall(L,2,0,0) != 0)
		{
			error.append("ClientScriptLua::Execute script error:");
			error.append(lua_tostring(L,-1));
			return false;
		}
		return true;
	}

	void ClientScriptLua::GC()
	{
		lua_gc(L,LUA_GCCOLLECT,0);
	}

}