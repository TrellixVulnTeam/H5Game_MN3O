#pragma once

#include "ToolDef.h"

USE_NS_AC;

// EffectCollisionWindow dialog

class EffectCollisionWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(EffectCollisionWindow)

public:
	EffectCollisionWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~EffectCollisionWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_EFFECTCOLLISION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeEffectcollisionobjtype();
	afx_msg void OnEnChangeEffectcollisionskillid();
	afx_msg void OnEnChangeEffectcollisionflyperformanceid();
	afx_msg void OnEnChangeEffectcollisionaura();
};
