
// GuideEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuideEditor.h"
#include "GuideEditorDlg.h"

#include "ToolExcel.h"
#include "ToolTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGuideEditorDlg dialog




CGuideEditorDlg::CGuideEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuideEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitialGlobalIDs();
}

void CGuideEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, m_objMainTab);
}

BEGIN_MESSAGE_MAP(CGuideEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, &CGuideEditorDlg::OnTcnSelchangeMainTab)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CGuideEditorDlg::OnEnChangeEditFind)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CGuideEditorDlg::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// CGuideEditorDlg message handlers

BOOL CGuideEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	_tsetlocale(LC_ALL, _T(""));

	// 设置心跳，10ms一次
	::SetTimer(m_hWnd,1,10,NULL);

	// 初始化工具
	InitializeTool(_T("GuideEditor"));

	// 初始化主Tab
	InitializeTab();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuideEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuideEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuideEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CWnd* CGuideEditorDlg::GetMainWnd()
{
	return this;
}

CWnd* CGuideEditorDlg::GetCurrentKeyWindow()
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("Guide"))
		return m_objGuideWindow.GetDlgItem(IDC_GUIDE_ID);
	else if(strCurrentDB == _T("GuideCondition"))
		return m_objGuideConditionWindow.GetDlgItem(IDC_GUIDECONDITION_ID);

	return NULL;
}

void CGuideEditorDlg::InitializeTab()
{
	m_objMainTab.InsertItem(0,_T("指引"));
	m_objMainTab.InsertItem(1,_T("开启条件"));

	m_nTabLastSel = 0;

	CRect rect;
	m_objMainTab.GetClientRect(&rect);
	ClientToScreen(&rect);
	rect.left -= 2;
	rect.top -= 4;

	m_objGuideWindow.Create(IDD_DIALOG_GUIDE,&m_objMainTab);
	m_objGuideConditionWindow.Create(IDD_DIALOG_GUIDECONDITION,&m_objMainTab);
	m_objGuideWindow.MoveWindow(&rect);
	m_objGuideConditionWindow.MoveWindow(&rect);

	m_objGuideWindow.ShowWindow(SW_SHOW);
	m_objGuideConditionWindow.ShowWindow(SW_HIDE);

	SetCurrentDB(_T("Guide"));
}

void CGuideEditorDlg::InitialGlobalIDs()
{
	ToolApp::_IDC_EDIT_TOTAL = IDC_EDIT_TOTAL;
	ToolApp::_IDC_MAIN_LOG = IDC_MAIN_LOG;
	ToolApp::_IDC_MAIN_TREE = IDC_MAIN_TREE;
}

void CGuideEditorDlg::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("Guide"))
		m_objGuideWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("GuideCondition"))
		m_objGuideConditionWindow.OnLoadFromDB(mapValues);
}

void CGuideEditorDlg::OnSaveToDB(MapCNameToValueT& mapValues)
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("Guide"))
		m_objGuideWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("GuideCondition"))
		m_objGuideConditionWindow.OnSaveToDB(mapValues);
}

void CGuideEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent == 1)
	{
		this->Update();
	}
	else if(nIDEvent == 3)
	{
		KillTimer(3);
		CString str;
		((CEdit *)GetDlgItem(IDC_EDIT_FIND))->GetWindowText(str);

		ToolTree* pTree = GetCurrentTree();
		ACCHECK(pTree);

		pTree->ResetLastFoundItem();
		pTree->FindNextItem(str);
	}

	__super::OnTimer(nIDEvent);
}

void CGuideEditorDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if(IsNewing())
	{
		m_objMainTab.SetCurSel(m_nTabLastSel);
		InfoMessageBox(_T("当前状态不能切换"));
		return;
	}

	switch(m_objMainTab.GetCurSel())
	{
	case 0:
		m_nTabLastSel = 0;
		SetCurrentDB(_T("Guide"));
		m_objGuideWindow.ShowWindow(SW_SHOW);
		m_objGuideConditionWindow.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_nTabLastSel = 1;
		SetCurrentDB(_T("GuideCondition"));
		m_objGuideWindow.ShowWindow(SW_HIDE);
		m_objGuideConditionWindow.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CGuideEditorDlg::OnEnChangeEditFind()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	KillTimer(3);
	SetTimer(3, 300, NULL);
}

void CGuideEditorDlg::OnBnClickedButtonFind()
{
	// TODO: Add your control notification handler code here
	CString str;
	((CEdit *)GetDlgItem(IDC_EDIT_FIND))->GetWindowText(str);

	ToolTree* pTree = GetCurrentTree();
	ACCHECK(pTree);
	pTree->FindNextItem(str);
}
