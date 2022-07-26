#pragma once
#include "afxcmn.h"
#include<vector>

// PropertyDlg 대화 상자입니다.

struct DlgInfo
{
public:
	bool isLevel;
	CString name;
	CDialogEx * pDlg;
public:
	DlgInfo() :isLevel(false), pDlg(nullptr) {}
};

class PropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PropertyDlg)

public:
	PropertyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~PropertyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PropertyDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangePropertytap(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CTabCtrl m_TabCtrl;
	std::vector<DlgInfo> m_TabInfo;
public:
	void ChangeTap(const wchar_t * name);
	void ChangeTap(const int idx);

public:
	void AllDlgHide();

public:
	void CreateTap(const wchar_t* name);

public:
	template<typename T>
	void CreateTap(const wchar_t* name, const int dlgID)
	{
		CreateTap<T>(name, true, dlgID);
	}


	template<typename T>
	void CreateTap(const wchar_t* name,const bool isLevel , const int dlgID)
	{
		m_TabCtrl.InsertItem((int)m_TabInfo.size(), name);

		SPTR<Level> levelPtr = nullptr;
		if (isLevel)
		{
			levelPtr = Level::CreateLevel(name);
		}

		T* newDlg = nullptr;
		if (-1 != dlgID)
		{
			newDlg = new T();
			newDlg->SetLevel(levelPtr);
			newDlg->Create(dlgID,&m_TabCtrl);
			newDlg->SetBackgroundColor(RGB(255, 255, 255), TRUE);
			newDlg->ShowWindow(SW_HIDE);
		}
		DlgInfo info;
		info.isLevel = isLevel;
		info.name = name;
		info.pDlg = (CDialogEx*)newDlg;
		m_TabInfo.push_back(info);
	}
	virtual BOOL OnInitDialog();
};
