#pragma once
#include"TabDlg.h"
#include "afxwin.h"


// MonDlg 대화 상자입니다.
class MonScript;
class MonDlg : public TabDlg
{
	DECLARE_DYNAMIC(MonDlg)

public:
	MonDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MonDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	SPTR<MonScript> m_LevelScript;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnLbnSelchangeList1();
	CListBox m_ListBox;
	afx_msg void OnBnClickedMapload();
};
