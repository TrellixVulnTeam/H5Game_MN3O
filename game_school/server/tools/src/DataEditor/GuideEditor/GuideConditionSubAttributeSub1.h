#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubAttributeSub1 dialog

class GuideConditionSubAttributeSub1 : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubAttributeSub1)

public:
	GuideConditionSubAttributeSub1(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubAttributeSub1();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBATTRIBUTE_SUB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
