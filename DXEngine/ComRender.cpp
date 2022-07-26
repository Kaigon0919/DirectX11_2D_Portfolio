#include "ComRender.h"
#include"Actor.h"
#include"Level.h"


bool ComRender::Init(int _renderGroup)
{
	m_RenderGroup = _renderGroup;

	if (true == GetActor()->IsOver())
	{
		std::list<std::wstring> OverList = Level::OverList(GetActor());
		std::list<std::wstring>::iterator StartIter = OverList.begin();
		std::list<std::wstring>::iterator EndIter = OverList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			SPTR<Level> FindScene = Level::FindLevel((*StartIter).c_str());
			FindScene->RMgr.PushRender(this);
		}
	}
	else
	{
		GetActor()->GetLevel()->RMgr.PushRender(this);

	}

	return true;
}

ComRender::ComRender()
{
}


ComRender::~ComRender()
{
}
