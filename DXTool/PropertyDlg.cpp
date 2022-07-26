// PropertyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DXTool.h"
#include "PropertyDlg.h"
#include"SpriteDlg.h"
#include"AniDlg.h"
#include"MapDlg.h"
#include"MonDlg.h"
#include "afxdialogex.h"
#include<Level.h>


// PropertyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(PropertyDlg, CDialogEx)

PropertyDlg::PropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PropertyDlg, pParent)
{

}

PropertyDlg::~PropertyDlg()
{
	for (size_t i = 0; i < m_TabInfo.size(); i++)
	{
		if (nullptr != m_TabInfo[i].pDlg)
		{
			delete m_TabInfo[i].pDlg;
		}
	}
}

void PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PropertyTap, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(PropertyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PropertyDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_PropertyTap, &PropertyDlg::OnTcnSelchangePropertytap)
END_MESSAGE_MAP()


// PropertyDlg 메시지 처리기입니다.


void PropertyDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnCancel();
}


void PropertyDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void PropertyDlg::OnTcnSelchangePropertytap(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int SelectIdx = m_TabCtrl.GetCurSel();
	if (SelectIdx == -1)
	{
		return;
	}
	ChangeTap(SelectIdx);
}

void PropertyDlg::ChangeTap(const wchar_t * name)
{
	for (size_t i = 0; i < m_TabInfo.size(); i++)
	{
		if (m_TabInfo[i].name == name)
		{
			ChangeTap((int)i);
			return;
		}
	}
}

void PropertyDlg::ChangeTap(const int idx)
{
	m_TabCtrl.SetCurSel(idx);

	if (m_TabInfo[idx].isLevel)
	{
		Level::ChangeLevel(m_TabInfo[idx].name.GetString());
	}

	if (m_TabInfo[idx].pDlg)
	{
		AllDlgHide();

		m_TabInfo[idx].pDlg->ShowWindow(SW_SHOWDEFAULT);
	}
	else
	{
		AllDlgHide();
	}
}

void PropertyDlg::AllDlgHide()
{
	for (size_t i = 0; i < m_TabInfo.size(); i++)
	{
		if (nullptr != m_TabInfo[i].pDlg)
		{
			m_TabInfo[i].pDlg->ShowWindow(SW_HIDE);
		}
	}
}

void PropertyDlg::CreateTap(const wchar_t * name)
{
	m_TabCtrl.InsertItem((int)m_TabInfo.size(), name);

	DlgInfo info;
	info.isLevel = false;
	info.name = name;
	m_TabInfo.push_back(info);
}


BOOL PropertyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CreateTap<MapDlg>(L"Map", IDD_MapDlg);
	CreateTap<AniDlg>(L"Ani",IDD_AniDlg);
	//CreateTap<SpriteDlg>(L"Sprite",IDD_SpriteDlg); 
	CreateTap<MonDlg>(L"Mon", IDD_MONDLG);


	RECT rc;
	m_TabCtrl.GetClientRect(&rc);
	m_TabCtrl.AdjustRect(FALSE, &rc);



	for (size_t i = 0; i < m_TabInfo.size(); ++i)
	{
		m_TabInfo[i].pDlg->SetWindowPos(nullptr, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
	}

	ChangeTap(1);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
