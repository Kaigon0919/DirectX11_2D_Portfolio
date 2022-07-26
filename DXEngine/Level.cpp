#include "Level.h"
#include"Actor.h"
#include"Transform.h"
#include"ComRender.h"

#ifdef _DEBUG
bool Level::m_bDebug = true;
#else
bool Level::m_bDebug = false;
#endif

std::list<SPTR<Level::OverActorInfo>> Level::m_OverActor;
std::list<SPTR<Level::OverActorInfo>> Level::m_WatingActor;


Level::Level() {}
Level::~Level() { }

void Level::OverActorPush(Actor * actor, std::list<std::wstring> levelList)
{
	OverActorInfo *newInfo = new OverActorInfo();
	newInfo->m_Actor = actor;
	newInfo->m_OverLevelList = levelList;
	m_WatingActor.push_back(newInfo);
}

void Level::OverActorProcess()
{
	std::list<SPTR<OverActorInfo>>::iterator itOverWatiStart = m_WatingActor.begin();
	std::list<SPTR<OverActorInfo>>::iterator itOverWatiEnd = m_WatingActor.end();
	
	for (; itOverWatiStart != itOverWatiEnd; ++itOverWatiStart)
	{

		Actor* actor = (*itOverWatiStart)->m_Actor.Get();
		std::list<std::wstring> levelList = (*itOverWatiStart)->m_OverLevelList;

		// OverActorInfo�� ������ ������ �����.
		OverActorInfo *newInfo = nullptr;


		// �ߺ��� Actor�� �ִ��� Ȯ���Ѵ�.
		std::list<SPTR<OverActorInfo>>::iterator itOverInofStart = m_OverActor.begin();
		std::list<SPTR<OverActorInfo>>::iterator itOverInofEnd = m_OverActor.end();
		for (; itOverInofStart != itOverInofEnd; ++itOverInofStart)
		{
			// �ߺ��� ���Ͱ� ������ newInfo�� �ش� Info�� �ּҰ��� �־��ش�.
			if ((*itOverInofStart)->m_Actor == actor)
			{
				newInfo = (*itOverInofStart).Get();
			}
		}

		// �ߺ��� ���Ͱ� ������ ���� ������ش�.
		if (newInfo == nullptr)
		{
			newInfo = new OverActorInfo();
			newInfo->m_Actor = actor;
			newInfo->m_OverLevelList = levelList;
			m_OverActor.push_back(newInfo);
		}
		else
		{
			// �ߺ��� �����̸� List�� ���� �������ش�.( ���� ����� ����)
			std::list<std::wstring>::iterator itTaget = levelList.begin();
			std::list<std::wstring>::iterator itStart;
			std::list<std::wstring>::iterator itEnd;
			for (; itTaget != levelList.end(); ++itTaget)
			{
				itStart = newInfo->m_OverLevelList.begin();
				itEnd = newInfo->m_OverLevelList.end();

				for (; itStart != itEnd; ++itStart)
				{
					if (*itStart == *itTaget)
					{
						break;
					}
				}
				if (itStart == itEnd)
				{
					newInfo->m_OverLevelList.push_back((*itTaget));
				}
			}
		}


		// List�� ����� Level�� ��ȯ�Ͽ� �����Ѵ�.
		std::list<std::wstring>::iterator itStart = newInfo->m_OverLevelList.begin();
		std::list<std::wstring>::iterator itEnd = newInfo->m_OverLevelList.end();
		for (; itStart != itEnd; ++itStart)
		{
			SPTR<Level>  findLevel = ResMgr<Level>::Find(*itStart);
			if (findLevel == nullptr)
			{
				assert(false && L"OverActorPush not find level");
				continue;
			}

			// �ش� ������ �ߺ��� ���Ͱ� �ִ��� Ȯ��
			if (findLevel->IsHasActor(actor) == false)
			{
				std::map<int, std::list<SPTR<Actor>>>::iterator itFind = findLevel->m_ActorMap.find(actor->GetOrder());

				if (itFind == findLevel->m_ActorMap.end())
				{
					findLevel->m_ActorMap.insert(std::map<int, std::list<SPTR<Actor>>>::value_type(actor->GetOrder(), std::list<SPTR<Actor>>()));
					itFind = findLevel->m_ActorMap.find(actor->GetOrder());
				}
				itFind->second.push_back(actor);
			}


			// Render ó��.
			std::list<SPTR<ComRender>> RenderList = actor->GetChildAllCom<ComRender>();
			std::list<SPTR<ComRender>>::iterator StartRenderIter = RenderList.begin();
			std::list<SPTR<ComRender>>::iterator EndRenderIter = RenderList.end();
			for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
			{
				// �ߺ��� ������ ������ �����Ѵ�.
				if (findLevel->RMgr.IsHasRender((*StartRenderIter).Get()))
				{
					continue;
				}
				findLevel->RMgr.PushRender((*StartRenderIter).Get());
			}

			// Collision ó��.
			std::list<SPTR<ComCol>> ColList = actor->GetChildAllCom<ComCol>();
			std::list<SPTR<ComCol>>::iterator StartColIter = ColList.begin();
			std::list<SPTR<ComCol>>::iterator EndColIter = ColList.end();
			for (; StartColIter != EndColIter; ++StartColIter)
			{
				// �ߺ��� ������ ������ �����Ѵ�.
				if (findLevel->CMgr.IsHasCol((*StartColIter).Get()))
				{
					continue;
				}
				findLevel->CMgr.PushCol((*StartColIter).Get());
			}
		}
	}
	m_WatingActor.clear();
}

void Level::OverActorChangeCheck()
{
	std::list<SPTR<OverActorInfo>>::iterator StartOverIter = m_OverActor.begin();
	std::list<SPTR<OverActorInfo>>::iterator EndOverIter = m_OverActor.end();

	for (; StartOverIter != EndOverIter; ++StartOverIter)
	{
		if (true == (*StartOverIter)->IsOverActor(m_CurLevel->GetName()))
		{
			(*StartOverIter)->m_Actor->SetLevel(m_CurLevel.Get());
		}
	}
}

std::list<std::wstring> Level::OverList(Actor * _Actor)
{
	std::list<SPTR<OverActorInfo>>::iterator itOverInofStart = m_OverActor.begin();
	std::list<SPTR<OverActorInfo>>::iterator itOverInofEnd = m_OverActor.end();
	for (; itOverInofStart != itOverInofEnd; ++itOverInofStart)
	{
		// �ߺ��� ���Ͱ� ������ newInfo�� �ش� Info�� �ּҰ��� �־��ش�.
		if ((*itOverInofStart)->m_Actor == _Actor)
		{
			return (*itOverInofStart)->m_OverLevelList;
		}
	}
	assert(false && L"Not find OverActorInfo");
	return std::list<std::wstring>();
}



bool Level::OverActorInfo::IsOverActor(const wchar_t* _Name)
{

	std::list<std::wstring>::iterator it_Start = m_OverLevelList.begin();
	std::list<std::wstring>::iterator it_End = m_OverLevelList.end();

	for (; it_Start != it_End; ++it_Start)
	{
		if ((*it_Start) == _Name)
		{
			return true;
		}
	}

	return false;
}

void Level::Loading()
{
	if (m_ScriptList.size() > 0)
	{
		UStartIter = m_ScriptList.begin();
		UEndIter = m_ScriptList.end();

		for (; UStartIter != UEndIter; ++UStartIter)
		{
			(*UStartIter)->Loading();
		}

	}

	isLoading = true;
}

bool Level::Create()
{
	return true;
}
void Level::Start()
{
	UStartIter = m_ScriptList.begin();
	UEndIter = m_ScriptList.end();

	for (; UStartIter != UEndIter; ++UStartIter)
	{
		(*UStartIter)->Start();
	}
}

void Level::End()
{
	UStartIter = m_ScriptList.begin();
	UEndIter = m_ScriptList.end();

	for (; UStartIter != UEndIter; ++UStartIter)
	{
		(*UStartIter)->End();
	}
}

void Level::ScriptUpdate()
{
	UStartIter = m_ScriptList.begin();
	UEndIter = m_ScriptList.end();

	for (; UStartIter != UEndIter; ++UStartIter)
	{
		(*UStartIter)->Update();
	}
}

void Level::ScriptLateUpdate()
{
	UStartIter = m_ScriptList.begin();
	UEndIter = m_ScriptList.end();

	for (; UStartIter != UEndIter; ++UStartIter)
	{
		(*UStartIter)->LateUpdate();
	}
}
void Level::Release()
{
	RMgr.Release();
	CMgr.Release();

	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd;)
		{
			(*it_ListStart)->ChildCheckProcess();
			if ((*it_ListStart)->IsDeath() || (*it_ListStart)->m_Parent != nullptr)
			{
				it_ListStart = it_ActorMapStart->second.erase(it_ListStart);
			}
			else
			{
				++it_ListStart;
			}
		}
	}
}
SPTR<Actor> Level::CreateActor(const wchar_t * _Name, int _Order)
{
	SPTR<Actor> temp = CreateNoneTransformActor(_Order, _Name);
	temp->AddComponent<Transform>();
	return temp;
}

SPTR<Actor> Level::CreateActor(int _Order, const wchar_t * _Name)
{
	SPTR<Actor> temp = CreateNoneTransformActor(_Order, _Name);
	temp->AddComponent<Transform>();
	return temp;
}

SPTR<Actor> Level::CreateNoneTransformActor(const wchar_t * _Name, int _Order)
{
	return CreateNoneTransformActor(_Order, _Name);
}

SPTR<Actor> Level::CreateNoneTransformActor(int _Order, const wchar_t * _Name)
{
	std::map<int, std::list<SPTR<Actor>>>::iterator FindIter = m_ActorMap.find(_Order);

	if (FindIter == m_ActorMap.end())
	{
		m_ActorMap.insert(std::map<int, std::list<SPTR<Actor>>>::value_type(_Order, std::list<SPTR<Actor>>()));
		FindIter = m_ActorMap.find(_Order);
	}

	Actor* NewObject = new Actor();
	NewObject->SetName(_Name);
	NewObject->SetLevel(this);
	NewObject->SetOrder(_Order);
	FindIter->second.push_back(NewObject);

	return NewObject;
}

bool Level::IsHasActor(const Actor  * const actor)
{
	std::map<int, std::list<SPTR<Actor>>>::iterator itActorMapStart = m_ActorMap.begin();
	std::map<int, std::list<SPTR<Actor>>>::iterator itActorMapEnd = m_ActorMap.end();
	for (; itActorMapStart != itActorMapEnd; ++itActorMapStart)
	{
		it_ListStart = itActorMapStart->second.begin();
		it_ListEnd = itActorMapStart->second.end();
		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart).Get() == actor)
			{
				return true;
			}
		}
	}
	return false;
}

bool Level::IsHasActor(const Actor * const actor, const int Order)
{
	std::map<int, std::list<SPTR<Actor>>>::iterator itFind = m_ActorMap.find(Order);

	std::list<SPTR<Actor>>::iterator itActorListStart = itFind->second.begin();
	std::list<SPTR<Actor>>::iterator itActorListEnd = itFind->second.end();
	for (; itActorListStart != itActorListEnd; ++itActorListStart)
	{
		if ((*itActorListStart).Get() == actor)
		{
			return true;
		}
	}
	return false;
}

SPTR<Actor> Level::FindActor(const wchar_t* actorName)
{
	std::map<int, std::list<SPTR<Actor>>>::iterator itMapStart = m_ActorMap.begin();
	std::map<int, std::list<SPTR<Actor>>>::iterator itMapEnd = m_ActorMap.end();

	std::list<SPTR<Actor>>::iterator itListStart;
	std::list<SPTR<Actor>>::iterator itListEnd;

	for (; itMapStart != itMapEnd; ++itMapStart)
	{
		itListStart = itMapStart->second.begin();
		itListEnd = itMapStart->second.end();

		for (; itListStart != itListEnd; ++itListStart)
		{
			if ((*itListStart)->m_Name == actorName)
			{
				return (*itListStart);
			}
		}
	}
	return nullptr;
}

void Level::Progress()
{
	ScriptUpdate();
	ActorUpdate();
	ScriptLateUpdate();
}

void Level::ActorUpdate()
{
	AFixUpdate();
	AUpdate();
	ALateUpdate();
	AEndUpdate();
	AFinalUpdate();
}

void Level::AFixUpdate()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->FixUpdate();
			}
		}
	}
}

void Level::AUpdate()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->Update();
			}
		}
	}
}

void Level::ALateUpdate()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->LateUpdate();
			}
		}
	}
}

void Level::AEndUpdate()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->EndUpdate();
			}
		}
	}
}

void Level::AFinalUpdate()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->FinalUpdate();
			}
		}
	}
}

void Level::ADebugRender()
{
	it_ActorMapStart = m_ActorMap.begin();
	it_ActorMapEnd = m_ActorMap.end();

	for (; it_ActorMapStart != it_ActorMapEnd; ++it_ActorMapStart)
	{
		it_ListStart = it_ActorMapStart->second.begin();
		it_ListEnd = it_ActorMapStart->second.end();

		for (; it_ListStart != it_ListEnd; ++it_ListStart)
		{
			if ((*it_ListStart)->IsUpdate())
			{
				(*it_ListStart)->DebugRender();
			}
		}
	}
}


void Level::Render()
{
	RMgr.Render();

	if (m_bDebug)
	{
		CMgr.DebugRender();
		ADebugRender();

		UStartIter = m_ScriptList.begin();
		UEndIter = m_ScriptList.end();

		for (; UStartIter != UEndIter; ++UStartIter)
		{
			(*UStartIter)->DebugRender();
		}
	}
}


void Level::Col()
{
	CMgr.Col();
}