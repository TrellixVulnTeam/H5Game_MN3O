// GuideConditionSubStage.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubStage.h"


// GuideConditionSubStage dialog

IMPLEMENT_DYNAMIC(GuideConditionSubStage, CDialog)

GuideConditionSubStage::GuideConditionSubStage(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubStage::IDD, pParent)
{

}

GuideConditionSubStage::~GuideConditionSubStage()
{
}

void GuideConditionSubStage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubStage, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubStage message handlers

BOOL GuideConditionSubStage::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void GuideConditionSubStage::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
}

void GuideConditionSubStage::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
}
