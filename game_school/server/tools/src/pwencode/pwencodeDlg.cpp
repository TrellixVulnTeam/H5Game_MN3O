
// pwencodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pwencode.h"
#include "pwencodeDlg.h"
#include "snappy/snappy.h"
#include "algorithm/pw_base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEncodeDlg 对话框




CEncodeDlg::CEncodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEncodeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CEncodeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CEncodeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CEncodeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEncodeDlg 消息处理程序

BOOL CEncodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEncodeDlg::OnPaint()
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
HCURSOR CEncodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEncodeDlg::OnBnClickedOk()
{
}

void CEncodeDlg::OnBnClickedButton3()
{
	char szFileName[MAX_PATH] = {0};
	OPENFILENAME openFileName={0};
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.nMaxFile = MAX_PATH;
	openFileName.lpstrFile = szFileName;
	openFileName.Flags = OFN_FILEMUSTEXIST;
	openFileName.lpstrFilter = "所有文件\0*.*";
	openFileName.nFilterIndex = 0;

	if(::GetOpenFileName(&openFileName))
	{
		this->GetDlgItem(IDC_EDIT1)->SetWindowText(szFileName);
	}
}

void CEncodeDlg::OnBnClickedButton1()
{
	CString text;
	this->GetDlgItem(IDC_EDIT1)->GetWindowText(text);

	if(text.GetLength() <= 0)
	{
		MessageBox("没有选择文件","错误");
		return;
	}

	FILE* f = fopen(text,"rb+");
	if(f == NULL)
	{
		MessageBox("打开文件失败","错误");
		return;
	}

	fseek(f,0,SEEK_END);
	long size = ftell(f);
	fseek(f,0,SEEK_SET);

	std::string buf;
	buf.resize(size);
	fread(&buf[0],buf.length(),1,f);
	fclose(f);

	std::string compressed;
	snappy::Compress(buf.c_str(),buf.length(),&compressed);

	std::string encoded;
	encoded = pwutils::base64_encode(compressed.c_str(),compressed.length());

	if(encoded.length() > 8192)
	{
		char* filename = tempnam(NULL,NULL);

		FILE* f = fopen(filename,"wb+");
		if(f == NULL)
		{
			free(filename);
			MessageBox("打开临时文件失败","错误");
			return;
		}
		fwrite(encoded.c_str(),encoded.length(),1,f);
		fclose(f);

		CString str;
		str.Format("数据太大,已保存到文件 %s",filename);
		GetDlgItem(IDC_EDIT2)->SetWindowText(str);

		free(filename);
	}
	else
	{
		GetDlgItem(IDC_EDIT2)->SetWindowText(encoded.c_str());
	}
}
