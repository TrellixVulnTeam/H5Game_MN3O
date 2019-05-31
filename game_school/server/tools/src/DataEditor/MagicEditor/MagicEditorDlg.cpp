
// MagicEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "MagicEditorDlg.h"

#include "ToolExcel.h"
#include "ToolTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMagicEditorDlg 对话框




CMagicEditorDlg::CMagicEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMagicEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitialGlobalIDs();
}

void CMagicEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, m_objMainTab);
}

BEGIN_MESSAGE_MAP(CMagicEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, &CMagicEditorDlg::OnTcnSelchangeMainTab)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CMagicEditorDlg::OnEnChangeEditFind)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CMagicEditorDlg::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// CMagicEditorDlg 消息处理程序

BOOL CMagicEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	_tsetlocale(LC_ALL, _T(""));

	// 设置心跳，10ms一次
	::SetTimer(m_hWnd,1,10,NULL);

	// 初始化工具
	InitializeTool(_T("MagicEditor"));

	// 初始化主Tab
	InitializeTab();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMagicEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMagicEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMagicEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CWnd* CMagicEditorDlg::GetMainWnd()
{
	return this;
}

CWnd* CMagicEditorDlg::GetCurrentKeyWindow()
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("MagicType"))
		return m_objMagicWindow.GetDlgItem(IDC_MAGIC_ID);
	else if(strCurrentDB == _T("EffectCommon"))
		return m_objEffectCommonWindow.GetDlgItem(IDC_EFFECTCOMMON_commonID);
	else if(strCurrentDB == _T("EffectCollision"))
		return m_objEffectCollisionWindow.GetDlgItem(IDC_EFFECTCOLLISION_collisionID);
	else if(strCurrentDB == _T("EffectFlexible"))
		return m_objEffectFlexibleWindow.GetDlgItem(IDC_EFFECTFLEXIBLE_ID);
	else if(strCurrentDB == _T("EffectMotion"))
		return m_objEffectMotionWindow.GetDlgItem(IDC_EFFECTMOTION_motionID);
	else if(strCurrentDB == _T("Aura"))
		return m_objAuraWindow.GetDlgItem(IDC_AURA_ID);
	else if(strCurrentDB == _T("AuraEffect"))
		return m_objAuraEffectWindow.GetDlgItem(IDC_AURAEFFECT_ID);

	return NULL;
}

void CMagicEditorDlg::InitializeTab()
{
	m_objMainTab.InsertItem(0,_T("Magic"));
	m_objMainTab.InsertItem(1,_T("EffectCommon"));
	m_objMainTab.InsertItem(2,_T("EffectCollision"));
	m_objMainTab.InsertItem(3,_T("EffectFlexible"));
	m_objMainTab.InsertItem(4,_T("EffectMotion"));
	m_objMainTab.InsertItem(5,_T("Aura"));
	m_objMainTab.InsertItem(6,_T("AuraEffect"));

	m_nTabLastSel = 0;

	CRect rect;
	m_objMainTab.GetClientRect(&rect);
	ClientToScreen(&rect);
	rect.left -= 2;
	rect.top -= 4;

	m_objMagicWindow.Create(IDD_DIALOG_MAGICTYPE,&m_objMainTab);
	m_objEffectCommonWindow.Create(IDD_DIALOG_EFFECTCOMMON,&m_objMainTab);
	m_objEffectCollisionWindow.Create(IDD_DIALOG_EFFECTCOLLISION,&m_objMainTab);
	m_objEffectFlexibleWindow.Create(IDD_DIALOG_EFFECTFLEXIBLE,&m_objMainTab);
	m_objEffectMotionWindow.Create(IDD_DIALOG_EFFECTMOTION,&m_objMainTab);
	m_objAuraWindow.Create(IDD_DIALOG_AURA,&m_objMainTab);
	m_objAuraEffectWindow.Create(IDD_DIALOG_AURAEFFECT,&m_objMainTab);
	m_objMagicWindow.MoveWindow(&rect);
	m_objEffectCommonWindow.MoveWindow(&rect);
	m_objEffectCollisionWindow.MoveWindow(&rect);
	m_objEffectFlexibleWindow.MoveWindow(&rect);
	m_objEffectMotionWindow.MoveWindow(&rect);
	m_objAuraWindow.MoveWindow(&rect);
	m_objAuraEffectWindow.MoveWindow(&rect);

	m_objMagicWindow.ShowWindow(SW_SHOW);
	m_objEffectCommonWindow.ShowWindow(SW_HIDE);
	m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
	m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
	m_objEffectMotionWindow.ShowWindow(SW_HIDE);
	m_objAuraWindow.ShowWindow(SW_HIDE);
	m_objAuraEffectWindow.ShowWindow(SW_HIDE);

	SetCurrentDB(_T("MagicType"));
}

void CMagicEditorDlg::InitialGlobalIDs()
{
	ToolApp::_IDC_EDIT_TOTAL = IDC_EDIT_TOTAL;
	ToolApp::_IDC_MAIN_LOG = IDC_MAIN_LOG;
	ToolApp::_IDC_MAIN_TREE = IDC_MAIN_TREE;
}

void CMagicEditorDlg::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("MagicType"))
		m_objMagicWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("EffectCommon"))
		m_objEffectCommonWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("EffectCollision"))
		m_objEffectCollisionWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("EffectFlexible"))
		m_objEffectFlexibleWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("EffectMotion"))
		m_objEffectMotionWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("Aura"))
		m_objAuraWindow.OnLoadFromDB(mapValues);
	else if(strCurrentDB == _T("AuraEffect"))
		m_objAuraEffectWindow.OnLoadFromDB(mapValues);
}

void CMagicEditorDlg::OnSaveToDB(MapCNameToValueT& mapValues)
{
	CString strCurrentDB = GetCurrentDB();
	if(strCurrentDB == _T("MagicType"))
		m_objMagicWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("EffectCommon"))
		m_objEffectCommonWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("EffectCollision"))
		m_objEffectCollisionWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("EffectFlexible"))
		m_objEffectFlexibleWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("EffectMotion"))
		m_objEffectMotionWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("Aura"))
		m_objAuraWindow.OnSaveToDB(mapValues);
	else if(strCurrentDB == _T("AuraEffect"))
		m_objAuraEffectWindow.OnSaveToDB(mapValues);
}

void CMagicEditorDlg::OnTimer(UINT_PTR nIDEvent)
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

void CMagicEditorDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
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
		SetCurrentDB(_T("MagicType"));
		m_objMagicWindow.ShowWindow(SW_SHOW);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_nTabLastSel = 1;
		SetCurrentDB(_T("EffectCommon"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_SHOW);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_nTabLastSel = 2;
		SetCurrentDB(_T("EffectCollision"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_SHOW);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_nTabLastSel = 3;
		SetCurrentDB(_T("EffectFlexible"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_SHOW);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_nTabLastSel = 4;
		SetCurrentDB(_T("EffectMotion"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_SHOW);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 5:
		m_nTabLastSel = 5;
		SetCurrentDB(_T("Aura"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_SHOW);
		m_objAuraEffectWindow.ShowWindow(SW_HIDE);
		break;
	case 6:
		m_nTabLastSel = 6;
		SetCurrentDB(_T("AuraEffect"));
		m_objMagicWindow.ShowWindow(SW_HIDE);
		m_objEffectCommonWindow.ShowWindow(SW_HIDE);
		m_objEffectCollisionWindow.ShowWindow(SW_HIDE);
		m_objEffectFlexibleWindow.ShowWindow(SW_HIDE);
		m_objEffectMotionWindow.ShowWindow(SW_HIDE);
		m_objAuraWindow.ShowWindow(SW_HIDE);
		m_objAuraEffectWindow.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CMagicEditorDlg::OnEnChangeEditFind()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	KillTimer(3);
	SetTimer(3, 300, NULL);
}

void CMagicEditorDlg::OnBnClickedButtonFind()
{
	// TODO: Add your control notification handler code here
	CString str;
	((CEdit *)GetDlgItem(IDC_EDIT_FIND))->GetWindowText(str);

	ToolTree* pTree = GetCurrentTree();
	ACCHECK(pTree);
	pTree->FindNextItem(str);
}
