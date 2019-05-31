#pragma once

#include "ToolDef.h"
#include "MagicTypeHuman.h"
#include "MagicTypeNpc.h"
#include "QuickList.h"
#include "afxcmn.h"

USE_NS_AC;

// MagicWindow dialog

class MagicWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	struct SEffectInfo
	{
		SEffectInfo()
		{
			m_strEffectType = _T("-1");
			m_strEffectID = _T("-1");
			m_strEffectDes = _T("");
		}

		SEffectInfo(const CString& strType,const CString& strID,const CString& strDes)
		{
			m_strEffectType = strType;
			m_strEffectID = strID;
			m_strEffectDes = strDes;
		}

		CString m_strEffectType;
		CString m_strEffectID;
		CString m_strEffectDes;
	};

	DECLARE_DYNAMIC(MagicWindow)

public:
	MagicWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~MagicWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAGICTYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeMagicmagicbelong();
protected:
	MagicTypeHuman m_objMagicTypeHuman;
	MagicTypeNpc m_objMagicTypeNpc;
	std::vector<SEffectInfo> m_vtEffects;
public:
	CQuickList m_objEffectList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);
	void UpdateList();
	afx_msg void OnLvnEndlabeleditMagicEffects(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeMagicadditioneffect();
private:
	CString GetEffectDes(const CString& strEffectType,const CString& strEffectID);
public:
	afx_msg void OnEnChangeMagicmagicperformanceid();
	afx_msg void OnEnChangeMagictargetperformanceid();
};
