// MapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DXTool.h"
#include "MapDlg.h"
#include "afxdialogex.h"
#include"MapDlgScript.h"
#include<Camera.h>
// MapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(MapDlg, CDialogEx)

MapDlg* MapDlg::ptr = nullptr;;

MapDlg::MapDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_MapDlg, pParent)
	, m_SpriteName(_T(""))
	, m_Mode(0)
	, m_GateMode(0)
	, m_GatePosX(0)
	, m_GatePosY(0)
	, m_GateScaleX(0)
	, m_GateScaleY(0)
	, m_NextLevel(_T(""))
	, m_GateNextPosX(0)
	, m_GateNextPosY(0)
{

}

MapDlg::~MapDlg()
{
}

void MapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TileList, m_TileList);
	DDX_Text(pDX, IDC_SPRITENAME, m_SpriteName);
	DDX_Radio(pDX, IDC_RADIO1, m_Mode);
	DDX_Radio(pDX, IDC_RADIO3, m_GateMode);
	DDX_Text(pDX, IDC_GATEPOSX, m_GatePosX);
	DDX_Text(pDX, IDC_GATEPOSY, m_GatePosY);
	DDX_Text(pDX, IDC_GATESCALEX, m_GateScaleX);
	DDX_Text(pDX, IDC_GATESCALEY, m_GateScaleY);
	DDX_Text(pDX, IDC_GATENEXTLEVEL, m_NextLevel);
	DDX_Text(pDX, IDC_GATENEXTPOSX, m_GateNextPosX);
	DDX_Text(pDX, IDC_GATENEXTPOSY, m_GateNextPosY);
	DDX_Control(pDX, IDC_OBJLIST, m_ObjListBox);
}


BEGIN_MESSAGE_MAP(MapDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MapDlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_TileList, &MapDlg::OnLbnSelchangeTilelist)
	ON_BN_CLICKED(IDC_SAVE, &MapDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &MapDlg::OnBnClickedLoad)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_LOADIMAGE, &MapDlg::OnBnClickedLoadimage)
	ON_EN_CHANGE(IDC_SPRITENAME, &MapDlg::OnEnChangeSpritename)
	ON_BN_CLICKED(IDC_RADIO1, &MapDlg::OnBnClickedTileMode)
	ON_BN_CLICKED(IDC_RADIO2, &MapDlg::OnBnClickedWarpMode)
	ON_BN_CLICKED(IDC_GATECREATE, &MapDlg::OnBnClickedGatecreate)
	ON_BN_CLICKED(IDC_DELETE, &MapDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_RADIO5, &MapDlg::OnBnClickedObjectMode)
	ON_BN_CLICKED(IDC_BUTTON1, &MapDlg::OnBnClickedObjDelete)
END_MESSAGE_MAP()


// MapDlg �޽��� ó�����Դϴ�.


void MapDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void MapDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}


BOOL MapDlg::OnInitDialog()
{
	TabDlg::OnInitDialog();


	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	ptr = this;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void MapDlg::OnLbnSelchangeTilelist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	GateData data;
	CString ObjectSprite;
	switch (m_Mode)
	{
	case 0:
		m_LevelScript->SetTileIndex(m_TileList.GetCurSel());
		break;
	case 1:
		data = m_LevelScript->GetGateData(m_TileList.GetCurSel());
		m_GateMode = data.Mode;
		m_GatePosX = data.Pos.x;
		m_GatePosY = data.Pos.y;
		m_GateScaleX = data.Scale.x;
		m_GateScaleY = data.Scale.y;
		m_NextLevel = data.NextLevel;
		m_GateNextPosX = data.NextPos.x;
		m_GateNextPosY = data.NextPos.y;
		break;
	case 2:
		m_TileList.GetText(m_TileList.GetCurSel(), ObjectSprite);
		m_LevelScript->ObjectSpriteName = ObjectSprite;
		break;
	default:
		break;
	}
	
	UpdateData(FALSE);
}


void MapDlg::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_LevelScript->MapSave();
}


void MapDlg::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->MapLoad();
	m_SpriteName = m_LevelScript->GetSpriteName().c_str();
	if (m_Mode == 1)
	{
		m_TileList.ResetContent();
		for (size_t i = 0; i < m_LevelScript->GetGateSize(); i++)
		{
			wchar_t Arr[50];
			_itow_s((int)i, Arr, 10);

			CString Str = Arr;

			m_TileList.AddString(Str);
		}
	}
	NewUpdate();
	UpdateData(FALSE);
}


void MapDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	TabDlg::OnShowWindow(bShow, nStatus);

	if (nullptr != m_LevelScript)
	{
		return;
	}

	m_LevelScript = TabLevel->CreateScript<MapDlgScript>();


	for (size_t i = 0; i < m_LevelScript->GetTileCutSize(); i++)
	{
		wchar_t Arr[50];
		_itow_s((int)i, Arr, 10);

		CString Str = Arr;

		m_TileList.AddString(Str);
	}


	UpdateData(TRUE);

	m_TileList.SetCurSel(0);
	m_LevelScript->SetTileIndex(m_TileList.GetCurSel());

	UpdateData(FALSE);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void MapDlg::OnBnClickedLoadimage()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void MapDlg::OnEnChangeSpritename()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// TabDlg::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	m_LevelScript->inputSpriteName = m_SpriteName;
	m_LevelScript->CheckOn();
	UpdateData(FALSE);
}


void MapDlg::OnBnClickedTileMode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->SetMode(m_Mode);
	m_TileList.ResetContent();
	for (size_t i = 0; i < m_LevelScript->GetTileCutSize(); i++)
	{
		wchar_t Arr[50];
		_itow_s((int)i, Arr, 10);

		CString Str = Arr;

		m_TileList.AddString(Str);
	}
	UpdateData(FALSE);
}


void MapDlg::OnBnClickedWarpMode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->SetMode(m_Mode);
	m_TileList.ResetContent();
	for (size_t i = 0; i < m_LevelScript->GetGateSize(); i++)
	{
		wchar_t Arr[50];
		_itow_s((int)i, Arr, 10);

		CString Str = Arr;

		m_TileList.AddString(Str);
	}
	UpdateData(FALSE);
}


void MapDlg::OnBnClickedGatecreate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_Mode != 1)
	{
		return;
	}
	UpdateData(TRUE);
	m_LevelScript->CreateGate(m_GateMode, Vector2f(m_GatePosX, m_GatePosY), Vector2f(m_GateScaleX, m_GateScaleY), m_NextLevel, Vector2f(m_GateNextPosX, m_GateNextPosY));
	
	wchar_t Arr[50];
	_itow_s((int)m_LevelScript->GetGateSize() - 1, Arr, 10);
	CString Str = Arr;
	m_TileList.AddString(Str);

	UpdateData(FALSE);
}


void MapDlg::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->DeleteGate(m_TileList.GetCurSel());
	m_TileList.DeleteString(m_TileList.GetCurSel());
	UpdateData(FALSE);
}


void MapDlg::OnBnClickedObjectMode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->SetMode(m_Mode);
	m_TileList.ResetContent();
	if (PathManager::FindPath(L"Objects") == L"")
	{
		PathManager::PlusCreatePath(L"Tex",L"Objects",L"Objects");
	}
	std::list<std::wstring> ObjectList = PathManager::GetAllFile(PathManager::FindPath(L"Objects").c_str());
	std::list<std::wstring>::iterator itStart = ObjectList.begin();;
	std::list<std::wstring>::iterator itEnd = ObjectList.end();
	for (; itStart != itEnd; ++itStart)
	{
		CString Str = (*itStart).c_str();
		m_TileList.AddString(Str);
	}

	std::list<std::wstring> DirList = PathManager::GetAllDir(PathManager::FindPath(L"Objects").c_str());
	std::list<std::wstring>::iterator itDirStart = DirList.begin();;
	std::list<std::wstring>::iterator itDirEnd = DirList.end();
	for (; itDirStart != itDirEnd; ++itDirStart)
	{
		ObjectList = PathManager::GetAllFile((PathManager::FindPath(L"Objects") + (*itDirStart)).c_str());
		itStart = ObjectList.begin();;
		itEnd = ObjectList.end();
		for (; itStart != itEnd; ++itStart)
		{
			CString Str = (*itStart).c_str();
			m_TileList.AddString(Str);
		}
	}

	
	UpdateData(FALSE);
}

void MapDlg::NewUpdate()
{
	if (ptr == nullptr)
	{
		return;
	}
	ptr->m_ObjListBox.ResetContent();

	size_t ObjSize = ptr->m_LevelScript->GetObjSIze();
	for (int i = 0; i < ObjSize; ++i)
	{
		ObjectData data;
		data = ptr->m_LevelScript->GetObjData(i);
		ptr->m_ObjListBox.AddString(data.SpriteName);
	}
}


void MapDlg::OnBnClickedObjDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_LevelScript->DeleteObject(m_ObjListBox.GetCurSel());
	m_ObjListBox.DeleteString(m_ObjListBox.GetCurSel());
	UpdateData(FALSE);
}
