#pragma once

#include "ToolDef.h"

USE_NS_AC

// MagicTypeHuman dialog

class MagicTypeHuman : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(MagicTypeHuman)

public:
	MagicTypeHuman(CWnd* pParent = NULL);   // standard constructor
	virtual ~MagicTypeHuman();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAGICTYPE_HUMAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
