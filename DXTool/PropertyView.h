#pragma once
#include"PropertyDlg.h"

// PropertyView ���Դϴ�.

class PropertyView : public CView
{
	DECLARE_DYNCREATE(PropertyView)

protected:
	PropertyView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~PropertyView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	PropertyDlg m_Dlg;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};


