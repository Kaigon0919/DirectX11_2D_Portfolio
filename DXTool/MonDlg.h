#pragma once
#include"TabDlg.h"
#include "afxwin.h"


// MonDlg ��ȭ �����Դϴ�.
class MonScript;
class MonDlg : public TabDlg
{
	DECLARE_DYNAMIC(MonDlg)

public:
	MonDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MonDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
