// GuideConditionWindow.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionWindow.h"

#include "ToolApp.h"
#include "ACString.h"

// GuideConditionWindow dialog

IMPLEMENT_DYNAMIC(GuideConditionWindow, CDialog)

GuideConditionWindow::GuideConditionWindow(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionWindow::IDD, pParent)
{

}

GuideConditionWindow::~GuideConditionWindow()
{
}

void GuideConditionWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_GUIDECONDITION_action, &GuideConditionWindow::OnCbnSelchangeGuideconditionaction)
END_MESSAGE_MAP()


// GuideConditionWindow message handlers

BOOL GuideConditionWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_GUIDECONDITION_sub)->ShowWindow(SW_HIDE);
	m_objSubAttribute.Create(IDD_DIALOG_SUBATTRIBUTE,this);
	m_objSubControl.Create(IDD_DIALOG_SUBCONTROL,this);
	m_objSubEnchant.Create(IDD_DIALOG_SUBENCHANT,this);
	m_objSubStage.Create(IDD_DIALOG_SUBSTAGE,this);
	m_objSubTask.Create(IDD_DIALOG_SUBTASK,this);
	m_objSubTaskCount.Create(IDD_DIALOG_SUBTASKCOUNT,this);
	m_objSubBlood.Create(IDD_DIALOG_SUBBLOOD,this);

	CRect rect;
	GetDlgItem(IDC_GUIDECONDITION_sub)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_objSubAttribute.MoveWindow(rect);
	m_objSubAttribute.ShowWindow(SW_HIDE);
	m_objSubControl.ShowWindow(SW_HIDE);
	m_objSubEnchant.ShowWindow(SW_HIDE);
	m_objSubStage.ShowWindow(SW_HIDE);
	m_objSubTask.ShowWindow(SW_HIDE);
	m_objSubTaskCount.ShowWindow(SW_HIDE);
	m_objSubBlood.ShowWindow(SW_HIDE);

	CreateCombobox(this,IDC_GUIDECONDITION_action,_T("GuideCondition"),_T("action"));

	return TRUE;
}

void GuideConditionWindow::RegisterWnds()
{

}

void GuideConditionWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_GUIDECONDITION_ID,_T("id"));
	DeclareEditStr(false,IDC_GUIDECONDITION_name,_T("name"));

	DeclareComboboxInt(false,IDC_GUIDECONDITION_action,_T("action"));
	OnCbnSelchangeGuideconditionaction();

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_action);
	ACCHECK(pComboBox);

	CString strValue;
	Combobox_Save(pComboBox,_T("action"),DATA_INT,strValue);
	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_OPEN_CONDITION_ATTRIBUTE_CHECK:
		m_objSubAttribute.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_TASK_CAN_ACCEPT:
	case GUIDE_OPEN_CONDITION_TASK_ACCEPTED:
	case GUIDE_OPEN_CONDITION_TASK_CANFINISH:
	case GUIDE_OPEN_CONDITION_TASK_FINISHED:
		m_objSubTask.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_TASK_COUNT_CHECK:
		m_objSubTaskCount.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_CREATURE_CONTROLLED:
		m_objSubControl.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_STAGE_CHECK:
		m_objSubStage.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_ENCHANT_MAX_LEVEL:
	case GUIDE_OPEN_CONDITION_ENCHANT_TOTAL_LEVEL:
		m_objSubEnchant.OnLoadFromDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_BLOOD_ACTIVE_COUNT:
		m_objSubBlood.OnLoadFromDB(mapValues);
		break;
	}
}

void GuideConditionWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_GUIDECONDITION_ID,_T("id"));
	DeclareEditStr(true,IDC_GUIDECONDITION_name,_T("name"));

	DeclareComboboxInt(true,IDC_GUIDECONDITION_action,_T("action"));

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_action);
	ACCHECK(pComboBox);

	CString strValue;
	Combobox_Save(pComboBox,_T("action"),DATA_INT,strValue);
	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_OPEN_CONDITION_ATTRIBUTE_CHECK:
		m_objSubAttribute.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_TASK_CAN_ACCEPT:
	case GUIDE_OPEN_CONDITION_TASK_ACCEPTED:
	case GUIDE_OPEN_CONDITION_TASK_CANFINISH:
	case GUIDE_OPEN_CONDITION_TASK_FINISHED:
		m_objSubTask.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_TASK_COUNT_CHECK:
		m_objSubTaskCount.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_CREATURE_CONTROLLED:
		m_objSubControl.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_STAGE_CHECK:
		m_objSubStage.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_ENCHANT_MAX_LEVEL:
	case GUIDE_OPEN_CONDITION_ENCHANT_TOTAL_LEVEL:
		m_objSubEnchant.OnSaveToDB(mapValues);
		break;
	case GUIDE_OPEN_CONDITION_BLOOD_ACTIVE_COUNT:
		m_objSubBlood.OnSaveToDB(mapValues);
		break;
	}

	ToolApp::Instance().CompletedWithDefault(mapValues);
}

void GuideConditionWindow::OnCbnSelchangeGuideconditionaction()
{
	// TODO: Add your control notification handler code here
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_action);
	ACCHECK(pComboBox);

	CRect rect;
	GetDlgItem(IDC_GUIDECONDITION_sub)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_objSubAttribute.ShowWindow(SW_HIDE);
	m_objSubControl.ShowWindow(SW_HIDE);
	m_objSubEnchant.ShowWindow(SW_HIDE);
	m_objSubStage.ShowWindow(SW_HIDE);
	m_objSubTask.ShowWindow(SW_HIDE);
	m_objSubTaskCount.ShowWindow(SW_HIDE);
	m_objSubBlood.ShowWindow(SW_HIDE);

	CString strValue;
	Combobox_Save(pComboBox,_T("action"),DATA_INT,strValue);
	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_OPEN_CONDITION_ATTRIBUTE_CHECK:
		m_objSubAttribute.MoveWindow(rect);
		m_objSubAttribute.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_TASK_CAN_ACCEPT:
	case GUIDE_OPEN_CONDITION_TASK_ACCEPTED:
	case GUIDE_OPEN_CONDITION_TASK_CANFINISH:
	case GUIDE_OPEN_CONDITION_TASK_FINISHED:
		m_objSubTask.MoveWindow(rect);
		m_objSubTask.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_TASK_COUNT_CHECK:
		m_objSubTaskCount.MoveWindow(rect);
		m_objSubTaskCount.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_CREATURE_CONTROLLED:
		m_objSubControl.MoveWindow(rect);
		m_objSubControl.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_STAGE_CHECK:
		m_objSubStage.MoveWindow(rect);
		m_objSubStage.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_ENCHANT_MAX_LEVEL:
	case GUIDE_OPEN_CONDITION_ENCHANT_TOTAL_LEVEL:
		m_objSubEnchant.MoveWindow(rect);
		m_objSubEnchant.ShowWindow(SW_SHOW);
		break;
	case GUIDE_OPEN_CONDITION_BLOOD_ACTIVE_COUNT:
		m_objSubBlood.MoveWindow(rect);
		m_objSubBlood.ShowWindow(SW_SHOW);
		break;
	}
}
