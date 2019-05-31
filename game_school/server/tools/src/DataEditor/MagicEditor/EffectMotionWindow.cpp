// EffectMotionWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "EffectMotionWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ACLog.h"

// EffectMotionWindow dialog

IMPLEMENT_DYNAMIC(EffectMotionWindow, CDialog)

EffectMotionWindow::EffectMotionWindow(CWnd* pParent /*=NULL*/)
	: CDialog(EffectMotionWindow::IDD, pParent)
{

}

EffectMotionWindow::~EffectMotionWindow()
{
}

void EffectMotionWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectMotionWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_EFFECTMOTION_objType, &EffectMotionWindow::OnCbnSelchangeEffectmotionobjtype)
	ON_EN_CHANGE(IDC_EFFECTMOTION_bginSkillID, &EffectMotionWindow::OnEnChangeEffectmotionbginskillid)
	ON_EN_CHANGE(IDC_EFFECTMOTION_skillID, &EffectMotionWindow::OnEnChangeEffectmotionskillid)
END_MESSAGE_MAP()


// EffectMotionWindow message handlers

BOOL EffectMotionWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	CreateCombobox(this,IDC_EFFECTMOTION_objType,_T("EffectMotion"),_T("objType"));
	CreateCombobox(this,IDC_EFFECTMOTION_motionPattern,_T("EffectMotion"),_T("motionPattern"));
	CreateCombobox(this,IDC_EFFECTMOTION_timeControl,_T("EffectMotion"),_T("timeControl"));
	CreateCombobox(this,IDC_EFFECTMOTION_barrier_type,_T("EffectMotion"),_T("barrier_type"));
	CreateCombobox(this,IDC_EFFECTMOTION_skillTarget,_T("EffectMotion"),_T("skillTarget"));
	CreateCombobox(this,IDC_EFFECTMOTION_movetype,_T("EffectMotion"),_T("movetype"));

	return TRUE;
}

void EffectMotionWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("EffectMotion_objParamDes1",GetDlgItem(IDC_EFFECTMOTION_objParamDes1));
	ToolApp::Instance().RegisterWnd("EffectMotion_objParamDes2",GetDlgItem(IDC_EFFECTMOTION_objParamDes2));
	ToolApp::Instance().RegisterWnd("EffectMotion_objParamDes3",GetDlgItem(IDC_EFFECTMOTION_objParamDes3));

	ToolApp::Instance().RegisterWnd("EffectMotion_objParam1",GetDlgItem(IDC_EFFECTMOTION_objParam1));
	ToolApp::Instance().RegisterWnd("EffectMotion_objParam2",GetDlgItem(IDC_EFFECTMOTION_objParam2));
	ToolApp::Instance().RegisterWnd("EffectMotion_objParam3",GetDlgItem(IDC_EFFECTMOTION_objParam3));
}

void EffectMotionWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_EFFECTMOTION_motionID,_T("motionID"));
	DeclareEditStr(false,IDC_EFFECTMOTION_des,_T("des"));

	DeclareComboboxInt(false,IDC_EFFECTMOTION_objType,_T("objType"));
	OnCbnSelchangeEffectmotionobjtype();
	DeclareEditFloat(false,IDC_EFFECTMOTION_objParam1,_T("objParam1"));
	DeclareEditFloat(false,IDC_EFFECTMOTION_objParam2,_T("objParam2"));
	DeclareEditFloat(false,IDC_EFFECTMOTION_objParam3,_T("objParam3"));

	DeclareComboboxInt(false,IDC_EFFECTMOTION_motionPattern,_T("motionPattern"));
	DeclareEditInt(false,IDC_EFFECTMOTION_motionPerformancePattern,_T("motionPerformancePattern"));
	DeclareEditInt(false,IDC_EFFECTMOTION_moveTime,_T("moveTime"));
	DeclareComboboxInt(false,IDC_EFFECTMOTION_timeControl,_T("timeControl"));
	DeclareComboboxInt(false,IDC_EFFECTMOTION_barrier_type,_T("barrier_type"));
	DeclareEditInt(false,IDC_EFFECTMOTION_bginSkillID,_T("bginSkillID"));
	DeclareEditInt(false,IDC_EFFECTMOTION_skillID,_T("skillID"));

	CString strDes = GetDBRecordField(_T("MagicType"),mapValues[_T("bginSkillID")],_T("magicName"));
	GetDlgItem(IDC_EFFECTMOTION_bginSkillDes)->SetWindowText(strDes);

	strDes = GetDBRecordField(_T("MagicType"),mapValues[_T("skillID")],_T("magicName"));
	GetDlgItem(IDC_EFFECTMOTION_skillDes)->SetWindowText(strDes);

	DeclareComboboxInt(false,IDC_EFFECTMOTION_skillTarget,_T("skillTarget"));
	DeclareComboboxInt(false,IDC_EFFECTMOTION_movetype,_T("movetype"));
	DeclareEditInt(false,IDC_EFFECTMOTION_delay,_T("delay"));
}

void EffectMotionWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_EFFECTMOTION_motionID,_T("motionID"));
	DeclareEditStr(true,IDC_EFFECTMOTION_des,_T("des"));

	DeclareComboboxInt(true,IDC_EFFECTMOTION_objType,_T("objType"));
	DeclareEditFloat(true,IDC_EFFECTMOTION_objParam1,_T("objParam1"));
	DeclareEditFloat(true,IDC_EFFECTMOTION_objParam2,_T("objParam2"));
	DeclareEditFloat(true,IDC_EFFECTMOTION_objParam3,_T("objParam3"));

	DeclareComboboxInt(true,IDC_EFFECTMOTION_motionPattern,_T("motionPattern"));
	DeclareEditInt(true,IDC_EFFECTMOTION_motionPerformancePattern,_T("motionPerformancePattern"));
	DeclareEditInt(true,IDC_EFFECTMOTION_moveTime,_T("moveTime"));
	DeclareComboboxInt(true,IDC_EFFECTMOTION_timeControl,_T("timeControl"));
	DeclareComboboxInt(true,IDC_EFFECTMOTION_barrier_type,_T("barrier_type"));
	DeclareEditInt(true,IDC_EFFECTMOTION_bginSkillID,_T("bginSkillID"));
	DeclareEditInt(true,IDC_EFFECTMOTION_skillID,_T("skillID"));
	DeclareComboboxInt(true,IDC_EFFECTMOTION_skillTarget,_T("skillTarget"));
	DeclareComboboxInt(true,IDC_EFFECTMOTION_movetype,_T("movetype"));
	DeclareEditInt(true,IDC_EFFECTMOTION_delay,_T("delay"));
}

void EffectMotionWindow::OnCbnSelchangeEffectmotionobjtype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_EFFECTMOTION_objType);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("objType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("EffectMotion,objType select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"objType",1,CStringToStlString(strText));
}

void EffectMotionWindow::OnEnChangeEffectmotionbginskillid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTMOTION_bginSkillID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("MagicType"),strKey,_T("magicName"));
	GetDlgItem(IDC_EFFECTMOTION_bginSkillDes)->SetWindowText(strDes);
}

void EffectMotionWindow::OnEnChangeEffectmotionskillid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTMOTION_skillID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("MagicType"),strKey,_T("magicName"));
	GetDlgItem(IDC_EFFECTMOTION_skillDes)->SetWindowText(strDes);
}
