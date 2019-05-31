// EffectFlexibleWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "EffectFlexibleWindow.h"

#include "ToolApp.h"
#include "ACString.h"
#include "ACLog.h"

// EffectFlexibleWindow dialog

IMPLEMENT_DYNAMIC(EffectFlexibleWindow, CDialog)

EffectFlexibleWindow::EffectFlexibleWindow(CWnd* pParent /*=NULL*/)
	: CDialog(EffectFlexibleWindow::IDD, pParent)
{

}

EffectFlexibleWindow::~EffectFlexibleWindow()
{
}

void EffectFlexibleWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectFlexibleWindow, CDialog)
	ON_CBN_SELCHANGE(IDC_EFFECTFLEXIBLE_objType, &EffectFlexibleWindow::OnCbnSelchangeEffectflexibleobjtype)
	ON_CBN_SELCHANGE(IDC_EFFECTFLEXIBLE_type, &EffectFlexibleWindow::OnCbnSelchangeEffectflexibletype)
END_MESSAGE_MAP()


// EffectFlexibleWindow message handlers

BOOL EffectFlexibleWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterWnds();

	CreateCombobox(this,IDC_EFFECTFLEXIBLE_objType,_T("EffectFlexible"),_T("objType"));
	CreateCombobox(this,IDC_EFFECTFLEXIBLE_type,_T("EffectFlexible"),_T("type"));

	return TRUE;
}

void EffectFlexibleWindow::RegisterWnds()
{
	ToolApp::Instance().RegisterWnd("EffectFlexible_objParamDes1",GetDlgItem(IDC_EFFECTFLEXIBLE_objParamDes1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_objParamDes2",GetDlgItem(IDC_EFFECTFLEXIBLE_objParamDes2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_objParamDes3",GetDlgItem(IDC_EFFECTFLEXIBLE_objParamDes3));

	ToolApp::Instance().RegisterWnd("EffectFlexible_objParam1",GetDlgItem(IDC_EFFECTFLEXIBLE_objParam1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_objParam2",GetDlgItem(IDC_EFFECTFLEXIBLE_objParam2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_objParam3",GetDlgItem(IDC_EFFECTFLEXIBLE_objParam3));

	ToolApp::Instance().RegisterWnd("EffectFlexible_nparamDes1",GetDlgItem(IDC_EFFECTFLEXIBLE_nparamDes1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nparamDes2",GetDlgItem(IDC_EFFECTFLEXIBLE_nparamDes2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nparamDes3",GetDlgItem(IDC_EFFECTFLEXIBLE_nparamDes3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparamDes1",GetDlgItem(IDC_EFFECTFLEXIBLE_fparamDes1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparamDes2",GetDlgItem(IDC_EFFECTFLEXIBLE_fparamDes2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparamDes3",GetDlgItem(IDC_EFFECTFLEXIBLE_fparamDes3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparamDes1",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparamDes1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparamDes2",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparamDes2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparamDes3",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparamDes3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparamDes1",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparamDes1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparamDes2",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparamDes2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparamDes3",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparamDes3));

	ToolApp::Instance().RegisterWnd("EffectFlexible_nparam1",GetDlgItem(IDC_EFFECTFLEXIBLE_nparam1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nparam2",GetDlgItem(IDC_EFFECTFLEXIBLE_nparam2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nparam3",GetDlgItem(IDC_EFFECTFLEXIBLE_nparam3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparam1",GetDlgItem(IDC_EFFECTFLEXIBLE_fparam1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparam2",GetDlgItem(IDC_EFFECTFLEXIBLE_fparam2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_fparam3",GetDlgItem(IDC_EFFECTFLEXIBLE_fparam3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparam1",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparam1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparam2",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparam2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_nnparam3",GetDlgItem(IDC_EFFECTFLEXIBLE_nnparam3));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparam1",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparam1));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparam2",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparam2));
	ToolApp::Instance().RegisterWnd("EffectFlexible_ffparam3",GetDlgItem(IDC_EFFECTFLEXIBLE_ffparam3));

	ToolApp::Instance().RegisterWnd("EffectFlexible_charm_typeDes",GetDlgItem(IDC_EFFECTFLEXIBLE_charm_typeDes));
	ToolApp::Instance().RegisterWnd("EffectFlexible_charm_type",GetDlgItem(IDC_EFFECTFLEXIBLE_charm_type));
	ToolApp::Instance().RegisterWnd("EffectFlexible_performanceDes",GetDlgItem(IDC_EFFECTFLEXIBLE_performanceDes));
	ToolApp::Instance().RegisterWnd("EffectFlexible_performance",GetDlgItem(IDC_EFFECTFLEXIBLE_performance));

	ToolApp::Instance().RegisterWnd("EffectFlexible_typeDes",GetDlgItem(IDC_EFFECTFLEXIBLE_typeDes));
}

void EffectFlexibleWindow::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(false,IDC_EFFECTFLEXIBLE_ID,_T("id"));
	DeclareEditStr(false,IDC_EFFECTFLEXIBLE_des,_T("des"));

	DeclareComboboxInt(false,IDC_EFFECTFLEXIBLE_objType,_T("objType"));
	OnCbnSelchangeEffectflexibleobjtype();
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_objParam1,_T("objParam1"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_objParam2,_T("objParam2"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_objParam3,_T("objParam3"));

	DeclareComboboxStr(false,IDC_EFFECTFLEXIBLE_type,_T("type"));
	OnCbnSelchangeEffectflexibletype();
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nparam1,_T("nparam1"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nparam2,_T("nparam2"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nparam3,_T("nparam3"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_fparam1,_T("fparam1"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_fparam2,_T("fparam2"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_fparam3,_T("fparam3"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nnparam1,_T("nnparam1"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nnparam2,_T("nnparam2"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_nnparam3,_T("nnparam3"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_ffparam1,_T("ffparam1"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_ffparam2,_T("ffparam2"));
	DeclareEditFloat(false,IDC_EFFECTFLEXIBLE_ffparam3,_T("ffparam3"));

	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_delay,_T("delay"));
	DeclareEditInt(false,IDC_EFFECTFLEXIBLE_charm_type,_T("charm_type"));
	DeclareEditStr(false,IDC_EFFECTFLEXIBLE_performance,_T("performance"));
}

void EffectFlexibleWindow::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);
	DeclareID(true,IDC_EFFECTFLEXIBLE_ID,_T("id"));
	DeclareEditStr(true,IDC_EFFECTFLEXIBLE_des,_T("des"));

	DeclareComboboxInt(true,IDC_EFFECTFLEXIBLE_objType,_T("objType"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_objParam1,_T("objParam1"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_objParam2,_T("objParam2"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_objParam3,_T("objParam3"));

	DeclareComboboxStr(true,IDC_EFFECTFLEXIBLE_type,_T("type"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nparam1,_T("nparam1"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nparam2,_T("nparam2"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nparam3,_T("nparam3"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_fparam1,_T("fparam1"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_fparam2,_T("fparam2"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_fparam3,_T("fparam3"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nnparam1,_T("nnparam1"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nnparam2,_T("nnparam2"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_nnparam3,_T("nnparam3"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_ffparam1,_T("ffparam1"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_ffparam2,_T("ffparam2"));
	DeclareEditFloat(true,IDC_EFFECTFLEXIBLE_ffparam3,_T("ffparam3"));

	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_delay,_T("delay"));
	DeclareEditInt(true,IDC_EFFECTFLEXIBLE_charm_type,_T("charm_type"));
	DeclareEditStr(true,IDC_EFFECTFLEXIBLE_performance,_T("performance"));
}

void EffectFlexibleWindow::OnCbnSelchangeEffectflexibleobjtype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombobox = (CComboBox*)GetDlgItem(IDC_EFFECTFLEXIBLE_objType);

	VectorComboItemT vtConfs;
	CString strExcel = ToolApp::Instance().GetCurrentDB();
	ToolApp::Instance().GetComboConfig(strExcel,_T("objType"),vtConfs);

	int nCurSel = pCombobox->GetCurSel();
	if(nCurSel < 0 || nCurSel >= vtConfs.size())
	{
		ERROR_MSG("EffectFlexible,objType select unknown item");
		nCurSel = 0;
	}

	CString strText;
	strText.Format(_T("%d"),vtConfs[nCurSel].m_nValue);
	ToolApp::Instance().FireEvent(CStringToStlString(strExcel),"objType",1,CStringToStlString(strText));

}

void EffectFlexibleWindow::OnCbnSelchangeEffectflexibletype()
{
	// TODO: Add your control notification handler code here
	CWnd* pCombobox = GetDlgItem(IDC_EFFECTFLEXIBLE_type);
	CString strText;
	pCombobox->GetWindowText(strText);
	ToolApp::Instance().FireEvent("EffectFlexible","type",1,CStringToStlString(strText));

}
