#pragma once


// DXWndView ���Դϴ�.

class DXWndView : public CView
{
	DECLARE_DYNCREATE(DXWndView)

protected:
	DXWndView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~DXWndView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


