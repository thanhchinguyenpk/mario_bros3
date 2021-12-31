#include "Koompas.h"

#include "Goomba.h"
#include "Mario.h"
#include "BrickCoin.h"
#include "BrickBlink.h"
#include "PlayScene.h"



Koompas::Koompas(float x, float y, LPGAMEOBJECT mario,int koompas_type, int koompas_state) :CGameObject(x, y)
{
	this->ax = 0;
	die_start = -1;
	type = koompas_type;
	
	SetState(koompas_state);
	player = dynamic_cast<CMario*>(mario);
	
	if(type== KOOMPAS_RED)
		virtalbox = new VirtalBox(x- GAP_VIRTUAL_BOX, y,mario);

	//CGame* game = CGame::GetInstance();
	//CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
	//scene->objects.push_back(virtalbox);
}

void Koompas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING|| 
		state == CONCO_STATE_WAS_BROUGHT||state == CONCO_STATE_SHELL_MOVING ||
		state == CONCO_STATE_INDENT_OUT|| state == CONCO_STATE_BEING_HOLDING)
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

	/*if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		if (dynamic_cast<CGoomba*>(e->obj)) return;
	}*/


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

			if (type == KOOMPAS_RED)
				if (vx > 0)
					virtalbox->SetPosition(this->x + GAP_VIRTUAL_BOX_TURAROUND_X, y - GAP_VIRTUAL_BOX_TURAROUND_Y);
				else
					virtalbox->SetPosition(this->x - GAP_VIRTUAL_BOX_TURAROUND_X, y - GAP_VIRTUAL_BOX_TURAROUND_Y);
		
		/* {
			if (this->state == CONCO_STATE_WALKING_LEFT)
			{
				this->SetState(CONCO_STATE_WALKING_RIGHT);
				virtalbox->SetPosition(this->x + 50, y);
			}
			else if (this->state == CONCO_STATE_WALKING_RIGHT)
			{
				this->SetState(CONCO_STATE_WALKING_LEFT);
				virtalbox->SetPosition(this->x - 50, y);
			}
		}*/
		
	}


	if (dynamic_cast<Koompas*>(e->obj))
		OnCollisionWithKoompas(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<FlatForm*>(e->obj))
		OnCollisionWithFlatForm(e);
	else if (dynamic_cast<BrickCoin*>(e->obj))
		OnCollisionWithBrickCoin(e);
	else if (dynamic_cast<BrickBlink*>(e->obj))
		OnCollisionWithBrickBlink(e);
	 


}


void Koompas::OnCollisionWithBrickBlink(LPCOLLISIONEVENT e)
{
	if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		BrickBlink* brick_blink = dynamic_cast<BrickBlink*>(e->obj);
		if (e->nx != 0)
		{
			if (brick_blink->GetState() == BRICKBLINK_STATE_BRICK)
				brick_blink->SetState(BRICKBLINK_STATE_IS_HIT);
		}
	}
}

void Koompas::OnCollisionWithBrickCoin(LPCOLLISIONEVENT e)
{
	if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		BrickCoin* brick = dynamic_cast<BrickCoin*>(e->obj);
		if (e->nx != 0)
		{
			if (brick->is_hit == false)
				brick->SetState(BRICK_COIN_STATE_DA_DAP);
		}
	}
}

void Koompas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	

	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	//if (state == GOOMBA_STATE_SHELL_RUNNING)
	//{

	/*	if (goomba->GetX() < this->GetX())
		{
			goomba->is_minus_vx = true;
		}*/
		//goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);

		
	//}
	// 
	//DebugOut(L"[INFO] vô 2 con và cham ko?\n");

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

			this->is_minus_vx = true;
		}

			SetState(CONCO_STATE_WAS_SHOOTED);

		
	}

	
	//koompas->SetState(CONCO_STATE_WAS_SHOOTED);
	
}

void Koompas::OnCollisionWithFlatForm(LPCOLLISIONEVENT e)
{
	if (type != KOOMPAS_RED)
		return;

	FlatForm* flatform = dynamic_cast<FlatForm*>(e->obj);


}

void Koompas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (player->x + CAM_DISTANCE > this->x && this->is_cam_coming == false)
	{
		is_cam_coming = true;
	}

	if (is_cam_coming == true)
	{
		if (type == KOOMPAS_RED)
		{
			virtalbox->vx = this->vx;
			virtalbox->Update(dt, coObjects);


			if (abs(virtalbox->y - this->y) > GAP_VIRTUAL_BOX_TO_KOOMPAS)
			{
				if (this->state == CONCO_STATE_WALKING_LEFT)
				{
					this->SetState(CONCO_STATE_WALKING_RIGHT);
					virtalbox->SetPosition(this->x + GAP_VIRTUAL_BOX_TURAROUND_X, y);
				}
				else if (this->state == CONCO_STATE_WALKING_RIGHT)
				{
					this->SetState(CONCO_STATE_WALKING_LEFT);
					virtalbox->SetPosition(this->x - GAP_VIRTUAL_BOX_TURAROUND_X, y);
				}
			}
		}

		CGameObject::Update(dt, coObjects);// sao
		if (is_brought == false)
		{
			vy += KOOMPAS_AY * dt;

		}




		/*if ((state == CONCO_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}*/




		CCollision::GetInstance()->Process(this, dt, coObjects);


		if (state == GOOMBA_STATE_INDENT_IN && GetTickCount64() - time_to_indent_out > TIME_TO_SHELL_MOVING)
		{
			SetState(CONCO_STATE_SHELL_MOVING);

		}
		if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > TIME_TO_INDENT_OUT)
		{
			SetState(CONCO_STATE_INDENT_OUT);

		}
		if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > TIME_TO_WALKING_LEFT)
		{
			SetPosition(this->x, this->y - GAP_AVOID_FALLING_DOWN);//để khi thọt ra mai rùa không bị rơi xuống
			SetState(CONCO_STATE_WALKING_LEFT);

			if (this->is_brought == true)
			{
				player->CollideWithEnemy();
				player->holding_something = NULL;
				player->SetState(MARIO_STATE_IDLE);
				player->is_holding = false;

				this->is_brought = false;

			}
		}





		if (player->GetState() == MARIO_STATE_SPIN)
			this->CheckWetherBeingAttacked(player, CONCO_STATE_WAS_SHOOTED);

		if (effect)
		{
			effect->Update(dt, coObjects);
			if (effect->isDeleted == true)
			{
				delete effect;
				effect = NULL;
			}
		}



		if (this->y > POS_Y_ENEMY_DELETE)
			this->Delete();

	}

	
}


void Koompas::Render()
{
	if (type == KOOMPAS_RED)
		virtalbox->Render();

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
		else if (state == GOOMBA_STATE_INDENT_IN|| state== CONCO_STATE_BEING_HOLDING)
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


	if (effect)
		effect->Render();

	RenderBoundingBox();
}

void Koompas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - KOOMPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;

		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -KOOMPAS_WALKING_SPEED;
		break;

	case CONCO_STATE_WALKING_RIGHT:
		vx = KOOMPAS_WALKING_SPEED;
		
		break;
	case GOOMBA_STATE_INDENT_IN:
		
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
		vx = 0;
		vy = 0; 
		time_to_indent_out = GetTickCount64();
		
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);

		vx = player->GetX() > x ? -KOOMPAS_VX_SHELL_RUNNING : KOOMPAS_VX_SHELL_RUNNING;
		is_blocking = 1;
		
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		
		break;
	case CONCO_STATE_INDENT_OUT:

		break;
	case CONCO_STATE_WAS_SHOOTED:
		vy = -KOOMPAS_VY_WAS_SHOOTED;
		
		vx = DirectionWhenBeingAttack ==-1 ?-KOOMPAS_VX_WAS_SHOOTED : KOOMPAS_VX_WAS_SHOOTED;
		is_colliable = 0;
		break;

	case CONCO_STATE_FLY_LEFT:
		vx = -KOOMPAS_FLYING_SPEED_X;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = KOOMPAS_FLYING_SPEED_X;
		break;
	case CONCO_STATE_BEING_HOLDING:
		vx = 0;
		vy = 0;
		
	}
}
