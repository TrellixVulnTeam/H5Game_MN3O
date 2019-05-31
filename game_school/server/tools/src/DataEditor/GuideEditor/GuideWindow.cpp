// GuideWindow.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideWindow.h"

#include "ACString.h"
#include "ToolApp.h"
#include "ACLog.h"

// GuideWindow dialog

IMPLEMENT_DYNAMIC(GuideWindow, CDialog)

GuideWindow::GuideWindow(CWnd* pParent /*=NULL*/)
	: CDialog(GuideWindow::IDD, pParent)
{

}

GuideWindow::~GuideWindow()
{
}

void GuideWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GUIDE_openCondition, m_objOpenConditionList);
	DDX_Control(pDX, IDC_GUIDE_activeclose, m_objActiveCloseList);
}


BEGIN_MESSAGE_MAP(GuideWindow, CDialog)
	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, &GuideWindow::OnGetListItem)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_GUIDE_openCondition, &GuideWindow::OnLvnEndlabeleditGuideopencondition)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_GUIDE_activeclose, &GuideWindow::OnLvnEndlabeleditGuideactiveclose)
	ON_BN_CLICKED(IDC_BUTTON1, &GuideWindow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &GuideWindow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &GuideWindow::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GuideWindow::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_GUIDE_prefixid, &GuideWindow::OnEnChangeGuideprefixid)
	ON_EN_CHANGE(IDC_GUIDE_suffixid, &GuideWindow::OnEnChangeGuidesuffixid)
	ON_CBN_SELCHANGE(IDC_GUIDE_triggerType1, &GuideWindow::OnCbnSelchangeGuidetriggertype1)
	ON_CBN_SELCHANGE(IDC_GUIDE_triggerType2, &GuideWindow::OnCbnSelchangeGuidetriggertype2)
	ON_CBN_SELCHANGE(IDC_GUIDE_triggerType3, &GuideWindow::OnCbnSelchangeGuidetriggertype3)
END_MESSAGE_MAP()


// GuideWindow message handlers

BOOL GuideWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	ListView_SetExtendedListViewStyleEx(m_objOpenConditionList.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	ListView_SetExtendedListViewStyleEx(m_objOpenConditionList.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(m_objOpenConditionList.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
	ListView_SetExtendedListViewStyleEx(m_objOpenConditionList.m_hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
	ListView_SetExtendedListViewStyleEx(m_objOpenConditionList.m_hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	m_objOpenConditionList.InsertColumn(0, _T("条件ID"), LVCFMT_LEFT, 50);
	m_objOpenConditionList.InsertColumn(1, _T("条件描述"), LVCFMT_LEFT, 140);

	ListView_SetExtendedListViewStyleEx(m_objActiveCloseList.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	ListView_SetExtendedListViewStyleEx(m_objActiveCloseList.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(m_objActiveCloseList.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
	ListView_SetExtendedListViewStyleEx(m_objActiveCloseList.m_hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
	ListView_SetExtendedListViewStyleEx(m_objActiveCloseList.m_hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	m_objActiveCloseList.InsertColumn(0, _T("指引ID"), LVCFMT_LEFT, 50);
	m_objActiveCloseList.InsertColumn(1, _T("指引描述"), LVCFMT_LEFT, 140);

	CreateCombobox(this,IDC_GUIDE_triggerType1,_T("Guide"),_T("triggerType"));
	CreateCombobox(this,IDC_GUIDE_triggerType2,_T("Guide"),_T("triggerType"));
	CreateCombobox(this,IDC_GUIDE_triggerType3,_T("Guide"),_T("triggerType"));

	return TRUE;
}

void GuideWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("GuideWindow_prefixid",GetDlgItem(IDC_GUIDE_prefixid));
}

void GuideWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_GUIDE_ID,_T("id"));
	DeclareEditStr(false,IDC_GUIDE_name,_T("name"));

	DeclareEditStr(false,IDC_GUIDE_groupname,_T("groupname"));
	
	CString strTriggerTypes = mapValues[_T("triggerType")];
	CString strTriggerKeys = mapValues[_T("triggerKey")];
	
	std::vector<CString> vtTypes;
	SplitCString(strTriggerTypes,vtTypes,ARRAY_DELIMITER);

	std::vector<CString> vtKeys;
	SplitCString(strTriggerKeys,vtKeys,ARRAY_DELIMITER);

	ACCHECK(vtTypes.size() == vtKeys.size());

	CComboBox* pTriggerType1 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType1);
	CComboBox* pTriggerType2 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType2);
	CComboBox* pTriggerType3 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType3);
	CEdit* pTriggerKey1 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey1);
	CEdit* pTriggerKey2 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey2);
	CEdit* pTriggerKey3 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey3);

	pTriggerType1->SetCurSel(-1);
	pTriggerType2->SetCurSel(-1);
	pTriggerType3->SetCurSel(-1);
	pTriggerKey1->SetWindowText(_T(""));
	pTriggerKey2->SetWindowText(_T(""));
	pTriggerKey3->SetWindowText(_T(""));

	if(vtTypes.size() > 0)
	{
		Combobox_Load(pTriggerType1,_T("triggerType"),DATA_INT,vtTypes[0]);
		pTriggerKey1->SetWindowText(vtKeys[0]);
		OnCbnSelchangeGuidetriggertype1();
	}

	if(vtTypes.size() > 1)
	{
		Combobox_Load(pTriggerType2,_T("triggerType"),DATA_INT,vtTypes[1]);
		pTriggerKey2->SetWindowText(vtKeys[1]);
		OnCbnSelchangeGuidetriggertype2();
	}

	if(vtTypes.size() > 2)
	{
		Combobox_Load(pTriggerType3,_T("triggerType"),DATA_INT,vtTypes[2]);
		pTriggerKey3->SetWindowText(vtKeys[2]);
		OnCbnSelchangeGuidetriggertype3();
	}

	DeclareEditInt(false,IDC_GUIDE_prefixid,_T("prefixid"));
	CString strDes = GetDBRecordField(_T("Guide"),mapValues[_T("prefixid")],_T("name"));
	((CEdit*)GetDlgItem(IDC_GUIDE_prefixdes))->SetWindowText(strDes);

	DeclareEditInt(false,IDC_GUIDE_suffixid,_T("suffixid"));
	strDes = GetDBRecordField(_T("Guide"),mapValues[_T("suffixid")],_T("name"));
	((CEdit*)GetDlgItem(IDC_GUIDE_suffixdes))->SetWindowText(strDes);

	DeclareCheckbox(false,IDC_GUIDE_closeTag,_T("closeTag"));

	m_vtOpenConditionList.clear();
	CString strCnds = mapValues[_T("openCondition")];
	std::vector<CString> vtCnds;
	SplitCString(strCnds,vtCnds,ARRAY_DELIMITER);
	for(size_t i = 0; i < vtCnds.size(); ++i)
	{
		CString strID = vtCnds[i];
		if(strID == _T("-1"))
			break;

		CString strDes = GetDBRecordField(_T("GuideCondition"),strID,_T("name"));
		m_vtOpenConditionList.push_back(SItemInfo(strID,strDes));
	}

	UpdateOpenConditionList();

	m_vtActiveCloseList.clear();
	CString strGuides = mapValues[_T("activeclose")];
	std::vector<CString> vtGuides;
	SplitCString(strGuides,vtGuides,ARRAY_DELIMITER);
	for(size_t i = 0; i < vtGuides.size(); ++i)
	{
		CString strID = vtGuides[i];
		if(strID == _T("-1"))
			break;

		CString strDes = GetDBRecordField(_T("Guide"),strID,_T("name"));
		m_vtActiveCloseList.push_back(SItemInfo(strID,strDes));
	}

	UpdateActiveCloseList();
}

void GuideWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_GUIDE_ID,_T("id"));
	DeclareEditStr(true,IDC_GUIDE_name,_T("name"));

	DeclareEditStr(true,IDC_GUIDE_groupname,_T("groupname"));

	std::vector<CString> vtTypes;
	std::vector<CString> vtKeys;

	CComboBox* pTriggerType1 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType1);
	CComboBox* pTriggerType2 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType2);
	CComboBox* pTriggerType3 = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType3);
	CEdit* pTriggerKey1 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey1);
	CEdit* pTriggerKey2 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey2);
	CEdit* pTriggerKey3 = (CEdit*)GetDlgItem(IDC_GUIDE_triggerKey3);

	if(pTriggerType1->GetCurSel() >= 0)
	{
		CString str;
		Combobox_Save(pTriggerType1,_T("triggerType"),DATA_INT,str);
		vtTypes.push_back(str);
		pTriggerKey1->GetWindowText(str);
		vtKeys.push_back(str);
	}

	if(pTriggerType2->GetCurSel() >= 0)
	{
		CString str;
		Combobox_Save(pTriggerType2,_T("triggerType"),DATA_INT,str);
		vtTypes.push_back(str);
		pTriggerKey2->GetWindowText(str);
		vtKeys.push_back(str);
	}

	if(pTriggerType3->GetCurSel() >= 0)
	{
		CString str;
		Combobox_Save(pTriggerType3,_T("triggerType"),DATA_INT,str);
		vtTypes.push_back(str);
		pTriggerKey3->GetWindowText(str);
		vtKeys.push_back(str);
	}

	CString strTriggerTypes;
	JoinCString(strTriggerTypes,vtTypes,ARRAY_DELIMITER);
	mapValues[_T("triggerType")] = strTriggerTypes;

	CString strTriggerKeys;
	JoinCString(strTriggerKeys,vtKeys,ARRAY_DELIMITER);
	mapValues[_T("triggerKey")] = strTriggerKeys;
	
	DeclareEditInt(true,IDC_GUIDE_prefixid,_T("prefixid"));
	DeclareEditInt(true,IDC_GUIDE_suffixid,_T("suffixid"));
	DeclareCheckbox(true,IDC_GUIDE_closeTag,_T("closeTag"));

	std::vector<CString> vtCnds;
	for(size_t i = 0; i < m_vtOpenConditionList.size(); ++i)
	{
		CString strID = m_vtOpenConditionList[i].m_strID;
		if(strID == _T("-1"))
			break;

		vtCnds.push_back(strID);
	}

	CString strCnds;
	JoinCString(strCnds,vtCnds,ARRAY_DELIMITER);
	mapValues[_T("openCondition")] = strCnds;

	std::vector<CString> vtGuides;
	for(size_t i = 0; i < m_vtActiveCloseList.size(); ++i)
	{
		CString strID = m_vtActiveCloseList[i].m_strID;
		if(strID == _T("-1"))
			break;

		vtGuides.push_back(strID);
	}

	CString strGuides;
	JoinCString(strGuides,vtGuides,ARRAY_DELIMITER);
	mapValues[_T("activeclose")] = strGuides;
}

void GuideWindow::OnLvnEndlabeleditGuideopencondition(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pDispInfo->item.pszText != NULL)
	{
		int nItem = pDispInfo->item.iItem;
		int nSubItem = pDispInfo->item.iSubItem;

		switch(nSubItem)
		{
		case 0:
			m_vtOpenConditionList[nItem].m_strID = pDispInfo->item.pszText;
			break;
		}

		if(nSubItem == 0)
		{
			CString strID = m_vtOpenConditionList[nItem].m_strID;

			m_vtOpenConditionList[nItem].m_strDes = GetDBRecordField(_T("GuideCondition"),strID,_T("name"));
			UpdateOpenConditionList();
		}

		//Select next item?
		if(m_objOpenConditionList.GetLastEndEditKey() == VK_RETURN)
		{
			//Select next item if possible
			if(nItem + 1 < m_objOpenConditionList.GetItemCount())
				m_objOpenConditionList.EditSubItem(nItem + 1, 0);

		}
	}
	*pResult = 0;
}

void GuideWindow::OnLvnEndlabeleditGuideactiveclose(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pDispInfo->item.pszText != NULL)
	{
		int nItem = pDispInfo->item.iItem;
		int nSubItem = pDispInfo->item.iSubItem;

		switch(nSubItem)
		{
		case 0:
			m_vtActiveCloseList[nItem].m_strID = pDispInfo->item.pszText;
			break;
		}

		if(nSubItem == 0)
		{
			CString strID = m_vtActiveCloseList[nItem].m_strID;

			m_vtActiveCloseList[nItem].m_strDes = GetDBRecordField(_T("Guide"),strID,_T("name"));
			UpdateActiveCloseList();
		}

		//Select next item?
		if(m_objActiveCloseList.GetLastEndEditKey() == VK_RETURN)
		{
			//Select next item if possible
			if(nItem + 1 < m_objActiveCloseList.GetItemCount())
				m_objActiveCloseList.EditSubItem(nItem + 1, 0);

		}
	}
	*pResult = 0;
}

void GuideWindow::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_vtOpenConditionList.push_back(SItemInfo());
	UpdateOpenConditionList();
}

void GuideWindow::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int nSel = m_objOpenConditionList.GetItemInFocus();
	if(nSel < 0 || nSel >= m_vtOpenConditionList.size())
		return;

	m_vtOpenConditionList.erase(m_vtOpenConditionList.begin() + nSel);

	UpdateOpenConditionList();
}

void GuideWindow::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	m_vtActiveCloseList.push_back(SItemInfo());
	UpdateActiveCloseList();
}

void GuideWindow::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	int nSel = m_objActiveCloseList.GetItemInFocus();
	if(nSel < 0 || nSel >= m_vtActiveCloseList.size())
		return;

	m_vtActiveCloseList.erase(m_vtActiveCloseList.begin() + nSel);

	UpdateActiveCloseList();
}

LRESULT GuideWindow::OnGetListItem(WPARAM wParam, LPARAM lParam)
{
	//wParam is a handler to the list
	//Make sure message comes from list box

	//lParam is a pointer to the data that is needed for the element
	CQuickList::CListItemData* data = (CQuickList::CListItemData*) lParam;

	//Get which item and subitem that is asked for.
	int item = data->GetItem();
	int subItem = data->GetSubItem();

	UpdateData();

	data->m_allowEdit = true;

	SItemInfo mydata;
	if((HWND)wParam == m_objOpenConditionList.GetSafeHwnd())
	{
		mydata = m_vtOpenConditionList[item];
	}
	else if((HWND)wParam == m_objActiveCloseList.GetSafeHwnd())
	{
		mydata = m_vtActiveCloseList[item];
	}

	switch(subItem)
	{
	case 0:
		data->m_text = mydata.m_strID.GetBuffer(0);
		break;
	case 1:
		data->m_text = mydata.m_strDes.GetBuffer(0);
		break;
	}

	return 0;
}

void GuideWindow::UpdateOpenConditionList()
{
	//m_objEffectList.LockWindowUpdate();
	m_objOpenConditionList.SetItemCount( (int) m_vtOpenConditionList.size() );
	//m_objEffectList.UnlockWindowUpdate();
	m_objOpenConditionList.RedrawItems(
		m_objOpenConditionList.GetTopIndex(),
		m_objOpenConditionList.GetTopIndex()+m_objOpenConditionList.GetCountPerPage());
}

void GuideWindow::UpdateActiveCloseList()
{
	//m_objEffectList.LockWindowUpdate();
	m_objActiveCloseList.SetItemCount( (int) m_vtActiveCloseList.size() );
	//m_objEffectList.UnlockWindowUpdate();
	m_objActiveCloseList.RedrawItems(
		m_objActiveCloseList.GetTopIndex(),
		m_objActiveCloseList.GetTopIndex()+m_objActiveCloseList.GetCountPerPage());
}

void GuideWindow::OnEnChangeGuideprefixid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_GUIDE_prefixid)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Guide"),strKey,_T("name"));
	GetDlgItem(IDC_GUIDE_prefixdes)->SetWindowText(strDes);
}

void GuideWindow::OnEnChangeGuidesuffixid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_GUIDE_suffixid)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Guide"),strKey,_T("name"));
	GetDlgItem(IDC_GUIDE_suffixdes)->SetWindowText(strDes);
}

void GuideWindow::OnCbnSelchangeGuidetriggertype1()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType1);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("triggerType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("GuideWindow,triggerType1 select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"triggerType1",1,CStringToStlString(strText));
}

void GuideWindow::OnCbnSelchangeGuidetriggertype2()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType2);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("triggerType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("GuideWindow,triggerType2 select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"triggerType2",1,CStringToStlString(strText));
}

void GuideWindow::OnCbnSelchangeGuidetriggertype3()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_GUIDE_triggerType3);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("triggerType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("GuideWindow,triggerType3 select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"triggerType3",1,CStringToStlString(strText));
}
