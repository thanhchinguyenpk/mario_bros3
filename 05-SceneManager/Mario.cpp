#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Koompas.h"

#include "Collision.h"
#include "MarioBullet.h"
#include "Brick.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy_store = vy; // nhảy từ dưới lên được
	
	
	

	if(state!= MARIO_STATE_FLY)
		vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	//if (GetState() == MARIO_STATE_STAND_SHOOT && GetTickCount64() - throw_start > 800 && throw_start)
	if (GetState() == MARIO_STATE_STAND_SHOOT && GetTickCount64() - throw_start >= 400 && throw_start)
	{
		SetState(MARIO_STATE_IDLE);
		throw_start = 0;
		
	}
	if (GetState() == MARIO_STATE_SPIN && GetTickCount64() - spin_start >= 600&& spin_start)
	{
		SetState(MARIO_STATE_IDLE);
		spin_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}
	if (GetState() == MARIO_STATE_FLY && GetTickCount64() - fly_start >= 300 && fly_start)
	{
		SetState(MARIO_STATE_IDLE);
		fly_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}
	//DebugOut(L"[INFO] state la: %d\n", state);
	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects,y_store);
	if (jump_down_to_up == true)
	{
		SetPosition(x, y-1);
		jump_down_to_up = false;
	}

	//DebugOut(L"[INFO] vy la: %f\n", vy);
	DebugOut(L"[INFO] x thực sự %f\n", x);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	DebugOut(L"[INFO] khong chamk yy\n");
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (e->ny != 0 && e->obj->IsBlocking()) // hàm ảo: nếu vật thể đó là block
	{
		vy_store = vy;
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx > 0  && e->obj->IsBlocking()) //<0 là từ bên trái di chuyển qua phải  //e->nx !=0 
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<Koompas*>(e->obj))
		OnCollisionWithKoompas(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);

	if (holding_something != NULL)
	{
		if (isHolding == false)
		{
			Koompas* koompas = dynamic_cast<Koompas*>(holding_something);
			koompas->SetState(GOOMBA_STATE_SHELL_RUNNING);
			holding_something = NULL;
		
		}
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	
	if (e->ny > 0)
	{
		/*DebugOut(L"[INFO] co vo va cham chieu duoi len ko?\n");
		float x_, y_;
		GetPosition(x_, y_);*/

		jump_down_to_up = true;
		vy = vy_store;
		//y += y_store*2;

		//SetPosition(x_, y+400);
		//vy = vy_store;
		
	}
	
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);


	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		/*if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}*/
	}
	else // hit by Goomba
	{
		/*if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}*/

		//DebugOut(L"[INFO] trung koompas không bên trong %d\n");

	}
	DebugOut(L"[INFO] trung koompas không bên ngoài %d\n");
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{/*
	e->obj->Delete();
	coin++;*/
	//DebugOut(L"[INFO] mario cham gach?\n");
	//DebugOut(L"[INFO] x trước %f\n",x);
	//SetPosition(x+300, y);
	//DebugOut(L"[INFO] x sau %f\n", x);
	
}

void CMario::OnCollisionWithKoompas(LPCOLLISIONEVENT e)
{
	Koompas* koompas = dynamic_cast<Koompas*>(e->obj);
	if (e->ny < 0)
	{
		float x, y;
		koompas->GetPosition(x, y);
		koompas->SetPosition(x, y - 1); // trừ bớt để khi đội đầu không bị rớt ra khỏi thế giới
		if (koompas->GetState() != GOOMBA_STATE_INDENT_IN)
		{
			koompas->SetState(GOOMBA_STATE_INDENT_IN);
			
		}
		else if(koompas->GetState() == GOOMBA_STATE_INDENT_IN)
		{
			koompas->SetState(GOOMBA_STATE_SHELL_RUNNING);
			
		}
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else
	{
		if (isHolding ==true)
		{
			if (koompas->GetState() == GOOMBA_STATE_INDENT_IN)
			{
				holding_something = koompas;
				koompas->SetState(GOOMBA_STATE_BEING_HOLDING);
			}
		}
		

		
		
	}

	

	

}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT; // là nhảy lên
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
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
	}
	else
	{
		if(state== MARIO_STATE_STAND_SHOOT)
		aniId = ID_ANI_MARIO_BIG_FIRE_SHOOT_BULLET_RIGHT;
	}


	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_FIRE_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		
		if (nx >= 0)
			aniId = ID_ANI_MARIO_BIG_TAIL_JUMP_RIGHT;
		if (state == MARIO_STATE_FLY)
			aniId = ID_ANI_MARIO_BIG_TAIL_FLY_DOWN_RIGHT;
	}
	else
	{
		if (state == MARIO_STATE_SPIN)
			aniId = ID_ANI_MARIO_BIG_TAIL_SPIN_RIGHT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_TAIL_STAND_RIGHT;

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
		if (abs(ax) == MARIO_ACCEL_RUN_X)
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
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == 3)
		aniId = GetAniIdFire();
	else if (level == 4)
		aniId = GetAniIdTail();
	//ID_ANI_MARIO_BIG_TAIL_SPIN_RIGHT
	animations->Get(aniId)->Render(x, y);
	//DebugOut(L"[INFO] anii: %d\n", aniId);
	RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
		//MARIO_STATE_FLY
	case MARIO_STATE_FLY:
		fly_start = GetTickCount64();
		vy = -0.02;
		break;
	case MARIO_STATE_SPIN:
		spin_start = GetTickCount64();
		break;
	case MARIO_STATE_STAND_SHOOT:
		throw_start = GetTickCount64();
		this->attack();

		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -(MARIO_JUMP_RUN_SPEED_Y+0.2);
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else
		{

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
	}

	CGameObject::SetState(state);
}

extern list<LPGAMEOBJECT> objects;

void CMario::attack()
{
	MarioBullet *temp = new MarioBullet(this->x,this->y);
	objects.push_back(temp);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG|| level == 3)
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
	if (level== 4)
	{
		//MARIO_TAIL_BBOX_WIDTH
		//MARIO_TAIL_BBOX_HEIGHT
		if (this->GetState() == MARIO_STATE_SPIN)
		{
			//chỗ này nè
			/*left = x - MARIO_TAIL_BBOX_WIDTH / 2-90;
			top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_BBOX_HEIGHT;*/

			left = x - MARIO_TAIL_BBOX_WIDTH / 2 - 90;
			//top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
			top = y - 5;

			right = x + MARIO_TAIL_BBOX_WIDTH / 2 + 90;
			bottom = y + MARIO_TAIL_BBOX_HEIGHT / 2;
		}
		else
		{
			left = x - MARIO_TAIL_BBOX_WIDTH / 2;
			top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_BBOX_HEIGHT;
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
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

