#include "pw_scripts.h"
#include "pw_def.h"
#include "pw_logger.h"
#include "pw_lua.h"

namespace pwngs
{
// 	static pthread_mutex_t g_script_lock;
// 	static lua_State* L = NULL;
// 
// 	int StartupScripts()
// 	{
// 		L = luaL_newstate();
// 		luaL_openlibs(L);
// 
// 		pthread_mutex_init(&g_script_lock,NULL);
// 
// 		pwngs::InitialExports(L);
// 
// 		luaL_dofile(L,"./Lua/worldsrv/main.lua");
// 
// 		return 0;
// 	}
// 
// 	int CleanupScripts()
// 	{
// 		pthread_mutex_lock(&g_script_lock);
// 		lua_close(L);
// 		pthread_mutex_unlock(&g_script_lock);
// 
// 		pthread_mutex_destroy(&g_script_lock);
// 
// 		return 0;
// 	}
// 
// 	int CreateEnvriment(lua_State*& l,int& r)
// 	{
// 		pthread_mutex_lock(&g_script_lock);
// 
// 		l = lua_newthread(L);
// 		r = lua_ref(L,true);
// 
// 		pthread_mutex_unlock(&g_script_lock);
// 
// 		return 0;
// 	}
// 
// 	int DeleteEnvriment( lua_State* l,int r )
// 	{
// 		pthread_mutex_lock(&g_script_lock);
// 
// 		lua_unref(L,r);
// 
// 		lua_gc(L,LUA_GCCOLLECT,0);
// 
// 		pthread_mutex_unlock(&g_script_lock);
// 
// 		return 0;
// 	}

}