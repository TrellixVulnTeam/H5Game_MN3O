
// GuideEditorDlg.h : header file
//

#pragma once

#include "ToolApp.h"
#include "afxcmn.h"

#include "GuideWindow.h"
#include "GuideConditionWindow.h"

USE_NS_AC;

// CGuideEditorDlg dialog
class CGuideEditorDlg : public CDialog, public ToolApp
{
	PRE_TRANSLATE_MESSAGE
// Construction
public:
	CGuideEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GUIDEEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual CWnd* GetMainWnd();
	virtual CWnd* GetCurrentKeyWindow();
protected:
	int m_nTabLastSel;
	CTabCtrl m_objMainTab;
	GuideWindow m_objGuideWindow;
	GuideConditionWindow m_objGuideConditionWindow;
protected:
	void InitializeTab();
	void InitialGlobalIDs();
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditFind();
	afx_msg void OnBnClickedButtonFind();
};
