#ifndef _TOOL_APP_H_
#define _TOOL_APP_H_

#include "ToolDef.h"
#include "ACLuaUtils.h"

BEGIN_NS_AC

class ToolLog;
class ToolExcel;
class ToolTree;

class ToolApp
{
public:
	ToolApp();
	virtual ~ToolApp();
public:
	virtual int InitializeTool(const CString& strAppName);
	virtual int Update();
	virtual int FinalizeTool();
public:
	int LoadFromDB(int key);
	int SaveToDB(int key);
public:
	virtual void OnLoadFromDB(MapCNameToValueT& mapValues){}
	virtual void OnSaveToDB(MapCNameToValueT& mapValues){}
public:
	void CompletedWithDefault(MapCNameToValueT& mapValues);
public:
	int MenuNew();
	int MenuSave();
	int MenuDelete();
	int MenuCopy();
	int MenuCancel();
public:
	int InsertByKey(int key);
public:
	int SetCurrentDB(const CString& strDBName);
	CString GetCurrentDB();
public:
	ToolTree* GetCurrentTree();
public:
	virtual CWnd* GetMainWnd()
	{
		return NULL;
	}
	virtual CWnd* GetCurrentKeyWindow()
	{
		return NULL;
	}
public:
	static ToolApp& Instance()
	{
		return *m_pInstance;
	}
public:
	ToolLog* GetMainLog()
	{
		return m_pLog;
	}
	ToolExcel* GetExcelTool()
	{
		return m_pExcel;
	}
public:
	bool IsNewing()
	{
		return m_bIsNewing;
	}
private:
	bool m_bIsNewing;
private:
	static ToolApp* m_pInstance;
protected:
	ToolLog* m_pLog;
	ToolExcel* m_pExcel;
	LuaConfig m_objLuaConfig;
public:
	CFont m_objFont;
	CMenu* m_pMenu;
public:
	void InsertCheckCombo(int nDlgID, CWnd* pCheckCombo);
	CWnd* FindCheckCombo(int nDlgID);
	void GetComboConfig(const CString& strExcel,const CString& strCtrl,VectorComboItemT& vtConfs);
protected:
	void pfnGetComboConfig(void* ctx);
protected:
	std::map<int,CWnd*> m_mapCheckCombos;
	CString m_strCurrentDB;
public:
	static int ilua_RegisterEventHander(lua_State* pLua);
	static int ilua_CWnd_ShowWindow(lua_State* pLua);
	static int ilua_CWnd_SetWindowText(lua_State* pLua);
	static int ilua_CWnd_EnableWindow(lua_State* pLua);
	static int ilua_GetDBRecordField(lua_State* pLua);
	static int ilua_DebugMsg(lua_State* pLua);
	static int ilua_ErrorMsg(lua_State* pLua);
	static int ilua_WarnMsg(lua_State* pLua);
	static int ilua_InfoMsg(lua_State* pLua);
public:
	void ExportLuaFunctions();
	void SetEventHandler(const std::string& strEventHandler);
	int FireEvent(const std::string& strExcelName,const std::string& strCtrlName,int nMsgType,const std::string& strParam1);
	int FireEvent(const std::string& strExcelName,const std::string& strCtrlName,int nMsgType,const std::string& strParam1,const std::string& strParam2);
	CWnd* GetWndByName(const std::string& strCtrlName);
	void RegisterWnd(const std::string& strCtrlName,CWnd* pWnd);
	void UpdateTotalCounterWnd();
protected:
	void OpenExcelDBs();
protected:
	void pfnOpenExcelDBs(void* ctx);
	void pfnLoadLayers(void* ctx);
	void pfnLoadDefaultValues(void* ctx);
protected:
	typedef std::map<std::string,CWnd*> MapNameToWndT;
protected:
	MapNameToWndT m_mapNameToWnd;
	std::string m_strEventHander;
	MapCNameToValueT m_mapDefaultValues;
public:
	static int _IDC_EDIT_TOTAL;
	static int _IDC_MAIN_LOG;
	static int _IDC_MAIN_TREE;
};

END_NS_AC

#endif//_TOOL_APP_H_