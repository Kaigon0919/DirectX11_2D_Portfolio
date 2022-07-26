#pragma once
#include"IRefCount.h"

#include<map>
#include<list>
#include<set>

class RenderMgr
{
public:	
	friend class Level;
	friend class Camera;
	friend class ComRender;
private:
	std::multimap<int, SPTR<Camera> > m_CameraMap;
	std::multimap<int, SPTR<Camera>>::iterator it_CameraMapStart;
	std::multimap<int, SPTR<Camera>>::iterator it_CameraMapEnd;

private:
	void InsertCamera(Camera* _camera);

private:
	std::map<int, std::list<SPTR<ComRender>>> m_RenderMap;
	std::map<int, std::list<SPTR<ComRender>>>::iterator it_RenderMapStart;
	std::map<int, std::list<SPTR<ComRender>>>::iterator it_RenderMapEnd;
	std::list<SPTR<ComRender>>::iterator it_ListStart;
	std::list<SPTR<ComRender>>::iterator it_ListEnd;

	std::set<int>::iterator itYSort;
	std::set<int> m_YSet;
	std::set<int>::iterator itZSort;
	std::set<int> m_ZSet;
public:
	bool IsHasRender(const ComRender  * const comReder);
private:
	void PushRender(ComRender* _Renderer);
	void CreateRenderOrder(int _order);
	void GroupRender(SPTR<Camera> _camera, std::list<SPTR<ComRender>>& _list);
public:
	void YSortOn(int _index);
	void YSortOff(int _index);
	void ZSortOn(int _index);
	void ZSortOff(int _index);
private:
	void Init();
	void Render();
	void CameraRender(const std::multimap<int, SPTR<Camera>>::iterator& _it);
public:
	void Release();
private:
	RenderMgr();
	virtual ~RenderMgr();
};

