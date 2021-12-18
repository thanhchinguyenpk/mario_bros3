#include "StoneKoompas.h"


StoneKoompas::StoneKoompas(float x, float y) :CGameObject(x, y)
{
}

void StoneKoompas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void StoneKoompas::Render()
{
	CAnimations::GetInstance()->Get(718)->Render(x, y);



	RenderBoundingBox();
}

void StoneKoompas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void StoneKoompas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void StoneKoompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOMPAS_BBOX_WIDTH / 2;
	top = y - KOOMPAS_BBOX_HEIGHT / 2;
	right = left + KOOMPAS_BBOX_WIDTH;
	bottom = top + KOOMPAS_BBOX_HEIGHT;
}
