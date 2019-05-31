
// MagicEditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "MagicEditorDlg.h"

#include "ToolExcel.h"
#include "ToolTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMagicEditorDlg �Ի���




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


// CMagicEditorDlg ��Ϣ�������

BOOL CMagicEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	_tsetlocale(LC_ALL, _T(""));

	// ����������10msһ��
	::SetTimer(m_hWnd,1,10,NULL);

	// ��ʼ������
	InitializeTool(_T("MagicEditor"));

	// ��ʼ����Tab
	InitializeTab();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMagicEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		InfoMessageBox(_T("��ǰ״̬�����л�"));
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
