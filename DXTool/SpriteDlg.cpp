// SpriteDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DXTool.h"
#include "SpriteDlg.h"
#include "afxdialogex.h"
#include"SpriteScript.h"
#include<Render2DSprite.h>
#include<Tex.h>
#include<GameSprite.h>
#include<PathManager.h>
#include<Camera.h>
#include<IRefCount.h>
#include<MyThread.h>

// 인덱스 무관으로 전체 출력 가능하게 변경해야한다.


SpriteDlg* Dlg = nullptr;
int LoadingCount = 0;
//
unsigned int __stdcall SpriteLoadThread(void*)
{
	Dlg->m_TreeCtrl.DeleteAllItems();

	std::wstring Name = PathManager::FindPath(L"Tex");
	CString Path = Name.c_str();

	HTREEITEM m_Item = Dlg->m_TreeCtrl.InsertItem(L"Tex");
	Dlg->SpriteLoader(Path, m_Item);

	Dlg->m_TreeCtrl.Expand(m_Item, TVE_EXPAND);
	return 0;
}

// SpriteDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(SpriteDlg, CDialogEx)

SpriteDlg::SpriteDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_SpriteDlg, pParent)
{

}

SpriteDlg::~SpriteDlg()
{
}

void SpriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SpriteTree, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(SpriteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SpriteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SpriteDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_SpriteTree, &SpriteDlg::OnTvnSelchangedSpritetree)
	ON_BN_CLICKED(IDC_LOAD, &SpriteDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// SpriteDlg 메시지 처리기입니다.


void SpriteDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void SpriteDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


BOOL SpriteDlg::OnInitDialog()
{
	Dlg = this;

	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SPTR<Actor> camera = TabLevel->CreateActor(L"SprtieCamera");
	camera->AddComponent<SpriteScript>();

	SPTR<Actor> actor = TabLevel->CreateActor(L"Actor");
	m_ComRender = actor->AddComponent<Render2DSprite>(0);
	m_ComRender->SetCutShow(false);
	//MyThread::CreateThread(L"LoadThread", SpriteLoadThread);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SpriteDlg::SpriteLoader(const CString & _Folder, HTREEITEM _Parent)
{
	CFileFind FildFinder;

	// *. * 모든 파일이름의 모든 확장자를 찾아라!
	BOOL IsFile = FildFinder.FindFile(_Folder + L"*.*");

	while (TRUE == IsFile)
	{
		IsFile = FildFinder.FindNextFileW();

		if (FildFinder.IsDots())
		{
			continue;
		}
		else if (TRUE == FildFinder.IsDirectory())
		{
			std::wstring FolderName = FildFinder.GetFileName();
			HTREEITEM FolderItem = m_TreeCtrl.InsertItem(FolderName.c_str(), _Parent);
			SpriteFinder(_Folder + FildFinder.GetFileName() + L"\\", FolderItem);

			SpriteInfo* Ptr = new SpriteInfo();
			Ptr->m_bFile = false;
			DWORD_PTR PTR = (DWORD_PTR)Ptr;
			m_TreeCtrl.SetItemData(FolderItem, PTR);

			m_List.push_back(Ptr);
		}
		else {
			std::wstring FolderName = FildFinder.GetFileName();
			HTREEITEM FileItem = m_TreeCtrl.InsertItem(FolderName.c_str(), _Parent);


			SpriteInfo* Ptr = new SpriteInfo();
			Ptr->m_bFile = true;
			Ptr->m_Path = _Folder + FolderName.c_str();
			Ptr->m_FileName = FolderName.c_str();
			DWORD_PTR PTR = (DWORD_PTR)Ptr;
			m_TreeCtrl.SetItemData(FileItem, PTR);
			m_List.push_back(Ptr);

			SPTR<Tex> LoadTex = ResMgr<Tex>::Find(Ptr->m_FileName.GetString());
			if (nullptr == LoadTex)
			{
				LoadTex = ResMgr<Tex>::Load(Ptr->m_Path.GetString());
			}
			SPTR<GameSprite> LoadSprite = ResMgr<GameSprite>::Find(Ptr->m_FileName.GetString());
			if(nullptr == LoadSprite)
			{ 
				LoadSprite = ResMgr<GameSprite>::Create(Ptr->m_FileName.GetString(), Ptr->m_FileName.GetString());
			}
		}
	}
}

void SpriteDlg::SpriteFinder(const CString & _Folder, HTREEITEM _Parent)
{
	CFileFind Finder;

	BOOL isFile = Finder.FindFile(_Folder + L"*.*");

	while (isFile)
	{
		isFile = Finder.FindNextFileW();

		CString test = Finder.GetFileName();
		if (Finder.IsDots() || Finder.GetFileName() == L"desktop.ini")
		{
			continue;
		}
		else if (Finder.IsDirectory())
		{
			std::wstring FolderName = Finder.GetFileName();
			HTREEITEM FolderItem = m_TreeCtrl.InsertItem(FolderName.c_str(), _Parent);
			SpriteFinder(_Folder + Finder.GetFileName() + L"\\", FolderItem);

			SpriteInfo* Ptr = new SpriteInfo();
			Ptr->m_bFile = false;
			DWORD_PTR PTR = (DWORD_PTR)Ptr;
			m_TreeCtrl.SetItemData(FolderItem, PTR);

			m_List.push_back(Ptr);
		}
		else
		{
			std::wstring FolderName = Finder.GetFileName();

			HTREEITEM FileItem = m_TreeCtrl.InsertItem(FolderName.c_str(), _Parent);

			SpriteInfo* Ptr = new SpriteInfo();
			Ptr->m_bFile = true;
			Ptr->m_Path = _Folder + FolderName.c_str();
			Ptr->m_FileName = FolderName.c_str();
			DWORD_PTR PTR = (DWORD_PTR)Ptr;
			m_TreeCtrl.SetItemData(FileItem, PTR);
			m_List.push_back(Ptr);
		}
	}
}


void SpriteDlg::OnDestroy()
{
	std::list<SpriteInfo*>::iterator StartIter = m_List.begin();
	std::list<SpriteInfo*>::iterator EndIter = m_List.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			delete (*StartIter);
		}
	}

	TabDlg::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void SpriteDlg::OnTvnSelchangedSpritetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	DWORD_PTR PTR = m_TreeCtrl.GetItemData(pNMTreeView->itemNew.hItem);
	SpriteInfo* Ptr = (SpriteInfo*)PTR;

	if (nullptr == m_ComRender)
	{
		return;
	}

	if (nullptr == Ptr)
	{
		return;
	}
	if (false == Ptr->m_bFile)
	{
		return;
	}

	SPTR<GameSprite> LoadSprite = ResMgr<GameSprite>::Find(Ptr->m_FileName.GetString());
	SPTR<Tex> LoadTex = ResMgr<Tex>::Find(Ptr->m_FileName.GetString());

	if (nullptr == LoadSprite)
	{
		LoadTex = ResMgr<Tex>::Load(Ptr->m_Path.GetString());
		LoadSprite = ResMgr<GameSprite>::Create(Ptr->m_FileName.GetString(), Ptr->m_FileName.GetString());
	}
	if (m_ComRender != nullptr)
	{
		m_ComRender->SetSprite(Ptr->m_FileName.GetString());
		m_ComRender->GetTransform()->SetLocalScale(m_ComRender->GetImageSIze());
	}
}


void SpriteDlg::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MyThread::CreateThread(L"LoadThread", SpriteLoadThread);
}
