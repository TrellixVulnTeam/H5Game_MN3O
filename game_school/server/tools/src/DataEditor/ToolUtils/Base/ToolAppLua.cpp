#include "stdafx.h"
#include "ToolApp.h"
#include "ACString.h"

#include "ACLog.h"

BEGIN_NS_AC

int ToolApp::ilua_RegisterEventHander(lua_State* pLua)
{
	ACCHECK(lua_gettop(pLua) >= 1);
	std::string strEventHandler = luaL_checkstring(pLua,1);
	Instance().SetEventHandler(strEventHandler);
	return 0;
}

int ToolApp::ilua_CWnd_ShowWindow(lua_State* pLua)
{
	ACCHECK(lua_gettop(pLua) >= 2);
	std::string strCtrlName = luaL_checkstring(pLua,1);
	BOOL bShow = lua_toboolean(pLua,2);
	
	CWnd* pWnd = Instance().GetWndByName(strCtrlName);
	if(!pWnd)
	{
		ERROR_MSG("CWnd_ShowWindow,Not find ctrl:%s",strCtrlName.c_str());
		return 0;
	}

	pWnd->ShowWindow(bShow);
	return 0;
}

int ToolApp::ilua_CWnd_SetWindowText(lua_State* pLua)
{
	ACCHECK(lua_gettop(pLua) >= 2);
	std::string strCtrlName = luaL_checkstring(pLua,1);
	std::string strText = luaL_checkstring(pLua,2);

	CWnd* pWnd = Instance().GetWndByName(strCtrlName);
	if(!pWnd)
	{
		ERROR_MSG("CWnd_SetWindowText,Not find ctrl:%s",strCtrlName.c_str());
		return 0;
	}

	pWnd->SetWindowText(StlStringToCString(strText));
	return 0;
}

int ToolApp::ilua_CWnd_EnableWindow(lua_State* pLua)
{
	ACCHECK(lua_gettop(pLua) >= 2);
	std::string strCtrlName = luaL_checkstring(pLua,1);
	bool bEnable = lua_toboolean(pLua,2);

	CWnd* pWnd = Instance().GetWndByName(strCtrlName);
	if(!pWnd)
	{
		ERROR_MSG("CWnd_SetWindowText,Not find ctrl:%s",strCtrlName.c_str());
		return 0;
	}

	pWnd->EnableWindow((BOOL)bEnable);
	return 0;
}

int ToolApp::ilua_GetDBRecordField(lua_State* pLua)
{
	ACCHECK(lua_gettop(pLua) >= 3);
	std::string strDBName = luaL_checkstring(pLua,1);
	std::string strKey = luaL_checkstring(pLua,2);
	std::string strFieldName = luaL_checkstring(pLua,3);

	CString strValue = GetDBRecordField(StlStringToCString(strDBName),StlStringToCString(strKey),StlStringToCString(strFieldName));
	lua_pushstring(pLua,CStringToStlString(strValue).c_str());
	return 1;
}

int ToolApp::ilua_DebugMsg(lua_State* pLua)
{
	if(lua_gettop(pLua) < 1)
	{
		ERROR_MSG("ilua_DebugMsg, require a param");
		return 0;
	}
	
	const char* pMsg = lua_tostring(pLua,1);
	if(pMsg == NULL)
	{
		ERROR_MSG("ilua_DebugMsg, require a string, type:%d", lua_type(pLua,1));
		return 0;
	}

	DEBUG_MSG("%s",pMsg);
	return 0;
}

int ToolApp::ilua_ErrorMsg(lua_State* pLua)
{
	if(lua_gettop(pLua) < 1)
	{
		ERROR_MSG("ilua_ErrorMsg, require a param");
		return 0;
	}

	const char* pMsg = lua_tostring(pLua,1);
	if(pMsg == NULL)
	{
		ERROR_MSG("ilua_ErrorMsg, require a string, type:%d", lua_type(pLua,1));
		return 0;
	}

	ERROR_MSG("%s",pMsg);
	return 0;
}

int ToolApp::ilua_WarnMsg(lua_State* pLua)
{
	if(lua_gettop(pLua) < 1)
	{
		ERROR_MSG("ilua_WarnMsg, require a param");
		return 0;
	}

	const char* pMsg = lua_tostring(pLua,1);
	if(pMsg == NULL)
	{
		ERROR_MSG("ilua_WarnMsg, require a string, type:%d", lua_type(pLua,1));
		return 0;
	}

	WARN_MSG("%s",pMsg);
	return 0;
}

int ToolApp::ilua_InfoMsg(lua_State* pLua)
{
	if(lua_gettop(pLua) < 1)
	{
		ERROR_MSG("ilua_InfoMsg, require a param");
		return 0;
	}

	const char* pMsg = lua_tostring(pLua,1);
	if(pMsg == NULL)
	{
		ERROR_MSG("ilua_InfoMsg, require a string, type:%d", lua_type(pLua,1));
		return 0;
	}

	INFO_MSG("%s",pMsg);
	return 0;
}

void ToolApp::ExportLuaFunctions()
{
	m_objLuaConfig.ExportCFunction("RegisterEventHander",&ToolApp::ilua_RegisterEventHander);
	m_objLuaConfig.ExportCFunction("CWnd_ShowWindow",&ToolApp::ilua_CWnd_ShowWindow);
	m_objLuaConfig.ExportCFunction("CWnd_SetWindowText",&ToolApp::ilua_CWnd_SetWindowText);
	m_objLuaConfig.ExportCFunction("CWnd_EnableWindow",&ToolApp::ilua_CWnd_EnableWindow);
	m_objLuaConfig.ExportCFunction("GetDBRecordField",&ToolApp::ilua_GetDBRecordField);

	m_objLuaConfig.ExportCFunction("DEBUG_MSG",&ToolApp::ilua_DebugMsg);
	m_objLuaConfig.ExportCFunction("ERROR_MSG",&ToolApp::ilua_ErrorMsg);
	m_objLuaConfig.ExportCFunction("WARN_MSG",&ToolApp::ilua_WarnMsg);
	m_objLuaConfig.ExportCFunction("INFO_MSG",&ToolApp::ilua_InfoMsg);
}

void ToolApp::SetEventHandler(const std::string& strEventHandler)
{
	m_strEventHander = strEventHandler;
}

int ToolApp::FireEvent(const std::string& strExcelName,const std::string& strCtrlName,int nMsgType,const std::string& strParam1)
{
	if(m_strEventHander.empty())
	{
		WARN_MSG("FireEvent,Not had register handler");
		return -1;
	}

	lua_State* pLua = m_objLuaConfig.GetLuaState();
	ACCHECK(pLua);

	lua_getglobal(pLua,m_strEventHander.c_str());
	if(!lua_isfunction(pLua,-1))
	{
		ERROR_MSG("FireEvent,Cant find event handler");
		lua_pop(pLua,1);	// pop lua_getglobal
		return -2;
	}

	lua_pushstring(pLua,strExcelName.c_str());
	lua_pushstring(pLua,strCtrlName.c_str());
	lua_pushinteger(pLua,nMsgType);
	lua_pushstring(pLua,strParam1.c_str());
	if(lua_pcall(pLua,4,0,0) != 0)
	{
		ERROR_MSG("FireEvent,lua error:%s",lua_tostring(pLua,-1));
		lua_pop(pLua,1);
		return -3;
	}

	return 0;
}

int ToolApp::FireEvent(const std::string& strExcelName,const std::string& strCtrlName,int nMsgType,const std::string& strParam1,const std::string& strParam2)
{
	if(m_strEventHander.empty())
	{
		WARN_MSG("FireEvent,Not had register handler");
		return -1;
	}

	lua_State* pLua = m_objLuaConfig.GetLuaState();
	ACCHECK(pLua);

	lua_getglobal(pLua,m_strEventHander.c_str());
	if(!lua_isfunction(pLua,-1))
	{
		ERROR_MSG("FireEvent,Cant find event handler");
		lua_pop(pLua,1);	// pop lua_getglobal
		return -2;
	}

	lua_pushstring(pLua,strExcelName.c_str());
	lua_pushstring(pLua,strCtrlName.c_str());
	lua_pushinteger(pLua,nMsgType);
	lua_pushstring(pLua,strParam1.c_str());
	lua_pushstring(pLua,strParam2.c_str());
	if(lua_pcall(pLua,5,0,0) != 0)
	{
		ERROR_MSG("FireEvent,lua error:%s",lua_tostring(pLua,-1));
		lua_pop(pLua,1);
		return -3;
	}

	return 0;
}

CWnd* ToolApp::GetWndByName(const std::string& strCtrlName)
{
	MapNameToWndT::iterator iter = m_mapNameToWnd.find(strCtrlName);
	if(iter != m_mapNameToWnd.end())
		return iter->second;

	return NULL;
}

void ToolApp::RegisterWnd(const std::string& strCtrlName,CWnd* pWnd)
{
	ACCHECK(pWnd);

	if(m_mapNameToWnd.find(strCtrlName) != m_mapNameToWnd.end())
	{
		ERROR_MSG("RegisterWnd,Had register:%s",strCtrlName.c_str());
		return;
	}

	m_mapNameToWnd.insert(std::make_pair(strCtrlName,pWnd));
}

END_NS_AC