#include "Koompas.h"

#include "Goomba.h"
#include "Mario.h"

#define KOOMPAS_VY_WAS_SHOOTED 0.6f
#define KOOMPAS_VX_WAS_SHOOTED 0.1f
#define KOOMPAS_VX_SHELL_RUNNING 0.4f

#define GAP_ANI_TO_RED 8

#define GAP_AVOID_FALLING_DOWN 32

Koompas::Koompas(float x, float y, LPGAMEOBJECT mario,int koompas_type, int koompas_state) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;

	type = koompas_type;
	//SetState(CONCO_STATE_FLY_LEFT);
	//SetState(koompas_state);
	SetState(koompas_state);
	player = mario;
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
		left = x - KOOMPAS_BBOX_WIDTH / 2;
		top = y - KOOMPAS_BBOX_HEIGHT / 2;
		right = left + KOOMPAS_BBOX_WIDTH;
		bottom = top + KOOMPAS_BBOX_HEIGHT;
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
	//if (dynamic_cast<Koompas*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (e->ny != 0)
	{
		if (state == CONCO_STATE_FLY_LEFT|| state == CONCO_STATE_FLY_RIGHT)
			vy = -KOOMPAS_FLYING_SPEED_Y;
		else vy = 0;
	}
	else if (e->nx != 0)
	{
		if (!dynamic_cast<Koompas*>(e->obj))
			vx = -vx;
	}


	if (dynamic_cast<Koompas*>(e->obj))
		OnCollisionWithKoompas(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<FlatForm*>(e->obj))
		OnCollisionWithFlatForm(e);
	 


}



void Koompas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	

	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	if (state == GOOMBA_STATE_SHELL_RUNNING)
	{

	/*	if (goomba->GetX() < this->GetX())
		{
			goomba->is_minus_vx = true;
		}*/
		
	}
	goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
	DebugOut(L"[INFO] vô 2 con và cham ko?\n");

}

void Koompas::OnCollisionWithKoompas(LPCOLLISIONEVENT e)
{
	Koompas* koompas = dynamic_cast<Koompas*>(e->obj);

	/*if (koompas->GetState() == GOOMBA_STATE_SHELL_RUNNING)
	{

		if ( this->GetX() < koompas->GetX() )
		{
			is_minus_vx = true;
			DebugOut(L"[INFO] vô bị shoot ko?\n");
		}

		this->SetState(CONCO_STATE_WAS_SHOOTED);
	}*/

	if (koompas->state == GOOMBA_STATE_SHELL_RUNNING)
	{

		if ( koompas->GetX()>this->GetX()  )
		{
			DebugOut(L"[INFO] heloo? %d\n", koompas->state);
				//koompas->is_minus_vx = true;//vx=is_minus_vx?-0.1:0.1;
				this->is_minus_vx = true;
		}
		//koompas->SetState(CONCO_STATE_WAS_SHOOTED);
			SetState(CONCO_STATE_WAS_SHOOTED);

		
	}

	
	//koompas->SetState(CONCO_STATE_WAS_SHOOTED);
	
}

void Koompas::OnCollisionWithFlatForm(LPCOLLISIONEVENT e)
{
	if (type != KOOMPAS_RED)
		return;

	FlatForm* flatform = dynamic_cast<FlatForm*>(e->obj);

	if (this->x > flatform->GetX() + flatform->width- flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	{
		vx = -abs(vx);
		DebugOut(L"[INFO] alo chi em tui?\n");
	}
	else if (this->x < flatform->GetX() - flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	{
		vx = abs(vx);
		DebugOut(L"[INFO] alo chi em tui?\n");
	}

}

void Koompas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[INFO] heloo? %d \n",state);

	//DebugOut(L"[INFO] state koompas %d \n",state);

	/*if (state == CONCO_STATE_WAS_BROUGHT)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x+50, y-40);
		//return;
	}
	if (state != CONCO_STATE_WAS_BROUGHT)
		vy += 0.002 * dt;

	*/
	//vx += ax * dt;

	if ((state == CONCO_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);// ủa đê chi
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
		SetPosition(this->x, this->y - GAP_AVOID_FALLING_DOWN);//để khi thọt ra mai rùa không bị rơi xuống
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
	} else
	{
		
		if (state == CONCO_STATE_WALKING_LEFT|| state == CONCO_STATE_WALKING_RIGHT)
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
		else if (state == CONCO_STATE_WAS_SHOOTED)
		{
			aniId = CONCO_ANI_GREEN_WAS_SHOOTED; //ani was shoot
		}
		else if (state == CONCO_STATE_FLY_LEFT|| state == CONCO_STATE_FLY_RIGHT)
		{
			if (vx > 0)
				aniId =  CONCO_ANI_GREEN_FLY_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_FLY_LEFT;
		}
		

	}

	if (type == KOOMPAS_RED)
		aniId -= GAP_ANI_TO_RED;

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
		vx = -KOOMPAS_WALKING_SPEED;
		//vx = 0;
		break;
	case CONCO_STATE_WALKING_RIGHT:
		vx = KOOMPAS_WALKING_SPEED;
		//vx = 0;
		break;
	case GOOMBA_STATE_INDENT_IN:
		//vx = -KOOMPAS_WALKING_SPEED;
		vx = 0;
		vy = 0; 
		time_to_indent_out = GetTickCount64();
		//ax = 0;
		//ay = 0;
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		vx = player->GetX() > x ? -KOOMPAS_VX_SHELL_RUNNING : KOOMPAS_VX_SHELL_RUNNING;
		is_blocking = 1;
		//vx = 0.02;
		//vy = 0;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		//vy = 0;
		break;
	case CONCO_STATE_INDENT_OUT:

		break;
	case CONCO_STATE_WAS_SHOOTED:
		vy = -KOOMPAS_VY_WAS_SHOOTED;
		vx = is_minus_vx?-KOOMPAS_VX_WAS_SHOOTED : KOOMPAS_VX_WAS_SHOOTED;
		//vx = 0.09;
		is_colliable = 0;
		break;

	case CONCO_STATE_FLY_LEFT:
		vx = -KOOMPAS_WALKING_SPEED;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = KOOMPAS_WALKING_SPEED;
		break;
		
		
	}
}
