#include "pw_lua.h"
#include <iostream>

namespace pwlua
{
	int int64_convert_int32(lua_State* L);

	fnContextInformation g_pfnContextInformation = NULL;

	void initial_int64_support(lua_State* L)
	{
		lua_newtable(L);

		lua_pushstring(L,"__eq");
		lua_pushcfunction(L,&int64_eq);
		lua_settable(L,-3);

		lua_pushstring(L,"__lt");
		lua_pushcfunction(L,&int64_lt);
		lua_settable(L,-3);

		lua_pushstring(L,"__le");
		lua_pushcfunction(L,&int64_le);
		lua_settable(L,-3);

		lua_pushstring(L,"__tostring");
		lua_pushcfunction(L,&int64_tostring);
		lua_settable(L,-3);
	
		lua_pushstring(L,"__unm");
		lua_pushcfunction(L,&int64_unm);
		lua_settable(L,-3);

		lua_pushstring(L,"__mod");
		lua_pushcfunction(L,&int64_mod);
		lua_settable(L,-3);

		lua_setglobal(L,cst_int64_metatable);

		// -------------------------------------------------

		lua_pushcfunction(L,&int64_convert);
		lua_setglobal(L,"toll");

		lua_pushcfunction(L,&int64_convert_int32);
		lua_setglobal(L,"toint32");

		lua_pushcfunction(L,&int64_is);
		lua_setglobal(L,"isll");
	}

	int int64_error(lua_State* L,int index)
	{
		gErrorStream( "**int64_error** type=" << lua_type(L,index) << " index = " << index);

#ifdef _DEBUG
		std::cout << "**int64_error** type=" << lua_type(L,index) << " index = " << index;

		assert(false && "invalid int64 type");
#endif

		return 0;
	}

	int int64_convert_int32(lua_State* L)
	{
		assert(lua_gettop(L) == 1);

		int type = lua_type(L,1);
		if( type == LUA_TUSERDATA || type == LUA_TLIGHTUSERDATA)
		{
			int64 n = pwlua::_detail::stack_helper<int64>::cast(L,1);
			pwlua::_detail::stack_helper<int32>::push(L,(int32)n);
		}
		else if(type == LUA_TSTRING || type == LUA_TNUMBER)
		{
			pwlua::_detail::stack_helper<int32>::push(L,lua_tointeger(L,1));
		}
		else
		{
			lua_pushnil(L);
		}

		return 1;
	}

	int int64_convert(lua_State* L)
	{
		assert(lua_gettop(L) == 1);

		int64 n = pwlua::_detail::stack_helper<int64>::cast(L,1);
		
		pwlua::_detail::stack_helper<int64>::push(L,n);

		return 1;
	}

	int int64_eq(lua_State* L)
	{
		assert(lua_gettop(L) == 2);

		int64 n1 = _detail::stack_helper<int64>::cast(L,1);
		int64 n2 = _detail::stack_helper<int64>::cast(L,2);

		lua_pushboolean(L,n1 == n2);

		return 1;
	}

	int int64_lt(lua_State* L)
	{
		assert(lua_gettop(L) == 2);

		int64 n1 = _detail::stack_helper<int64>::cast(L,1);
		int64 n2 = _detail::stack_helper<int64>::cast(L,2);

		lua_pushboolean(L,n1 < n2);

		return 1;
	}

	int int64_le(lua_State* L)
	{
		assert(lua_gettop(L) == 2);

		int64 n1 = _detail::stack_helper<int64>::cast(L,1);
		int64 n2 = _detail::stack_helper<int64>::cast(L,2);

		lua_pushboolean(L,n1 <= n2);

		return 1;
	}

	int int64_tostring(lua_State* L)
	{
		assert(lua_gettop(L) == 1);

		char buf[100];
		int64 n1 = _detail::stack_helper<int64>::cast(L,1);

#ifdef _MSC_VER	
		sprintf(buf,"%I64d",n1);
#else
		sprintf(buf,"%lld",n1);
#endif
		lua_pushstring(L,buf);
		return 1;
	}

	int int64_unm( lua_State* L )
	{
		assert(lua_gettop(L) == 1);

		int64 n = pwlua::_detail::stack_helper<int64>::cast(L,1);

		pwlua::_detail::stack_helper<int64>::push(L,-n);

		return 1;
	}

	int int64_mod( lua_State* L )
	{
		assert(lua_gettop(L) == 2);

		int64 n1 = _detail::stack_helper<int64>::cast(L,1);
		int64 n2 = _detail::stack_helper<int64>::cast(L,2);

		pwlua::_detail::stack_helper<int64>::push(L,n1 % n2);

		return 1;
	}

	bool int64_check(lua_State* L,int index)
	{
		if(lua_getmetatable(L,index) == 0)
		{
			return false;
		}

		lua_getglobal(L,cst_int64_metatable);
		
		int result = lua_rawequal(L,-1,-2);

		lua_pop(L,2);

		return result == 1;
	}

	int int64_is( lua_State* L )
	{
		assert(lua_gettop(L) == 1);

		lua_pushboolean(L,int64_check(L,1));

		return 1;
	}

	static std::string lua_backtrace(lua_State* L,const char* errorstr)
	{
		lua_Debug ldbg;
		std::stringstream ss;

		ss << "Lua stack backtrace: " << errorstr << "\n";

		for (int i = 1; lua_getstack(L, i, &ldbg); i++)
		{
			ss << "\t#" << i - 1 << " ";

			if (!lua_getinfo(L, "nSl", &ldbg))
			{
				ss << "???\n";
				continue;
			}

			if (ldbg.namewhat && ldbg.namewhat[0])
				ss << " " << ldbg.namewhat;

			if (ldbg.name && ldbg.name[0] != 0)
				ss << "function " << ldbg.name << "()";
			else
			{
				if (strcmp(ldbg.what, "main") == 0)
					ss << "mainline of chunk";
				else if (strcmp(ldbg.what, "tail") == 0)
					ss << "tail call";
				else
					ss << "unidentifiable function";
			}

			ss << "\t";

			if (strcmp(ldbg.what, "C") == 0)
				ss << "in native code";
			else if (strcmp(ldbg.what, "tail") == 0)
				ss << "in Lua code";
			else if (ldbg.source && (strcmp(ldbg.source, "=?") == 0) && (ldbg.currentline == 0) )
				ss << "in Lua code (debug info stripped)";
			else
			{
				ss << "in Lua code at " << ldbg.short_src;
				if (ldbg.currentline != -1)
					ss << ":" << ldbg.currentline;
				if(ldbg.name != 0)
					ss << " " << ldbg.name << "()";
			}
			ss << "\n";
		}
		return ss.str();
	}


	void utils::print_script_info( lua_State* L )
	{
		std::string stack = lua_backtrace(L,"invalid param");
		luaL_error(L,stack.c_str());
		/*
		lua_Debug ar = {0};
		lua_getfield(L,LUA_GLOBALSINDEX,"f");
		lua_getinfo(L,">Sfl",&ar);

		if(ar.source)
			gErrorStream("script source=" << ar.source << " line=" << ar.currentline);
		if(ar.what)
			gErrorStream("script what=" << ar.what);
		if(ar.short_src)
			gErrorStream("script short_src=" << ar.short_src);
		*/
	}

}