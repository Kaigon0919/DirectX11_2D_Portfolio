#pragma once
#include"TabDlg.h"
#include "afxwin.h"

// AniDlg 대화 상자입니다.
class AniScript;
class Com2DFrameAni;
class Col2DRect;
struct AniEventData;
class AniDlg : public TabDlg
{
	DECLARE_DYNAMIC(AniDlg)

public:
	AniDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AniDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AniDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
private:
	SPTR<AniScript> script;
	SPTR<Col2DRect> RIGHTCOL;
public:
	void TestEventOn(void*);
	void TestEventOff(void*);
	CString m_AniName;
	UINT m_StartFrame;
	UINT m_EndFrame;
	float m_DefTime;
	UINT m_EStartFrame;
	UINT m_EEndFrame;
	float m_EPosX;
	float m_EPosY;
	float m_EScaleX;
	float m_EScaleY;
	afx_msg void OnLbnSelchangeAnilist();
	CListBox m_AniList;
	afx_msg void OnBnClickedAnicreate();
	afx_msg void OnBnClickedEcreate();
	afx_msg void OnBnClickedAnidelete();
	BOOL m_bLoop;
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

private:
	std::list<AniEventData*> EventDataList;
public:
	void EventDataClear();
	CEdit m_AniNameCtrol;
	CButton m_AniCreateButton;
	afx_msg void OnBnClickedSpriteLoad();
	afx_msg void OnBnClickedSubPosLoad();
	CButton m_AniDeleteButton;
	CButton m_EventCreateButton;
	CButton m_EventDeleteButton;
	CButton m_SaveButton;
	CButton m_LoadButton;
	afx_msg void OnLbnSelchangeList1();
	CListBox m_EventListBox;
	afx_msg void OnBnClickedEdelete();
	int m_PivotX;
	int m_PivotY;
	afx_msg void OnEnChangePivotx();
	afx_msg void OnEnChangePivoty();
	afx_msg void OnBnClickedCheck1();
	BOOL m_bShowAxis;
};
