
// gen_csv.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGenCsvApp:
// �йش����ʵ�֣������ gen_csv.cpp
//

class CGenCsvApp : public CWinAppEx
{
public:
	CGenCsvApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGenCsvApp theApp;