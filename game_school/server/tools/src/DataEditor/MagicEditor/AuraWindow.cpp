// AuraWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "AuraWindow.h"

#include "ToolApp.h"
#include "ACString.h"

// AuraWindow dialog

IMPLEMENT_DYNAMIC(AuraWindow, CDialog)

AuraWindow::AuraWindow(CWnd* pParent /*=NULL*/)
	: CDialog(AuraWindow::IDD, pParent)
{

}

AuraWindow::~AuraWindow()
{
}

void AuraWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AURA_EFFECTS, m_objEffectList);
}


BEGIN_MESSAGE_MAP(AuraWindow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &AuraWindow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &AuraWindow::OnBnClickedButton2)
	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnGetListItem)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_AURA_EFFECTS, &AuraWindow::OnLvnEndlabeleditAuraEffects)
	ON_EN_CHANGE(IDC_AURA_groupID, &AuraWindow::OnEnChangeAuragroupid)
	ON_EN_CHANGE(IDC_AURA_ClientEffect, &AuraWindow::OnEnChangeAuraClienteffect)
END_MESSAGE_MAP()


// AuraWindow message handlers

BOOL AuraWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	m_objEffectList.InsertColumn(0, _T("效果ID"), LVCFMT_LEFT, 80);
	m_objEffectList.InsertColumn(1, _T("效果描述"), LVCFMT_LEFT, 80);

	CreateCombobox(this,IDC_AURA_friendlyLevel,_T("Aura"),_T("friendlyLevel"));
	CreateCheckCombo(this,IDC_AURA_auraTarget,_T("Aura"),_T("auraTarget"));
	CreateCombobox(this,IDC_AURA_liveStyle,_T("Aura"),_T("liveStyle"));
	CreateCheckCombo(this,IDC_AURA_flags,_T("Aura"),_T("flags"));
	CreateCombobox(this,IDC_AURA_EffectTarget,_T("Aura"),_T("EffectTarget"));
	CreateCombobox(this,IDC_AURA_type,_T("Aura"),_T("type"));

	return TRUE;
}

void AuraWindow::RegisterWnds()
{

}

void AuraWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_AURA_ID,_T("id"));
	DeclareEditStr(false,IDC_AURA_name,_T("name"));

	DeclareEditStr(false,IDC_AURA_desc,_T("desc"));
	DeclareComboboxInt(false,IDC_AURA_friendlyLevel,_T("friendlyLevel"));
	DeclareCheckbox(false,IDC_AURA_managerByMagic,_T("managerByMagic"));

	DeclareCheckbox(false,IDC_AURA_isIconDisplay,_T("isIconDisplay"));
	DeclareEditStr(false,IDC_AURA_iconGroup,_T("iconGroup"));
	DeclareEditStr(false,IDC_AURA_icon,_T("icon"));

	DeclareEditInt(false,IDC_AURA_groupID,_T("groupID"));

	CString strOper = GetDBRecordField(_T("AuraGroup"),mapValues[_T("groupID")],_T("oper"));
	strOper = Combobox_ConvertDBToCtrl(_T("AuraGroup"),_T("oper"),DATA_INT,strOper);
	GetDlgItem(IDC_AURA_groupOper)->SetWindowText(strOper);

	CString strDes = GetDBRecordField(_T("AuraGroup"),mapValues[_T("groupID")],_T("name"));
	GetDlgItem(IDC_AURA_groupDes)->SetWindowText(strDes);

	DeclareEditInt(false,IDC_AURA_groupPriority,_T("groupPriority"));

	DeclareCheckComboBit(false,IDC_AURA_auraTarget,_T("auraTarget"));
	DeclareEditInt(false,IDC_AURA_auraTime,_T("auraTime"));
	DeclareEditFloat(false,IDC_AURA_auraRadius,_T("auraRadius"));
	DeclareEditInt(false,IDC_AURA_auraUpdateTime,_T("auraUpdateTime"));

	DeclareCheckbox(false,IDC_AURA_isendSceneSwitch,_T("isendSceneSwitch"));
	DeclareCheckbox(false,IDC_AURA_isendDeath,_T("isendDeath"));
	DeclareCheckbox(false,IDC_AURA_isendOffline,_T("isendOffline"));
	DeclareCheckbox(false,IDC_AURA_isOfflineTiming,_T("isOfflineTiming"));

	DeclareComboboxInt(false,IDC_AURA_liveStyle,_T("liveStyle"));
	DeclareCheckComboBit(false,IDC_AURA_flags,_T("flags"));
	DeclareEditInt(false,IDC_AURA_defaultLayers,_T("defaultLayers"));
	DeclareEditInt(false,IDC_AURA_maxLayers,_T("maxLayers"));

	DeclareEditInt(false,IDC_AURA_ClientEffect,_T("ClientEffect"));

	strDes = GetDBRecordField(_T("BuffEffect"),mapValues[_T("ClientEffect")],_T("des"));
	GetDlgItem(IDC_AURA_ClientEffectDes)->SetWindowText(strDes);

	DeclareEditStr(false,IDC_AURA_validStages,_T("validStages"));
	DeclareComboboxInt(false,IDC_AURA_EffectTarget,_T("EffectTarget"));
	DeclareComboboxInt(false,IDC_AURA_type,_T("type"));

	m_vtEffects.clear();
	CString strEffectID;
	for(int i = 1; i <= 6; ++i)
	{
		CString strCNameID;
		strCNameID.Format(_T("%s%d"),_T("effectID"),i);

		strEffectID = mapValues[strCNameID];
		if(strEffectID == _T("-1"))
			break;

		CString strEffectDes = GetDBRecordField(_T("AuraEffect"),strEffectID,_T("desc"));

		m_vtEffects.push_back(SEffectInfo(strEffectID,strEffectDes));
	}

	UpdateList();
}

void AuraWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_AURA_ID,_T("id"));
	DeclareEditStr(true,IDC_AURA_name,_T("name"));

	DeclareEditStr(true,IDC_AURA_desc,_T("desc"));
	DeclareComboboxInt(true,IDC_AURA_friendlyLevel,_T("friendlyLevel"));
	DeclareCheckbox(true,IDC_AURA_managerByMagic,_T("managerByMagic"));

	DeclareCheckbox(true,IDC_AURA_isIconDisplay,_T("isIconDisplay"));
	DeclareEditStr(true,IDC_AURA_iconGroup,_T("iconGroup"));
	DeclareEditStr(true,IDC_AURA_icon,_T("icon"));

	DeclareEditInt(true,IDC_AURA_groupID,_T("groupID"));
	DeclareEditInt(true,IDC_AURA_groupPriority,_T("groupPriority"));

	DeclareCheckComboBit(true,IDC_AURA_auraTarget,_T("auraTarget"));
	DeclareEditInt(true,IDC_AURA_auraTime,_T("auraTime"));
	DeclareEditFloat(true,IDC_AURA_auraRadius,_T("auraRadius"));
	DeclareEditInt(true,IDC_AURA_auraUpdateTime,_T("auraUpdateTime"));

	DeclareCheckbox(true,IDC_AURA_isendSceneSwitch,_T("isendSceneSwitch"));
	DeclareCheckbox(true,IDC_AURA_isendDeath,_T("isendDeath"));
	DeclareCheckbox(true,IDC_AURA_isendOffline,_T("isendOffline"));
	DeclareCheckbox(true,IDC_AURA_isOfflineTiming,_T("isOfflineTiming"));

	DeclareComboboxInt(true,IDC_AURA_liveStyle,_T("liveStyle"));
	DeclareCheckComboBit(true,IDC_AURA_flags,_T("flags"));
	DeclareEditInt(true,IDC_AURA_defaultLayers,_T("defaultLayers"));
	DeclareEditInt(true,IDC_AURA_maxLayers,_T("maxLayers"));

	DeclareEditInt(true,IDC_AURA_ClientEffect,_T("ClientEffect"));
	DeclareEditStr(true,IDC_AURA_validStages,_T("validStages"));
	DeclareComboboxInt(true,IDC_AURA_EffectTarget,_T("EffectTarget"));
	DeclareComboboxInt(true,IDC_AURA_type,_T("type"));

	CString strEffectID;
	for(int i = 1; i <= 6; ++i)
	{
		CString strCNameID;
		strCNameID.Format(_T("%s%d"),_T("effectID"),i);

		if(i <= m_vtEffects.size())
			mapValues.insert(std::make_pair(strCNameID,m_vtEffects[i-1].m_strEffectID));
		else
			mapValues.insert(std::make_pair(strCNameID,_T("-1")));
	}
}

void AuraWindow::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_vtEffects.push_back(SEffectInfo());
	UpdateList();
}

void AuraWindow::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int nSel = m_objEffectList.GetItemInFocus();
	if(nSel < 0 || nSel >= m_vtEffects.size())
		return;

	m_vtEffects.erase(m_vtEffects.begin() + nSel);

	UpdateList();
}

LRESULT AuraWindow::OnGetListItem(WPARAM wParam, LPARAM lParam)
{
	//wParam is a handler to the list
	//Make sure message comes from list box
	ASSERT( (HWND)wParam == m_objEffectList.GetSafeHwnd() );

	//lParam is a pointer to the data that is needed for the element
	CQuickList::CListItemData* data = (CQuickList::CListItemData*) lParam;

	//Get which item and subitem that is asked for.
	int item = data->GetItem();
	int subItem = data->GetSubItem();

	UpdateData();

	data->m_allowEdit = true;

	SEffectInfo& mydata = m_vtEffects[item];

	switch(subItem)
	{
	case 0:
		data->m_text = mydata.m_strEffectID.GetBuffer(0);
		break;
	case 1:
		data->m_text = mydata.m_strEffectDes.GetBuffer(0);
		break;
	}

	return 0;
}

void AuraWindow::UpdateList()
{
	//m_objEffectList.LockWindowUpdate();
	m_objEffectList.SetItemCount( (int) m_vtEffects.size() );
	//m_objEffectList.UnlockWindowUpdate();
	m_objEffectList.RedrawItems(
		m_objEffectList.GetTopIndex(),
		m_objEffectList.GetTopIndex()+m_objEffectList.GetCountPerPage());
}

void AuraWindow::OnLvnEndlabeleditAuraEffects(NMHDR *pNMHDR, LRESULT *pResult)
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
			m_vtEffects[nItem].m_strEffectID = pDispInfo->item.pszText;
			break;
		}

		if(nSubItem == 0)
		{
			CString strID = m_vtEffects[nItem].m_strEffectID;

			m_vtEffects[nItem].m_strEffectDes = GetDBRecordField(_T("AuraEffect"),strID,_T("desc"));
			UpdateList();
		}

		//Select next item?
		if(m_objEffectList.GetLastEndEditKey() == VK_RETURN)
		{
			//Select next item if possible
			if(nItem + 1 < m_objEffectList.GetItemCount())
				m_objEffectList.EditSubItem(nItem + 1, 0);

		}
	}
	*pResult = 0;
}

void AuraWindow::OnEnChangeAuragroupid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_AURA_groupID)->GetWindowText(strKey);

	CString strOper = GetDBRecordField(_T("AuraGroup"),strKey,_T("oper"));
	strOper = Combobox_ConvertDBToCtrl(_T("AuraGroup"),_T("oper"),DATA_INT,strOper);
	GetDlgItem(IDC_AURA_groupOper)->SetWindowText(strOper);

	CString strDes = GetDBRecordField(_T("AuraGroup"),strKey,_T("name"));
	GetDlgItem(IDC_AURA_groupDes)->SetWindowText(strDes);
}

void AuraWindow::OnEnChangeAuraClienteffect()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_AURA_ClientEffect)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("BuffEffect"),strKey,_T("des"));
	GetDlgItem(IDC_AURA_ClientEffectDes)->SetWindowText(strDes);
}
