
// DXTool.h : DXTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CDXToolApp:
// �� Ŭ������ ������ ���ؼ��� DXTool.cpp�� �����Ͻʽÿ�.
//

class CDXToolApp : public CWinApp
{
public:
	CDXToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	UINT  m_nAppLook;
	virtual BOOL OnIdle(LONG lCount);
};

extern CDXToolApp theApp;
