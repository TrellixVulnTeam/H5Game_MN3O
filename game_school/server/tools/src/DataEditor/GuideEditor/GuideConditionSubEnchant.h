#pragma once

#include "ToolDef.h"

USE_NS_AC;

// GuideConditionSubEnchant dialog

class GuideConditionSubEnchant : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubEnchant)

public:
	GuideConditionSubEnchant(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubEnchant();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBENCHANT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
