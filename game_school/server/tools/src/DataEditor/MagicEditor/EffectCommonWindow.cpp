// EffectCommonWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "EffectCommonWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ACLog.h"

// EffectCommonWindow dialog

IMPLEMENT_DYNAMIC(EffectCommonWindow, CDialog)

EffectCommonWindow::EffectCommonWindow(CWnd* pParent /*=NULL*/)
	: CDialog(EffectCommonWindow::IDD, pParent)
{

}

EffectCommonWindow::~EffectCommonWindow()
{
}

void EffectCommonWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectCommonWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_EFFECTCOMMON_rangeType, &EffectCommonWindow::OnCbnSelchangeEffectcommonrangetype)
	ON_EN_CHANGE(IDC_EFFECTCOMMON_beatBackProbablity, &EffectCommonWindow::OnEnChangeEffectcommonbeatbackprobablity)
	ON_EN_CHANGE(IDC_EFFECTCOMMON_hitBuff1, &EffectCommonWindow::OnEnChangeEffectcommonhitbuff1)
	ON_EN_CHANGE(IDC_EFFECTCOMMON_hitBuff2, &EffectCommonWindow::OnEnChangeEffectcommonhitbuff2)
	ON_EN_CHANGE(IDC_EFFECTCOMMON_hitBuff3, &EffectCommonWindow::OnEnChangeEffectcommonhitbuff3)
END_MESSAGE_MAP()


// EffectCommonWindow message handlers

BOOL EffectCommonWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	CreateCheckCombo(this,IDC_EFFECTCOMMON_effectBits,_T("EffectCommon"),_T("effectBits"));
	CreateCombobox(this,IDC_EFFECTCOMMON_rangeType,_T("EffectCommon"),_T("rangeType"));
	CreateCombobox(this,IDC_EFFECTCOMMON_beatBackType,_T("EffectCommon"),_T("beatBackType"));
	CreateCombobox(this,IDC_EFFECTCOMMON_physicsForceType,_T("EffectCommon"),_T("physicsForceType"));
	CreateCombobox(this,IDC_EFFECTCOMMON_physicsForceHeight,_T("EffectCommon"),_T("physicsForceHeight"));
	CreateCombobox(this,IDC_EFFECTCOMMON_additionalHurtType,_T("EffectCommon"),_T("additionalHurtType"));
	CreateCombobox(this,IDC_EFFECTCOMMON_additionalHurtTransType,_T("EffectCommon"),_T("additionalHurtTransType"));

	return TRUE;
}

void EffectCommonWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("EffectCommon_rangeDes1",GetDlgItem(IDC_EFFECTCOMMON_rangeDes1));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangeDes2",GetDlgItem(IDC_EFFECTCOMMON_rangeDes2));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangeDes3",GetDlgItem(IDC_EFFECTCOMMON_rangeDes3));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangeDes4",GetDlgItem(IDC_EFFECTCOMMON_rangeDes4));

	ToolApp::Instance().RegisterWnd("EffectCommon_rangePara1",GetDlgItem(IDC_EFFECTCOMMON_rangePara1));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangePara2",GetDlgItem(IDC_EFFECTCOMMON_rangePara2));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangePara3",GetDlgItem(IDC_EFFECTCOMMON_rangePara3));
	ToolApp::Instance().RegisterWnd("EffectCommon_rangePara4",GetDlgItem(IDC_EFFECTCOMMON_rangePara4));
}

void EffectCommonWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_EFFECTCOMMON_commonID,_T("commonID"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_des,_T("des"));

	DeclareCheckComboBit(false,IDC_EFFECTCOMMON_effectBits,_T("effectBits"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_delay,_T("delay"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_objectNum,_T("objectNum"));

	DeclareComboboxInt(false,IDC_EFFECTCOMMON_rangeType,_T("rangeType"));
	OnCbnSelchangeEffectcommonrangetype();
	DeclareEditFloat(false,IDC_EFFECTCOMMON_rangePara1,_T("rangePara1"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_rangePara2,_T("rangePara2"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_rangePara3,_T("rangePara3"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_rangePara4,_T("rangePara4"));

	DeclareEditInt(false,IDC_EFFECTCOMMON_beatenPerformanceID,_T("beatenPerformanceID"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_deadSmashProbablity,_T("deadSmashProbablity"));

	DeclareEditFloat(false,IDC_EFFECTCOMMON_beatBackProbablity,_T("beatBackProbablity"));
	OnEnChangeEffectcommonbeatbackprobablity();
	DeclareComboboxInt(false,IDC_EFFECTCOMMON_beatBackType,_T("beatBackType"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_beatBackDistMin,_T("beatBackDistMin"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_beatBackDistMax,_T("beatBackDistMax"));

	DeclareEditFloat(false,IDC_EFFECTCOMMON_hitBuffChance1,_T("hitBuffChance1"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hitBuff1,_T("hitBuff1"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_hitBuffChance2,_T("hitBuffChance2"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hitBuff2,_T("hitBuff2"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_hitBuffChance3,_T("hitBuffChance3"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hitBuff3,_T("hitBuff3"));

	CString strDes = GetDBRecordField(_T("Aura"),mapValues[_T("hitBuff1")],_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes1)->SetWindowText(strDes);

	strDes = GetDBRecordField(_T("Aura"),mapValues[_T("hitBuff2")],_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes2)->SetWindowText(strDes);

	strDes = GetDBRecordField(_T("Aura"),mapValues[_T("hitBuff3")],_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes3)->SetWindowText(strDes);

	DeclareComboboxInt(false,IDC_EFFECTCOMMON_physicsForceType,_T("physicsForceType"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physicsForce,_T("physicsForce"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physicsForceAdjustAngle,_T("physicsForceAdjustAngle"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physicsForceAdjustY,_T("physicsForceAdjustY"));
	DeclareComboboxInt(false,IDC_EFFECTCOMMON_physicsForceHeight,_T("physicsForceHeight"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physics_if_top,_T("physics_if_top"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physics_if_middle,_T("physics_if_middle"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_physics_if_bottom,_T("physics_if_bottom"));

	DeclareCheckbox(false,IDC_EFFECTCOMMON_isMustHit,_T("isMustHit"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hurtPercentagePhys,_T("hurtPercentagePhys"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hurtValuePhys,_T("hurtValuePhys"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_hurtPercentagePhysMods,_T("hurtPercentagePhysMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_hurtValuePhysMods,_T("hurtValuePhysMods"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hurtPercentageMage,_T("hurtPercentageMage"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_hurtValueMage,_T("hurtValueMage"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_hurtPercentageMageMods,_T("hurtPercentageMageMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_hurtValueMageMods,_T("hurtValueMageMods"));

	DeclareComboboxInt(false,IDC_EFFECTCOMMON_additionalHurtType,_T("additionalHurtType"));
	DeclareComboboxInt(false,IDC_EFFECTCOMMON_additionalHurtTransType,_T("additionalHurtTransType"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_additionalFireHurtValue,_T("additionalFireHurtValue"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_additionalColdHurtValue,_T("additionalColdHurtValue"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_additionalLightHurtValue,_T("additionalLightHurtValue"));
	DeclareEditInt(false,IDC_EFFECTCOMMON_additionalPoisonHurtValue,_T("additionalPoisonHurtValue"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalFireHurtValueMods,_T("additionalFireHurtValueMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalColdHurtValueMods,_T("additionalColdHurtValueMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalLightHurtValueMods,_T("additionalLightHurtValueMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalPoisonHurtValueMods,_T("additionalPoisonHurtValueMods"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_additionalFireHurtTransRate,_T("additionalFireHurtTransRate"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_additionalColdHurtTransRate,_T("additionalColdHurtTransRate"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_additionalLightHurtTransRate,_T("additionalLightHurtTransRate"));
	DeclareEditFloat(false,IDC_EFFECTCOMMON_additionalPoisonHurtTransRate,_T("additionalPoisonHurtTransRate"));

	DeclareEditFloat(false,IDC_EFFECTCOMMON_humanAttrHurtTransRate,_T("humanAttrHurtTransRate"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalFireHurtTransRateMods,_T("additionalFireHurtTransRateMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalColdHurtTransRateMods,_T("additionalColdHurtTransRateMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalLightHurtTransRateMods,_T("additionalLightHurtTransRateMods"));
	DeclareEditStr(false,IDC_EFFECTCOMMON_additionalPoisonHurtTransRateMods,_T("additionalPoisonHurtTransRateMods"));
}

void EffectCommonWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_EFFECTCOMMON_commonID,_T("commonID"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_des,_T("des"));

	DeclareCheckComboBit(true,IDC_EFFECTCOMMON_effectBits,_T("effectBits"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_delay,_T("delay"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_objectNum,_T("objectNum"));

	DeclareComboboxInt(true,IDC_EFFECTCOMMON_rangeType,_T("rangeType"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_rangePara1,_T("rangePara1"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_rangePara2,_T("rangePara2"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_rangePara3,_T("rangePara3"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_rangePara4,_T("rangePara4"));

	DeclareEditInt(true,IDC_EFFECTCOMMON_beatenPerformanceID,_T("beatenPerformanceID"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_deadSmashProbablity,_T("deadSmashProbablity"));

	DeclareEditFloat(true,IDC_EFFECTCOMMON_beatBackProbablity,_T("beatBackProbablity"));
	DeclareComboboxInt(true,IDC_EFFECTCOMMON_beatBackType,_T("beatBackType"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_beatBackDistMin,_T("beatBackDistMin"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_beatBackDistMax,_T("beatBackDistMax"));

	DeclareEditFloat(true,IDC_EFFECTCOMMON_hitBuffChance1,_T("hitBuffChance1"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hitBuff1,_T("hitBuff1"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_hitBuffChance2,_T("hitBuffChance2"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hitBuff2,_T("hitBuff2"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_hitBuffChance3,_T("hitBuffChance3"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hitBuff3,_T("hitBuff3"));

	DeclareComboboxInt(true,IDC_EFFECTCOMMON_physicsForceType,_T("physicsForceType"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physicsForce,_T("physicsForce"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physicsForceAdjustAngle,_T("physicsForceAdjustAngle"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physicsForceAdjustY,_T("physicsForceAdjustY"));
	DeclareComboboxInt(true,IDC_EFFECTCOMMON_physicsForceHeight,_T("physicsForceHeight"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physics_if_top,_T("physics_if_top"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physics_if_middle,_T("physics_if_middle"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_physics_if_bottom,_T("physics_if_bottom"));

	DeclareCheckbox(true,IDC_EFFECTCOMMON_isMustHit,_T("isMustHit"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hurtPercentagePhys,_T("hurtPercentagePhys"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hurtValuePhys,_T("hurtValuePhys"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_hurtPercentagePhysMods,_T("hurtPercentagePhysMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_hurtValuePhysMods,_T("hurtValuePhysMods"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hurtPercentageMage,_T("hurtPercentageMage"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_hurtValueMage,_T("hurtValueMage"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_hurtPercentageMageMods,_T("hurtPercentageMageMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_hurtValueMageMods,_T("hurtValueMageMods"));

	DeclareComboboxInt(true,IDC_EFFECTCOMMON_additionalHurtType,_T("additionalHurtType"));
	DeclareComboboxInt(true,IDC_EFFECTCOMMON_additionalHurtTransType,_T("additionalHurtTransType"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_additionalFireHurtValue,_T("additionalFireHurtValue"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_additionalColdHurtValue,_T("additionalColdHurtValue"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_additionalLightHurtValue,_T("additionalLightHurtValue"));
	DeclareEditInt(true,IDC_EFFECTCOMMON_additionalPoisonHurtValue,_T("additionalPoisonHurtValue"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalFireHurtValueMods,_T("additionalFireHurtValueMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalColdHurtValueMods,_T("additionalColdHurtValueMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalLightHurtValueMods,_T("additionalLightHurtValueMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalPoisonHurtValueMods,_T("additionalPoisonHurtValueMods"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_additionalFireHurtTransRate,_T("additionalFireHurtTransRate"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_additionalColdHurtTransRate,_T("additionalColdHurtTransRate"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_additionalLightHurtTransRate,_T("additionalLightHurtTransRate"));
	DeclareEditFloat(true,IDC_EFFECTCOMMON_additionalPoisonHurtTransRate,_T("additionalPoisonHurtTransRate"));

	DeclareEditFloat(true,IDC_EFFECTCOMMON_humanAttrHurtTransRate,_T("humanAttrHurtTransRate"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalFireHurtTransRateMods,_T("additionalFireHurtTransRateMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalColdHurtTransRateMods,_T("additionalColdHurtTransRateMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalLightHurtTransRateMods,_T("additionalLightHurtTransRateMods"));
	DeclareEditStr(true,IDC_EFFECTCOMMON_additionalPoisonHurtTransRateMods,_T("additionalPoisonHurtTransRateMods"));
}

void EffectCommonWindow::OnCbnSelchangeEffectcommonrangetype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_EFFECTCOMMON_rangeType);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("rangeType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("EffectCommon,rangeType select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"rangeType",1,CStringToStlString(strText));
}

void EffectCommonWindow::OnEnChangeEffectcommonbeatbackprobablity()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pbeatBackProbablity = GetDlgItem(IDC_EFFECTCOMMON_beatBackProbablity);
	ACCHECK(pbeatBackProbablity);

	CWnd* pbeatBackType = GetDlgItem(IDC_EFFECTCOMMON_beatBackType);
	ACCHECK(pbeatBackType);

	CWnd* pbeatBackDistMin = GetDlgItem(IDC_EFFECTCOMMON_beatBackDistMin);
	ACCHECK(pbeatBackDistMin);

	CWnd* pbeatBackDistMax = GetDlgItem(IDC_EFFECTCOMMON_beatBackDistMax);
	ACCHECK(pbeatBackDistMax);

	CString strText;
	pbeatBackProbablity->GetWindowText(strText);

	double fValue = ACAtof(CStringToStlString(strText).c_str());
	if(fValue > 0 && fValue <= 1.0f)
	{
		pbeatBackType->EnableWindow(TRUE);
		pbeatBackDistMin->EnableWindow(TRUE);
		pbeatBackDistMax->EnableWindow(TRUE);
	}
	else
	{
		pbeatBackType->EnableWindow(FALSE);
		pbeatBackDistMin->EnableWindow(FALSE);
		pbeatBackDistMax->EnableWindow(FALSE);
	}
}

void EffectCommonWindow::OnEnChangeEffectcommonhitbuff1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOMMON_hitBuff1)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Aura"),strKey,_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes1)->SetWindowText(strDes);
}

void EffectCommonWindow::OnEnChangeEffectcommonhitbuff2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOMMON_hitBuff2)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Aura"),strKey,_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes2)->SetWindowText(strDes);
}

void EffectCommonWindow::OnEnChangeEffectcommonhitbuff3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strKey;
	GetDlgItem(IDC_EFFECTCOMMON_hitBuff3)->GetWindowText(strKey);

	CString strDes = GetDBRecordField(_T("Aura"),strKey,_T("name"));
	GetDlgItem(IDC_EFFECTCOMMON_hitBuffDes3)->SetWindowText(strDes);
}
