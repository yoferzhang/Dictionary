
// Dictionary.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDictionaryApp: 
// �йش����ʵ�֣������ Dictionary.cpp
//

class CDictionaryApp : public CWinApp
{
public:
	CDictionaryApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDictionaryApp theApp;