// GuideConditionSubBlood.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubBlood.h"


// GuideConditionSubBlood dialog

IMPLEMENT_DYNAMIC(GuideConditionSubBlood, CDialog)

GuideConditionSubBlood::GuideConditionSubBlood(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubBlood::IDD, pParent)
{

}

GuideConditionSubBlood::~GuideConditionSubBlood()
{
}

void GuideConditionSubBlood::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubBlood, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubBlood message handlers

BOOL GuideConditionSubBlood::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_GUIDECONDITION_op,_T("GuideCondition"),_T("op"));

	return TRUE;
}

void GuideConditionSubBlood::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(false,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
}

void GuideConditionSubBlood::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(true,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
}
