#include "MarioBullet.h"
#include "Koompas.h"
#include "Goomba.h"
#include "ParaGoompa.h"
#include "VirtalBox.h"

MarioBullet::MarioBullet(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MARIO_BULLET_GRAVITY;
	die_start = -1;
	//SetState(MARIO_BULLET_STATE_WALKING_LEFT);
}


void MarioBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == MARIO_BULLET_STATE_DIE)
	{
		left = x - MARIO_BULLET_BBOX_WIDTH / 2;
		top = y - MARIO_BULLET_BBOX_HEIGHT_DIE / 2;
		right = left + MARIO_BULLET_BBOX_WIDTH;
		bottom = top + MARIO_BULLET_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - MARIO_BULLET_BBOX_WIDTH / 2;
		top = y - MARIO_BULLET_BBOX_HEIGHT / 2;
		right = left + MARIO_BULLET_BBOX_WIDTH;
		bottom = top + MARIO_BULLET_BBOX_HEIGHT;
	}
}

void MarioBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void MarioBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<MarioBullet*>(e->obj)) return;
	if (dynamic_cast<VirtalBox*>(e->obj)) return;
	

	if (e->ny != 0)
	{
		vy = -0.25 * 1.5;
		//vy = -vy;
		//vy = 0;
	}
	else if (e->nx != 0)
	{
		vy = 0;
		vx = 0;
		
		this->Delete();
	}



	if (dynamic_cast<CGoomba*>(e->obj))
	{
		//DebugOut(L"[INFO] hiiiiiii %d\n");
		//this->BeingAttackedByFireBallMario(dynamic_cast<CGoomba*>(e->obj),GOOMBA_STATE_WAS_SHOOTED);
		//BeingAttackedByFireBallMario
		//dynamic_cast<CGoomba*>(e->obj)->SetState(GOOMBA_STATE_WAS_SHOOTED);
		dynamic_cast<CGoomba*>(e->obj)->BeingAttackedByFireBallMario(this, GOOMBA_STATE_WAS_SHOOTED);
	}
	else if(dynamic_cast<Koompas*>(e->obj))
	{
		//DebugOut(L"[INFO] hiiiiiii %d\n");
		//dynamic_cast<Koompas*>(e->obj)->SetState(CONCO_STATE_WAS_SHOOTED);
		dynamic_cast<Koompas*>(e->obj)->BeingAttackedByFireBallMario(this, CONCO_STATE_WAS_SHOOTED);

	}
	else if (dynamic_cast<ParaGoompa*>(e->obj))
	{
		//DebugOut(L"[INFO] hiiiiiii %d\n");
		//dynamic_cast<ParaGoompa*>(e->obj)->SetState(PARA_GOOMBA_STATE_WAS_SHOOTED);
		dynamic_cast<ParaGoompa*>(e->obj)->BeingAttackedByFireBallMario(this, PARA_GOOMBA_STATE_WAS_SHOOTED);

	}
}

void MarioBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == MARIO_BULLET_STATE_DIE) && (GetTickCount64() - die_start > MARIO_BULLET_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);

	this->DeleteWhenOutOfCam();
}


void MarioBullet::Render()
{
	int aniId = ID_ANI_MARIO_BULLET_WALKING;
	if (state == MARIO_BULLET_STATE_DIE)
	{
		aniId = ID_ANI_MARIO_BULLET_DIE;
	}

	CAnimations::GetInstance()->Get(704)->Render(x, y);
	RenderBoundingBox();
}

void MarioBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_BULLET_STATE_DIE:
		die_start = GetTickCount64();
		y += (MARIO_BULLET_BBOX_HEIGHT - MARIO_BULLET_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case MARIO_BULLET_STATE_WALKING_RIGHT:
		vx = MARIO_BULLET_WALKING_SPEED;
		break;
	case MARIO_BULLET_STATE_WALKING_LEFT:
		vx = -MARIO_BULLET_WALKING_SPEED;
		break;
	}
}
