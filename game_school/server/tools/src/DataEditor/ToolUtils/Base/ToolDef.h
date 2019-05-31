#ifndef _TOOL_DEF_H_
#define _TOOL_DEF_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <map>
#include <vector>

#include "ACDef.h"

#define IDC_TREE_START	5100

#define ID_MENU_NEW		5000
#define ID_MENU_SAVE	5001
#define ID_MENU_DELETE	5002
#define ID_MENU_COPY	5003
#define ID_MENU_CANCEL	5004

#define ARRAY_DELIMITER _T(",")

BEGIN_NS_AC

#define PRE_TRANSLATE_MESSAGE_SUB BOOL PreTranslateMessage(MSG* pMsg)\
{\
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN || pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)\
	{\
		::TranslateMessage (pMsg);\
		::DispatchMessage (pMsg);\
		return TRUE;\
	}\
	return CDialog::PreTranslateMessage(pMsg);\
}

#define PRE_TRANSLATE_MESSAGE BOOL PreTranslateMessage(MSG* pMsg)\
{\
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)\
	{\
		::TranslateMessage (pMsg);\
		::DispatchMessage (pMsg);\
		return TRUE;\
	}\
	else if(pMsg->message == WM_RBUTTONDOWN)\
	{\
		m_pMenu->TrackPopupMenu(TPM_LEFTALIGN,pMsg->pt.x,pMsg->pt.y,this);\
		return TRUE;\
	}\
	else if(pMsg->message == WM_COMMAND && pMsg->wParam == ID_MENU_NEW)\
	{\
		MenuNew();\
		return TRUE;\
	}\
	else if(pMsg->message == WM_COMMAND && pMsg->wParam == ID_MENU_SAVE)\
	{\
		MenuSave();\
		return TRUE;\
	}\
	else if(pMsg->message == WM_COMMAND && pMsg->wParam == ID_MENU_DELETE)\
	{\
		MenuDelete();\
		return TRUE;\
	}\
	else if(pMsg->message == WM_COMMAND && pMsg->wParam == ID_MENU_COPY)\
	{\
		MenuCopy();\
		return TRUE;\
	}\
	else if(pMsg->message == WM_COMMAND && pMsg->wParam == ID_MENU_CANCEL)\
	{\
		MenuCancel();\
		return TRUE;\
	}\
	else if(pMsg->message == WM_KEYDOWN)\
	{\
		if(pMsg->wParam == 'C' && ((GetAsyncKeyState(VK_CONTROL) & 0x8000)))\
		{\
			MenuCopy();\
			return TRUE;\
		}\
		else if(pMsg->wParam == 'V' && ((GetAsyncKeyState(VK_CONTROL) & 0x8000)))\
		{\
			MenuSave();\
			return TRUE;\
		}\
		else if(pMsg->wParam == 'S' && ((GetAsyncKeyState(VK_CONTROL) & 0x8000)))\
		{\
			MenuSave();\
			return TRUE;\
		}\
		else if(pMsg->wParam == VK_DELETE)\
		{\
			MenuDelete();\
			return TRUE;\
		}\
		else if(pMsg->wParam == VK_RETURN)\
		{\
			OnBnClickedButtonFind();\
			return TRUE;\
		}\
	}\
	return CDialog::PreTranslateMessage(pMsg);\
}

enum EDataType
{
	DATA_INT = 0,
	DATA_FLOAT,
	DATA_STRING,
	DATA_BOOL,
};

EDataType GetDataTypeFromName(CString strTypeName);

enum ECtrlType
{
	CTRL_EDIT = 0,
	CTRL_CHECK,
	CTRL_STATIC,
	CTRL_COMBOBOX,
	CTRL_CHECKCOMBO,
};

enum EDBType
{
	DB_EXCEL = 0,
	DB_LUA,
	DB_PYTHON,
};

typedef std::map<CString,CString> MapCNameToValueT;

struct SLayerInfo
{
	CString strCName;		// Excel中的表头名字
	CString strType;		// 类型(现支持"edit","comboboxint")
	int nCol;				// Excel中所在的列

	SLayerInfo(const CString& name,const CString& type)
		: strCName(name)
		, strType(type)
		, nCol(-1)
	{}
};

struct SExcelConfig
{
	CString m_strExcelPath;		// Excel的完整路径(包括文件名)
	CString m_strExcelCName;	// Excel的名字
	CString m_strKeyCName;		// Excel中代表Key的列的表头名字
	CString m_strDesCName;		// Excel中代表Des的列的表头名字
	std::vector<SLayerInfo> m_vtLayers; // Excel中代表Layer的列的表头名字
	int m_nHeadRow;				// Excel中表头所在的行(索引从0开始)
	int m_nTypeRow;				// Excel中列类型所在的行(索引从0开始)
	int m_nDataRow;				// Excel中数据起始的行(索引从0开始)
	int m_bExpand;
};

//-----------------------------------------------------------

CString GetDBRecordField(const CString& strDBName,const CString& strKey,const CString& strField);

//-----------------------------------------------------------

struct SComboItem
{
	CString m_strName;
	CString m_strValue;
	int m_nValue;
	float m_fValue;
	SComboItem(const CString& strName,const CString& strValue)
	{
		m_strName = strName;
		m_strValue = strValue;
		m_nValue = 0;
		m_fValue = 0.0f;
	}
	SComboItem(const CString& strName,int nValue)
	{
		m_strName = strName;
		m_strValue = _T("");
		m_nValue = nValue;
		m_fValue = 0.0f;
	}
	SComboItem(const CString& strName,float fValue)
	{
		m_strName = strName;
		m_strValue = _T("");
		m_nValue = 0;
		m_fValue = fValue;
	}
};

typedef std::vector<SComboItem> VectorComboItemT;

void CreateCheckCombo(CWnd* pWnd, int nDlgID, const CString& strExcel, const CString& strConf);
void CreateCombobox(CWnd* pWnd, int nDlgID, const CString& strExcel, const CString& strConf);

CString Combobox_ConvertDBToCtrl(const CString& strExcel,const CString& strCName,int nDataType,const CString& strValue);
void Combobox_Load(CComboBox* pWnd,const CString& strConf,int nDataType,const CString& strValue);
void Combobox_Save(CComboBox* pWnd,const CString& strConf,int nDataType,CString& strValue);

void InitDeclare(CWnd* pWnd,MapCNameToValueT& mapValues);

void DeclareID(bool bSaveOrLoad,int nDlgID,const CString& strCName);

void DeclareEditStr(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareEditInt(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareEditFloat(bool bSaveOrLoad,int nDlgID,const CString& strCName);

void DeclareCheckbox(bool bSaveOrLoad,int nDlgID,const CString& strCName);

void DeclareComboboxStr(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareComboboxInt(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareComboboxFloat(bool bSaveOrLoad,int nDlgID,const CString& strCName);

void DeclareCheckComboStrArray(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareCheckComboIntArray(bool bSaveOrLoad,int nDlgID,const CString& strCName);
void DeclareCheckComboFloatArray(bool bSaveOrLoad,int nDlgID,const CString& strCName);

void DeclareCheckComboBit(bool bSaveOrLoad,int nDlgID,const CString& strCName);

//-----------------------------------------------------------

template <class T>
class Module
{
public:
	Module(T* pOwner)
		: m_pOwner(pOwner)
	{}
	virtual ~Module()
	{
		m_pOwner = NULL;
	}
	T* GetOwner()
	{
		return m_pOwner;
	}
protected:
	T* m_pOwner;
};

END_NS_AC

#endif//_TOOL_DEF_H_