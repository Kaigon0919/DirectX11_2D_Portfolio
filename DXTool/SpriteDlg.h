#pragma once
#include "afxcmn.h"
#include"TabDlg.h"

// SpriteDlg 대화 상자입니다.

class Render2DSprite;
struct SpriteInfo
{
public:
	CString m_Path;
	CString m_FileName;
	bool m_bFile;
};


class SpriteDlg : public TabDlg
{
	DECLARE_DYNAMIC(SpriteDlg)

public:
	SpriteDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SpriteDlg();

protected:
	SPTR<Render2DSprite> m_ComRender;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SpriteDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	std::list<SpriteInfo*> m_List;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	virtual BOOL OnInitDialog();

	CTreeCtrl m_TreeCtrl;
	void SpriteLoader(const CString& _Folder, HTREEITEM _Parent);
	void SpriteFinder(const CString& _Folder, HTREEITEM _Parent);

	afx_msg void OnDestroy();
	afx_msg void OnTvnSelchangedSpritetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedLoad();
public:
	friend unsigned int __stdcall SpriteLoadThread(void*);
};
