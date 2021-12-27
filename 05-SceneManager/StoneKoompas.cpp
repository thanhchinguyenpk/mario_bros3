#include "StoneKoompas.h"


StoneKoompas::StoneKoompas(float x, float y) :CGameObject(x, y)
{
	this->SetState(STONE_KOOMPAS_STATE_WALKING_LEFT);
}

void StoneKoompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STONE_KOOMPAS_STATE_DIE|| state == STONE_KOOMPAS_STATE_HEAD_MOVING)
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

	if (state == STONE_KOOMPAS_STATE_DIE && GetTickCount64() - time_to_rescure > STONE_KOOMPAS_TIME_TO_DIE)
	{
		
		this->SetState(STONE_KOOMPAS_STATE_HEAD_MOVING);
		
	}
	if (state == STONE_KOOMPAS_STATE_HEAD_MOVING && GetTickCount64() - time_to_rescure > STONE_KOOMPAS_TIME_TO_HEAD_MOVING)
	{
		SetPosition(this->x, this->y - STONE_KOOMPAS_GAP_AVOID_FALLING);

		if(nx<=0)
			this->SetState(STONE_KOOMPAS_STATE_WALKING_LEFT);
		else
			this->SetState(STONE_KOOMPAS_STATE_WALKING_RIGHT);
	}

	DebugOut(L"nx cua sto %d\n", nx);
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

	int idAni = ANI_STONE_KOOMPAS_WALKING_LEFT;

	if(vx<0)
		idAni = ANI_STONE_KOOMPAS_WALKING_LEFT;
	else if(vx>0)
		idAni = ANI_STONE_KOOMPAS_WALKING_RIGHT;
	else
	{
		if (nx == -1)
		{
			if (state == STONE_KOOMPAS_STATE_DIE)
				idAni = ANI_STONE_KOOMPAS_DIE_LEFT;
			else if (state == STONE_KOOMPAS_STATE_HEAD_MOVING)
				idAni = ANI_STONE_KOOMPAS_HEAD_MOVING_LEFT;
		}
		else
		{
			if (state == STONE_KOOMPAS_STATE_DIE)
				idAni = ANI_STONE_KOOMPAS_DIE_RIGHT;
			else if (state == STONE_KOOMPAS_STATE_HEAD_MOVING)
				idAni = ANI_STONE_KOOMPAS_HEAD_MOVING_RIGHT;
		}
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
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		//vx = -vx;
		if (state == STONE_KOOMPAS_STATE_WALKING_LEFT)
			this->SetState(STONE_KOOMPAS_STATE_WALKING_RIGHT);
		else
			this->SetState(STONE_KOOMPAS_STATE_WALKING_LEFT);
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
		time_to_rescure = GetTickCount64();
		//ay = 0;
		break;
	case STONE_KOOMPAS_STATE_HEAD_MOVING:
		vx = 0;
		vy = 0;
		break;
	case STONE_KOOMPAS_STATE_WALKING_LEFT:
		nx = -1;
		vx = -STONE_KOOMPAS_WALKING_SPEED;
		break;
	case STONE_KOOMPAS_STATE_WALKING_RIGHT:
		vx = STONE_KOOMPAS_WALKING_SPEED;
		nx = 1;
		break;
		
	}
}
