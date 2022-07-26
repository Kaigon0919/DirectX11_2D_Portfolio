#include "Gate.h"
#include"Player.h"
#include<Col2DRect.h>
#include<Render2DSprite.h>
#include<Level.h>
#include"Fade.h"

bool Gate::Init()
{
	SPTR<Col2DRect> Col = AddComponent<Col2DRect>(L"Gate");
	Col->PushEnterFunc(&Gate::ColEnter, this);
	Col->PushStayFunc(&Gate::ColStay, this);
	Col->PushExitFunc(&Gate::ColExit, this);

	GetActor()->GetLevel()->CMgr.ColLink(L"Gate", L"PlayerMove");

	return true;
}

void Gate::Update()
{
	if (m_bNext)
	{
		if (m_Fade->IsFadeOutComplete())
		{
			switch (type)
			{
			case Gate::GT_LEVELGATE:
				GetActor()->GetLevel()->ChangeLevel(NextLevelName.c_str());
				break;
			case Gate::GT_POSGATE:

				break;
			case Gate::GT_MAX:
				break;
			default:
				break;
			}
			player->SetVirtualPosition(NextLevelPos);
			m_bNext = false;
		}
	}
}

void Gate::LateUpdate()
{
}

void Gate::DebugRender()
{
}

void Gate::ColEnter(ComCol *, ComCol * other)
{
	player = other->GetActor()->GetComponent<Player>();
	if (player != nullptr)
	{
		m_bNext = true;
		m_Fade->FadeOut();
	}
}

void Gate::ColStay(ComCol * , ComCol * other)
{
}

void Gate::ColExit(ComCol * , ComCol * other)
{
}

void Gate::SetNextLevel(const std::wstring next)
{
	NextLevelName = next;
}

void Gate::SetNextPos(const Vector3f & Pos)
{
	NextLevelPos = Pos;
}

void Gate::SetType(GateType _type)
{
	type = _type;
}

void Gate::SetSprite(const wchar_t * sprite)
{
	SPTR<Transform> trans = GetComponent<Transform>();
	SPTR<Render2DSprite> Render = AddComponent<Render2DSprite>(1);
	if (Render != nullptr)
	{
		Render->SetSprite(sprite);
		trans->SetLocalScale(Render->GetImageSIze());
	}
}

void Gate::SetFaid(SPTR<Fade> fade)
{
	m_Fade = fade;
}

Gate::Gate() : type(GateType::GT_POSGATE) , m_bNext(false)
{
}


Gate::~Gate()
{
}
