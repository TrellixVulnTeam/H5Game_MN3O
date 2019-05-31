#pragma once

#include "ToolDef.h"

USE_NS_AC;

// AuraEffectWindow dialog

class AuraEffectWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(AuraEffectWindow)

public:
	AuraEffectWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~AuraEffectWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_AURAEFFECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeAuraeffecttype();
	afx_msg void OnEnChangeAuraeffectpara1();
	afx_msg void OnEnChangeAuraeffectpara2();
};
