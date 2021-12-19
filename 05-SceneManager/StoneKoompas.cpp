#include "StoneKoompas.h"


StoneKoompas::StoneKoompas(float x, float y) :CGameObject(x, y)
{
	this->SetState(STONE_KOOMPAS_STATE_WALKING_LEFT);
}

void StoneKoompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STONE_KOOMPAS_STATE_DIE)
	{
		left = x - STONE_KOOMPAS_BBOX_WIDTH_DIE / 2;
		top = y - STONE_KOOMPAS_BBOX_HEIGHT_DIE / 2;
		right = left + STONE_KOOMPAS_BBOX_WIDTH_DIE;
		bottom = top + STONE_KOOMPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOMPAS_BBOX_WIDTH / 2;
		top = y - KOOMPAS_BBOX_HEIGHT / 2;
		right = left + KOOMPAS_BBOX_WIDTH;
		bottom = top + KOOMPAS_BBOX_HEIGHT;
	}

}


void StoneKoompas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.002 * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void StoneKoompas::Render()
{
	/*CAnimations::GetInstance()->Get(6000)->Render(x, y);
	CAnimations::GetInstance()->Get(6001)->Render(x+50, y); // xà xuống lúc đội đầu
	CAnimations::GetInstance()->Get(6002)->Render(x + 100, y);
	CAnimations::GetInstance()->Get(6003)->Render(x + 200, y);
	*/

	/*CAnimations::GetInstance()->Get(6010)->Render(x, y);
	CAnimations::GetInstance()->Get(6011)->Render(x + 50, y);
	CAnimations::GetInstance()->Get(6012)->Render(x + 100, y);
	CAnimations::GetInstance()->Get(6013)->Render(x + 200, y);*/

	int idAni = 6000;

	if(vx<0)
		idAni = ANI_STONE_KOOMPAS_WALKING_LEFT;
	else if(vx>0)
		idAni = ANI_STONE_KOOMPAS_WALKING_RIGHT;
	else
	{
		if (state == STONE_KOOMPAS_STATE_DIE)
			idAni = 6002;
	}


	CAnimations::GetInstance()->Get(idAni)->Render(x, y);
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



void StoneKoompas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STONE_KOOMPAS_STATE_DIE:
		//die_start = GetTickCount64();
		//y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		is_block = 0;
		//ay = 0;
		break;
	case STONE_KOOMPAS_STATE_WALKING_LEFT:
		vx = -0.06;
		break;
	case STONE_KOOMPAS_STATE_WALKING_RIGHT:
		vx = 0.06;
		break;
	}
}
