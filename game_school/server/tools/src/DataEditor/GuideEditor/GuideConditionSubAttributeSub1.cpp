// GuideConditionSubAttributeSub1.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubAttributeSub1.h"


// GuideConditionSubAttributeSub1 dialog

IMPLEMENT_DYNAMIC(GuideConditionSubAttributeSub1, CDialog)

GuideConditionSubAttributeSub1::GuideConditionSubAttributeSub1(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubAttributeSub1::IDD, pParent)
{

}

GuideConditionSubAttributeSub1::~GuideConditionSubAttributeSub1()
{
}

void GuideConditionSubAttributeSub1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubAttributeSub1, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubAttributeSub1 message handlers

BOOL GuideConditionSubAttributeSub1::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_GUIDECONDITION_param2,_T("GuideCondition"),_T("profession"));

	return TRUE;
}

void GuideConditionSubAttributeSub1::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_param2);
	ACCHECK(pComboBox);

	CString strValue = mapValues[_T("param2")];
	Combobox_Load(pComboBox,_T("profession"),DATA_INT,strValue);
}

void GuideConditionSubAttributeSub1::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_param2);
	ACCHECK(pComboBox);

	CString strValue;
	Combobox_Save(pComboBox,_T("profession"),DATA_INT,strValue);
	mapValues[_T("param2")] = strValue;
}