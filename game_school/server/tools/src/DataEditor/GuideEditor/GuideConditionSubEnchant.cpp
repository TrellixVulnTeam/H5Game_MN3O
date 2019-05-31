// GuideConditionSubEnchant.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubEnchant.h"


// GuideConditionSubEnchant dialog

IMPLEMENT_DYNAMIC(GuideConditionSubEnchant, CDialog)

GuideConditionSubEnchant::GuideConditionSubEnchant(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubEnchant::IDD, pParent)
{

}

GuideConditionSubEnchant::~GuideConditionSubEnchant()
{
}

void GuideConditionSubEnchant::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubEnchant, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubEnchant message handlers

BOOL GuideConditionSubEnchant::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_GUIDECONDITION_op,_T("GuideCondition"),_T("op"));

	return TRUE;
}

void GuideConditionSubEnchant::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(false,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
}

void GuideConditionSubEnchant::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(true,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
}
