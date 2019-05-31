#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubTask dialog

class GuideConditionSubTask : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubTask)

public:
	GuideConditionSubTask(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubTask();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
