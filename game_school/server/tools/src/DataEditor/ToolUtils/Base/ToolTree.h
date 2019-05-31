#ifndef _TOOL_TREE_H_
#define _TOOL_TREE_H_

#define _CRT_SECURE_NO_WARNINGS

#include <afx.h>
#include <afxwin.h>
#include <afxcmn.h>
#include <afxdtctl.h>
#include "OptionTree.h"
#include "ToolDef.h"
#include "ToolExcel.h"
#include "ACString.h"

BEGIN_NS_AC

class ToolTree : public COptionTree, public Module<ExcelDB>
{
public:
	ToolTree(ExcelDB* db);
	virtual ~ToolTree();
public:
	BOOL Create(RECT rcRect, CWnd* pWnd, UINT nID);
public:
	int Create();
public:
	void OnSelect(int key);
public:
	void SelectKey(int key);
	int GetLastSelectKey()
	{
		return m_nLastSelKey;
	}
public:
	int InsertUndefinedRoot();
public:
	int UpdateOrInsertItemByKey(int key,CString& strDes,std::vector<CString>& vtLayers);
	int DeleteItemByKey(int key);
public:
	COptionTreeItem* FindItemByKey(int key);
public:
	void ResetLastFoundItem();
	COptionTreeItem* FindChildAndSibling(COptionTreeItem* pFindStart,const CString& strKeyOrDes);
	COptionTreeItem* FindNextItem(const CString& strKeyOrDes);
protected:
	COptionTreeItem* FindOrCreateLayers(std::vector<CString>& vtLayers);
	COptionTreeItem* FindItemByInfoText(COptionTreeItem* otiRoot, const CString& strInfoText);
protected:
	static BOOL CALLBACK EnumFindItemByInfoText(COptionTree* otProp, COptionTreeItem* otiItem, LPARAM lParam);
private:
	int m_nLastSelKey;
	COptionTreeItem* m_pUndefinedRoot;
	COptionTreeItem* m_pLastFoundItem;
private:
	static int m_nNextTreeID;
};

class COptionTreeItemStaticEx : public COptionTreeItemStatic
{
public:
	virtual void OnSelect()
	{
		ToolTree* pTree = (ToolTree*)m_otOption;
		CString key = GetInfoText();
		pTree->OnSelect(ACAtoi(CStringToStlString(key).c_str()));
	}
};

END_NS_AC

#endif//_TOOL_TREE_H_