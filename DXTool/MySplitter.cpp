#include "stdafx.h"
#include "MySplitter.h"


MySplitter::MySplitter() : isLock(false)
{
}


MySplitter::~MySplitter()
{
}

BEGIN_MESSAGE_MAP(MySplitter, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void MySplitter::OnLButtonDown(UINT _nFlages, CPoint _Point)
{
	if (false == isLock)
	{
		CSplitterWnd::OnLButtonDown(_nFlages, _Point);
	}
}

BOOL MySplitter::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_cxBorder = 1;
	m_cyBorder = 1;

	return CSplitterWnd::PreCreateWindow(cs);
}
