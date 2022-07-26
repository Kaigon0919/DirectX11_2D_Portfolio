#pragma once
#include<Level.h>

// TabDlg ��ȭ �����Դϴ�.

class TabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TabDlg)

public:
	TabDlg(UINT nID, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabDlg();

protected:
	SPTR<Level> TabLevel;
public:
	void SetLevel(SPTR<Level> level)
	{
		TabLevel = level;
	}

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
