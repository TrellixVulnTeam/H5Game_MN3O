// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include <afxsock.h>  
#include <afxwin.h>
//#include "CommonFun.h"

 #include <Sensapi.h>
 #pragma comment(lib, "Sensapi.lib")
// #include <WinInet.h>
// #pragma comment(lib, "wininet")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEdit m_recvCtrl;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

DWORD  WinExecAndWait32(LPCTSTR lpszAppPath,  
									LPCTSTR lpParameters,  
									LPCTSTR lpszDirectory, 
									DWORD dwMilliseconds) 
{
	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize    = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask	= SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd        = NULL;
	ShExecInfo.lpVerb    = NULL;
	ShExecInfo.lpFile    = lpszAppPath;        
	ShExecInfo.lpParameters = lpParameters;    
	ShExecInfo.lpDirectory    = lpszDirectory;
	ShExecInfo.nShow    = SW_HIDE;	//SW_SHOW
	ShExecInfo.hInstApp = NULL;    
	ShellExecuteEx(&ShExecInfo);

	if ( ShExecInfo.hProcess == NULL)
		return 1;

	BOOL bIsWait = TRUE;
	if ( !bIsWait )
		return 0;

	if (WaitForSingleObject(ShExecInfo.hProcess, dwMilliseconds) == WAIT_TIMEOUT)
	{    
		TerminateProcess(ShExecInfo.hProcess, 0);
		return 1;   
	}

	DWORD dwExitCode;
	BOOL bOK = GetExitCodeProcess(ShExecInfo.hProcess, &dwExitCode);
	ASSERT(bOK);

	return dwExitCode;
}

/*
BOOL CheckNetIsOK(const CString sUpdateIP)
{
	//Judge Network is Connected
	int nCount = 1;
	do 
	{
		DWORD dw;
		if( IsNetworkAlive(&dw))
		{
			break;
		}
		else
		{
			Sleep(10000);
			CString sNetWorkConnect;
			sNetWorkConnect.Format("第%d次网络未成功连接, 10秒后重试", nCount);
			m_recvCtrl.SetWindowText(sNetWorkConnect);
			nCount++ ;
		}
	} while (nCount <4);

	if (nCount == 4)
	{
		m_recvCtrl.SetWindowText("网络连接失败, 共检测40秒");
		return FALSE;
	}

	DWORD n = WinExecAndWait32(_T("ping.exe"), sUpdateIP + " -n 2"/ *sCmdPara* /, NULL, 10000);
	if (n == 0)
	{
		return TRUE;
	}
	else
	{
		CString sNetWorkConnect;
		sNetWorkConnect.Format("网络连接正常, Ping:%s 失败, 请检测此IP对应的服务器是否正常工作", sUpdateIP);
		m_recvCtrl.SetWindowText(sNetWorkConnect);
		return FALSE;
	}
}*/


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
/*
	DDX_Control(pDX, IDC_EDIT1, m_recvCtrl);
	DDX_Control(pDX, IDC_EDIT_IP, m_serverIPCtrl);
	DDX_Control(pDX, IDC_EDIT_PORT, m_serverPortCtrl);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btnCtrl);*/



	DDX_Control(pDX, IDC_COMBO_SERVER, m_cbb_server);
	DDX_Control(pDX, IDC_COMBO_FILE, m_cbb_file);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bn_save);
/*
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_bn_load);

	DDX_Control(pDX, IDC_EDIT_NAME, m_edit_name);
	DDX_Control(pDX, IDC_EDIT_MYSQL_HOST, m_edit_mysql_host);
	DDX_Control(pDX, IDC_EDIT_MYSQL_USER, m_edit_mysql_user);
	DDX_Control(pDX, IDC_EDIT_MYSQL_PSWD, m_edit_mysql_pswd);
	DDX_Control(pDX, IDC_EDIT_MYSQL_DB, m_edit_mysql_db);
	DDX_Control(pDX, IDC_EDIT_LISTEN_ADDR, m_edit_listen_addr);
	DDX_Control(pDX, IDC_EDIT_CONNSRV_ADDR, m_edit_connsrv_addr);
	

	DDX_Control(pDX, IDC_EDIT_LISTEN_PORT, m_edit_listen_port);*/


}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BTN_CONNECT, &CClientDlg::OnBnClickedBtnConnect)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, &CClientDlg::OnCbnSelchangeComboServer)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CClientDlg::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_LOAD, &CClientDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	InitCombo();

	InitDate();

	m_doc = NULL;
	//m_bn_load.EnableWindow(TRUE);
	//m_bn_load.ShowWindow(FALSE);
	m_bn_save.EnableWindow(TRUE);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
void CClientDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strText;
	this->GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(strText);

	if (strText.IsEmpty())
	{
		return;
	}
	
	aSocket.Send(strText, strText.GetLength());

	char szRecValue[1024] = {0};
	int nRecLen = aSocket.Receive(szRecValue, 10240*2);
	if (nRecLen > 0)
	{
		CString sInfo,strEdit;
		sInfo.Format("%s",szRecValue);		
		ShowWindowText(sInfo);
	}
	else if (nRecLen == 0)
	{
		ShowWindowText("Clent Disconnect Server!");
	}
	else
	{
		CString sErrorMsg;
		sErrorMsg.Format("Recv Error Type : SOCKET_ERROR , ErrorCode : %d", ::GetLastError());
		ShowWindowText(sErrorMsg);
	}
}*/


/*
void CClientDlg::ShowWindowText(const CString& sText)
{
	int LineNum=m_recvCtrl.GetLineCount();
	if(LineNum > 100)								// 超过最大信息显示行数
	{
		m_recvCtrl.SetSel(0, -1);
		m_recvCtrl.Clear();							// 清空编辑框
	}	

	CTime RevTime = CTime::GetCurrentTime();
	CString Temp = RevTime.Format("[%Y/%m/%d %H:%M:%S]: ");

	CString strEdit;	
	m_recvCtrl.GetWindowText(strEdit);   
	m_recvCtrl.SetSel(strEdit.GetLength(), strEdit.GetLength());  
	m_recvCtrl.ReplaceSel(Temp + sText + "\n");
}*/


/*
void CClientDlg::OnBnClickedBtnConnect()
{
	// TODO: Add your control notification handler code here
	CString sValue;
	m_btnCtrl.GetWindowText(sValue);
	if (sValue.CompareNoCase("connect") == 0)
	{
		ConnectServer();
		m_btnCtrl.SetWindowText("Stop Connect");
	}
	else
	{
		aSocket.Close();
		m_btnCtrl.SetWindowText("Connect");
		ShowWindowText("Stop Connect Server!");
	}	
}*/


/*
BOOL CClientDlg::ConnectServer()
{
	CString sServerIP, sServerPort;
	m_serverIPCtrl.GetWindowText(sServerIP);
	m_serverPortCtrl.GetWindowText(sServerPort);

	if (sServerPort.IsEmpty() || sServerIP.IsEmpty())
	{
		ShowWindowText("Server IP And Port Are Not Empty!");
		return FALSE;
	}

	/ *
	if (!CheckNetIsOK(sServerIP))
		{
			ShowWindowText("网络连接失败，请检查网络设置");
			return FALSE;
		}* /
	
	
	ShowWindowText("Network is Connected!");
	AfxSocketInit();

	if(!aSocket.Create())
	{
		ShowWindowText("Creat Socket faild!");
		return FALSE;
	}

	if(aSocket.Connect(sServerIP, atoi(sServerPort)))
	{
		ShowWindowText("Connect Server Success!");
		return TRUE;
	}
	else
	{
		ShowWindowText("Connect Server Faild!");
		return FALSE;
	}
}*/


void CClientDlg::OnCbnSelchangeComboServer()
{
	// TODO: Add your control notification handler code here
	InitDate();
}

void CClientDlg::InitCombo()
{
	TiXmlDocument config("./config.xml");

	bool loadOkay = config.LoadFile();

	if (!loadOkay)
	{
		return;
	}

	TiXmlElement* rootElement = config.RootElement();
	assert(rootElement);

	TiXmlNode* serverNode = rootElement->FirstChild("server");

	bool bCur = true;
	while(serverNode)
	{
		int id = atoi(serverNode->FirstChildElement("id")->GetText());

		CString str = serverNode->FirstChildElement("name")->GetText();
		m_cbb_server.InsertString(id, str);

		str = serverNode->FirstChildElement("dir")->GetText();
		m_mConfig.insert(std::make_pair(id, str));

		serverNode = serverNode->NextSibling();

		if (bCur)
		{
			m_cbb_server.SetCurSel(id);
			bCur = false;
		}
		
	}

	int index = 0;
	m_cbb_file.InsertString(ConfigurePwaccsrv, (LPCTSTR)"pwaccsrv.xml");
	m_cbb_file.InsertString(ConfigurePwconnsrv, (LPCTSTR)"pwconnsrv.xml");
	m_cbb_file.InsertString(Configurepwctrlsrv, (LPCTSTR)"pwctrlsrv.xml");
	m_cbb_file.InsertString(ConfigurePwdbsrv, (LPCTSTR)"pwdbsrv.xml");
	m_cbb_file.InsertString(ConfigureServer_0, (LPCTSTR)"server_0.xml");

	m_cbb_file.SetCurSel(0);
	m_cbb_file.EnableWindow(FALSE);
	
}

void CClientDlg::InitDate()
{
	CString strFile;
	CString configure;
	bool loadOkay = false;

	m_cbb_file.GetWindowText(strFile);

	CollectionConfigT::iterator iter = m_mConfig.find(m_cbb_server.GetCurSel());
	if (iter != m_mConfig.end())
	{
		for (int index = 0; index < m_cbb_file.GetCount(); index++)
		{
			m_cbb_file.GetLBText(index, strFile);
			configure.Format("%s%s", iter->second.c_str(), strFile);

			TiXmlDocument doc(configure);
			
			loadOkay = doc.LoadFile();
			if (loadOkay)
			{
				TiXmlElement* rootElement = doc.RootElement();
				assert(rootElement);

				switch(index)
				{
					case ConfigurePwaccsrv:
						{
							((CEdit *)GetDlgItem(IDC_EDIT_PWACCSRV_ADDR))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_HOST))->SetWindowText(rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("host")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_USER))->SetWindowText(rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("user")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_PSWD))->SetWindowText(rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("pswd")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_DB))->SetWindowText(rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("db")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_PORT))->SetWindowText(rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("port")->GetText());
						}
						break;
					case ConfigurePwconnsrv:
						{
							((CEdit *)GetDlgItem(IDC_EDIT_PWCONNSRV_ADDR2))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
						}
						break;
					case Configurepwctrlsrv:
						{
							((CEdit *)GetDlgItem(IDC_EDIT_PWCTRLSRV_ADDR))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
						}
						break;
					case ConfigurePwdbsrv:
						{
							((CEdit *)GetDlgItem(IDC_EDIT_PWDBSRV_ADDR))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_HOST))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("host")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_USER))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("user")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_PSWD))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("pswd")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_DB))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("db")->GetText());
							((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_PORT))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("port")->GetText());
						}
						break;
					case ConfigureServer_0:
						{
							((CEdit *)GetDlgItem(IDC_EDIT_WORLDSRV0_ADDR))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
						}
						break;
				}
			}
		}
		
	}	
		
}

void CClientDlg::SaveDate()
{
	CString strFile;
	CString configure;
	CString str;
	bool loadOkay = false;

	m_cbb_file.GetWindowText(strFile);

	CollectionConfigT::iterator iter = m_mConfig.find(m_cbb_server.GetCurSel());
	if (iter != m_mConfig.end())
	{
		for (int index = 0; index < m_cbb_file.GetCount(); index++)
		{
			m_cbb_file.GetLBText(index, strFile);
			configure.Format("%s%s", iter->second.c_str(), strFile);

			TiXmlDocument doc(configure);

			loadOkay = doc.LoadFile();
			if (loadOkay)
			{
				TiXmlElement* rootElement = doc.RootElement();
				assert(rootElement);

				switch(index)
				{
					case ConfigurePwaccsrv:
						{
							{
								TiXmlNode* node = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWACCSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("host");
								((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_HOST))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("user");
								((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_USER))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("pswd");
								((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_PSWD))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("db");
								((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_DB))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwaccsrv")->FirstChildElement("mysql")->FirstChildElement("port");
								((CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT_DB_PORT))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{		
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCONNSRV_ADDR2))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}
							
						}
						break;
					case ConfigurePwconnsrv:
						{
							{
								TiXmlNode* node = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCONNSRV_ADDR2))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}
						}
						break;
					case Configurepwctrlsrv:
						{
							{
								TiXmlNode* node = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCTRLSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWDBSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCONNSRV_ADDR2))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWACCSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}
						}
						break;
					case ConfigurePwdbsrv:
						{
							{
								TiXmlNode* node = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWDBSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("host");
								((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_HOST))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("user");
								((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_USER))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("pswd");
								((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_PSWD))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("db");
								((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_DB))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("port");
								((CEdit *)GetDlgItem(IDC_EDIT_CHARACTER_DB_PORT))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}
						}
						break;
					case ConfigureServer_0:
						{
							{
								TiXmlNode* node = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
								((CEdit *)GetDlgItem(IDC_EDIT_WORLDSRV0_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWDBSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCTRLSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}

							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWCONNSRV_ADDR2))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}


							{
								TiXmlNode* node = rootElement->FirstChildElement("nodes")->FirstChildElement("node4")->FirstChildElement("addr");
								((CEdit *)GetDlgItem(IDC_EDIT_PWACCSRV_ADDR))->GetWindowText(str);
								TiXmlText newText(str);
								node->ReplaceChild(node->FirstChild(), newText);
							}
						}
						break;
				}
				doc.SaveFile();
			}
		}
	}
}

void CClientDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here

	SaveDate();
/*
	SaveConfigureInfo(m_cbb_file.GetCurSel());
	m_doc->SaveFile();
	delete m_doc;
	m_doc = NULL;
	m_bn_load.EnableWindow(TRUE);
	m_bn_save.EnableWindow(FALSE);
	m_cbb_file.EnableWindow(TRUE);
	m_cbb_server.EnableWindow(TRUE);*/

}

/*
void CClientDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here

	CString strFile;
	CString configure;

	m_cbb_file.GetWindowText(strFile);

	CollectionConfigT::iterator iter = m_mConfig.find(m_cbb_server.GetCurSel());
	if (iter != m_mConfig.end())
	{
		configure.Format("%s%s", iter->second.c_str(), strFile);
	}
	

	if (m_doc != NULL)
	{
		delete m_doc;
	}
	
	m_doc = new TiXmlDocument(configure);
	bool loadOkay = m_doc->LoadFile();

	if (!loadOkay)
	{
		printf( "Could not load test file %s. Error='%s'. Exiting.\n", configure, m_doc->ErrorDesc() );
		return;
	}
	else
	{
		ShowConfigureInfo(m_cbb_file.GetCurSel());
	}

//	m_bn_load.EnableWindow(FALSE);
	m_bn_save.EnableWindow(TRUE);
	m_cbb_file.EnableWindow(FALSE);
	m_cbb_server.EnableWindow(FALSE);

}*/


/*
void CClientDlg::ShowConfigureInfo(int type )
{

	if (m_doc == NULL)
	{
		return;
	}

	TiXmlElement* rootElement = m_doc->RootElement();
	TiXmlElement* communicatorElement = NULL;
	TiXmlElement* pwaccsrvElement = NULL;
	TiXmlElement* mysqlElement = NULL;

	TiXmlElement* hostElement = NULL;
	TiXmlElement* userElement = NULL;
	TiXmlElement* pswdElement = NULL;
	TiXmlElement* dbElement = NULL;
	TiXmlElement* listen_addrElement = NULL;

	if (rootElement)
	{
		TiXmlElement* nameElement = rootElement->FirstChildElement("name");
		m_edit_name.SetWindowText(nameElement->GetText());

		switch(type)
		{
			case ConfigurePwaccsrv:
				{
					pwaccsrvElement = rootElement->FirstChildElement("pwaccsrv");
					assert(pwaccsrvElement);

					mysqlElement = pwaccsrvElement->FirstChildElement("mysql");
					assert(mysqlElement);

					hostElement = mysqlElement->FirstChildElement("host");
					assert(hostElement);
					m_edit_mysql_host.SetWindowText(hostElement->GetText());

					userElement = mysqlElement->FirstChildElement("user");
					assert(userElement);
					m_edit_mysql_user.SetWindowText(userElement->GetText());

					pswdElement = mysqlElement->FirstChildElement("pswd");
					assert(pswdElement);
					m_edit_mysql_pswd.SetWindowText(pswdElement->GetText());

					dbElement = mysqlElement->FirstChildElement("db");
					assert(dbElement);
					m_edit_mysql_db.SetWindowText(dbElement->GetText());

					communicatorElement = rootElement->FirstChildElement("communicator");
					assert(communicatorElement);

					listen_addrElement = communicatorElement->FirstChildElement("listen_addr");
					assert(listen_addrElement);
					m_edit_listen_addr.SetWindowText(listen_addrElement->GetText());

					m_edit_connsrv_addr.SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr")->GetText());

				}
				break;

			case ConfigurePwconnsrv:
				m_edit_listen_port.SetWindowText( rootElement->FirstChildElement("game")->FirstChildElement("listen_port")->GetText());
				break;
			case Configurepwctrlsrv:
				{
					((CEdit *)GetDlgItem(IDC_EDIT_SIMPL_ENTRANCE))->SetWindowText(rootElement->FirstChildElement("simpl_entrance")->FirstChildElement("port")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_PERFORMANCE_HTTP))->SetWindowText(rootElement->FirstChildElement("performance_http")->FirstChildElement("port")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_SQLITEDB_PATH))->SetWindowText(rootElement->FirstChildElement("sqlitedb_path")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DBSRV_ADDR))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_CONNSRV_ADDR1))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_ACCSRV_ADDR))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr")->GetText());					
					
				}
				break;
			case ConfigurePwdbsrv:
				{				
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR1))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DB_HOST))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("host")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DB_USER))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("user")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DB_NAME))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("db")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DB_PSWD))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("pswd")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DB_PORT))->SetWindowText(rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("port")->GetText());
				}															
				break;
			case ConfigureServer_0:
				{
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR2))->SetWindowText(rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_DBSRV_ADDR1))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_CTRL_ADDR))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_CONNSRV_ADDR2))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr")->GetText());
					((CEdit *)GetDlgItem(IDC_EDIT_ACCSRV_ADDR1))->SetWindowText(rootElement->FirstChildElement("nodes")->FirstChildElement("node4")->FirstChildElement("addr")->GetText());																													
				}
				break;

		}

	}
	

	
}*/


/*
void CClientDlg::SaveConfigureInfo( int type )
{
	if (m_doc == NULL)
	{
		return;
	}

	TiXmlElement* rootElement = m_doc->RootElement();
	TiXmlElement* pwaccsrvElement = NULL;
	TiXmlElement* mysqlElement = NULL;
	TiXmlElement* communicatorElement = NULL;
	TiXmlNode* hostNode = NULL;
	TiXmlNode* userNode = NULL;
	TiXmlNode* pswdNode = NULL;
	TiXmlNode* dbNode = NULL;
	TiXmlNode* listenAddrNode = NULL;
	TiXmlNode* connsrvAddrNode = NULL;

	TiXmlNode* connsrvListenAddr = NULL;
	CString str;

	switch(type)
	{
		case ConfigurePwaccsrv:
			{
				pwaccsrvElement = rootElement->FirstChildElement("pwaccsrv");
				assert(pwaccsrvElement);

				mysqlElement = pwaccsrvElement->FirstChildElement("mysql");
				assert(mysqlElement);

				communicatorElement =  rootElement->FirstChildElement("communicator");
				assert(communicatorElement);

				{
					hostNode = mysqlElement->FirstChild("host");
					assert(hostNode);
					TiXmlElement* tmpElement =hostNode->ToElement();				
					m_edit_mysql_host.GetWindowText(str);
					TiXmlText newText(str);
					tmpElement->ReplaceChild(tmpElement->FirstChild(), newText);
				}
				
				{
					userNode = mysqlElement->FirstChildElement("user");
					assert(userNode);
					m_edit_mysql_user.GetWindowText(str);
					TiXmlText newText(str);
					userNode->ReplaceChild(userNode->FirstChild(), newText);
				}
				{
					pswdNode = mysqlElement->FirstChildElement("pswd");
					assert(pswdNode);
					m_edit_mysql_pswd.GetWindowText(str);
					TiXmlText newText(str);
					pswdNode->ReplaceChild(pswdNode->FirstChild(), newText);
				}
				
				{
					dbNode = mysqlElement->FirstChildElement("db");
					assert(dbNode);
					m_edit_mysql_db.GetWindowText(str);
					TiXmlText newText(str);
					dbNode->ReplaceChild(dbNode->FirstChild(), newText);
				}

				{
					listenAddrNode = communicatorElement->FirstChildElement("listen_addr");
					m_edit_listen_addr.GetWindowText(str);
					TiXmlText newText(str);
					listenAddrNode->ReplaceChild(listenAddrNode->FirstChild(), newText);
				}

				{
					connsrvAddrNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
					m_edit_connsrv_addr.GetWindowText(str);
					TiXmlText newText(str);
					connsrvAddrNode->ReplaceChild(connsrvAddrNode->FirstChild(), newText);
				}
			}

			break;
		case ConfigurePwconnsrv:
			{
				{
					connsrvListenAddr = rootElement->FirstChildElement("game")->FirstChildElement("listen_port");
					m_edit_listen_port.GetWindowText(str);
					TiXmlText newText(str);
					connsrvListenAddr->ReplaceChild(connsrvListenAddr->FirstChild(), newText);
				}
				
			}
			break;
		case Configurepwctrlsrv:
			{
				{
					TiXmlNode* simpleEntranceNode = rootElement->FirstChildElement("simpl_entrance")->FirstChildElement("port");
					((CEdit *)GetDlgItem(IDC_EDIT_SIMPL_ENTRANCE))->GetWindowText(str);
					TiXmlText newText(str);
					simpleEntranceNode->ReplaceChild(simpleEntranceNode->FirstChild(), newText);
				}



				{
					TiXmlNode* httpNode = rootElement->FirstChildElement("performance_http")->FirstChildElement("port");
					((CEdit *)GetDlgItem(IDC_EDIT_PERFORMANCE_HTTP))->GetWindowText(str);
					TiXmlText newText(str);
					httpNode->ReplaceChild(httpNode->FirstChild(), newText);
				}

				{
					TiXmlNode* communicatorNode = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR))->GetWindowText(str);
					TiXmlText newText(str);
					communicatorNode->ReplaceChild(communicatorNode->FirstChild(), newText);
				}

				{
					TiXmlNode* sqlitedbNode = rootElement->FirstChildElement("sqlitedb_path");
					((CEdit *)GetDlgItem(IDC_EDIT_SQLITEDB_PATH))->GetWindowText(str);
					TiXmlText newText(str);
					sqlitedbNode->ReplaceChild(sqlitedbNode->FirstChild(), newText);
				}


				{
					TiXmlNode* dbsrvNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_DBSRV_ADDR))->GetWindowText(str);
					TiXmlText newText(str);
					dbsrvNode->ReplaceChild(dbsrvNode->FirstChild(), newText);
				}

				{
					TiXmlNode* connsrvNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_CONNSRV_ADDR1))->GetWindowText(str);
					TiXmlText newText(str);
					connsrvNode->ReplaceChild(connsrvNode->FirstChild(), newText);
				}

				{
					TiXmlNode* accsrvNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_ACCSRV_ADDR))->GetWindowText(str);
					TiXmlText newText(str);
					accsrvNode->ReplaceChild(accsrvNode->FirstChild(), newText);
				}
			}
			break;
		case ConfigurePwdbsrv:
			{

				{
					TiXmlNode* communicatorNode = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR1))->GetWindowText(str);
					TiXmlText newText(str);
					communicatorNode->ReplaceChild(communicatorNode->FirstChild(), newText);
				}

				{
					TiXmlNode* hostNode = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("host");
					((CEdit *)GetDlgItem(IDC_EDIT_DB_HOST))->GetWindowText(str);
					TiXmlText newText(str);
					hostNode->ReplaceChild(hostNode->FirstChild(), newText);
				}

				{
					TiXmlNode* userNode = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("user");
					((CEdit *)GetDlgItem(IDC_EDIT_DB_USER))->GetWindowText(str);
					TiXmlText newText(str);
					userNode->ReplaceChild(userNode->FirstChild(), newText);
				}

				{
					TiXmlNode* pwdbNode = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("db");
					((CEdit *)GetDlgItem(IDC_EDIT_DB_NAME))->GetWindowText(str);
					TiXmlText newText(str);
					pwdbNode->ReplaceChild(pwdbNode->FirstChild(), newText);
				}

				{
					TiXmlNode* pswdNode = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("pswd");
					((CEdit *)GetDlgItem(IDC_EDIT_DB_PSWD))->GetWindowText(str);
					TiXmlText newText(str);
					pswdNode->ReplaceChild(pswdNode->FirstChild(), newText);
				}

				{
					TiXmlNode* portNode = rootElement->FirstChildElement("pwdbsrv")->FirstChildElement("mysql")->FirstChildElement("port");
					((CEdit *)GetDlgItem(IDC_EDIT_DB_PORT))->GetWindowText(str);
					TiXmlText newText(str);
					portNode->ReplaceChild(portNode->FirstChild(), newText);
				}
			}
			break;
		case ConfigureServer_0:
			{
				{
					TiXmlNode* communicatorNode = rootElement->FirstChildElement("communicator")->FirstChildElement("listen_addr");
					((CEdit *)GetDlgItem(IDC_EDIT_COMMUNICATOR2))->GetWindowText(str);
					TiXmlText newText(str);
					communicatorNode->ReplaceChild(communicatorNode->FirstChild(), newText);
				}

				{
					TiXmlNode* dbNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node1")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_DBSRV_ADDR1))->GetWindowText(str);
					TiXmlText newText(str);
					dbNode->ReplaceChild(dbNode->FirstChild(), newText);
				}

				{
					TiXmlNode* ctrlNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node2")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_CTRL_ADDR))->GetWindowText(str);
					TiXmlText newText(str);
					ctrlNode->ReplaceChild(ctrlNode->FirstChild(), newText);
				}

				{
					TiXmlNode* connsrvNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node3")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_CONNSRV_ADDR2))->GetWindowText(str);
					TiXmlText newText(str);
					connsrvNode->ReplaceChild(connsrvNode->FirstChild(), newText);
				}

				{
					TiXmlNode* accsrvNode = rootElement->FirstChildElement("nodes")->FirstChildElement("node4")->FirstChildElement("addr");
					((CEdit *)GetDlgItem(IDC_EDIT_ACCSRV_ADDR1))->GetWindowText(str);
					TiXmlText newText(str);
					accsrvNode->ReplaceChild(accsrvNode->FirstChild(), newText);
				}
			}
			break;
	}
}*/

