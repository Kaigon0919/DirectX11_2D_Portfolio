// PropertyView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DXTool.h"
#include "PropertyView.h"

// PropertyView

IMPLEMENT_DYNCREATE(PropertyView, CView)

PropertyView::PropertyView()
{

}

PropertyView::~PropertyView()
{
}

BEGIN_MESSAGE_MAP(PropertyView, CView)
END_MESSAGE_MAP()


// PropertyView �׸����Դϴ�.

void PropertyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// PropertyView �����Դϴ�.

#ifdef _DEBUG
void PropertyView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void PropertyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// PropertyView �޽��� ó�����Դϴ�.


BOOL PropertyView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	BOOL Result = CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	RECT rc;

	GetClientRect(&rc);
	m_Dlg.Create(IDD_PropertyDlg, this);
	m_Dlg.SetWindowPos(nullptr,rc.left,rc.top,rc.right-rc.left - 1,rc.bottom, SWP_NOZORDER);
	m_Dlg.ShowWindow(SW_SHOW);

	return Result;
}
