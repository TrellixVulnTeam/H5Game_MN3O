#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubStage dialog

class GuideConditionSubStage : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubStage)

public:
	GuideConditionSubStage(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubStage();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBSTAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
