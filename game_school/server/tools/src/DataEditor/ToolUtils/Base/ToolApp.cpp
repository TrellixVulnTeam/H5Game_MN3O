#include "stdafx.h"
#include "ToolApp.h"
#include "ACString.h"

#include "ToolTree.h"
#include "ToolLog.h"
#include "ToolExcel.h"

BEGIN_NS_AC

ToolApp* ToolApp::m_pInstance = NULL;

int ToolApp::_IDC_EDIT_TOTAL = 0;
int ToolApp::_IDC_MAIN_LOG = 0;
int ToolApp::_IDC_MAIN_TREE = 0;

ToolApp::ToolApp()
: m_bIsNewing(false)
{
	m_pInstance = this;
	m_pLog = new ToolLog(this);
	m_pExcel = new ToolExcel(this);
	m_strCurrentDB = _T("");
}

ToolApp::~ToolApp()
{
	FinalizeTool();
	_safe_delete(m_pLog);
	_safe_delete(m_pExcel);
	m_pInstance = NULL;
}

int ToolApp::InitializeTool(const CString& strAppName)
{
	m_objFont.CreateFont(20, // Height
		0, // Width
		0, // Escapement
		0, // Orientation
		FW_BLACK, // Weight
		FALSE, // Italic
		FALSE, // Underline
		0, // StrikeOut
		ANSI_CHARSET, // CharSet
		OUT_DEFAULT_PRECIS, // OutPrecision
		CLIP_DEFAULT_PRECIS, // ClipPrecision
		DEFAULT_QUALITY, // Quality
		DEFAULT_PITCH | FF_SWISS, // PitchAndFamily
		_T("微软雅黑")); // Facename

	m_pLog->Create(strAppName);

	m_pMenu = new CMenu;
	m_pMenu->CreatePopupMenu();
	m_pMenu->AppendMenu(MF_STRING,ID_MENU_NEW,_T("新建"));
	m_pMenu->AppendMenu(MF_STRING,ID_MENU_SAVE,_T("保存"));
	m_pMenu->AppendMenu(MF_STRING,ID_MENU_DELETE,_T("删除"));
	m_pMenu->AppendMenu(MF_STRING,ID_MENU_COPY,_T("复制"));
	m_pMenu->AppendMenu(MF_STRING,ID_MENU_CANCEL,_T("取消"));
	//SetMenu(GetMainWnd()->GetSafeHwnd(),m_pMenu->GetSafeHmenu());

	m_pMenu->EnableMenuItem(ID_MENU_NEW,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_SAVE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_DELETE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_COPY,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_CANCEL,TRUE);

	INFO_MSG("--------------------------------------------");
	INFO_MSG("               %s Start             ",CStringToStlString(strAppName).c_str());
	INFO_MSG("--------------------------------------------");

	ExportLuaFunctions();

	CString strConfigPath = strAppName;
	strConfigPath.Append(_T(".lua"));
	m_objLuaConfig.Load(CStringToStlString(strConfigPath));

	// 打开ExcelDB
	OpenExcelDBs();

	return 0;
}

int ToolApp::FinalizeTool()
{
	for(std::map<int,CWnd*>::iterator iter = m_mapCheckCombos.begin(); iter != m_mapCheckCombos.end(); ++iter)
	{
		CWnd* pCheckCombo = iter->second;
		_safe_delete(pCheckCombo);
	}
	m_mapCheckCombos.clear();

	m_pMenu->DestroyMenu();
	delete m_pMenu;
	m_objFont.DeleteObject();
	return 0;
}

int ToolApp::Update()
{
	m_pLog->Update();
	return 0;
}

int ToolApp::LoadFromDB(int key)
{
	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	MapCNameToValueT mapValues;
	pExcelDB->ReadDBRecord(key,mapValues);
	OnLoadFromDB(mapValues);
	return 0;
}

int ToolApp::SaveToDB(int key)
{
	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	MapCNameToValueT mapValues;
	OnSaveToDB(mapValues);
	pExcelDB->WriteDBRecord(key,mapValues);
	return 0;
}

void ToolApp::CompletedWithDefault(MapCNameToValueT& mapValues)
{
	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	MapCNameToValueT mapDefault;
	pExcelDB->GetDBDefaultValue(mapDefault);

	for(MapCNameToValueT::iterator iter = mapDefault.begin(); iter != mapDefault.end(); ++iter)
	{
		if(mapValues.find(iter->first) != mapValues.end())
		{
			iter->second = mapValues[iter->first];
		}
	}

	mapValues = mapDefault;
}

int ToolApp::MenuNew()
{
	if(m_bIsNewing)
		return -1;

	m_bIsNewing = true;

	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	pExcelDB->EnableTree(FALSE);

	m_pMenu->EnableMenuItem(ID_MENU_NEW,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_SAVE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_DELETE,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_COPY,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_CANCEL,FALSE);

	// 载入默认值
	MapCNameToValueT mapDefault;
	pExcelDB->GetDBDefaultValue(mapDefault);
	OnLoadFromDB(mapDefault);

	CEdit* pKeyWnd = (CEdit*)GetCurrentKeyWindow();
	ACCHECK(pKeyWnd);

	pKeyWnd->EnableWindow(TRUE);

	// 设置key默认值
	int nNewKey = pExcelDB->GetUnusedKey();
	CString strNewKey;
	strNewKey.Format(_T("%d"),nNewKey);
	pKeyWnd->SetWindowText(strNewKey);
	return 0;
}

int ToolApp::MenuSave()
{
	CEdit* pKeyWnd = (CEdit*)GetCurrentKeyWindow();
	ACCHECK(pKeyWnd);

	CString strKey;
	pKeyWnd->GetWindowText(strKey);
	int nKey = ACAtoi(CStringToStlString(strKey).c_str());

	if(m_bIsNewing)
	{
		if(InsertByKey(nKey) != 0)
		{
			WarningMessageBox(_T("ID无效"));
			pKeyWnd->SetFocus();
			return -1;
		}

		m_bIsNewing = false;
		pKeyWnd->EnableWindow(FALSE);
		
		CString strCurrentDB = GetCurrentDB();
		ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
		ACCHECK(pExcelDB);

		pExcelDB->EnableTree(TRUE);

		m_pMenu->EnableMenuItem(ID_MENU_NEW,FALSE);
		m_pMenu->EnableMenuItem(ID_MENU_SAVE,FALSE);
		m_pMenu->EnableMenuItem(ID_MENU_DELETE,FALSE);
		m_pMenu->EnableMenuItem(ID_MENU_COPY,FALSE);
		m_pMenu->EnableMenuItem(ID_MENU_CANCEL,TRUE);
	}
	else
		SaveToDB(nKey);

	return 0;
}

int ToolApp::MenuDelete()
{
	CEdit* pKeyWnd = (CEdit*)GetCurrentKeyWindow();
	ACCHECK(pKeyWnd);

	CString strKey;
	pKeyWnd->GetWindowText(strKey);
	int nKey = ACAtoi(CStringToStlString(strKey).c_str());

	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	int ret = pExcelDB->DeleteByKey(nKey);
	UpdateTotalCounterWnd();
	return ret;
}

int ToolApp::MenuCopy()
{
	if(m_bIsNewing)
		return -1;

	m_bIsNewing = true;
	
	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	pExcelDB->EnableTree(FALSE);

	m_pMenu->EnableMenuItem(ID_MENU_NEW,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_SAVE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_DELETE,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_COPY,TRUE);
	m_pMenu->EnableMenuItem(ID_MENU_CANCEL,FALSE);

	CEdit* pKeyWnd = (CEdit*)GetCurrentKeyWindow();
	ACCHECK(pKeyWnd);

	pKeyWnd->EnableWindow(TRUE);

	// 设置key默认值
	int nNewKey = pExcelDB->GetUnusedKey();
	CString strNewKey;
	strNewKey.Format(_T("%d"),nNewKey);
	pKeyWnd->SetWindowText(strNewKey);
	return 0;
}

int ToolApp::MenuCancel()
{
	if(!IsNewing())
		return -1;

	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);
	
	LoadFromDB(pExcelDB->GetTreeLastSelected());

	CEdit* pKeyWnd = (CEdit*)GetCurrentKeyWindow();
	ACCHECK(pKeyWnd);

	m_bIsNewing = false;
	pKeyWnd->EnableWindow(FALSE);
	pExcelDB->EnableTree(TRUE);

	m_pMenu->EnableMenuItem(ID_MENU_NEW,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_SAVE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_DELETE,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_COPY,FALSE);
	m_pMenu->EnableMenuItem(ID_MENU_CANCEL,TRUE);
	return 0;
}

int ToolApp::InsertByKey(int key)
{
	CString strCurrentDB = GetCurrentDB();
	ExcelDB* pExcelDB = m_pExcel->GetWorkbook(strCurrentDB);
	ACCHECK(pExcelDB);

	MapCNameToValueT mapDefault;
	pExcelDB->GetDBDefaultValue(mapDefault);

	MapCNameToValueT mapCurrent;
	OnSaveToDB(mapCurrent);

	for(MapCNameToValueT::iterator iter = mapCurrent.begin(); iter != mapCurrent.end(); ++iter)
	{
		CString strCName = iter->first;
		CString strValue = iter->second;

		MapCNameToValueT::iterator iterDefault = mapDefault.find(strCName);
		if(iterDefault != mapDefault.end())
			iterDefault->second = strValue;
	}

	if(pExcelDB->InsertByKey(key,mapDefault) > 0)
	{
		UpdateTotalCounterWnd();
		return 0;
	}
	
	return -1;
}

void ToolApp::InsertCheckCombo(int nDlgID, CWnd* pCheckCombo)
{
	m_mapCheckCombos.insert(std::make_pair(nDlgID,pCheckCombo));
}

CWnd* ToolApp::FindCheckCombo(int nDlgID)
{
	std::map<int,CWnd*>::iterator iter = m_mapCheckCombos.find(nDlgID);
	if(iter != m_mapCheckCombos.end())
		return iter->second;

	return NULL;
}

void ToolApp::GetComboConfig(const CString& strExcel,const CString& strCtrl,VectorComboItemT& vtConfs)
{
	CString strConfPath = _T("/ExcelDBs/") + strExcel + _T("/ComboConfig/") + strCtrl;
	m_objLuaConfig.IterArray(CStringToStlString(strConfPath),this,&ToolApp::pfnGetComboConfig,&vtConfs);
}

void ToolApp::pfnGetComboConfig(void* ctx)
{
	ACCHECK(ctx);
	VectorComboItemT* pVtConfs = (VectorComboItemT*)ctx;
	std::string strstlName = m_objLuaConfig.GetString("./Name");
	CString strName = StlStringToCString(strstlName);
	switch(m_objLuaConfig.GetType("./Value"))
	{
	case LUA_TNUMBER:
		pVtConfs->push_back(SComboItem(strName,m_objLuaConfig.GetInteger("./Value")));
		break;
	case LUA_TSTRING:
		pVtConfs->push_back(SComboItem(strName,StlStringToCString(m_objLuaConfig.GetString("./Value"))));
		break;
	default:
		ERROR_MSG("GetComboConfig, Unknown data type,strName:%s",strstlName.c_str());
	}
}

int ToolApp::SetCurrentDB(const CString& strDBName)
{
	if(strDBName == m_strCurrentDB)
		return 0;

	if(!m_strCurrentDB.IsEmpty())
	{
		ExcelDB* pOldDB = m_pExcel->GetWorkbook(m_strCurrentDB);
		ACCHECK(pOldDB);

		pOldDB->ShowTree(SW_HIDE);
	}

	m_strCurrentDB = strDBName;

	if(!m_strCurrentDB.IsEmpty())
	{
		ExcelDB* pNewDB = m_pExcel->GetWorkbook(m_strCurrentDB);
		ACCHECK(pNewDB);

		pNewDB->ShowTree(SW_SHOW);

		UpdateTotalCounterWnd();
	}

	return 0;
}

CString ToolApp::GetCurrentDB()
{
	return m_strCurrentDB;
}

ToolTree* ToolApp::GetCurrentTree()
{
	ExcelDB* pDB = m_pExcel->GetWorkbook(m_strCurrentDB);
	ACCHECK(pDB);

	return pDB->GetTree();
}

void ToolApp::UpdateTotalCounterWnd()
{
	CEdit* pTotalCounterWnd = (CEdit*)GetMainWnd()->GetDlgItem(ToolApp::_IDC_EDIT_TOTAL);
	ACCHECK(pTotalCounterWnd);

	ExcelDB* pDB = m_pExcel->GetWorkbook(m_strCurrentDB);
	ACCHECK(pDB);

	size_t nCount = pDB->GetTreeItemInfoCount();
	CString strCount;
	strCount.Format(_T("%d"),nCount);
	pTotalCounterWnd->SetWindowText(strCount);
}

void ToolApp::OpenExcelDBs()
{
	m_objLuaConfig.IterTable("/ExcelDBs",this,&ToolApp::pfnOpenExcelDBs,NULL);
}


void ToolApp::pfnOpenExcelDBs(void* ctx)
{
	HMODULE module = GetModuleHandle(0);   
	wchar_t pFileName[MAX_PATH];   
	GetModuleFileName(module, pFileName, MAX_PATH);   

	CString strPath(pFileName);   
	int nPos = strPath.ReverseFind(_T('\\'));   
	if(nPos < 0)
	{
		AfxMessageBox(_T("Can not open excel!"));
		ExitProcess(-1);
	}
	else
	{
		strPath = strPath.Left(nPos) + _T("\\");
	}

	SExcelConfig config;
	config.m_strExcelPath = strPath + StlStringToCString(m_objLuaConfig.GetString("./ExcelPath"));
	config.m_strExcelCName = StlStringToCString(m_objLuaConfig.GetTopAsString(-2));
	config.m_strKeyCName = StlStringToCString(m_objLuaConfig.GetString("./KeyName"));
	config.m_strDesCName = StlStringToCString(m_objLuaConfig.GetString("./DesName"));
	config.m_nHeadRow = m_objLuaConfig.GetInteger("./HeadRow");
	config.m_nTypeRow = m_objLuaConfig.GetInteger("./TypeRow");
	config.m_nDataRow = m_objLuaConfig.GetInteger("./DataRow");
	config.m_bExpand = m_objLuaConfig.GetBoolean("./Expand");

	m_objLuaConfig.IterArray("./Layers",this,&ToolApp::pfnLoadLayers,&config);

	ExcelDB* pExcelDB = m_pExcel->OpenWorkbook(config);
	ACCHECK(pExcelDB);

	m_mapDefaultValues.clear();
	m_objLuaConfig.IterTable("./DefaultValue",this,&ToolApp::pfnLoadDefaultValues,NULL);
	pExcelDB->SetDBDefaultValue(m_mapDefaultValues);
}

void ToolApp::pfnLoadLayers(void* ctx)
{
	CString strName = StlStringToCString(m_objLuaConfig.GetString("./Name"));
	CString strType = StlStringToCString(m_objLuaConfig.GetString("./Type"));

	SExcelConfig* pConfig = (SExcelConfig*)ctx;
	ACCHECK(pConfig);

	pConfig->m_vtLayers.push_back(SLayerInfo(strName,strType));
}

void ToolApp::pfnLoadDefaultValues(void* ctx)
{
	CString strName = StlStringToCString(m_objLuaConfig.GetTopAsString(-2));
	CString strValue = StlStringToCString(m_objLuaConfig.GetTopAsString(-1));
	m_mapDefaultValues.insert(std::make_pair(strName,strValue));
}

END_NS_AC