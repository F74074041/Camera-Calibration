
// HW2_2.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CHW2_2App: 
// �аѾ\��@�����O�� HW2_2.cpp
//

class CHW2_2App : public CWinApp
{
public:
	CHW2_2App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CHW2_2App theApp;