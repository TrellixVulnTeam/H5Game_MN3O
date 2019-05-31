#pragma once

#include "ToolDef.h"

USE_NS_AC;

// EffectFlexibleWindow dialog

class EffectFlexibleWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(EffectFlexibleWindow)

public:
	EffectFlexibleWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~EffectFlexibleWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_EFFECTFLEXIBLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeEffectflexibleobjtype();
	afx_msg void OnCbnSelchangeEffectflexibletype();
};
