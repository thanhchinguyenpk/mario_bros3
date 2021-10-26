#include "Koompas.h"

//#include "Goomba.h"
#include "Mario.h"

//extern  CMario* mario;
Koompas::Koompas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(CONCO_STATE_WALKING_LEFT);

	//player = mario;
}

void Koompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING|| 
		state == CONCO_STATE_WAS_BROUGHT||state == CONCO_STATE_SHELL_MOVING ||
		state == CONCO_STATE_INDENT_OUT)
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
	if (state == CONCO_STATE_WAS_BROUGHT)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x+50, y-40);
		//return;
	}
	if (state != CONCO_STATE_WAS_BROUGHT)
		vy += 0.002 * dt;
	//vx += ax * dt;

	if ((state == CONCO_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float no_thing;
	CCollision::GetInstance()->Process(this, dt, coObjects);


	if (state == GOOMBA_STATE_INDENT_IN && GetTickCount64() - time_to_indent_out > 7000)
	{
		SetState(CONCO_STATE_SHELL_MOVING);

	}
	if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > 10000)
	{
		SetState(CONCO_STATE_INDENT_OUT);

	}
	if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > 12000)
	{
		SetPosition(this->x, this->y - 32);//để khi thọt ra mai rùa không bị rơi xuống
		SetState(CONCO_STATE_WALKING_LEFT);
	}


	/*float l_a, t_a, r_a, b_a;
	float l_b, t_b, r_b, b_b;
	this->GetBoundingBox(l_a, t_a, r_a, b_a);
	player->GetBoundingBox(l_b, t_b, r_b, b_b);

	if (this->CheckOverLap(l_a, t_a, r_a, b_a, l_b, t_b, r_b, b_b))
	{
		DebugOut(L"[INFO] đã vô hàm checkoverlap \n");
	}*/

	//DebugOut(L"[INFO] state con co la: %d \n",state);


	/*
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
	*/
}


void Koompas::Render()
{
	int aniId = CONCO_ANI_GREEN_WALKING_LEFT;
	if (state == CONCO_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	//else if (state == GOOMBA_STATE_INDENT_IN||state==400 || state == CONCO_STATE_WAS_BROUGHT)// á
	//{
	//	aniId = ID_ANI_KOOMPAS_INDENT_IN;
	//}
	else
	{
		
		if (state == CONCO_STATE_WALKING_LEFT)
		{
			if (vx > 0)
				aniId = CONCO_ANI_GREEN_WALKING_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_WALKING_LEFT;
		}
		else if (state == GOOMBA_STATE_INDENT_IN)
		{
			aniId = CONCO_ANI_GREEN_THUT_VAO;
		}
		else if (state == GOOMBA_STATE_SHELL_RUNNING)
		{
			aniId = CONCO_ANI_GREEN_MAI_RUA_CHAY;
		}
		else if (state == CONCO_STATE_SHELL_MOVING)
		{
			aniId = CONCO_ANI_GREEN_SHELL_MOVING;
		}
		else if (state == CONCO_STATE_INDENT_OUT)
		{
			aniId = CONCO_ANI_GREEN_INDENT_OUT;
		}

	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//for (int i = 0; i < 9; i++)
	//	animations->Get(716 + i)->Render(x + i * 50, y);

	RenderBoundingBox();
}

void Koompas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -GOOMBA_WALKING_SPEED;
		//vx = 0;
		break;
	case GOOMBA_STATE_INDENT_IN:
		//vx = -GOOMBA_WALKING_SPEED;
		vx = 0;
		vy = 0; 
		time_to_indent_out = GetTickCount64();
		//ax = 0;
		//ay = 0;
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		vx = 0.02;
		//vy = 0;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		//vy = 0;
		break;
	case CONCO_STATE_INDENT_OUT:

		break;

		
		
	}
}
