// GuideConditionSubAttribute.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubAttribute.h"

#include "ACString.h"

// GuideConditionSubAttribute dialog

IMPLEMENT_DYNAMIC(GuideConditionSubAttribute, CDialog)

GuideConditionSubAttribute::GuideConditionSubAttribute(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubAttribute::IDD, pParent)
{

}

GuideConditionSubAttribute::~GuideConditionSubAttribute()
{
}

void GuideConditionSubAttribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubAttribute, CDialog)
	ON_CBN_SELCHANGE(IDC_GUIDECONDITION_param1, &GuideConditionSubAttribute::OnCbnSelchangeGuideconditionparam1)
END_MESSAGE_MAP()


// GuideConditionSubAttribute message handlers

BOOL GuideConditionSubAttribute::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_GUIDECONDITION_sub)->ShowWindow(SW_HIDE);
	m_objSub1.Create(IDD_DIALOG_SUBATTRIBUTE_SUB1,this);
	m_objSub2.Create(IDD_DIALOG_SUBATTRIBUTE_SUB2,this);

	CRect rect;
	GetDlgItem(IDC_GUIDECONDITION_sub)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_objSub1.MoveWindow(rect);
	m_objSub1.ShowWindow(SW_HIDE);
	m_objSub2.ShowWindow(SW_HIDE);

	CreateCombobox(this,IDC_GUIDECONDITION_param1,_T("GuideCondition"),_T("attribute"));

	return TRUE;
}

void GuideConditionSubAttribute::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_param1);
	ACCHECK(pComboBox);

	CString strValue = mapValues[_T("param1")];
	Combobox_Load(pComboBox,_T("attribute"),DATA_INT,strValue);
	OnCbnSelchangeGuideconditionparam1();

	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_ATTRIBUTE_TYPE_PROFESSION:
		m_objSub1.OnLoadFromDB(mapValues);
		break;
	case GUIDE_ATTRIBUTE_TYPE_LEVEL:
	case GUIDE_ATTRIBUTE_TYPE_MANA:
	case GUIDE_ATTRIBUTE_TYPE_BLOODLINE:
		m_objSub2.OnLoadFromDB(mapValues);
		break;
	}
}

void GuideConditionSubAttribute::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_param1);
	ACCHECK(pComboBox);

	CString strValue;
	Combobox_Save(pComboBox,_T("attribute"),DATA_INT,strValue);
	mapValues[_T("param1")] = strValue;

	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_ATTRIBUTE_TYPE_PROFESSION:
		m_objSub1.OnSaveToDB(mapValues);
		break;
	case GUIDE_ATTRIBUTE_TYPE_LEVEL:
	case GUIDE_ATTRIBUTE_TYPE_MANA:
	case GUIDE_ATTRIBUTE_TYPE_BLOODLINE:
		m_objSub2.OnSaveToDB(mapValues);
		break;
	}
}

void GuideConditionSubAttribute::OnCbnSelchangeGuideconditionparam1()
{
	// TODO: Add your control notification handler code here
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_GUIDECONDITION_param1);
	ACCHECK(pComboBox);

	CRect rect;
	GetDlgItem(IDC_GUIDECONDITION_sub)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_objSub1.ShowWindow(SW_HIDE);
	m_objSub2.ShowWindow(SW_HIDE);

	CString strValue;
	Combobox_Save(pComboBox,_T("attribute"),DATA_INT,strValue);
	int nValue = ACAtoi(CStringToStlString(strValue).c_str());
	switch(nValue)
	{
	case GUIDE_ATTRIBUTE_TYPE_PROFESSION:
		m_objSub1.MoveWindow(rect);
		m_objSub1.ShowWindow(SW_SHOW);
		break;
	case GUIDE_ATTRIBUTE_TYPE_LEVEL:
	case GUIDE_ATTRIBUTE_TYPE_MANA:
	case GUIDE_ATTRIBUTE_TYPE_BLOODLINE:
		m_objSub2.MoveWindow(rect);
		m_objSub2.ShowWindow(SW_SHOW);
		break;
	}
}
