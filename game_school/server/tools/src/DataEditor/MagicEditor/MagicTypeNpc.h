#pragma once

#include "ToolDef.h"

USE_NS_AC

// MagicTypeNpc dialog

class MagicTypeNpc : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(MagicTypeNpc)

public:
	MagicTypeNpc(CWnd* pParent = NULL);   // standard constructor
	virtual ~MagicTypeNpc();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAGICTYPE_NPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
};
