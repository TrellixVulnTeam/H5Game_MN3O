#ifndef _pw_lua_utils_
#define _pw_lua_utils_

#include "pw_lua.h"
#include "pw_types.h"
#include "pw_logger.h"

namespace pwlua
{
	struct table_utils
	{
		template<class T> static T GetField(lua_State* L,int tableIndex,int index)
		{
			T result = 0;
			lua_pushvalue(L,tableIndex);
			lua_pushinteger(L,index);
			lua_gettable(L,-2);
			result = pwlua::_detail::stack_helper<T>::cast(L,-1);
			lua_pop(L,2);
			return result;
		}

		template<class T> static T GetField(lua_State* L,int tableIndex,const char* index)
		{
			T result = 0;
			lua_pushvalue(L,tableIndex);
			lua_pushinteger(L,index);
			lua_gettable(L,-2);
			result = pwlua::_detail::stack_helper<T>::cast(L,-1);
			lua_pop(L,2);
			return result;
		}
	};

	struct func_utils
	{
		static bool getfunc(lua_State* L,const char* func,int table = LUA_GLOBALSINDEX)
		{
			lua_getfield(L,table,func);
			if(lua_type(L,-1) != LUA_TFUNCTION)
			{
				lua_pop(L,1);
				return false;
			}
			return true;
		}
	};


	struct ExecuteHelper
	{
		int ExecuteScript(lua_State* L,int ref,const_char_ptr functionName)
		{
			if(ref == LUA_REFNIL || functionName == NULL || strlen(functionName) == 0)
				return -1;

			lua_getref(L,ref);

			lua_pushstring(L,functionName);
			lua_gettable(L,-2);

			int t = lua_type(L,-1);
			if( t != LUA_TFUNCTION)
			{
				lua_pop(L,1);

				pwreportvars(false,"ExecuteHelper::ExecuteScript " << functionName);
				pwasserte(false && "ExecuteHelper::ExecuteScript func no exists");
			}
			else
			{
				lua_pushvalue(L,-2); // push dungeon script object
				if(lua_pcall(L,1,0,0) != 0)
				{
					pwreportvars(false,"ExecuteHelper::ExecuteScript Failed " << functionName << lua_tostring(L,-1));
					pwasserte(false && "ExecuteHelper::ExecuteScript func Failed");
				}
			}
			lua_pop(L,1); // pop dungeon script object

			return 0;
		}

		template<class P1> int ExecuteScript(lua_State* L,int ref,const_char_ptr functionName,P1 v1)
		{
			if(ref == LUA_REFNIL || functionName == NULL || strlen(functionName) == 0)
				return -1;

			lua_getref(L,ref);

			lua_pushstring(L,functionName);
			lua_gettable(L,-2);

			int t = lua_type(L,-1);
			if( t != LUA_TFUNCTION)
			{
				lua_pop(L,1);

				pwreportvars(false,"ExecuteHelper::ExecuteScript " << functionName);
				pwasserte(false && "ExecuteHelper::ExecuteScript func no exists");
			}
			else
			{
				lua_pushvalue(L,-2); // push dungeon script object
				pwlua::_detail::stack_helper<P1>::push(L,v1);
				if(lua_pcall(L,2,0,0) != 0)
				{
					pwreportvars(false,"ExecuteHelper::ExecuteScript Failed " << functionName << ":" << lua_tostring(L,-1));
					pwasserte(false && "ExecuteHelper::ExecuteScript func Failed");
				}
			}
			lua_pop(L,1); // pop dungeon script object

			return 0;
		}

		template<class P1,class P2> int ExecuteScript(lua_State* L,int ref,const_char_ptr functionName,P1 v1,P2 v2)
		{
			if(ref == LUA_REFNIL || functionName == NULL || strlen(functionName) == 0)
				return -1;

			lua_getref(L,ref);

			lua_pushstring(L,functionName);
			lua_gettable(L,-2);

			int t = lua_type(L,-1);
			if( t != LUA_TFUNCTION)
			{
				lua_pop(L,1);

				pwreportvars(false,"ExecuteHelper::ExecuteScript " << functionName);
				pwasserte(false && "ExecuteHelper::ExecuteScript func no exists");
			}
			else
			{
				lua_pushvalue(L,-2); // push dungeon script object
				pwlua::_detail::stack_helper<P1>::push(L,v1);
				pwlua::_detail::stack_helper<P2>::push(L,v2);
				if(lua_pcall(L,3,0,0) != 0)
				{
					pwreportvars(false,"ExecuteHelper::ExecuteScript Failed " << functionName << ":" << lua_tostring(L,-1));
					pwasserte(false && "ExecuteHelper::ExecuteScript func Failed");
				}
			}
			lua_pop(L,1); // pop dungeon script object

			return 0;
		}

		template<class P1,class P2,class P3> int ExecuteScript(lua_State* L,int ref,const_char_ptr functionName,P1 v1,P2 v2,P3 v3)
		{
			if(ref == LUA_REFNIL || functionName == NULL || strlen(functionName) == 0)
				return -1;

			lua_getref(L,ref);

			lua_pushstring(L,functionName);
			lua_gettable(L,-2);

			int t = lua_type(L,-1);
			if( t != LUA_TFUNCTION)
			{
				lua_pop(L,1);

				pwreportvars(false,"ExecuteHelper::ExecuteScript " << functionName);
				pwasserte(false && "ExecuteHelper::ExecuteScript func no exists");
			}
			else
			{
				lua_pushvalue(L,-2); // push dungeon script object
				pwlua::_detail::stack_helper<P1>::push(L,v1);
				pwlua::_detail::stack_helper<P2>::push(L,v2);
				pwlua::_detail::stack_helper<P3>::push(L,v3);
				if(lua_pcall(L,4,0,0) != 0)
				{
					pwreportvars(false,"ExecuteHelper::ExecuteScript Failed " << functionName << ":" << lua_tostring(L,-1));
					pwasserte(false && "ExecuteHelper::ExecuteScript func Failed");
				}
			}
			lua_pop(L,1); // pop dungeon script object

			return 0;
		}
		template<class P1,class P2,class P3,class P4> int ExecuteScript(lua_State* L,int ref,const_char_ptr functionName,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			if(ref == LUA_REFNIL || functionName == NULL || strlen(functionName) == 0)
				return -1;

			lua_getref(L,ref);

			lua_pushstring(L,functionName);
			lua_gettable(L,-2);

			int t = lua_type(L,-1);
			if( t != LUA_TFUNCTION)
			{
				lua_pop(L,1);

				pwreportvars(false,"ExecuteHelper::ExecuteScript " << functionName);
				pwasserte(false && "ExecuteHelper::ExecuteScript func no exists");
			}
			else
			{
				lua_pushvalue(L,-2); // push dungeon script object
				pwlua::_detail::stack_helper<P1>::push(L,v1);
				pwlua::_detail::stack_helper<P2>::push(L,v2);
				pwlua::_detail::stack_helper<P3>::push(L,v3);
				pwlua::_detail::stack_helper<P4>::push(L,v4);
				if(lua_pcall(L,5,0,0) != 0)
				{
					pwreportvars(false,"ExecuteHelper::ExecuteScript Failed " << functionName << ":" << lua_tostring(L,-1));
					pwasserte(false && "ExecuteHelper::ExecuteScript func Failed");
				}
			}
			lua_pop(L,1); // pop dungeon script object

			return 0;
		}
	};
}

#endif // _pw_lua_utils_