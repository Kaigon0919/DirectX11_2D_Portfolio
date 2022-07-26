// AniDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DXTool.h"
#include "AniDlg.h"
#include "afxdialogex.h"
#include<Tex.h>
#include<GameSprite.h>
#include<Com2DFrameAni.h>
#include<Render2DSprite.h>
#include<Camera.h>
#include<Col2DRect.h>
#include<SaveAndLoadData.h>
#include<BWStream.h>
#include<BRStream.h>
#include"AniScript.h"
// AniDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(AniDlg, TabDlg)

AniDlg::AniDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_AniDlg, pParent)
	, m_AniName(_T(""))
	, m_StartFrame(0)
	, m_EndFrame(0)
	, m_DefTime(0.1f)
	, m_EStartFrame(0)
	, m_EEndFrame(0)
	, m_EPosX(0.0f)
	, m_EPosY(0.0f)
	, m_EScaleX(1.0f)
	, m_EScaleY(1.0f)
	, m_bLoop(FALSE)
	, m_PivotX(0)
	, m_PivotY(0)
	, m_bShowAxis(FALSE)
{

}

AniDlg::~AniDlg()
{
	EventDataClear();
}

void AniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANINAME, m_AniName);
	DDX_Text(pDX, IDC_STARTFRAME, m_StartFrame);
	DDX_Text(pDX, IDC_ENDFRAME, m_EndFrame);
	DDX_Text(pDX, IDC_DEFTIME, m_DefTime);
	DDX_Text(pDX, IDC_ESTART, m_EStartFrame);
	DDX_Text(pDX, IDC_EEND, m_EEndFrame);
	DDX_Text(pDX, IDC_EPOSX, m_EPosX);
	DDX_Text(pDX, IDC_EPOSY, m_EPosY);
	DDX_Text(pDX, IDC_SCALEX, m_EScaleX);
	DDX_Text(pDX, IDC_ESCALEY, m_EScaleY);
	DDX_Control(pDX, IDC_ANILIST, m_AniList);
	DDX_Check(pDX, IDC_LOOP, m_bLoop);
	DDX_Control(pDX, IDC_ANINAME, m_AniNameCtrol);
	DDX_Control(pDX, IDC_ANICREATE2, m_AniCreateButton);
	DDX_Control(pDX, IDC_ANIDELETE, m_AniDeleteButton);
	DDX_Control(pDX, IDC_ECREATE, m_EventCreateButton);
	DDX_Control(pDX, IDC_EDELETE, m_EventDeleteButton);
	DDX_Control(pDX, IDC_SAVE, m_SaveButton);
	DDX_Control(pDX, IDC_LOAD, m_LoadButton);
	DDX_Control(pDX, IDC_LIST1, m_EventListBox);
	DDX_Text(pDX, IDC_PIVOTX, m_PivotX);
	DDX_Text(pDX, IDC_PIVOTY, m_PivotY);
	DDX_Check(pDX, IDC_CHECK1, m_bShowAxis);
}


BEGIN_MESSAGE_MAP(AniDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AniDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AniDlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_ANILIST, &AniDlg::OnLbnSelchangeAnilist)
	ON_BN_CLICKED(IDC_ANICREATE2, &AniDlg::OnBnClickedAnicreate)
	ON_BN_CLICKED(IDC_ECREATE, &AniDlg::OnBnClickedEcreate)
	ON_BN_CLICKED(IDC_ANIDELETE, &AniDlg::OnBnClickedAnidelete)
	ON_BN_CLICKED(IDC_SAVE, &AniDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &AniDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &AniDlg::OnBnClickedSpriteLoad)
	ON_BN_CLICKED(IDC_BUTTON2, &AniDlg::OnBnClickedSubPosLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &AniDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_EDELETE, &AniDlg::OnBnClickedEdelete)
	ON_EN_CHANGE(IDC_PIVOTX, &AniDlg::OnEnChangePivotx)
	ON_EN_CHANGE(IDC_PIVOTY, &AniDlg::OnEnChangePivoty)
	ON_BN_CLICKED(IDC_CHECK1, &AniDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// AniDlg 메시지 처리기입니다.


void AniDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void AniDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


BOOL AniDlg::OnInitDialog()
{
	TabDlg::OnInitDialog();

	m_AniList.AddString(L"<Create>");
	
	ResMgr<Tex>::TexLoadFileInDir(L"Tex");
	ResMgr<GameSprite>::Create(L"Character_Swordman.png", L"Character_Swordman.png", 30, 7);
	ResMgr<GameSprite>::Create(L"GoblinBody0.png", L"GoblinBody0.png", 6, 3);
	ResMgr<GameSprite>::Create(L"GoblinBody1.png", L"GoblinBody1.png", 6, 3);
	ResMgr<GameSprite>::Create(L"GoblinWeapon1.png", L"GoblinWeapon1.png", 6, 3);
	ResMgr<GameSprite>::Create(L"Tau.png", L"Tau.png", 8, 4);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SPTR<Actor> NewActor = TabLevel->CreateActor(L"Camera");
	SPTR<Camera> Ptr = NewActor->AddComponent<Camera>();
	Ptr->OnViewGroup(0, 1, 2, 3, 4, 5);
	Ptr->GetTransform()->SetLocalPosition(Vector3f(0.0f, 0.0f, -100.0f));


	SPTR<Actor> TagetActor = TabLevel->CreateActor(L"TagetActor");
	script = TagetActor->AddComponent<AniScript>();
	//FrameAni = TagetActor->AddComponent<Com2DFrameAni>();

	TagetActor->GetTransform()->SetLocalScale(1.0f,1.0f,1.0f);
	RIGHTCOL = TagetActor->AddComponent<Col2DRect>(L"Right");
	RIGHTCOL->SetUpdate(false);
	RIGHTCOL->SetLocalSubPosition(Vector3f{50.0f, 100.0f ,0.0f});
	RIGHTCOL->SetLocalSubScale(Vector3f{100.0f, 20.0f, 0.0f});

	m_AniCreateButton.EnableWindow(false);
	m_AniDeleteButton.EnableWindow(false);
	m_EventCreateButton.EnableWindow(false);
	m_EventDeleteButton.EnableWindow(false);
	m_SaveButton.EnableWindow(false);
	m_LoadButton.EnableWindow(false);
	return TRUE;
}

void AniDlg::TestEventOn(void * _Value)
{
	AniEventData* eData = (AniEventData*)_Value;

	RIGHTCOL->SetLocalSubPosition(Vector3f{ eData->Position.x, eData->Position.y,0.0f });
	RIGHTCOL->SetLocalSubScale(Vector3f{ eData->Scale.x, eData->Scale.y ,1.0f});

	RIGHTCOL->SetUpdate(true);
}

void AniDlg::TestEventOff(void *)
{
	RIGHTCOL->SetUpdate(false);
}


void AniDlg::OnLbnSelchangeAnilist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// 다른 애니매이션으로 변경될때 Collision은 꺼주자.
	RIGHTCOL->SetUpdate(false);

	CString ChangeName;

	m_AniList.GetText(m_AniList.GetCurSel(), ChangeName);
	if (ChangeName != L"<Create>") 
	{
		m_AniCreateButton.SetWindowText(L"Modify");
		script->ChangeAni(ChangeName.GetString());
		Com2DFrameAni::AniData data = script->GetComFrameAni()->GetAniData(ChangeName.GetString());
		//m_AniNameCtrol.SetReadOnly(true);
		m_AniName = data.AniName.c_str();
		m_StartFrame = data.StartFrame;
		m_EndFrame = data.EndFrame;
		m_bLoop = data.isLoop;
		m_DefTime = data.DefTime;
	}
	else
	{
		m_AniCreateButton.SetWindowText(L"Ani Create");

		//m_AniNameCtrol.SetReadOnly(false);
	}
	UpdateData(FALSE);

}


void AniDlg::OnBnClickedAnicreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int curSel = m_AniList.GetCurSel();

	if (curSel <= 0)
	{
		m_AniName.Trim();

		if (m_AniName == "")
		{
			AfxMessageBox(L"이름이 없습니다.");
			return;
		}

		int index = m_AniList.FindString(0, m_AniName);
		if (index != -1)
		{
			AfxMessageBox(L"존재하는 애니메이션 입니다.");
		}
		else
		{
			if (m_StartFrame > m_EndFrame)
			{
				AfxMessageBox(L"StartFrame이 EndFrame보다 클수 없습니다.");
				UpdateData(FALSE);
				return;
			}
			script->CreateAni(m_AniName.GetString(), m_StartFrame, m_EndFrame, m_bLoop == TRUE, m_DefTime);
			m_AniList.AddString(m_AniName.GetString());
		}
	}
	else 
	{
		CString ChangeName;
		m_AniList.GetText(curSel, ChangeName);
		script->DeleteAni(ChangeName.GetString());
		script->CreateAni(m_AniName.GetString(), m_StartFrame, m_EndFrame, m_bLoop == TRUE, m_DefTime);
		m_AniList.DeleteString(curSel);
		m_AniList.AddString(m_AniName.GetString());
	}
	UpdateData(FALSE);

}


void AniDlg::OnBnClickedEcreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (-1 >= m_AniList.GetCurSel())
	{
		AfxMessageBox(L"프레임 설정이 틀렸습니다.");
		return;
	}

	CString ChangeName;
	m_AniList.GetText(m_AniList.GetCurSel(), ChangeName);

	AniEventData* Event = new AniEventData();

	Event->StartFrame = m_EStartFrame;
	Event->EndFrame = m_EEndFrame;
	Event->Position.x = m_EPosX;
	Event->Position.y = m_EPosY;
	Event->Scale.x = m_EScaleX;
	Event->Scale.y = m_EScaleY;

	m_EventListBox.AddString(ChangeName);

	EventDataList.push_back(Event);

	script->GetComFrameAni()->SetFrameEvent(ChangeName.GetString(), m_EStartFrame, m_EEndFrame, &AniDlg::TestEventOn, this, Event);
	script->GetComFrameAni()->SetFrameEvent(ChangeName.GetString(), m_EEndFrame, m_EEndFrame, &AniDlg::TestEventOff, this, nullptr);


	UpdateData(FALSE);
}


void AniDlg::OnBnClickedAnidelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_AniList.GetCurSel() <= 0)
	{
		return;
	}


	CString ItemName;
	m_AniList.GetText(m_AniList.GetCurSel(), ItemName);
	script->DeleteAni(ItemName.GetString());

	m_AniList.DeleteString(m_AniList.GetCurSel());

	UpdateData(FALSE);
}


BOOL AniDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	return TabDlg::DestroyWindow();
}


void AniDlg::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	std::wstring DlgPath = PathManager::FindPath(L"AniData");
	if (DlgPath == L"")
	{
		assert(false && L"Not FindPath AniData");
		return;
	}


	CFileDialog dlgFile(FALSE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"data";
	ofn.lpstrFilter = L"Data File\0 *.data\0Every File\0*.*\0";

	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}

	// 파일명.
	//CString FileName = dlgFile.GetFileName();
	// 파일명까지의 경로.
	CString PathName = dlgFile.GetPathName();
	// 폴더경로 (파일명 X)
	//CString FolderPath = dlgFile.GetFolderPath();
	if (PathName == L"")
	{
		return;
	}


	UpdateData(TRUE);

	std::list<Com2DFrameAni::AniData> List = script->GetComFrameAni()->IOAllData();
	BWFStream bis = BWFStream(PathName);

	bis.Write(m_PivotX);
	bis.Write(m_PivotY);


	int size = (int)List.size();
	bis.Write(size);

	if (size == 0)
	{
		return;
	}



	std::list<Com2DFrameAni::AniData>::iterator StartIter = List.begin();
	std::list<Com2DFrameAni::AniData>::iterator EndIter = List.end();


	std::list<void*>::iterator itStartEvnetList;
	std::list<void*>::iterator itEndEvnetList;

	Com2DFrameAni::AniData ani = (*StartIter);

	SaveAniData saveAni;
	AniEventData eventData;

	for (; StartIter != EndIter; ++StartIter)
	{
		// 기본 애니메이션 저장.
		ani = (*StartIter);
		StrCpyW(saveAni.AniName, ani.AniName.c_str());
		saveAni.DefTime = ani.DefTime;
		saveAni.StartFrame = ani.StartFrame;
		saveAni.EndFrame = ani.EndFrame;
		saveAni.isLoop = ani.isLoop;
		bis.Write(saveAni);

		// 이벤트 저장.
		int eventSize = (int)ani.Event.size();
		bis.Write(eventSize);
		
		itStartEvnetList = ani.Event.begin();
		itEndEvnetList = ani.Event.end();
		for (;itStartEvnetList != itEndEvnetList; ++itStartEvnetList)
		{
			eventData = *((AniEventData*)(*itStartEvnetList));
			bis.Write(eventData);
		}
	}
}


void AniDlg::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::wstring DlgPath = PathManager::FindPath(L"AniData");
	if (DlgPath == L"")
	{
		DlgPath = PathManager::GetRootPath();
	}
	CFileDialog dlgFile(true);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"data";
	ofn.lpstrFilter = L"Data File\0 *.data\0Every File\0*.*\0";
	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}
	CString PathName = dlgFile.GetPathName();
	if (PathName == L"")
	{
		return;
	}
	UpdateData(TRUE);

	// Dlg List, Ani 클리어.
	m_AniList.ResetContent();
	m_AniList.AddString(L"<Create>");
	script->Clear();
	EventDataList.clear();
	m_EventListBox.ResetContent();

	BRStream Stream = BRStream(PathName);

	Stream.Read(m_PivotX);
	Stream.Read(m_PivotY);
	script->SetPivot(m_PivotX, m_PivotY);

	int size;
	int eventSize;
	Stream.Read(size);

	SaveAniData MyLoadData = {};
	AniEventData EventData;

	for (int i = 0; i < size; ++i)
	{
		Stream.Read(MyLoadData);
		script->CreateAni(MyLoadData.AniName, MyLoadData.StartFrame, MyLoadData.EndFrame, MyLoadData.isLoop, MyLoadData.DefTime);
		m_AniList.AddString(MyLoadData.AniName);

		Stream.Read(eventSize);
		for (int j = 0; j<eventSize  ; ++j)
		{
			Stream.Read(EventData);
			AniEventData* ptr = new AniEventData;
			ptr->StartFrame =EventData.StartFrame;
			ptr->EndFrame= EventData.EndFrame;
			ptr->Position= EventData.Position;
			ptr->Scale= EventData.Scale;

			m_EventListBox.AddString(MyLoadData.AniName);

			EventDataList.push_back(ptr);
			script->GetComFrameAni()->SetFrameEvent(MyLoadData.AniName, EventData.StartFrame, EventData.EndFrame, &AniDlg::TestEventOn, this, ptr);
			script->GetComFrameAni()->SetFrameEvent(MyLoadData.AniName, EventData.EndFrame, EventData.EndFrame, &AniDlg::TestEventOff, this, nullptr);
		}

	}
	MyLoadData = {};
	UpdateData(FALSE);
}

void AniDlg::EventDataClear()
{
	std::list<AniEventData*>::iterator itStart = EventDataList.begin();
	std::list<AniEventData*>::iterator itEnd = EventDataList.end();

	while (itStart != itEnd)
	{
		if ((*itStart) != nullptr)
		{
			delete *itStart;
		}
		++itStart;
	}
	EventDataList.clear();
}


void AniDlg::OnBnClickedSpriteLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::wstring DlgPath = PathManager::FindPath(L"Tex");
	if (DlgPath == L"")
	{
		DlgPath = PathManager::GetRootPath();
	}
	CFileDialog dlgFile(true);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"png";
	ofn.lpstrFilter = L"Png File\0 *.png\0Every File\0*.*\0";
	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}
	CString PathName = dlgFile.GetPathName();
	CString FileName = dlgFile.GetFileName();
	if (PathName == L"")
	{
		return;
	}
	// Dlg List, Ani 클리어.
	//m_AniList.ResetContent();
	//m_AniList.AddString(L"<Create>");
	//m_AniList.SetCurSel(-1);
	//script->Clear();
	//EventDataList.clear();
	//m_EventListBox.ResetContent();

	if (ResMgr<Tex>::Find(FileName.GetString()) == nullptr)
	{
		ResMgr<Tex>::Load(PathName.GetString());
	}
	if (ResMgr<GameSprite>::Find(FileName.GetString()) == nullptr)
	{
		ResMgr<GameSprite>::Create(FileName.GetString(), FileName.GetString());
	}
	script->SpriteSet(FileName);

	m_AniCreateButton.EnableWindow(true);
	m_AniDeleteButton.EnableWindow(true);
	m_EventCreateButton.EnableWindow(true);
	m_EventDeleteButton.EnableWindow(true);
	m_SaveButton.EnableWindow(true);
	m_LoadButton.EnableWindow(true);
}


void AniDlg::OnBnClickedSubPosLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::wstring DlgPath = PathManager::FindPath(L"SubTransData");
	if (DlgPath == L"")
	{
		DlgPath = PathManager::GetRootPath();
	}
	CFileDialog dlgFile(true);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrInitialDir = DlgPath.c_str();
	ofn.lpstrDefExt = L"data";
	ofn.lpstrFilter = L"Data File\0 *.data\0Every File\0*.*\0";
	if (dlgFile.DoModal() == IDCANCEL)
	{
		return;
	}
	CString PathName = dlgFile.GetPathName();
	CString FileName = dlgFile.GetFileName();
	CString FileExt = dlgFile.GetFileExt();
	if (PathName == L"")
	{
		return;
	}
	if (FileExt != L"data")
	{
		AfxMessageBox(L"Data파일이 아닙니다.");
		return;
	}
	script->SubDataSet(FileName);
}


void AniDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	std::list<AniEventData*>::iterator itStart = EventDataList.begin();

	for (int i = 0; i < m_EventListBox.GetCurSel(); ++i)
	{
		++itStart;
	}
	m_EPosX = (*itStart)->Position.x;
	m_EPosY = (*itStart)->Position.y;
	m_EScaleX = (*itStart)->Scale.x;
	m_EScaleY = (*itStart)->Scale.y;
	m_EStartFrame = (*itStart)->StartFrame;
	m_EEndFrame = (*itStart)->EndFrame;

	UpdateData(FALSE);
}


void AniDlg::OnBnClickedEdelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_EventListBox.GetCurSel() <= -1)
	{
		return;
	}
	if (m_EventListBox.GetCurSel() >= EventDataList.size())
	{
		return;
	}

	std::list<AniEventData*>::iterator itStart = EventDataList.begin();
	for (int i = 0; i < m_EventListBox.GetCurSel(); ++i)
	{
		++itStart;
	}

	CString TagetAni;
	m_EventListBox.GetText(m_EventListBox.GetCurSel(), TagetAni);
	script->EventDelete(TagetAni, (*itStart)->StartFrame, (*itStart)->EndFrame);

	m_EventListBox.DeleteString(m_EventListBox.GetCurSel());
	EventDataList.erase(itStart);

	UpdateData(FALSE);
}


void AniDlg::OnEnChangePivotx()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// TabDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	script->SetPivot(m_PivotX, m_PivotY);
	UpdateData(FALSE);

}


void AniDlg::OnEnChangePivoty()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// TabDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	script->SetPivot(m_PivotX, m_PivotY);
	UpdateData(FALSE);
}


void AniDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	script->SetAxis(m_bShowAxis == TRUE);
	UpdateData(FALSE);

}
