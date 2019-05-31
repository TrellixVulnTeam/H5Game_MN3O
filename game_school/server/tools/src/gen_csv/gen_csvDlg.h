
// gen_csvDlg.h : 头文件
//

#pragma once

#include <string>
#include <vector>
#include "BasicExcel.hpp"
#include "afxwin.h"

using namespace YExcel;

// CGenCsvDlg 对话框
class CGenCsvDlg : public CDialog
{
// 构造
public:
	CGenCsvDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GEN_CSV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
