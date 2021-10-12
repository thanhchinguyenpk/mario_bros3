#include "Koompas.h"

//#include "Goomba.h"
#include "Mario.h"

//extern  CMario* mario;
Koompas::Koompas(float x, float y, CMario* mario) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);

	player = mario;
}

void Koompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING|| 
		state == GOOMBA_STATE_BEING_HOLDING)
	{
		left = x - GOOMBA_BBOX_WIDTH_INDENT_IN / 2;
		top = y - GOOMBA_BBOX_HEIGHT_INDENT_IN / 2;
		right = left + GOOMBA_BBOX_WIDTH_INDENT_IN;
		bottom = top + GOOMBA_BBOX_HEIGHT_INDENT_IN;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void Koompas::OnNoCollision(DWORD dt)
{
	
	x += vx * dt;
	y += vy * dt;
	//y += vy * dt;
};

void Koompas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<Koompas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}


}

void Koompas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[INFO] state koompas %d \n",state);
	if (state == GOOMBA_STATE_BEING_HOLDING)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x+50, y-40);
		//return;
	}
	if (state != GOOMBA_STATE_BEING_HOLDING)
		vy += 0.002 * dt;
	//vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float no_thing;
	CCollision::GetInstance()->Process(this, dt, coObjects,no_thing);

	/*float l_a, t_a, r_a, b_a;
	float l_b, t_b, r_b, b_b;
	this->GetBoundingBox(l_a, t_a, r_a, b_a);
	player->GetBoundingBox(l_b, t_b, r_b, b_b);

	if (this->CheckOverLap(l_a, t_a, r_a, b_a, l_b, t_b, r_b, b_b))
	{
		DebugOut(L"[INFO] đã vô hàm checkoverlap \n");
	}*/

	//DebugOut(L"[INFO] state con co la: %d \n",state);
	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);
	//DebugOut(L"[INFO] l của mario %f \n",ml);
	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{
		//SetState(CONCO_STATE_WAS_SHOOTED);
		//DebugOut(L"[INFO] bump, kill koompas  \n");
		DebugOut(L"[INFO] đã vô hàm checkoverlap \n");
		//this->SetState(GOOMBA_STATE_DIE);
	}

	//DebugOut(L"[INFO] vyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy: %f\n", vy);
}


void Koompas::Render()
{
	int aniId = ID_ANI_KOOMPAS_WALKING_LEFT;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_INDENT_IN||state==400 || state == GOOMBA_STATE_BEING_HOLDING)// á
	{
		aniId = ID_ANI_KOOMPAS_INDENT_IN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void Koompas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		vx = 0;
		break;
	case GOOMBA_STATE_INDENT_IN:
		//vx = -GOOMBA_WALKING_SPEED;
		vx = 0;
		vy = 0; 
		//ax = 0;
		//ay = 0;
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		vx = 0.02;
		//vy = 0;
		break;
	case GOOMBA_STATE_BEING_HOLDING:
		vx = 0;
		vy = 0;
		//vy = 0;
		break;
		

		
		
	}
}
