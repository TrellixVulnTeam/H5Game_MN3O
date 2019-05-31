// EffectCollisionWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "EffectCollisionWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ACLog.h"

// EffectCollisionWindow dialog

IMPLEMENT_DYNAMIC(EffectCollisionWindow, CDialog)

EffectCollisionWindow::EffectCollisionWindow(CWnd* pParent /*=NULL*/)
	: CDialog(EffectCollisionWindow::IDD, pParent)
{

}

EffectCollisionWindow::~EffectCollisionWindow()
{
}

void EffectCollisionWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectCollisionWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_EFFECTCOLLISION_objType, &EffectCollisionWindow::OnCbnSelchangeEffectcollisionobjtype)
	ON_EN_CHANGE(IDC_EFFECTCOLLISION_skillID, &EffectCollisionWindow::OnEnChangeEffectcollisionskillid)
	ON_EN_CHANGE(IDC_EFFECTCOLLISION_flyPerformanceID, &EffectCollisionWindow::OnEnChangeEffectcollisionflyperformanceid)
	ON_EN_CHANGE(IDC_EFFECTCOLLISION_aura, &EffectCollisionWindow::OnEnChangeEffectcollisionaura)
END_MESSAGE_MAP()


// EffectCollisionWindow message handlers

BOOL EffectCollisionWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	CreateCombobox(this,IDC_EFFECTCOLLISION_objType,_T("EffectCollision"),_T("objType"));
	CreateCombobox(this,IDC_EFFECTCOLLISION_generateType,_T("EffectCollision"),_T("generateType"));
	CreateCheckCombo(this,IDC_EFFECTCOLLISION_flags,_T("EffectCollision"),_T("flags"));

	return TRUE;
}

void EffectCollisionWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("EffectCollision_objParamDes1",GetDlgItem(IDC_EFFECTCOLLISION_objParamDes1));
	ToolApp::Instance().RegisterWnd("EffectCollision_objParamDes2",GetDlgItem(IDC_EFFECTCOLLISION_objParamDes2));
	ToolApp::Instance().RegisterWnd("EffectCollision_objParamDes3",GetDlgItem(IDC_EFFECTCOLLISION_objParamDes3));

	ToolApp::Instance().RegisterWnd("EffectCollision_objParam1",GetDlgItem(IDC_EFFECTCOLLISION_objParam1));
	ToolApp::Instance().RegisterWnd("EffectCollision_objParam2",GetDlgItem(IDC_EFFECTCOLLISION_objParam2));
	ToolApp::Instance().RegisterWnd("EffectCollision_objParam3",GetDlgItem(IDC_EFFECTCOLLISION_objParam3));
}

void EffectCollisionWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_EFFECTCOLLISION_collisionID,_T("collisionID"));
	DeclareEditStr(false,IDC_EFFECTCOLLISION_des,_T("des"));

	DeclareComboboxInt(false,IDC_EFFECTCOLLISION_objType,_T("objType"));
	OnCbnSelchangeEffectcollisionobjtype();
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_objParam1,_T("objParam1"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_objParam2,_T("objParam2"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_objParam3,_T("objParam3"));

	DeclareComboboxInt(false,IDC_EFFECTCOLLISION_generateType,_T("generateType"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_generateNum,_T("generateNum"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_bulletGap,_T("bulletGap"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_bezierId,_T("bezierId"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_maxDist,_T("maxDist"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_speed,_T("speed"));

	DeclareEditInt(false,IDC_EFFECTCOLLISION_skillID,_T("skillID"));

	CString strDes = GetDBRecordField(_T("MagicType"),mapValues[_T("skillID")],_T("magicName"));
	GetDlgItem(IDC_EFFECTCOLLISION_skillDes)->SetWindowText(strDes);

	DeclareEditInt(false,IDC_EFFECTCOLLISION_maxCollisionTimes,_T("maxCollisionTimes"));
	DeclareCheckbox(false,IDC_EFFECTCOLLISION_hasFinalEffect,_T("hasFinalEffect"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_flyPerformanceID,_T("flyPerformanceID"));

	strDes = GetDBRecordField(_T("PerformanceFlyModel"),mapValues[_T("flyPerformanceID")],_T("des"));
	GetDlgItem(IDC_EFFECTCOLLISION_flyPerformanceDes)->SetWindowText(strDes);

	DeclareEditStr(false,IDC_EFFECTCOLLISION_bind,_T("bind"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_charPerformanceID,_T("charPerformanceID"));
	DeclareEditFloat(false,IDC_EFFECTCOLLISION_scale,_T("scale"));
	DeclareCheckbox(false,IDC_EFFECTCOLLISION_hitOnce,_T("hitOnce"));
	DeclareCheckbox(false,IDC_EFFECTCOLLISION_hitOnceG,_T("hitOnceG"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_delay,_T("delay"));
	DeclareEditInt(false,IDC_EFFECTCOLLISION_aura,_T("aura"));

	strDes = GetDBRecordField(_T("Aura"),mapValues[_T("aura")],_T("name"));
	GetDlgItem(IDC_EFFECTCOLLISION_auraDes)->SetWindowText(strDes);

	DeclareCheckComboBit(false,IDC_EFFECTCOLLISION_flags,_T("flags"));
}

void EffectCollisionWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_EFFECTCOLLISION_collisionID,_T("collisionID"));
	DeclareEditStr(true,IDC_EFFECTCOLLISION_des,_T("des"));

	DeclareComboboxInt(true,IDC_EFFECTCOLLISION_objType,_T("objType"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_objParam1,_T("objParam1"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_objParam2,_T("objParam2"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_objParam3,_T("objParam3"));

	DeclareComboboxInt(true,IDC_EFFECTCOLLISION_generateType,_T("generateType"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_generateNum,_T("generateNum"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_bulletGap,_T("bulletGap"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_bezierId,_T("bezierId"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_maxDist,_T("maxDist"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_speed,_T("speed"));

	DeclareEditInt(true,IDC_EFFECTCOLLISION_skillID,_T("skillID"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_maxCollisionTimes,_T("maxCollisionTimes"));
	DeclareCheckbox(true,IDC_EFFECTCOLLISION_hasFinalEffect,_T("hasFinalEffect"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_flyPerformanceID,_T("flyPerformanceID"));
	DeclareEditStr(true,IDC_EFFECTCOLLISION_bind,_T("bind"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_charPerformanceID,_T("charPerformanceID"));
	DeclareEditFloat(true,IDC_EFFECTCOLLISION_scale,_T("scale"));
	DeclareCheckbox(true,IDC_EFFECTCOLLISION_hitOnce,_T("hitOnce"));
	DeclareCheckbox(true,IDC_EFFECTCOLLISION_hitOnceG,_T("hitOnceG"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_delay,_T("delay"));
	DeclareEditInt(true,IDC_EFFECTCOLLISION_aura,_T("aura"));
	DeclareCheckComboBit(true,IDC_EFFECTCOLLISION_flags,_T("flags"));
}

void EffectCollisionWindow::OnCbnSelchangeEffectcollisionobjtype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_EFFECTCOLLISION_objType);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("objType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("EffectCollision,objType select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"objType",1,CStringToStlString(strText));
}

void EffectCollisionWindow::OnEnChangeEffectcollisionskillid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOLLISION_skillID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("MagicType"),strKey,_T("magicName"));
	GetDlgItem(IDC_EFFECTCOLLISION_skillDes)->SetWindowText(strDes);
}

void EffectCollisionWindow::OnEnChangeEffectcollisionflyperformanceid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOLLISION_flyPerformanceID)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("PerformanceFlyModel"),strKey,_T("des"));
	GetDlgItem(IDC_EFFECTCOLLISION_flyPerformanceDes)->SetWindowText(strDes);
}

void EffectCollisionWindow::OnEnChangeEffectcollisionaura()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOLLISION_aura)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Aura"),strKey,_T("name"));
	GetDlgItem(IDC_EFFECTCOLLISION_auraDes)->SetWindowText(strDes);
}
