#pragma once

#include "ToolDef.h"
#include "QuickList.h"
#include "afxcmn.h"

USE_NS_AC;

// AuraWindow dialog

class AuraWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	struct SEffectInfo
	{
		SEffectInfo()
		{
			m_strEffectID = _T("-1");
			m_strEffectDes = _T("");
		}

		SEffectInfo(const CString& strID,const CString& strDes)
		{
			m_strEffectID = strID;
			m_strEffectDes = strDes;
		}

		CString m_strEffectID;
		CString m_strEffectDes;
	};

	DECLARE_DYNAMIC(AuraWindow)

public:
	AuraWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~AuraWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_AURA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
protected:
	std::vector<SEffectInfo> m_vtEffects;
public:
	CQuickList m_objEffectList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);
	void UpdateList();
	afx_msg void OnLvnEndlabeleditAuraEffects(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeAuragroupid();
	afx_msg void OnEnChangeAuraClienteffect();
};
