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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_cxBorder = 1;
	m_cyBorder = 1;

	return CSplitterWnd::PreCreateWindow(cs);
}
