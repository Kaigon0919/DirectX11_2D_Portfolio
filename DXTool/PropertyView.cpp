// PropertyView.cpp : 구현 파일입니다.
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


// PropertyView 그리기입니다.

void PropertyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// PropertyView 진단입니다.

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


// PropertyView 메시지 처리기입니다.


BOOL PropertyView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BOOL Result = CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	RECT rc;

	GetClientRect(&rc);
	m_Dlg.Create(IDD_PropertyDlg, this);
	m_Dlg.SetWindowPos(nullptr,rc.left,rc.top,rc.right-rc.left - 1,rc.bottom, SWP_NOZORDER);
	m_Dlg.ShowWindow(SW_SHOW);

	return Result;
}
