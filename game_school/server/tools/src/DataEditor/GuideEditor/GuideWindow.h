#pragma once

#include "ToolDef.h"
#include "QuickList.h"
#include "afxcmn.h"
#include "d:\arpg\server\tools\src\dataeditor\toolutils\quicklist.h"
#include "d:\arpg\server\tools\src\dataeditor\toolutils\quicklist.h"

USE_NS_AC;

// GuideWindow dialog

class GuideWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	struct SItemInfo
	{
		SItemInfo()
		{
			m_strID = _T("-1");
			m_strDes = _T("");
		}

		SItemInfo(const CString& strID,const CString& strDes)
		{
			m_strID = strID;
			m_strDes = strDes;
		}

		CString m_strID;
		CString m_strDes;
	};

	DECLARE_DYNAMIC(GuideWindow)

public:
	GuideWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
protected:
	std::vector<SItemInfo> m_vtOpenConditionList;
	std::vector<SItemInfo> m_vtActiveCloseList;
protected:
	CQuickList m_objOpenConditionList;
	CQuickList m_objActiveCloseList;
public:
	afx_msg void OnLvnEndlabeleditGuideopencondition(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditGuideactiveclose(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);
	void UpdateOpenConditionList();
	void UpdateActiveCloseList();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeGuideprefixid();
	afx_msg void OnEnChangeGuidesuffixid();
//	afx_msg void OnCbnEditchangeGuidetriggertype1();
	afx_msg void OnCbnSelchangeGuidetriggertype1();
	afx_msg void OnCbnSelchangeGuidetriggertype2();
	afx_msg void OnCbnSelchangeGuidetriggertype3();
};
