// SpriteDlg.cpp : ���� �����Դϴ�.
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

// �ε��� �������� ��ü ��� �����ϰ� �����ؾ��Ѵ�.


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

// SpriteDlg ��ȭ �����Դϴ�.

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


// SpriteDlg �޽��� ó�����Դϴ�.


void SpriteDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void SpriteDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}


BOOL SpriteDlg::OnInitDialog()
{
	Dlg = this;

	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SPTR<Actor> camera = TabLevel->CreateActor(L"SprtieCamera");
	camera->AddComponent<SpriteScript>();

	SPTR<Actor> actor = TabLevel->CreateActor(L"Actor");
	m_ComRender = actor->AddComponent<Render2DSprite>(0);
	m_ComRender->SetCutShow(false);
	//MyThread::CreateThread(L"LoadThread", SpriteLoadThread);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void SpriteDlg::SpriteLoader(const CString & _Folder, HTREEITEM _Parent)
{
	CFileFind FildFinder;

	// *. * ��� �����̸��� ��� Ȯ���ڸ� ã�ƶ�!
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void SpriteDlg::OnTvnSelchangedSpritetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MyThread::CreateThread(L"LoadThread", SpriteLoadThread);
}
