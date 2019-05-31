// MagicWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "MagicWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ToolExcel.h"

// MagicWindow dialog

IMPLEMENT_DYNAMIC(MagicWindow, CDialog)

MagicWindow::MagicWindow(CWnd* pParent /*=NULL*/)
	: CDialog(MagicWindow::IDD, pParent)
{

}

MagicWindow::~MagicWindow()
{
}

void MagicWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAGIC_EFFECTS, m_objEffectList);
}


BEGIN_MESSAGE_MAP(MagicWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_MAGIC_magicBelong, &MagicWindow::OnCbnSelchangeMagicmagicbelong)
	ON_BN_CLICKED(IDC_BUTTON1, &MagicWindow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MagicWindow::OnBnClickedButton2)
	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, &MagicWindow::OnGetListItem)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MAGIC_EFFECTS, &MagicWindow::OnLvnEndlabeleditMagicEffects)
	ON_CBN_SELCHANGE(IDC_MAGIC_additionEffect, &MagicWindow::OnCbnSelchangeMagicadditioneffect)
	ON_EN_CHANGE(IDC_MAGIC_magicPerformanceID, &MagicWindow::OnEnChangeMagicmagicperformanceid)
	ON_EN_CHANGE(IDC_MAGIC_targetPerformanceID, &MagicWindow::OnEnChangeMagictargetperformanceid)
END_MESSAGE_MAP()


// MagicWindow message handlers

BOOL MagicWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
	ListView_SetExtendedListViewStyleEx(m_objEffectList.m_hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	m_objEffectList.InsertColumn(0, _T("效果类型(-1:不起作用,0:判定,1:移动,2:子弹发射,3:专有)"), LVCFMT_LEFT, 80);
	m_objEffectList.InsertColumn(1, _T("效果ID"), LVCFMT_LEFT, 80);
	m_objEffectList.InsertColumn(2, _T("效果描述"), LVCFMT_LEFT, 80);

	GetDlgItem(IDC_MAGIC_SUB_magicBelong)->ShowWindow(SW_HIDE);
	m_objMagicTypeHuman.Create(IDD_DIALOG_MAGICTYPE_HUMAN,this);
	m_objMagicTypeNpc.Create(IDD_DIALOG_MAGICTYPE_NPC,this);

	CRect rect;
	GetDlgItem(IDC_MAGIC_SUB_magicBelong)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_objMagicTypeHuman.MoveWindow(rect);
	m_objMagicTypeHuman.ShowWindow(SW_SHOW);
	m_objMagicTypeNpc.ShowWindow(SW_HIDE);

	CreateCombobox(this,IDC_MAGIC_magicBelong,_T("MagicType"),_T("magicBelong"));
	CreateCombobox(this,IDC_MAGIC_profession,_T("MagicType"),_T("profession"));
	CreateCheckCombo(this,IDC_MAGIC_effectTarget,_T("MagicType"),_T("effectTarget"));
	CreateCombobox(this,IDC_MAGIC_castTarget,_T("MagicType"),_T("castTarget"));
	CreateCombobox(this,IDC_MAGIC_castTargetCondition,_T("MagicType"),_T("castTargetCondition"));
	CreateCombobox(this,IDC_MAGIC_magicType,_T("MagicType"),_T("magicType"));
	CreateCombobox(this,IDC_MAGIC_magicAttackType,_T("MagicType"),_T("magicAttackType"));
	CreateCombobox(this,IDC_MAGIC_additionEffect,_T("MagicType"),_T("additionEffect"));

	return TRUE;
}

void MagicWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes1",GetDlgItem(IDC_MAGIC_additionEffectDes1));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes2",GetDlgItem(IDC_MAGIC_additionEffectDes2));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes3",GetDlgItem(IDC_MAGIC_additionEffectDes3));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes4",GetDlgItem(IDC_MAGIC_additionEffectDes4));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes5",GetDlgItem(IDC_MAGIC_additionEffectDes5));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes6",GetDlgItem(IDC_MAGIC_additionEffectDes6));

	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam1",GetDlgItem(IDC_MAGIC_additionEffectParam1));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam2",GetDlgItem(IDC_MAGIC_additionEffectParam2));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam3",GetDlgItem(IDC_MAGIC_additionEffectParam3));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam4",GetDlgItem(IDC_MAGIC_additionEffectParam4));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam5",GetDlgItem(IDC_MAGIC_additionEffectParam5));
	ToolApp::Instance().RegisterWnd("MagicType_additionEffectParam6",GetDlgItem(IDC_MAGIC_additionEffectParam6));

	ToolApp::Instance().RegisterWnd("MagicType_additionEffectDes",GetDlgItem(IDC_MAGIC_additionEffectDes));
}

void MagicWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_MAGIC_ID,_T("id"));
	DeclareEditStr(false,IDC_MAGIC_magicName,_T("magicName"));
	DeclareCheckbox(false,IDC_MAGIC_isActive,_T("isActive"));
	DeclareCheckbox(false,IDC_MAGIC_interruptWhenHurt,_T("interruptWhenHurt"));
	DeclareCheckbox(false,IDC_MAGIC_allowInterruptDelay,_T("allowInterruptDelay"));

	DeclareComboboxInt(false,IDC_MAGIC_magicBelong,_T("magicBelong"));
	OnCbnSelchangeMagicmagicbelong();

	DeclareComboboxInt(false,IDC_MAGIC_profession,_T("profession"));

	DeclareEditInt(false,IDC_MAGIC_CDTime,_T("CDTime"));
	DeclareCheckbox(false,IDC_MAGIC_isPublicCD,_T("isPublicCD"));
	DeclareEditInt(false,IDC_MAGIC_CDGroup,_T("CDGroup"));
	DeclareEditInt(false,IDC_MAGIC_CDGroupTime,_T("CDGroupTime"));
	DeclareEditFloat(false,IDC_MAGIC_maxCastDistance,_T("maxCastDistance"));

	DeclareCheckComboBit(false,IDC_MAGIC_effectTarget,_T("effectTarget"));

	DeclareComboboxInt(false,IDC_MAGIC_castTarget,_T("castTarget"));
	DeclareComboboxInt(false,IDC_MAGIC_castTargetCondition,_T("castTargetCondition"));

	DeclareComboboxInt(false,IDC_MAGIC_magicType,_T("magicType"));

	DeclareEditInt(false,IDC_MAGIC_clientCastSwingTime,_T("clientCastSwingTime"));
	DeclareEditInt(false,IDC_MAGIC_castSwingTime,_T("castSwingTime"));
	DeclareEditInt(false,IDC_MAGIC_castStiffTime,_T("castStiffTime"));
	DeclareEditInt(false,IDC_MAGIC_castBackswingTime,_T("castBackswingTime"));
	DeclareEditInt(false,IDC_MAGIC_magicPerformanceID,_T("magicPerformanceID"));

	CString strDes = GetDBRecordField(_T("Performance"),mapValues[_T("magicPerformanceID")],_T("performanceDescription"));
	GetDlgItem(IDC_MAGIC_magicPerformanceDes)->SetWindowText(strDes);

	DeclareEditInt(false,IDC_MAGIC_targetPerformanceID,_T("targetPerformanceID"));

	strDes = GetDBRecordField(_T("Performance"),mapValues[_T("targetPerformanceID")],_T("performanceDescription"));
	GetDlgItem(IDC_MAGIC_targetPerformanceDes)->SetWindowText(strDes);

	DeclareComboboxInt(false,IDC_MAGIC_magicAttackType,_T("magicAttackType"));

	DeclareComboboxStr(false,IDC_MAGIC_additionEffect,_T("additionEffect"));
	OnCbnSelchangeMagicadditioneffect();

	DeclareEditInt(false,IDC_MAGIC_additionEffectParam1,_T("additionEffectParam1"));
	DeclareEditInt(false,IDC_MAGIC_additionEffectParam2,_T("additionEffectParam2"));
	DeclareEditInt(false,IDC_MAGIC_additionEffectParam3,_T("additionEffectParam3"));
	DeclareEditFloat(false,IDC_MAGIC_additionEffectParam4,_T("additionEffectParam4"));
	DeclareEditFloat(false,IDC_MAGIC_additionEffectParam5,_T("additionEffectParam5"));
	DeclareEditFloat(false,IDC_MAGIC_additionEffectParam6,_T("additionEffectParam6"));
	DeclareCheckbox(false,IDC_MAGIC_stopMove,_T("stopMove"));
	DeclareCheckbox(false,IDC_MAGIC_showSwing,_T("showSwing"));

	m_vtEffects.clear();
	CString strEffectType,strEffectID;
	for(int i = 1; i <= 12; ++i)
	{
		CString strCNameType;
		strCNameType.Format(_T("%s%d"),_T("effectType"),i);
		CString strCNameID;
		strCNameID.Format(_T("%s%d"),_T("effectID"),i);

		strEffectType = mapValues[strCNameType];
		strEffectID = mapValues[strCNameID];
		if(strEffectType == _T("-1") && strEffectID == _T("-1"))
			break;

		CString strEffectDes = GetEffectDes(strEffectType,strEffectID);

		m_vtEffects.push_back(SEffectInfo(strEffectType,strEffectID,strEffectDes));
	}

	UpdateList();

	// 必须在函数末尾
	m_objMagicTypeHuman.OnLoadFromDB(mapValues);
	m_objMagicTypeNpc.OnLoadFromDB(mapValues);
}

void MagicWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_MAGIC_ID,_T("id"));
	DeclareEditStr(true,IDC_MAGIC_magicName,_T("magicName"));
	DeclareCheckbox(true,IDC_MAGIC_isActive,_T("isActive"));
	DeclareCheckbox(true,IDC_MAGIC_interruptWhenHurt,_T("interruptWhenHurt"));
	DeclareCheckbox(true,IDC_MAGIC_allowInterruptDelay,_T("allowInterruptDelay"));

	DeclareComboboxInt(true,IDC_MAGIC_magicBelong,_T("magicBelong"));

	DeclareComboboxInt(true,IDC_MAGIC_profession,_T("profession"));

	DeclareEditInt(true,IDC_MAGIC_CDTime,_T("CDTime"));
	DeclareCheckbox(true,IDC_MAGIC_isPublicCD,_T("isPublicCD"));
	DeclareEditInt(true,IDC_MAGIC_CDGroup,_T("CDGroup"));
	DeclareEditInt(true,IDC_MAGIC_CDGroupTime,_T("CDGroupTime"));
	DeclareEditFloat(true,IDC_MAGIC_maxCastDistance,_T("maxCastDistance"));

	DeclareCheckComboBit(true,IDC_MAGIC_effectTarget,_T("effectTarget"));

	DeclareComboboxInt(true,IDC_MAGIC_castTarget,_T("castTarget"));
	DeclareComboboxInt(true,IDC_MAGIC_castTargetCondition,_T("castTargetCondition"));

	DeclareComboboxInt(true,IDC_MAGIC_magicType,_T("magicType"));

	DeclareEditInt(true,IDC_MAGIC_clientCastSwingTime,_T("clientCastSwingTime"));
	DeclareEditInt(true,IDC_MAGIC_castSwingTime,_T("castSwingTime"));
	DeclareEditInt(true,IDC_MAGIC_castStiffTime,_T("castStiffTime"));
	DeclareEditInt(true,IDC_MAGIC_castBackswingTime,_T("castBackswingTime"));
	DeclareEditInt(true,IDC_MAGIC_magicPerformanceID,_T("magicPerformanceID"));
	DeclareEditInt(true,IDC_MAGIC_targetPerformanceID,_T("targetPerformanceID"));

	DeclareComboboxInt(true,IDC_MAGIC_magicAttackType,_T("magicAttackType"));

	DeclareComboboxStr(true,IDC_MAGIC_additionEffect,_T("additionEffect"));

	DeclareEditInt(true,IDC_MAGIC_additionEffectParam1,_T("additionEffectParam1"));
	DeclareEditInt(true,IDC_MAGIC_additionEffectParam2,_T("additionEffectParam2"));
	DeclareEditInt(true,IDC_MAGIC_additionEffectParam3,_T("additionEffectParam3"));
	DeclareEditFloat(true,IDC_MAGIC_additionEffectParam4,_T("additionEffectParam4"));
	DeclareEditFloat(true,IDC_MAGIC_additionEffectParam5,_T("additionEffectParam5"));
	DeclareEditFloat(true,IDC_MAGIC_additionEffectParam6,_T("additionEffectParam6"));
	DeclareCheckbox(true,IDC_MAGIC_stopMove,_T("stopMove"));
	DeclareCheckbox(true,IDC_MAGIC_showSwing,_T("showSwing"));

	CString strEffectType,strEffectID;
	for(int i = 1; i <= 12; ++i)
	{
		CString strCNameType;
		strCNameType.Format(_T("%s%d"),_T("effectType"),i);
		CString strCNameID;
		strCNameID.Format(_T("%s%d"),_T("effectID"),i);

		if(i <= m_vtEffects.size())
		{
			mapValues.insert(std::make_pair(strCNameType,m_vtEffects[i-1].m_strEffectType));
			mapValues.insert(std::make_pair(strCNameID,m_vtEffects[i-1].m_strEffectID));
		}
		else
		{
			mapValues.insert(std::make_pair(strCNameType,_T("-1")));
			mapValues.insert(std::make_pair(strCNameID,_T("-1")));
		}
	}

	// 必须在函数末尾
	m_objMagicTypeHuman.OnSaveToDB(mapValues);
	m_objMagicTypeNpc.OnSaveToDB(mapValues);
}

void MagicWindow::OnCbnSelchangeMagicmagicbelong()
{
	// TODO: Add your control notification handler code here
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_MAGIC_magicBelong);
	ACCHECK(pComboBox);

	CRect rect;
	GetDlgItem(IDC_MAGIC_SUB_magicBelong)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nCurSel = pComboBox->GetCurSel();
	if(nCurSel == 0 || nCurSel == 2)
	{
		m_objMagicTypeHuman.MoveWindow(rect);
		m_objMagicTypeHuman.ShowWindow(SW_SHOW);
		m_objMagicTypeNpc.ShowWindow(SW_HIDE);
	}
	else if(nCurSel == 1)
	{
		m_objMagicTypeNpc.MoveWindow(rect);
		m_objMagicTypeNpc.ShowWindow(SW_SHOW);
		m_objMagicTypeHuman.ShowWindow(SW_HIDE);
	}
}

void MagicWindow::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_vtEffects.push_back(SEffectInfo());
	UpdateList();
}

void MagicWindow::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int nSel = m_objEffectList.GetItemInFocus();
	if(nSel < 0 || nSel >= m_vtEffects.size())
		return;

	m_vtEffects.erase(m_vtEffects.begin() + nSel);

	UpdateList();
}

LRESULT MagicWindow::OnGetListItem(WPARAM wParam, LPARAM lParam)
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
		data->m_text = mydata.m_strEffectType.GetBuffer(0);
		break;
	case 1:
		data->m_text = mydata.m_strEffectID.GetBuffer(0);
		break;
	case 2:
		data->m_text = mydata.m_strEffectDes.GetBuffer(0);
		break;
	}

	return 0;
}

void MagicWindow::UpdateList()
{
	//m_objEffectList.LockWindowUpdate();
	m_objEffectList.SetItemCount( (int) m_vtEffects.size() );
	//m_objEffectList.UnlockWindowUpdate();
	m_objEffectList.RedrawItems(
		m_objEffectList.GetTopIndex(),
		m_objEffectList.GetTopIndex()+m_objEffectList.GetCountPerPage());
}

void MagicWindow::OnLvnEndlabeleditMagicEffects(NMHDR *pNMHDR, LRESULT *pResult)
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
			m_vtEffects[nItem].m_strEffectType = pDispInfo->item.pszText;
			break;
		case 1:
			m_vtEffects[nItem].m_strEffectID = pDispInfo->item.pszText;
			break;
		}

		if(nSubItem == 0 || nSubItem == 1)
		{
			CString strType = m_vtEffects[nItem].m_strEffectType;
			CString strID = m_vtEffects[nItem].m_strEffectID;

			m_vtEffects[nItem].m_strEffectDes = GetEffectDes(strType,strID);
			UpdateList();
		}

		//Select next item?
		if(m_objEffectList.GetLastEndEditKey() == VK_RETURN)
		{
			//If column 0, select in next column
			if(nSubItem == 0)
			{
				m_objEffectList.EditSubItem(nItem, 1);
			}
			else if(nItem + 1 < m_objEffectList.GetItemCount())
			{
				m_objEffectList.EditSubItem(nItem + 1, 0);
			}
		}
	}
	*pResult = 0;
}

void MagicWindow::OnCbnSelchangeMagicadditioneffect()
{
	// TODO: Add your control notification handler code here
	CWnd* pCombobox = GetDlgItem(IDC_MAGIC_additionEffect);
	CString strText;
	pCombobox->GetWindowText(strText);
	ToolApp::Instance().FireEvent("MagicType","additionEffect",1,CStringToStlString(strText));
}

CString MagicWindow::GetEffectDes(const CString& strEffectType,const CString& strEffectID)
{
	int nType = ACAtoi(CStringToStlString(strEffectType).c_str());
	int nKey = ACAtoi(CStringToStlString(strEffectID).c_str());

	CString strDBName,strFieldName = _T("des");
	switch(nType)
	{
	case 0:
		strDBName = _T("EffectCommon");
		break;
	case 1:
		strDBName = _T("EffectMotion");
		break;
	case 2:
		strDBName = _T("EffectCollision");
		break;
	case 3:
		strDBName = _T("EffectFlexible");
		break;
	}

	return GetDBRecordField(strDBName,strEffectID,strFieldName);
}

void MagicWindow::OnEnChangeMagicmagicperformanceid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_MAGIC_magicPerformanceID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Performance"),strKey,_T("performanceDescription"));
	GetDlgItem(IDC_MAGIC_magicPerformanceDes)->SetWindowText(strDes);
}

void MagicWindow::OnEnChangeMagictargetperformanceid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_MAGIC_targetPerformanceID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Performance"),strKey,_T("performanceDescription"));
	GetDlgItem(IDC_MAGIC_targetPerformanceDes)->SetWindowText(strDes);
}
