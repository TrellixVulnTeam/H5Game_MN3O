// GuideConditionSubTaskCount.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubTaskCount.h"


// GuideConditionSubTaskCount dialog

IMPLEMENT_DYNAMIC(GuideConditionSubTaskCount, CDialog)

GuideConditionSubTaskCount::GuideConditionSubTaskCount(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubTaskCount::IDD, pParent)
{

}

GuideConditionSubTaskCount::~GuideConditionSubTaskCount()
{
}

void GuideConditionSubTaskCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubTaskCount, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubTaskCount message handlers

BOOL GuideConditionSubTaskCount::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_GUIDECONDITION_op,_T("GuideCondition"),_T("op"));

	return TRUE;
}

void GuideConditionSubTaskCount::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(false,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param2,_T("param2"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param3,_T("param3"));
}

void GuideConditionSubTaskCount::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(true,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param2,_T("param2"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param3,_T("param3"));
}
