#include "ACLuaUtils.h"
#include <iostream>
#include "ACString.h"
#include "ACLog.h"

BEGIN_NS_AC

LuaConfig::LuaConfig()
{
	m_pLua = luaL_newstate();
	luaL_openlibs(m_pLua);
}

LuaConfig::~LuaConfig()
{
	lua_close(m_pLua);
}

int LuaConfig::Load(const std::string& strFileName)
{
	int ret = luaL_dofile(m_pLua,strFileName.c_str());
	if(ret != 0)
	{
		std::string strLuaError = lua_tostring(m_pLua,-1);
		CString strErr;
		strErr.Format(_T("Load config failed : %s"),StlStringToCString(strLuaError));
		ErrorMessageBox(strErr.GetBuffer());
		ExitProcess(-1);
	}

	return ret;
}

int LuaConfig::GetInteger(const std::string& strParamName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strParamName);
	if(ret != 0)
	{
		ERROR_MSG("Param format invalid:%s",strParamName.c_str());
		ACCHECK(false);
	}

	ACCHECK(lua_isnumber(m_pLua,-1));
	int result = lua_tointeger(m_pLua,-1);

	lua_settop(m_pLua,oldTop);
	return result;
}

std::string LuaConfig::GetString(const std::string& strParamName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strParamName);
	if(ret != 0)
	{
		ERROR_MSG("Param format invalid:%s",strParamName.c_str());
		ACCHECK(false);
	}

	ACCHECK(lua_isstring(m_pLua,-1));
	std::string result = lua_tostring(m_pLua,-1);

	lua_settop(m_pLua,oldTop);
	return result;
}

bool LuaConfig::GetBoolean(const std::string& strParamName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strParamName);
	if(ret != 0)
	{
		ERROR_MSG("Param format invalid:%s",strParamName.c_str());
		ACCHECK(false);
	}

	ACCHECK(lua_isboolean(m_pLua,-1));
	bool result = (lua_toboolean(m_pLua,-1) ? true : false);

	lua_settop(m_pLua,oldTop);
	return result;
}

int LuaConfig::GetType(const std::string& strParamName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strParamName);
	if(ret != 0)
	{
		ERROR_MSG("Param format invalid:%s",strParamName.c_str());
		ACCHECK(false);
	}

	int result = lua_type(m_pLua,-1);

	lua_settop(m_pLua,oldTop);
	return result;
}

std::vector<std::string> LuaConfig::GetStringVector(const std::string& strParamName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strParamName);
	if(ret != 0)
	{
		ERROR_MSG("Param format invalid:%s",strParamName.c_str());
		ACCHECK(false);
	}

	ACCHECK(lua_istable(m_pLua,-1));
	std::vector<std::string> result;
	
	int tableLen = lua_objlen(m_pLua,-1);
	for(int i = 1; i <= tableLen; ++i)
	{
		lua_pushinteger(m_pLua, i);
		lua_gettable(m_pLua, -2);

		ACCHECK(lua_isstring(m_pLua,-1));
		result.push_back(lua_tostring(m_pLua,-1));

		lua_pop(m_pLua, 1);
	}

	lua_settop(m_pLua,oldTop);
	return result;
}

int LuaConfig::PushParam(const std::string& strParamName)
{
	std::vector<std::string> vtStr;
	SplitStlString(strParamName,vtStr,'/');
	if(vtStr.empty())
		return -1;

	size_t idx = 0;
	if(vtStr[0] == ".")
	{
		idx = 1;
	}
	else if((vtStr.size() >= 2) && vtStr[0].empty() && !vtStr[1].empty())
	{
		lua_getglobal(m_pLua,vtStr[1].c_str());
		idx = 2;
	}
	else
		return -1;

	for(; idx < vtStr.size(); ++idx)
	{
		ACCHECK(lua_istable(m_pLua,-1));
		lua_getfield(m_pLua,-1,vtStr[idx].c_str());
	}

	return 0;
}

void LuaConfig::PushTable(const std::string& strTableName)
{
	int oldTop = lua_gettop(m_pLua);

	int ret = PushParam(strTableName);
	if(ret != 0)
	{
		ERROR_MSG("Table name format invalid:%s",strTableName.c_str());
		ACCHECK(false);
	}

	ACCHECK(lua_istable(m_pLua,-1));
	lua_insert(m_pLua,oldTop + 1);

	lua_settop(m_pLua,oldTop + 1);
}

bool LuaConfig::IsTopTable()
{
	return lua_istable(m_pLua,-1);
}

int LuaConfig::GetTableLen(const std::string& strTableName)
{
	PushTable(strTableName);
	int len = lua_objlen(m_pLua,-1);
	lua_pop(m_pLua,1);
	return len;
}

std::string LuaConfig::GetTopAsString(int statckIdx)
{
	return lua_tostring(m_pLua,statckIdx);
}

void LuaConfig::ExportCFunction(const std::string& strFuncName,lua_CFunction pFunc)
{
	lua_register(m_pLua,strFuncName.c_str(),pFunc);
}

END_NS_AC