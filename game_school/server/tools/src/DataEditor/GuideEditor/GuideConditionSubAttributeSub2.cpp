// GuideConditionSubAttributeSub2.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubAttributeSub2.h"


// GuideConditionSubAttributeSub2 dialog

IMPLEMENT_DYNAMIC(GuideConditionSubAttributeSub2, CDialog)

GuideConditionSubAttributeSub2::GuideConditionSubAttributeSub2(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubAttributeSub2::IDD, pParent)
{

}

GuideConditionSubAttributeSub2::~GuideConditionSubAttributeSub2()
{
}

void GuideConditionSubAttributeSub2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubAttributeSub2, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubAttributeSub2 message handlers

BOOL GuideConditionSubAttributeSub2::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_GUIDECONDITION_op,_T("GuideCondition"),_T("op"));

	return TRUE;
}

void GuideConditionSubAttributeSub2::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(false,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(false,IDC_GUIDECONDITION_param2,_T("param2"));
}

void GuideConditionSubAttributeSub2::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(true,IDC_GUIDECONDITION_op,_T("op"));
	DeclareEditInt(true,IDC_GUIDECONDITION_param2,_T("param2"));
}