// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__6E81449C_EFAC_45BD_A835_0DCD2B57292F__INCLUDED_)
#define AFX_CLIENTDLG_H__6E81449C_EFAC_45BD_A835_0DCD2B57292F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxsock.h> 
#include "afxwin.h"
#include "tinyxml.h"
#include <iostream>
#include <map>
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

	struct FileTransferThreadStruct
	{
		SOCKET  hSOCKET;
	}pfilesock;

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:

	CSocket aSocket;

	static	DWORD WINAPI ClientRecvThread(LPVOID Param);
	void	ShowWindowText(const CString& sText);
	
	long m_nMessageLines;
	afx_msg void OnBnClickedBtnConnect();
	BOOL ConnectServer();
// 	CEdit m_serverIPCtrl;
// 	CEdit m_serverPortCtrl;
// 	CButton m_btnCtrl;
	afx_msg void OnCbnSelchangeComboServer();
public:
	enum EConfigureType
	{
		ConfigurePwaccsrv = 0,
		ConfigurePwconnsrv,
		Configurepwctrlsrv,
		ConfigurePwdbsrv,
		ConfigureServer_0,
		ConfigureServer_1,
	};

public:

	CComboBox m_cbb_server;
	CComboBox m_cbb_file;
	CButton m_bn_save;

private:
	TiXmlDocument* m_doc;
	typedef std::map<int, std::string> CollectionConfigT;
	CollectionConfigT m_mConfig;

public:
	void InitCombo();
	void InitDate();
	void SaveDate();
	//void ShowConfigureInfo(int type);
	//void SaveConfigureInfo(int type);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__6E81449C_EFAC_45BD_A835_0DCD2B57292F__INCLUDED_)
