#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubBlood dialog

class GuideConditionSubBlood : public CDialog
{
	DECLARE_DYNAMIC(GuideConditionSubBlood)

public:
	GuideConditionSubBlood(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubBlood();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBBLOOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
