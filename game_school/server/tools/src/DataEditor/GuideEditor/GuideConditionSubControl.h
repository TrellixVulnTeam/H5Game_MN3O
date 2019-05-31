#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubControl dialog

class GuideConditionSubControl : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubControl)

public:
	GuideConditionSubControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubControl();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
