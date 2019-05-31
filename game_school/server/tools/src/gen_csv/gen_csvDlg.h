
// gen_csvDlg.h : ͷ�ļ�
//

#pragma once

#include <string>
#include <vector>
#include "BasicExcel.hpp"
#include "afxwin.h"

using namespace YExcel;

// CGenCsvDlg �Ի���
class CGenCsvDlg : public CDialog
{
// ����
public:
	CGenCsvDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GEN_CSV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_strServerDir;
public:
	void Generate(const std::string& name,const std::string& file,const std::string& hpp_file,const std::string& cpp_file,const std::string& csv_file);
	void GenerateHpp(BasicExcelWorksheet* sheet,const std::string& hpp_file,const std::string& name);
	void GenerateCpp(BasicExcelWorksheet* sheet,const std::string& cpp_file,const std::string& name);
	void GenerateCsvHeader(BasicExcelWorksheet* sheet,CFile& csvfile);
	void GenerateCsv(BasicExcelWorksheet* sheet,CFile& csvfile);
	CListBox m_ctrlLogs;
};
