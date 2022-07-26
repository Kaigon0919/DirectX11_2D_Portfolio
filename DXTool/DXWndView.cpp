// DXWndView.cpp : 구현 파일입니다.
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


// DXWndView 그리기입니다.

void DXWndView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// DXWndView 진단입니다.

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


// DXWndView 메시지 처리기입니다.


BOOL DXWndView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	InputManager::SetMouseWHeel(zDelta);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
