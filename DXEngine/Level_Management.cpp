#include"Level.h"
#include"DxDevice.h"
SPTR<Level> Level::m_CurLevel = nullptr;
SPTR<Level> Level::m_NextLevel = nullptr;


SPTR<Level> Level::CreateLevel(const wchar_t * levelName)
{
	if ( nullptr != FindLevel(levelName))
	{
		assert(false && L"CreateLevel,It already exists.");
		return nullptr;
	}

	SPTR<Level> newLevel = ResMgr<Level,std::wstring>::Create(levelName);
	newLevel->RTTISetting();
	newLevel->SetName(levelName);
	return newLevel;
}

SPTR<Level> Level::FindLevel(const wchar_t * _Name)
{
	return ResMgr<Level,std::wstring>::Find(_Name);
}

bool Level::ChangeLevel(const wchar_t * _Name)
{
	m_NextLevel = ResMgr<Level, std::wstring>::Find(_Name);

	if (nullptr == m_NextLevel)
	{
		assert(false && L"NextLevel is nullptr");
		return false;
	}

	return true;
}


void Level::LevelChangeCheck()
{
	if (nullptr != m_NextLevel)
	{
		if (nullptr != m_CurLevel)
		{
			m_CurLevel->End();
		}

		m_CurLevel = m_NextLevel;

		if (false == m_CurLevel->IsLoading())
		{
			m_CurLevel->Loading();
		}
		OverActorChangeCheck();
		m_CurLevel->Start();

		m_NextLevel = nullptr;
	}
}

void Level::LevelUpdate()
{
	LevelChangeCheck();
	if (nullptr != m_CurLevel)
	{
		m_CurLevel->Progress();

		// Render
		DxDevice::ClearTaget();
		DxDevice::StateSetting();
		Level::LevelRender();
		DxDevice::Present();
		m_CurLevel->Col();
		m_CurLevel->Release();
		m_CurLevel->OverActorProcess();
	}
}

void Level::LevelRender()
{
	if (m_CurLevel == nullptr)
	{
		assert(false && L"CurLevel nullptr");
		return;
	}
	m_CurLevel->Render();

}
