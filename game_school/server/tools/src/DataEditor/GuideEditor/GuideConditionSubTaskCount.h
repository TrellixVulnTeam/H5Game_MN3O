#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubTaskCount dialog

class GuideConditionSubTaskCount : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubTaskCount)

public:
	GuideConditionSubTaskCount(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubTaskCount();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBTASKCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
