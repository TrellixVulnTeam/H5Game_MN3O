
// MagicEditorDlg.h : 头文件
//

#pragma once

#include "ToolApp.h"
#include "afxcmn.h"

#include "MagicWindow.h"
#include "EffectCommonWindow.h"
#include "EffectCollisionWindow.h"
#include "EffectFlexibleWindow.h"
#include "EffectMotionWindow.h"

#include "AuraWindow.h"
#include "AuraEffectWindow.h"

// CMagicEditorDlg 对话框
class CMagicEditorDlg : public CDialog, public ToolApp
{
	PRE_TRANSLATE_MESSAGE
// 构造
public:
	CMagicEditorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAGICEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	MagicWindow m_objMagicWindow;
	EffectCommonWindow m_objEffectCommonWindow;
	EffectCollisionWindow m_objEffectCollisionWindow;
	EffectFlexibleWindow m_objEffectFlexibleWindow;
	EffectMotionWindow m_objEffectMotionWindow;

	AuraWindow m_objAuraWindow;
	AuraEffectWindow m_objAuraEffectWindow;
protected:
	void InitializeTab();
	void InitialGlobalIDs();
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnEnChangeEditFind();
	afx_msg void OnBnClickedButtonFind();
};
