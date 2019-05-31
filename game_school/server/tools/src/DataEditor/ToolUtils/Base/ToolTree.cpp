#include "stdafx.h"
#include "ToolTree.h"
#include "ToolExcel.h"

BEGIN_NS_AC

int ToolTree::m_nNextTreeID = IDC_TREE_START;

ToolTree::ToolTree(ExcelDB* db)
: Module<ExcelDB>(db)
, m_nLastSelKey(-1)
, m_pUndefinedRoot(NULL)
{
	ResetLastFoundItem();
}

ToolTree::~ToolTree()
{}

BOOL ToolTree::Create(RECT rcRect, CWnd* pWnd, UINT nID)
{
	DWORD dwStyle, dwOptions;

	// Setup the window style
	dwStyle = WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Setup the tree options 
	// OT_OPTIONS_SHOWINFOWINDOW
	dwOptions = OT_OPTIONS_SHADEEXPANDCOLUMN | OT_OPTIONS_SHADEROOTITEMS;

	// Create tree options
	BOOL ret = COptionTree::Create(dwStyle, rcRect, pWnd, dwOptions, nID);

	// Want to be notified
	SetNotify(TRUE, this);
	return ret;
}

int ToolTree::Create()
{
	CWnd* pParent = ToolApp::Instance().GetMainWnd();
	ACCHECK(pParent);

	CRect rect;
	pParent->GetDlgItem(ToolApp::_IDC_MAIN_TREE)->GetWindowRect(&rect);
	pParent->ScreenToClient(&rect);

	if(!Create(rect, pParent, m_nNextTreeID++))
	{
		ErrorMessageBox(_T("Create main tree failed!"));
		ExitProcess(-1);
	}

	SetColumn(80);

	ShowWindow(SW_HIDE);

	return 0;
}

int ToolTree::UpdateOrInsertItemByKey(int key,CString& strDes,std::vector<CString>& vtLayers)
{
	CString strKey;
	strKey.Format(_T("%d"), key);

	COptionTreeItem* pInsertPosition = FindOrCreateLayers(vtLayers);
	COptionTreeItemStaticEx* pOptItem = (COptionTreeItemStaticEx*)FindItemByInfoText(pInsertPosition,strKey);
	if(pOptItem == NULL)
	{
		pOptItem = (COptionTreeItemStaticEx*)COptionTree::InsertItem(new COptionTreeItemStaticEx(),pInsertPosition);
		pOptItem->CreateStaticItem(0);
	}

	ACCHECK(pOptItem);

	pOptItem->SetLabelText(strKey);
	pOptItem->SetInfoText(strKey);
	pOptItem->SetStaticText(strDes);

	return 0;
}

int ToolTree::DeleteItemByKey(int key)
{
	COptionTreeItem* pFoundItem = FindItemByKey(key);
	if(pFoundItem)
	{
		COptionTree::DeleteItem(pFoundItem);
	}
	return 0;
}

void ToolTree::OnSelect(int key)
{
	if(key < 0 || key == m_nLastSelKey)
		return;

	m_nLastSelKey = key;

	ToolApp::Instance().LoadFromDB(key);
}

void ToolTree::SelectKey(int key)
{
	if(key < 0)
		return;

	COptionTreeItem* pTreeItem = FindItemByKey(key);
	if(!pTreeItem)
		return;

	SelectItems(NULL,FALSE);
	SetFocusedItem(pTreeItem);
	pTreeItem->Select(TRUE);
}

int ToolTree::InsertUndefinedRoot()
{
	m_pUndefinedRoot = COptionTree::InsertItem(new COptionTreeItem());
	ACCHECK(m_pUndefinedRoot);

	m_pUndefinedRoot->SetLabelText(_T("未分类"));
	m_pUndefinedRoot->SetInfoText(_T("未分类"));
	return 0;
}

COptionTreeItem* ToolTree::FindOrCreateLayers(std::vector<CString>& vtLayers)
{
	if(vtLayers.empty())
		return m_pUndefinedRoot;

	COptionTreeItem* pCurrentRoot = &m_otiRoot;
	for(std::vector<CString>::iterator iter = vtLayers.begin(); iter != vtLayers.end(); ++iter)
	{
		COptionTreeItem* pFoundItem = FindItemByInfoText(pCurrentRoot,*iter);
		if(pFoundItem == NULL)
		{
			pFoundItem = COptionTree::InsertItem(new COptionTreeItem(),pCurrentRoot);
			ACCHECK(pFoundItem);

			pFoundItem->SetLabelText(*iter);
			pFoundItem->SetInfoText(*iter);
		}

		pCurrentRoot = pFoundItem;
	}

	return pCurrentRoot;
}

COptionTreeItem* ToolTree::FindItemByKey(int key)
{
	CString strKey;
	strKey.Format(_T("%d"),key);
	return FindItemByInfoText(&m_otiRoot,strKey);
}

COptionTreeItem* ToolTree::FindItemByInfoText(COptionTreeItem* otiRoot, const CString& strInfoText)
{
	// Mark found as NULL
	m_otiFound = NULL;

	// Enumerate items
	EnumItems(otiRoot, EnumFindItemByInfoText, (LPARAM)(&strInfoText));

	return m_otiFound;
}

BOOL CALLBACK ToolTree::EnumFindItemByInfoText(COptionTree* otProp, COptionTreeItem* otiItem, LPARAM lParam)
{
	// Validate items
	if (otiItem == NULL)
	{
		return FALSE;
	}

	CString* pInfoText = (CString*)lParam;
	if (pInfoText == NULL)
	{
		return FALSE;
	}

	if (otiItem->GetInfoText() == *pInfoText)
	{
		m_otiFound = otiItem;

		return FALSE;
	}

	return TRUE;
}

void ToolTree::ResetLastFoundItem()
{
	m_pLastFoundItem = GetRootItem();
}

COptionTreeItem* ToolTree::FindChildAndSibling(COptionTreeItem* pFindStart,const CString& strKeyOrDes)
{
	CString strKey,strDes;
	if(pFindStart == NULL)
		return NULL;

	if(COptionTreeItem* pFirstChild = pFindStart->GetChild())
	{
		// 只搜索叶子结点
		if(COptionTreeItemStaticEx* pStatic = dynamic_cast<COptionTreeItemStaticEx*>(pFirstChild))
		{
			strKey = pStatic->GetInfoText();
			strDes = pStatic->GetStaticText();
			if((strKey.Find(strKeyOrDes) != -1) || (strDes.Find(strKeyOrDes) != -1))
			{
				return pFirstChild;
			}
		}

		COptionTreeItem* pFound = FindChildAndSibling(pFirstChild,strKeyOrDes);
		if(pFound)
		{
			return pFound;
		}
	}

	if(COptionTreeItem* pNextSibling = pFindStart->GetSibling())
	{
		// 只搜索叶子结点
		if(COptionTreeItemStaticEx* pStatic = dynamic_cast<COptionTreeItemStaticEx*>(pNextSibling))
		{
			strKey = pStatic->GetInfoText();
			strDes = pStatic->GetStaticText();
			if((strKey.Find(strKeyOrDes) != -1) || (strDes.Find(strKeyOrDes) != -1))
			{
				return pNextSibling;
			}
		}

		COptionTreeItem* pFound = FindChildAndSibling(pNextSibling,strKeyOrDes);
		if(pFound)
		{
			return pFound;
		}
	}
	
	return NULL;
}

COptionTreeItem* ToolTree::FindNextItem(const CString& strKeyOrDes)
{
	CString strKey,strDes;
	CString strFindValue = strKeyOrDes;
	strFindValue.Trim();
	if(strFindValue.IsEmpty())
		return NULL;

	COptionTreeItem* pFindStart = m_pLastFoundItem ? m_pLastFoundItem : GetRootItem();

	COptionTreeItem* pFound = FindChildAndSibling(pFindStart,strFindValue);
	while(!pFound && (pFindStart->GetParent() != GetRootItem()))
	{
		if(COptionTreeItem* pParent = pFindStart->GetParent())
		{
			if(COptionTreeItem* pParentSibling = pParent->GetSibling())
			{
				// 只搜索叶子结点
				if(COptionTreeItemStaticEx* pStatic = dynamic_cast<COptionTreeItemStaticEx*>(pParentSibling))
				{
					strKey = pStatic->GetInfoText();
					strDes = pStatic->GetStaticText();
					if((strKey.Find(strFindValue) != -1) || (strDes.Find(strFindValue) != -1))
					{
						pFound = pParentSibling;
						break;
					}
				}

				pFound = FindChildAndSibling(pParentSibling,strFindValue);
			}

			pFindStart = pParent;
		}
		else
			break;
	}

	if(pFound)
	{
		Expand(pFound,TRUE);
		SelectItems(NULL, FALSE);
		SelectItems(pFound, 1);
		UpdatedItems();
		SetFocusedItem(pFound);
		RedrawWindow();
		m_pLastFoundItem = pFound;
		return pFound;
	}
	else
	{
		if(m_pLastFoundItem != GetRootItem())
		{
			if(::MessageBox(AfxGetMainWnd()->m_hWnd, _T("已找到末尾，是否再从头开始查找"), _T("警告"), MB_YESNO) == IDYES)
			{
				ResetLastFoundItem();
				return FindNextItem(strFindValue);
			}
		}
	}

	return NULL;
}

END_NS_AC