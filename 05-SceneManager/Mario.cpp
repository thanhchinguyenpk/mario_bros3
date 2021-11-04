﻿#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koompas.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "ParaGoompa.h"
#include "GameTime.h"
#include "BrickCoin.h"
#include "Mushroom.h"

#include "SuperLeaf.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy_store = vy; // nhảy từ dưới lên được


	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
		DebugOut(L"[INFO] vo day ko?\n");
	}


	DebugOut(L"[INFO]maxVx la: %f\n", maxVx);
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);


	if (jump_down_to_up == true)
	{
		SetPosition(x, y-1);
		jump_down_to_up = false;
		//DebugOut(L"[INFO] vo day khoooooooooooooooooooooooooong \n" );
	}


	if (is_kick==true && GetTickCount64() - kick_start >=200  && kick_start)
	{
		
		kick_start = 0;
		is_kick = false;
	
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<Koompas*>(e->obj))
		OnCollisionWithKoompas(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<ParaGoompa*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<BrickCoin*>(e->obj))
		OnCollisionWithBrickCoin(e);
	else if (dynamic_cast<Mushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<SuperLeaf*>(e->obj))
		OnCollisionWithSuperLeaf(e);
	else if (dynamic_cast<FlatForm*>(e->obj))
		OnCollisionWithFlatForm(e);
}

void CMario::OnCollisionWithFlatForm(LPCOLLISIONEVENT e)
{

	if (e->ny > 0)
	{
		jump_down_to_up = true;
		vy = vy_store;
	}

}

void CMario::OnCollisionWithKoompas(LPCOLLISIONEVENT e)
{
	Koompas* koompas = dynamic_cast<Koompas*>(e->obj);

//	koompas->SetState(CONCO_STATE_WAS_SHOOTED);

	
	if (e->ny < 0)
	{
		if (koompas->GetState() == GOOMBA_STATE_INDENT_IN|| koompas->GetState() == CONCO_STATE_INDENT_OUT ||
			koompas->GetState() == CONCO_STATE_SHELL_MOVING)
		{

			koompas->SetState(GOOMBA_STATE_SHELL_RUNNING);
		}
		else
		{
			koompas->SetState(GOOMBA_STATE_INDENT_IN);
		}
		koompas->UpdatePositionVertiacally();
		
	
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else
	{
		if (e->nx != 0)
		{
			if (koompas->GetState() == GOOMBA_STATE_INDENT_IN || koompas->GetState() == CONCO_STATE_INDENT_OUT ||
				koompas->GetState() == CONCO_STATE_SHELL_MOVING)
			{
				if (GetState() == MARIO_STATE_WALKING_RIGHT || GetState() == MARIO_STATE_WALKING_LEFT)
				{
					this->SetState(MARIO_STATE_KICK);
					koompas->SetState(GOOMBA_STATE_SHELL_RUNNING);
				}
			}
			else
				CollideWithEnemy();

		}
		else
			CollideWithEnemy(); // truowngf hop nhay tu tren xuong cham marrio
	}
	
	/*if (koompas->GetState() == GOOMBA_STATE_SHELL_RUNNING ||
		koompas->GetState() == CONCO_STATE_WALKING_LEFT || 
		koompas->GetState() == CONCO_STATE_WALKING_LEFT)
	{
		
	}*/

}
void CMario::OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	//coin++;

}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(MARIO_LEVEL_BIG);
	

}
void CMario::OnCollisionWithBrickCoin(LPCOLLISIONEVENT e)
{
	BrickCoin* brick = dynamic_cast<BrickCoin*>(e->obj);
	if (e->ny > 0)
	{
		if (brick->is_hit == false)
			brick->SetState(BRICK_COIN_STATE_DA_DAP);
	}


	
}


void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	ParaGoompa* paragoomba = dynamic_cast<ParaGoompa*>(e->obj);
	if (e->ny < 0) // phương va chạm hướng lên
	{
		//score += 100;
		if (paragoomba->GetState() == PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING)
		{
			paragoomba->SetState(PARA_GOOMBA_STATE_DIE);
			//paragoomba->used = true;
			//DebugOut(L"[ERROR-------------para die?----------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
		}
		else
			paragoomba->SetState(PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING);

		vy = -MARIO_JUMP_DEFLECT_SPEED;

	}
	else
	{
		CollideWithEnemy();
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	//goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
	//vy = -MARIO_JUMP_DEFLECT_SPEED;



	
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		//if (untouchable == 0)
		//{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
			/*	if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					
				}
				else
				{
					
					SetState(MARIO_STATE_DIE);
				}*/

				CollideWithEnemy();
				
			}
		//}
	}

	
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::CollideWithEnemy()
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}

		else
			SetState(MARIO_STATE_DIE);
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)//==false
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				/*if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else 
					aniId = ID_ANI_MARIO_WALKING_RIGHT;*/
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else 
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else 
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	if (is_kick == true)
	{
		if (nx == 1)
			aniId = 439;
		else
			aniId = 539;
	}

	return aniId;
}
//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				// chỗ này lần milestone1
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else 
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId =  ID_ANI_MARIO_BRACE_RIGHT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	if (is_kick == true)
	{
		if(nx==1)
			aniId = 440;
		else
			aniId = 540;
	}

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;
	if (isSitting)
	{
		if (nx > 0)
			aniId = MARIO_ANI_TAIL_SITDOWN_RIGHT;
		else
			aniId = MARIO_ANI_TAIL_SITDOWN_RIGHT+TO_BECOME_LEFT;
	}
	else
		if (vx == 0)
		{
			if (nx > 0) aniId = MARIO_ANI_TAIL_IDLE_RIGHT;
			else aniId = MARIO_ANI_TAIL_IDLE_RIGHT+TO_BECOME_LEFT;
		}
		else if (vx > 0)
		{
			// chỗ này lần milestone1
			if (ax < 0)
				aniId = MARIO_ANI_TAIL_SKID_LEFT;
			else if (vx == MARIO_RUNNING_SPEED)
				aniId = MARIO_ANI_TAIL_RUN_RIGHT;
			else
				aniId = MARIO_ANI_TAIL_WALKING_RIGHT;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = MARIO_ANI_TAIL_SKID_LEFT + TO_BECOME_LEFT;
			else if (vx == -MARIO_RUNNING_SPEED)
				aniId = MARIO_ANI_TAIL_RUN_RIGHT + TO_BECOME_LEFT;
			else
				aniId = MARIO_ANI_TAIL_WALKING_RIGHT + TO_BECOME_LEFT;
		}

	if (aniId == -1) aniId = MARIO_ANI_ORANGE_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (isSitting)
	{
		if (nx > 0)
			aniId = MARIO_ANI_ORANGE_SITDOWN_RIGHT;
		else
			aniId = MARIO_ANI_ORANGE_SITDOWN_RIGHT  + TO_BECOME_LEFT;
	}
	else
		if (vx == 0)
		{
			if (nx > 0) aniId = MARIO_ANI_ORANGE_IDLE_RIGHT;
			else aniId = MARIO_ANI_ORANGE_IDLE_RIGHT  +  TO_BECOME_LEFT;
		}
		else if (vx > 0)
		{
			// chỗ này lần milestone1
			if (ax < 0)
				aniId = MARIO_ANI_ORANGE_SKID_LEFT;
			else if (vx == MARIO_RUNNING_SPEED)
				aniId = MARIO_ANI_ORANGE_RUN_RIGHT;
			else
				aniId = MARIO_ANI_ORANGE_WALKING_RIGHT;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = MARIO_ANI_ORANGE_SKID_LEFT+ TO_BECOME_LEFT;
			else if (vx == -MARIO_RUNNING_SPEED)
				aniId = MARIO_ANI_ORANGE_RUN_RIGHT+TO_BECOME_LEFT;
			else
				aniId = MARIO_ANI_ORANGE_WALKING_RIGHT + TO_BECOME_LEFT;
		}

	if (aniId == -1) aniId = MARIO_ANI_ORANGE_IDLE_RIGHT;
	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_BIG_TAIL)
		aniId = GetAniIdTail();
	else if (level == MARIO_LEVEL_BIG_ORANGE)
		aniId = GetAniIdFire();
	

	/*int count = 402;
	GameTime* game_time = GameTime::GetInstance();

	if (game_time->gameTime % 4 == 1)
	{
		DebugOut(L"lin da xin chào cả nhà ố là la %d\n", count);
	}*/
	
	//for(int i=0;i<8;i++)
		//animations->Get(539 +i)->Render(x +i*60, y);

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		//ax = MARIO_ACCEL_RUN_X;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		//ax = 0;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		//ax = 0;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
			{
				vy = -MARIO_JUMP_SPEED_Y;
				vx = nx==1?0.3:-0.3;
			}
		
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_KICK:
		kick_start = GetTickCount64();
		is_kick = true;
		break;

		
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG|| level == MARIO_LEVEL_BIG_ORANGE)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_BIG_TAIL)
	{ /*#define MARIO_BIG_TAIL_BBOX_WIDTH  21*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22*3
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 19*3*/


		if (isSitting)
		{
			left = x - MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH;
			bottom = top + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_TAIL_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_BIG_TAIL_BBOX_HEIGHT;
		}

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL|| level == MARIO_LEVEL_BIG_TAIL|| level == MARIO_LEVEL_BIG_ORANGE)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

