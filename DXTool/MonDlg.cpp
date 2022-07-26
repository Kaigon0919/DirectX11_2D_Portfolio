// MonDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DXTool.h"
#include "MonDlg.h"
#include "afxdialogex.h"
#include"MonDlg.h"
#include"MonScript.h"

// MonDlg ��ȭ �����Դϴ�.

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


// MonDlg �޽��� ó�����Դϴ�.


BOOL MonDlg::OnInitDialog()
{
	TabDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_LevelScript = TabLevel->CreateScript<MonScript>();
	for (int i = 0; i < MonType::Mon_Max; ++i)
	{
		wchar_t Arr[50];
		_itow_s((int)i, Arr, 10);

		CString Str = Arr;

		m_ListBox.AddString(Str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void MonDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void MonDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void MonDlg::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_LevelScript->Save();
}


void MonDlg::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_LevelScript->Load();
}


void MonDlg::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->SetType(m_ListBox.GetCurSel());
	UpdateData(FALSE);

}


void MonDlg::OnBnClickedMapload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_LevelScript->SpriteLoad();
}
