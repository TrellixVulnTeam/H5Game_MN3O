// GuideConditionSubControl.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubControl.h"


// GuideConditionSubControl dialog

IMPLEMENT_DYNAMIC(GuideConditionSubControl, CDialog)

GuideConditionSubControl::GuideConditionSubControl(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubControl::IDD, pParent)
{

}

GuideConditionSubControl::~GuideConditionSubControl()
{
}

void GuideConditionSubControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubControl, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubControl message handlers

BOOL GuideConditionSubControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void GuideConditionSubControl::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
}

void GuideConditionSubControl::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
}
