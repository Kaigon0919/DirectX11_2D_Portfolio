#pragma once
#include<Level.h>

// TabDlg 대화 상자입니다.

class TabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TabDlg)

public:
	TabDlg(UINT nID, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabDlg();

protected:
	SPTR<Level> TabLevel;
public:
	void SetLevel(SPTR<Level> level)
	{
		TabLevel = level;
	}

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
