#pragma once

#include "ToolDef.h"

USE_NS_AC;

// EffectCommonWindow dialog

class EffectCommonWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(EffectCommonWindow)

public:
	EffectCommonWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~EffectCommonWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_EFFECTCOMMON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeEffectcommonrangetype();
	afx_msg void OnEnChangeEffectcommonbeatbackprobablity();
	afx_msg void OnEnChangeEffectcommonhitbuff1();
	afx_msg void OnEnChangeEffectcommonhitbuff2();
	afx_msg void OnEnChangeEffectcommonhitbuff3();
};
