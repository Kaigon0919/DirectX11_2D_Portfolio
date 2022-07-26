#include "RenderMgr.h"
#include"Camera.h"
#include"ComRender.h"
#include"Transform.h"

bool YSortFunc(const SPTR<ComRender> one, SPTR<ComRender> two)
{
	if (one->GetActor() == nullptr || two->GetActor() == nullptr)
	{
		return false;
	}
	if (one->GetTransform()->GetWorldPosition().y > two->GetTransform()->GetWorldPosition().y)
	{
		return true;
	}

	return false;
}

bool ZSortFunc(const SPTR<ComRender> one, SPTR<ComRender> two)
{
	if (one->GetActor() == nullptr || two->GetActor() == nullptr)
	{
		return false;
	}
	if (one->GetWorldSubPosition().z > two->GetWorldSubPosition().z)
	{
		return true;
	}

	return false;
}


RenderMgr::RenderMgr()
{
}

RenderMgr::~RenderMgr()
{
}

void RenderMgr::InsertCamera(Camera * _camera)
{
	if (_camera == nullptr)
	{
		return;
	}
	// 나는 Order값을 바꾸지는 않겠지만 혹시 모르니 전체 체크합니다.
	std::multimap<int, SPTR<Camera>>::iterator StartIter = m_CameraMap.begin();
	std::multimap<int, SPTR<Camera>>::iterator EndIter = m_CameraMap.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->second == _camera)
		{
			return;
		}
	}
	m_CameraMap.insert(std::multimap<int, SPTR<Camera>>::value_type(_camera->GetOrder(), _camera));
}

bool RenderMgr::IsHasRender(const ComRender * const comReder)
{
	if (comReder == nullptr)
	{
		assert(false);
		return false;
	}
	std::map<int, std::list<SPTR<ComRender>>>::iterator itFinder = m_RenderMap.find(comReder->m_RenderGroup);
	if (itFinder == m_RenderMap.end())
	{
		return false;
	}
	else
	{
		std::list<SPTR<ComRender>>::iterator itListStart = itFinder->second.begin();
		std::list<SPTR<ComRender>>::iterator itListEnd = itFinder->second.end();

		for (; itListStart != itListEnd; ++itListStart)\
		{
			if ((*itListStart) == comReder)
			{
				return true;
			}
		}
	}
	return false;

}

void RenderMgr::PushRender(ComRender * _Renderer)
{
	if (_Renderer == nullptr)
	{
		assert(false);
		return;
	}
	std::map<int, std::list<SPTR<ComRender>>>::iterator itFinder = m_RenderMap.find(_Renderer->m_RenderGroup);

	if (itFinder == m_RenderMap.end())
	{
		std::list<SPTR<ComRender>> newList;
		newList.push_back(_Renderer);
		m_RenderMap.insert(std::map<int, std::list<SPTR<ComRender>>>::value_type(_Renderer->m_RenderGroup, newList));
	}
	else
	{
		std::list<SPTR<ComRender>>::iterator itListStart = itFinder->second.begin();
		std::list<SPTR<ComRender>>::iterator itListEnd = itFinder->second.end();

		for (; itListStart != itListEnd; ++itListStart)\
		{
			if ((*itListStart) == _Renderer)
			{
				assert(false && L"Renderer 중복");
				return;
			}
		}
		itFinder->second.push_back(_Renderer);
	}
}

void RenderMgr::CreateRenderOrder(int _order)
{
	std::map<int, std::list<SPTR<ComRender>>>::iterator itFind = m_RenderMap.find(_order);

	if (itFind == m_RenderMap.end())
	{
		m_RenderMap.insert(std::map<int, std::list<SPTR<ComRender>>>::value_type(_order, std::list<SPTR<ComRender>>()));
	}
}

void RenderMgr::Init()
{
}

void RenderMgr::Render()
{
	it_CameraMapStart = m_CameraMap.begin();
	it_CameraMapEnd = m_CameraMap.end();

	for (; it_CameraMapStart != it_CameraMapEnd; ++it_CameraMapStart)
	{
		if (it_CameraMapStart->second->IsUpdate() == false)
		{
			continue;
		}
		CameraRender(it_CameraMapStart);
	}

}

void RenderMgr::CameraRender(const std::multimap<int, SPTR<Camera>>::iterator & _it)
{
	std::map<int, std::list<SPTR<ComRender>>>::iterator FindGroup;
	for (size_t i = 0; i < _it->second->GetLayerNumber(); ++i)
	{
		if (_it->second->CheckLayerOn((int)i) == false)
		{
			continue;
		}

		FindGroup = m_RenderMap.find((int)i);

		if (FindGroup == m_RenderMap.end())
		{
			assert(false && L"없는 렌더그룹입니다");
			continue;
		}

		if (FindGroup->second.size() == 0)
		{
			continue;
		}

		itYSort = m_YSet.find((int)i);
		if (itYSort != m_YSet.end())
		{
			FindGroup->second.sort(YSortFunc);
		}
		itZSort = m_ZSet.find((int)i);
		if (itZSort != m_ZSet.end())
		{
			FindGroup->second.sort(ZSortFunc);
		}

		GroupRender(_it->second, FindGroup->second);
	}
}
void RenderMgr::Release()
{
	it_CameraMapStart = m_CameraMap.begin();
	it_CameraMapEnd = m_CameraMap.end();

	// 컴포넌트 카메라를 지우는 것이 아닌 렌더매니저의 리스트에서만 뺀다.
	for (; it_CameraMapStart != it_CameraMapEnd;)
	{
		if (true == it_CameraMapStart->second->IsDeath())
		{
			it_CameraMapStart = m_CameraMap.erase(it_CameraMapStart);
		}
		else {
			++it_CameraMapStart;
		}
	}

	// 컴포넌트 렌더러를 지우는 것이 아닌 렌더매니저의 리스트에서만 뺀다.
	it_RenderMapStart = m_RenderMap.begin();
	it_RenderMapEnd = m_RenderMap.end();

	for (; it_RenderMapStart != it_RenderMapEnd; ++it_RenderMapStart)
	{
		if (it_RenderMapStart->second.size() <= 0)
		{
			continue;
		}
		it_ListStart = it_RenderMapStart->second.begin();
		it_ListEnd = it_RenderMapStart->second.end();
		for (; it_ListStart != it_ListEnd; )
		{
			if ((*it_ListStart)->IsDeath() == true)
			{
				it_ListStart = it_RenderMapStart->second.erase(it_ListStart);
			}
			else
			{
				++it_ListStart;
			}
		}

	}
}
void RenderMgr::GroupRender(SPTR<Camera> _camera, std::list<SPTR<ComRender>>& _list)
{

	it_ListStart = _list.begin();
	it_ListEnd = _list.end();
	for (; it_ListStart != it_ListEnd; ++it_ListStart)
	{
		if ((*it_ListStart)->IsUpdate() == false)
		{
			continue;
		}
		(*it_ListStart)->Render(_camera->GetMatrixVP());
	}
}

void RenderMgr::YSortOn(int _index)
{
	itYSort = m_YSet.find(_index);
	if (itYSort == m_YSet.end())
	{
		m_YSet.insert(_index);
	}
}

void RenderMgr::YSortOff(int _index)
{
	itYSort = m_YSet.find(_index);
	if (itYSort != m_YSet.end())
	{
		m_YSet.erase(itYSort);
	}
}

void RenderMgr::ZSortOn(int _index)
{
	itZSort = m_ZSet.find(_index);
	if (itZSort == m_ZSet.end())
	{
		m_ZSet.insert(_index);
	}
}

void RenderMgr::ZSortOff(int _index)
{
	itZSort = m_ZSet.find(_index);
	if (itZSort != m_ZSet.end())
	{
		m_ZSet.erase(itZSort);
	}
}
