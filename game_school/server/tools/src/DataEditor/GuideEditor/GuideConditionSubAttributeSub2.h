#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubAttributeSub2 dialog

class GuideConditionSubAttributeSub2 : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubAttributeSub2)

public:
	GuideConditionSubAttributeSub2(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubAttributeSub2();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBATTRIBUTE_SUB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
