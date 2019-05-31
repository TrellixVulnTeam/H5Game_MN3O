// AuraEffectWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "AuraEffectWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ACLog.h"

// AuraEffectWindow dialog

IMPLEMENT_DYNAMIC(AuraEffectWindow, CDialog)

AuraEffectWindow::AuraEffectWindow(CWnd* pParent /*=NULL*/)
	: CDialog(AuraEffectWindow::IDD, pParent)
{

}

AuraEffectWindow::~AuraEffectWindow()
{
}

void AuraEffectWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AuraEffectWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_AURAEFFECT_type, &AuraEffectWindow::OnCbnSelchangeAuraeffecttype)
	ON_EN_CHANGE(IDC_AURAEFFECT_para1, &AuraEffectWindow::OnEnChangeAuraeffectpara1)
	ON_EN_CHANGE(IDC_AURAEFFECT_para2, &AuraEffectWindow::OnEnChangeAuraeffectpara2)
END_MESSAGE_MAP()


// AuraEffectWindow message handlers

BOOL AuraEffectWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	CreateCombobox(this,IDC_AURAEFFECT_type,_T("AuraEffect"),_T("type"));

	return TRUE;
}

void AuraEffectWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes1",GetDlgItem(IDC_AURAEFFECT_paraDes1));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes2",GetDlgItem(IDC_AURAEFFECT_paraDes2));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes3",GetDlgItem(IDC_AURAEFFECT_paraDes3));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes4",GetDlgItem(IDC_AURAEFFECT_paraDes4));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes5",GetDlgItem(IDC_AURAEFFECT_paraDes5));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes6",GetDlgItem(IDC_AURAEFFECT_paraDes6));
	ToolApp::Instance().RegisterWnd("AuraEffect_para1",GetDlgItem(IDC_AURAEFFECT_para1));
	ToolApp::Instance().RegisterWnd("AuraEffect_para2",GetDlgItem(IDC_AURAEFFECT_para2));
	ToolApp::Instance().RegisterWnd("AuraEffect_para3",GetDlgItem(IDC_AURAEFFECT_para3));
	ToolApp::Instance().RegisterWnd("AuraEffect_para4",GetDlgItem(IDC_AURAEFFECT_para4));
	ToolApp::Instance().RegisterWnd("AuraEffect_para5",GetDlgItem(IDC_AURAEFFECT_para5));
	ToolApp::Instance().RegisterWnd("AuraEffect_para6",GetDlgItem(IDC_AURAEFFECT_para6));

	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes1_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes1_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes2_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes2_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes3_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes3_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes4_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes4_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes5_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes5_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_paraDes6_lvmod",GetDlgItem(IDC_AURAEFFECT_paraDes6_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para1_lvmod",GetDlgItem(IDC_AURAEFFECT_para1_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para2_lvmod",GetDlgItem(IDC_AURAEFFECT_para2_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para3_lvmod",GetDlgItem(IDC_AURAEFFECT_para3_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para4_lvmod",GetDlgItem(IDC_AURAEFFECT_para4_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para5_lvmod",GetDlgItem(IDC_AURAEFFECT_para5_lvmod));
	ToolApp::Instance().RegisterWnd("AuraEffect_para6_lvmod",GetDlgItem(IDC_AURAEFFECT_para6_lvmod));

	ToolApp::Instance().RegisterWnd("AuraEffect_typeDes",GetDlgItem(IDC_AURAEFFECT_typeDes));

	ToolApp::Instance().RegisterWnd("AuraEffect_cycleTimeDes",GetDlgItem(IDC_AURAEFFECT_cycleTimeDes));
	ToolApp::Instance().RegisterWnd("AuraEffect_cycleTime",GetDlgItem(IDC_AURAEFFECT_cycleTime));

	ToolApp::Instance().RegisterWnd("AuraEffect_para1Tips",GetDlgItem(IDC_AURAEFFECT_para1Tips));
}

void AuraEffectWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_AURAEFFECT_ID,_T("id"));
	DeclareEditStr(false,IDC_AURAEFFECT_desc,_T("desc"));

	DeclareEditInt(false,IDC_AURAEFFECT_cycleTime,_T("cycleTime"));
	DeclareEditStr(false,IDC_AURAEFFECT_triggerCondition,_T("triggerCondition"));
	DeclareEditInt(false,IDC_AURAEFFECT_internalCD,_T("internalCD"));
	DeclareEditInt(false,IDC_AURAEFFECT_trigger_id,_T("trigger_id"));

	DeclareComboboxStr(false,IDC_AURAEFFECT_type,_T("type"));
	OnCbnSelchangeAuraeffecttype();
	DeclareEditInt(false,IDC_AURAEFFECT_para1,_T("para1"));
	OnEnChangeAuraeffectpara1();
	DeclareEditInt(false,IDC_AURAEFFECT_para2,_T("para2"));
	OnEnChangeAuraeffectpara2();
	DeclareEditInt(false,IDC_AURAEFFECT_para3,_T("para3"));
	DeclareEditFloat(false,IDC_AURAEFFECT_para4,_T("para4"));
	DeclareEditFloat(false,IDC_AURAEFFECT_para5,_T("para5"));
	DeclareEditFloat(false,IDC_AURAEFFECT_para6,_T("para6"));
	DeclareEditStr(false,IDC_AURAEFFECT_para1_lvmod,_T("para1_lvmod"));
	DeclareEditStr(false,IDC_AURAEFFECT_para2_lvmod,_T("para2_lvmod"));
	DeclareEditStr(false,IDC_AURAEFFECT_para3_lvmod,_T("para3_lvmod"));
	DeclareEditStr(false,IDC_AURAEFFECT_para4_lvmod,_T("para4_lvmod"));
	DeclareEditStr(false,IDC_AURAEFFECT_para5_lvmod,_T("para5_lvmod"));
	DeclareEditStr(false,IDC_AURAEFFECT_para6_lvmod,_T("para6_lvmod"));
}

void AuraEffectWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_AURAEFFECT_ID,_T("id"));
	DeclareEditStr(true,IDC_AURAEFFECT_desc,_T("desc"));

	DeclareEditInt(true,IDC_AURAEFFECT_cycleTime,_T("cycleTime"));
	DeclareEditStr(true,IDC_AURAEFFECT_triggerCondition,_T("triggerCondition"));
	DeclareEditInt(true,IDC_AURAEFFECT_internalCD,_T("internalCD"));
	DeclareEditInt(true,IDC_AURAEFFECT_trigger_id,_T("trigger_id"));

	DeclareComboboxStr(true,IDC_AURAEFFECT_type,_T("type"));
	DeclareEditInt(true,IDC_AURAEFFECT_para1,_T("para1"));
	DeclareEditInt(true,IDC_AURAEFFECT_para2,_T("para2"));
	DeclareEditInt(true,IDC_AURAEFFECT_para3,_T("para3"));
	DeclareEditFloat(true,IDC_AURAEFFECT_para4,_T("para4"));
	DeclareEditFloat(true,IDC_AURAEFFECT_para5,_T("para5"));
	DeclareEditFloat(true,IDC_AURAEFFECT_para6,_T("para6"));
	DeclareEditStr(true,IDC_AURAEFFECT_para1_lvmod,_T("para1_lvmod"));
	DeclareEditStr(true,IDC_AURAEFFECT_para2_lvmod,_T("para2_lvmod"));
	DeclareEditStr(true,IDC_AURAEFFECT_para3_lvmod,_T("para3_lvmod"));
	DeclareEditStr(true,IDC_AURAEFFECT_para4_lvmod,_T("para4_lvmod"));
	DeclareEditStr(true,IDC_AURAEFFECT_para5_lvmod,_T("para5_lvmod"));
	DeclareEditStr(true,IDC_AURAEFFECT_para6_lvmod,_T("para6_lvmod"));
}

void AuraEffectWindow::OnCbnSelchangeAuraeffecttype()
{
	// TODO: Add your control notification handler code here
	CWnd* pCombobox = GetDlgItem(IDC_AURAEFFECT_type);
	CString strText;
	pCombobox->GetWindowText(strText);
	ToolApp::Instance().FireEvent("AuraEffect","type",1,CStringToStlString(strText));

	OnEnChangeAuraeffectpara1();
	OnEnChangeAuraeffectpara2();
}

void AuraEffectWindow::OnEnChangeAuraeffectpara1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pCombobox = GetDlgItem(IDC_AURAEFFECT_type);
	CString strType;
	pCombobox->GetWindowText(strType);

	CString strPara1;
	GetDlgItem(IDC_AURAEFFECT_para1)->GetWindowText(strPara1);

	ToolApp::Instance().FireEvent("AuraEffect","para1",2,CStringToStlString(strPara1),CStringToStlString(strType));
}

void AuraEffectWindow::OnEnChangeAuraeffectpara2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pCombobox = GetDlgItem(IDC_AURAEFFECT_type);
	CString strType;
	pCombobox->GetWindowText(strType);

	CString strPara2;
	GetDlgItem(IDC_AURAEFFECT_para2)->GetWindowText(strPara2);

	ToolApp::Instance().FireEvent("AuraEffect","para2",2,CStringToStlString(strPara2),CStringToStlString(strType));
}
