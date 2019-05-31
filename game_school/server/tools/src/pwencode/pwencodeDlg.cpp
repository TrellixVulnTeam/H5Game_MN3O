
// pwencodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pwencode.h"
#include "pwencodeDlg.h"
#include "snappy/snappy.h"
#include "algorithm/pw_base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEncodeDlg �Ի���




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


// CEncodeDlg ��Ϣ�������

BOOL CEncodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEncodeDlg::OnPaint()
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
	openFileName.lpstrFilter = "�����ļ�\0*.*";
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
		MessageBox("û��ѡ���ļ�","����");
		return;
	}

	FILE* f = fopen(text,"rb+");
	if(f == NULL)
	{
		MessageBox("���ļ�ʧ��","����");
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
			MessageBox("����ʱ�ļ�ʧ��","����");
			return;
		}
		fwrite(encoded.c_str(),encoded.length(),1,f);
		fclose(f);

		CString str;
		str.Format("����̫��,�ѱ��浽�ļ� %s",filename);
		GetDlgItem(IDC_EDIT2)->SetWindowText(str);

		free(filename);
	}
	else
	{
		GetDlgItem(IDC_EDIT2)->SetWindowText(encoded.c_str());
	}
}
