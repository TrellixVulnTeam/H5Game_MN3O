
// MagicEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMagicEditorApp:
// �йش����ʵ�֣������ MagicEditor.cpp
//

class CMagicEditorApp : public CWinAppEx
{
public:
	CMagicEditorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMagicEditorApp theApp;