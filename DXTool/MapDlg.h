#pragma once
#include"TabDlg.h"
#include "afxwin.h"

// MapDlg 대화 상자입니다.
class MapDlgScript;
class MapDlg : public TabDlg
{
	DECLARE_DYNAMIC(MapDlg)

public:
	MapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MapDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnLbnSelchangeTilelist();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

private:
	SPTR<MapDlgScript> m_LevelScript;
public:
	CListBox m_TileList;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedLoadimage();
	afx_msg void OnEnChangeSpritename();
	CString m_SpriteName;
	int m_Mode;
	int m_GateMode;
	afx_msg void OnBnClickedTileMode();
	afx_msg void OnBnClickedWarpMode();
	afx_msg void OnBnClickedGatecreate();
	float m_GatePosX;
	float m_GatePosY;
	float m_GateScaleX;
	float m_GateScaleY;
	CString m_NextLevel;
	float m_GateNextPosX;
	float m_GateNextPosY;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedObjectMode();
public:
	static void NewUpdate();
private:
	static MapDlg* ptr;
public:
	CListBox m_ObjListBox;
	afx_msg void OnBnClickedObjDelete();
};
