#ifndef _AC_LUA_UTILS_H_
#define _AC_LUA_UTILS_H_

#include <lua.hpp>
#include <string>
#include <vector>
#include "ACDef.h"

BEGIN_NS_AC

class LuaConfig
{
public:
	LuaConfig();
	~LuaConfig();
public:
	int Load(const std::string& strFileName);
public:
	int GetInteger(const std::string& strParamName);
	std::string GetString(const std::string& strParamName);
	bool GetBoolean(const std::string& strParamName);
	std::vector<std::string> GetStringVector(const std::string& strParamName);
	int GetType(const std::string& strParamName);
public:
	void ExportCFunction(const std::string& strFuncName,lua_CFunction pFunc);
public:
	inline lua_State* GetLuaState()
	{
		return m_pLua;
	}
public:
	void PushTable(const std::string& strTableName);
public:
	bool IsTopTable();
	int GetTableLen(const std::string& strTableName);
public:
	template <class T>
	void IterArray(const std::string& strTableName, T* obj, void(T::*func)(void*), void* ctx = NULL)
	{
		PushTable(strTableName);

		int tableLen = lua_objlen(m_pLua,-1);
		for(int i = 1; i <= tableLen; ++i)
		{
			lua_pushinteger(m_pLua, i);
			lua_gettable(m_pLua, -2);

			(obj->*func)(ctx);

			lua_pop(m_pLua, 1);
		}

		lua_pop(m_pLua, 1);
	}
	template <class T>
	void IterTable(const std::string& strTableName, T* obj, void(T::*func)(void*), void* ctx = NULL)
	{
		PushTable(strTableName);

		lua_pushnil(m_pLua);
		while(lua_next(m_pLua,-2) != 0)
		{
			(obj->*func)(ctx);

			lua_pop(m_pLua,1);
		}

		lua_pop(m_pLua, 1);
	}
public:
	std::string GetTopAsString(int statckIdx);
private:
	int PushParam(const std::string& strParamName);
private:
	lua_State* m_pLua;
};

END_NS_AC

#endif//_AC_LUA_UTILS_H_