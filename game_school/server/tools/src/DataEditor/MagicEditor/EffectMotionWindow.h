#pragma once

#include "ToolDef.h"

USE_NS_AC;

// EffectMotionWindow dialog

class EffectMotionWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(EffectMotionWindow)

public:
	EffectMotionWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~EffectMotionWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_EFFECTMOTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeEffectmotionobjtype();
	afx_msg void OnEnChangeEffectmotionbginskillid();
	afx_msg void OnEnChangeEffectmotionskillid();
};
