// MonDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DXTool.h"
#include "MonDlg.h"
#include "afxdialogex.h"
#include"MonDlg.h"
#include"MonScript.h"

// MonDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(MonDlg, CDialogEx)

MonDlg::MonDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_MONDLG, pParent)
{

}

MonDlg::~MonDlg()
{
}

void MonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(MonDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MonDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MonDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SAVE, &MonDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &MonDlg::OnBnClickedLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &MonDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_MAPLOAD, &MonDlg::OnBnClickedMapload)
END_MESSAGE_MAP()


// MonDlg 메시지 처리기입니다.


BOOL MonDlg::OnInitDialog()
{
	TabDlg::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_LevelScript = TabLevel->CreateScript<MonScript>();
	for (int i = 0; i < MonType::Mon_Max; ++i)
	{
		wchar_t Arr[50];
		_itow_s((int)i, Arr, 10);

		CString Str = Arr;

		m_ListBox.AddString(Str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MonDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MonDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MonDlg::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_LevelScript->Save();
}


void MonDlg::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_LevelScript->Load();
}


void MonDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_LevelScript->SetType(m_ListBox.GetCurSel());
	UpdateData(FALSE);

}


void MonDlg::OnBnClickedMapload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_LevelScript->SpriteLoad();
}
