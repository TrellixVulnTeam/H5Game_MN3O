// GuideConditionSubTask.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideConditionSubTask.h"


// GuideConditionSubTask dialog

IMPLEMENT_DYNAMIC(GuideConditionSubTask, CDialog)

GuideConditionSubTask::GuideConditionSubTask(CWnd* pParent /*=NULL*/)
	: CDialog(GuideConditionSubTask::IDD, pParent)
{

}

GuideConditionSubTask::~GuideConditionSubTask()
{
}

void GuideConditionSubTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GuideConditionSubTask, CDialog)
END_MESSAGE_MAP()


// GuideConditionSubTask message handlers

BOOL GuideConditionSubTask::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void GuideConditionSubTask::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(false,IDC_GUIDECONDITION_param1,_T("param1"));
}

void GuideConditionSubTask::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditInt(true,IDC_GUIDECONDITION_param1,_T("param1"));
}
