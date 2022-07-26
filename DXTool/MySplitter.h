#pragma once

class MySplitter :	public CSplitterWnd
{
private:
	bool isLock;

public:
	void SetLock(bool is)
	{
		isLock = is;
	}
	void OnLock()
	{
		isLock = true;
	}
	void UnLock()
	{
		isLock = false;
	}

	int GetBoderSizeX() { return m_cxBorder; }
	int GetBoderSizeY() { return m_cyBorder; }

public:
	afx_msg void OnLButtonDown(UINT _nFlages, CPoint _Point);
	DECLARE_MESSAGE_MAP()
public:
	MySplitter();
	~MySplitter();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

