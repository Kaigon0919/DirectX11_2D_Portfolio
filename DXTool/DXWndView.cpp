// DXWndView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DXTool.h"
#include "DXWndView.h"
#include<InputManager.h>

// DXWndView

IMPLEMENT_DYNCREATE(DXWndView, CView)

DXWndView::DXWndView()
{

}

DXWndView::~DXWndView()
{
}

BEGIN_MESSAGE_MAP(DXWndView, CView)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DXWndView �׸����Դϴ�.

void DXWndView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// DXWndView �����Դϴ�.

#ifdef _DEBUG
void DXWndView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void DXWndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// DXWndView �޽��� ó�����Դϴ�.


BOOL DXWndView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	InputManager::SetMouseWHeel(zDelta);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
