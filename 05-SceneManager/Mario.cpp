#include <algorithm>
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
#include "PButton.h"
#include "Pine.h"
#include "MapScene.h"
#include "TimerCustom.h"

#include "BrickBlink.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"


#include "SuperLeaf.h"
#include "VirtalBox.h"
#include "StoneKoompas.h"
#include "FireFlower.h"
#include "Door.h"
#include "SpinyTurtle.h"
#include "CircularMoving.h"
#include "LavaBall.h"


void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (is_on_the_ground == false && y > POS_Y_HOLD || x > POS_Y_END_MAP) // rơi xuống hố hoặc đi qua end scene hoặc chết vì enemy(phía dưới)
		CGame::GetInstance()->InitiateSwitchScene(MAP_SCENE);*/

	//CGameObject::Update(dt);
	if (is_moving_in_world_map == true)
	{
		CGame* game_temp = CGame::GetInstance();
		MapScene* map_scene = (MapScene*)game_temp->GetCurrentScene();

		if (x >= map_scene->current_portal->x && vx > 0 || x <= map_scene->current_portal->x && vx < 0)
		{// thêm vx để biết được hướng đi của mario, nếu ko có vx nó sẽ qua cái hoặc số 2
			this->SetPosition(map_scene->current_portal->x, map_scene->current_portal->y);
			vx = 0;
		}
		else
			x += vx * dt;
		
		if (y <= map_scene->current_portal->y && vy < 0 || y >= map_scene->current_portal->y && vy > 0)
		{
			this->SetPosition(map_scene->current_portal->x, map_scene->current_portal->y);
			vy = 0;
		}
		else
			y += vy * dt;

		return;
	}

	if (is_set_position == true)
	{
		if (GetTickCount64() - time_to_go_down > MARIO_TIME_TO_GO_PINE)
		{
			if (this->GetY() < MARIO_Y_ABOVE)
			{
				SetPosition(MARIO_POS_X_UNDER_GROUND, MARIO_POS_Y_UNDER_GROUND); // dưới lòng đất
				is_set_position = false;
				time_to_go_down = 0;

				is_on_the_ground = true;
			}
			else if(this->GetY()>= MARIO_Y_ABOVE && this->GetY()<= MARIO_Y_BELOW)
			{
				is_set_position = false;
				time_to_go_down = 0;
			}
			else
			{
				SetPosition(MARIO_POS_X_IN_GROUND, MARIO_POS_Y_IN_GROUND); //trên mặt đất
				time_to_go_down = GetTickCount64();

				is_on_the_ground = false;
			}

			
		}
		else
		{
			if (this->GetY() < MARIO_Y_ABOVE)
				y += MARIO_VY_GO_DOWN_PINE * dt;
			else 
				y -= MARIO_VY_GO_UP_PINE * dt;

			

			return;
		}
	}


	if (is_auto)
	{
		x += MARIO_VX_AUTO * dt;
		return;
	}

	if (state == MARIO_STATE_FLY_LANDING || state == MARIO_STATE_FLY_HIGH)
		vy = vy;
	else
		vy += ay * dt;
	//if (state != MARIO_STATE_FLY_HIGH)
	//	vy += ay * dt;

	vy_store = vy; // nhảy từ dưới lên được


	//vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
		//DebugOut(L"[INFO] vo day ko?\n");
	}


	//DebugOut(L"[INFO]maxVx la: %f\n", maxVx);
	// reset untouchable timer if untouchable time has passed
	
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	/*if (untouchtable_timer->IsTimeUp())
	{
		untouchtable_timer->Reset();
	}*/

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);


	if (jump_down_to_up == true)
	{
		SetPosition(x, y- MARIO_GAP_JUMP);
		jump_down_to_up = false;
		//DebugOut(L"[INFO] vo day khoooooooooooooooooooooooooong \n" );
	}


	if (is_kick==true && GetTickCount64() - kick_start >= MARIO_TIME_KICK && kick_start)
	{
		
		kick_start = 0;
		is_kick = false;
	
	}

	for (int i = 0; i < listWeapons.size(); i++)
		listWeapons[i]->Update(dt, coObjects);

	for (int i = 0; i < listWeapons.size(); i++)
	{
		if (listWeapons[i]->IsDeleted())
		{
			delete listWeapons[i];
			listWeapons[i] = nullptr;
			listWeapons.erase(listWeapons.begin() + i);
			//DebugOut(L"[INFO] xoa gach \n");
		}
	}


	if (GetState() == MARIO_STATE_STAND_SHOOT && GetTickCount64() - throw_start >= MARIO_TIME_THROW && throw_start)
	{
		SetState(MARIO_STATE_IDLE);
		throw_start = 0;

	}
	if (GetState() == MARIO_STATE_SPIN && GetTickCount64() - spin_start >= MARIO_TIME_SPIN && spin_start)
	{
		SetState(MARIO_STATE_IDLE);
		spin_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}

	if (GetState() == MARIO_STATE_FLY_LANDING && GetTickCount64() - fly_start >= MARIO_TIME_FLY_LANDING && fly_start)
	{
		SetState(MARIO_STATE_IDLE);
		fly_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}

	if (GetState() == MARIO_STATE_FLY_HIGH && GetTickCount64() - fly_high_start >= MARIO_TIME_FLY_HIGH && fly_high_start)
	{
		SetState(MARIO_STATE_IDLE);
		fly_high_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}
	if (GetState() == MARIO_STATE_JUMP_SHOOT_BULLET && GetTickCount64() - jump_fire_throw_start >= MARIO_TIME_JUMP_AND_SHOOT && jump_fire_throw_start)
	{
		SetState(MARIO_STATE_IDLE);
		jump_fire_throw_start = 0;
		//DebugOut(L"[INFO] ra luôn luôn?\n");
	}
	
	if (GetState() == MARIO_STATE_DIE && GetTickCount64() - time_to_switch_scene >= MARIO_TIME_TO_SWITCH_SCENE)
	{
		CGame::GetInstance()->InitiateSwitchScene(MAP_SCENE);
	}

	if (this->GetY() < 0)
	{
		//SetState(MARIO_STATE_FLY_LANDING);
		SetState(MARIO_STATE_IDLE);
	}

	//DebugOut(L"state la: %d\n", state);


	if (holding_something != NULL)
	{
		//this->hold_somthing->SetPosition(this->x + 40, this->y);

		if (is_holding == true)
		{

			//if (nx == -1)
			
			if (level == MARIO_LEVEL_SMALL)
			{
				this->holding_something->SetPosition(this->x + MARIO_GAP_HOLDING_X, this->y - MARIO_GAP_HOLDING_Y);
				if (this->nx < 0)
					this->holding_something->SetPosition(this->x - MARIO_GAP_HOLDING_X, this->y - MARIO_GAP_HOLDING_Y);
			}
			else
			{
				this->holding_something->SetPosition(x + MARIO_GAP_HOLDING_X, y);
				if (nx < 0)
					this->holding_something->SetPosition(x - MARIO_GAP_HOLDING_X, y);

			}

			dynamic_cast<Koompas*>(holding_something)->is_brought = true;
		}
		else
		{
			Koompas* koompas = dynamic_cast<Koompas*>(holding_something);
			koompas->SetState(GOOMBA_STATE_SHELL_RUNNING);
			koompas->is_brought = false;
			holding_something = NULL;

			this->SetState(MARIO_STATE_KICK);
		}
	}

	if (is_jumped)
	{
		this->SetPosition(x, y - MARIO_GAP_BEING_JUMPED);
		is_jumped = false;
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
	else if (dynamic_cast<Mushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<BrickBlink*>(e->obj))
		OnCollisionWithBrickBlink(e);
	else if (dynamic_cast<PButton*>(e->obj))
		OnCollisionWithPButton(e);
	else if (dynamic_cast<Pine*>(e->obj))
		OnCollisionWithPine(e);
	else if (dynamic_cast<VirtalBox*>(e->obj))
		OnCollisionWithVirtalBox(e);
	else if (dynamic_cast<StoneKoompas*>(e->obj))
		OnCollisionWithStoneKoompas(e);
	else if (dynamic_cast<PiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<VenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<FireFlower*>(e->obj))
		OnCollisionWithFireFlower(e);
	else if (dynamic_cast<Door*>(e->obj))
		OnCollisionWithDoor(e);
	else if (dynamic_cast<SpinyTurtle*>(e->obj))
		OnCollisionWithSpinyTurtle(e);
	else if (dynamic_cast<CircularMoving*>(e->obj))
		OnCollisionWithCircularMoving(e);
	else if (dynamic_cast<LavaBall*>(e->obj))
		OnCollisionWithLavaBall(e);
	
	
	


	//DebugOut(L"dam len nut helloooooooooooooooo %d \n", this->go_down);

	if (dynamic_cast<Pine*>(e->obj)&&dynamic_cast<Pine*>(e->obj)->is_pine_can_go == true)
	{
		this->go_down = true;
		//SetPosition(200, 100);
	}
	else
		this->go_down = false;



	

	//DebugOut(L"[INFO]y la------------------------------: %f\n", y);
}


void CMario::OnCollisionWithLavaBall(LPCOLLISIONEVENT e)
{
	CollideWithEnemy();
}

void CMario::OnCollisionWithCircularMoving(LPCOLLISIONEVENT e)
{
	CollideWithEnemy();
}

void CMario::OnCollisionWithSpinyTurtle(LPCOLLISIONEVENT e)
{
	SpinyTurtle* spiny_turtle = dynamic_cast<SpinyTurtle*>(e->obj);
	if (e->ny < 0)
	{
		if (spiny_turtle->stage == 1)
		{

			if (spiny_turtle->GetState() == SPINY_TURTLE_STATE_JUMP ||
				spiny_turtle->GetState() == SPINY_TURTLE_STATE_WALKING)
			{
				spiny_turtle->SetState(SPINY_TURTLE_STATE_INJURY);
				

				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else
				CollideWithEnemy();
		}

		spiny_turtle->SetPosition(spiny_turtle->x, spiny_turtle->y - 1);
	}
	else
		CollideWithEnemy();
}


void CMario::OnCollisionWithDoor(LPCOLLISIONEVENT e)
{
	//SetLevel(MARIO_LEVEL_BIG_ORANGE);
	
	Door* door = dynamic_cast<Door*>(e->obj);

	if (door->type == 1)
	{
		this->SetPosition(3600, 2300);
		is_on_the_ground = true;
	}
	else if (door->type == 2)
	{
		this->SetPosition(5958, 1083);
		is_on_the_ground = false;
	}
	
}

void CMario::OnCollisionWithFireFlower(LPCOLLISIONEVENT e)
{
	SetLevel(MARIO_LEVEL_BIG_ORANGE);
	dynamic_cast<FireFlower*>(e->obj)->Delete();
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CollideWithEnemy();
}
void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	CollideWithEnemy();
}

void CMario::OnCollisionWithPine(LPCOLLISIONEVENT e)
{
	//dưới hầm đi từ pine đen
	if (e->ny > 0 && dynamic_cast<Pine*>(e->obj)->is_pine_can_go ==true && is_up_press==true)
	{

		
		is_set_position = true;
		time_to_go_down = GetTickCount64();
		//SetPosition(7000,500);
	}
}

void CMario::OnCollisionWithPButton(LPCOLLISIONEVENT e)
{
	PButton* pbutton = dynamic_cast<PButton*>(e->obj);
	if (e->ny < 0 && pbutton->is_hit==false)
	{
		//DebugOut(L"dam len nut P rui \n");
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		dynamic_cast<PButton*>(e->obj)->SetState(PBUTTON_STATE_IS_HIT);
		pbutton->is_hit = true;
	}
}
void CMario::OnCollisionWithBrickBlink(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<BrickBlink*>(e->obj)->is_block == false)
	{
		dynamic_cast<BrickBlink*>(e->obj)->Delete();
	}
	else
	{
		if (e->ny > 0)
		{
			//dynamic_cast<CBrick*>(e->obj)->is_hit = true;
			dynamic_cast<BrickBlink*>(e->obj)->SetState(BRICKBLINK_STATE_IS_HIT);
		}
	}

}


void CMario::OnCollisionWithFlatForm(LPCOLLISIONEVENT e)
{
	if (is_hit_bonus == true)
		is_auto = true;

	if (e->ny > 0 && dynamic_cast<FlatForm*>(e->obj)->is_go_through==true)
	{
		jump_down_to_up = true;
		vy = vy_store;
	}

}

void CMario::OnCollisionWithKoompas(LPCOLLISIONEVENT e)
{
	Koompas* koompas = dynamic_cast<Koompas*>(e->obj);

	//koompas->SetState(CONCO_STATE_WAS_SHOOTED);

	
	if (e->ny < 0)
	{
		this->score += SCORE;

		if (koompas->GetState() == CONCO_STATE_FLY_LEFT)
		{
			koompas->SetState(CONCO_STATE_WALKING_LEFT);
		}
		else if (koompas->GetState() == CONCO_STATE_FLY_RIGHT)
		{
			koompas->SetState(CONCO_STATE_WALKING_RIGHT);
		}
		else if (koompas->GetState() == GOOMBA_STATE_INDENT_IN|| koompas->GetState() == CONCO_STATE_INDENT_OUT ||
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
	else if (e->ny > 0)
	{
		CollideWithEnemy();
		 //set post ở đây không có ý nghĩa
		is_jumped = true;
		DebugOut(L"va cham tren dau roi ne %d \n");
	}
	else
	{

		if (e->nx != 0)
		{
			if (is_holding == false)
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
			{
					if (is_holding == true)
					{
						if (koompas->GetState() == GOOMBA_STATE_INDENT_IN)
						{
							holding_something = koompas;
							//koompas->SetState(CONCO_STATE_BEING_HOLDING);
							//CONCO_STATE_WAS_BROUGHT
							
						}
					}

			}
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

void CMario::OnCollisionWithStoneKoompas(LPCOLLISIONEVENT e)
{
	//e->obj->Delete();
	//coin++;
	if (e->ny < 0)
	{
		e->obj->SetState(STONE_KOOMPAS_STATE_DIE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		//DebugOut(L"stone koompas %d \n");
	}
	else
		CollideWithEnemy();
}

void CMario::OnCollisionWithVirtalBox(LPCOLLISIONEVENT e)
{
	//e->obj->Delete();
	//coin++;
	//e->obj->vx = this->vx;
	//DebugOut(L"virtal box truoc %f \n", e->obj->y);
	if (e->ny < 0)
	{
		e->obj->SetState(VIRTUAL_BOX_ADJUST_HEIGHT);
	}
	//DebugOut(L"virtal box sau %f \n", e->obj->y);
}
void CMario::OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	//coin++;

}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();

	
	if(dynamic_cast<Mushroom*>(e->obj)->type==RED)
		SetLevel(MARIO_LEVEL_BIG);
	

}
void CMario::OnCollisionWithBrickCoin(LPCOLLISIONEVENT e)
{
	BrickCoin* brick = dynamic_cast<BrickCoin*>(e->obj);
	if (e->ny > 0)
	{
		
		if (brick->is_hit == false)
		{
			this->hit_brick_number++;
			brick->SetState(BRICK_COIN_STATE_DA_DAP);
		}
	}

}


void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	ParaGoompa* paragoomba = dynamic_cast<ParaGoompa*>(e->obj);
	if (e->ny < 0) // phương va chạm hướng lên
	{
		this->score += SCORE;

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
		this->score += SCORE;
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
		//DebugOut(L"vo may lan vay? %d \n", this->level);
		if (level > MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
			//DebugOut(L"level truoc khi chet mall %d \n", this->level);
		}
		else
		{
			SetState(MARIO_STATE_DIE);
			//DebugOut(L"level truoc khi chet die %d \n", this->level);
		}
	}
	//untouchtable_timer

	/*if (untouchtable_timer->startTime == 0)
	{
		if (level > MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
		
			untouchtable_timer->StartTime();
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			untouchtable_timer->StartTime();
		}

		else
			SetState(MARIO_STATE_DIE);
	}*/
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


		if (holding_something != NULL)
			if (nx >= 0)
				aniId = MARIO_ANI_SMALL_BRING_JUMP_RIGHT;
			else
				aniId = MARIO_ANI_SMALL_BRING_JUMP_RIGHT + TO_BECOME_LEFT;
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
				if (holding_something == NULL)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = MARIO_ANI_SMALL_STAND_HOLD;
					else  aniId = MARIO_ANI_SMALL_STAND_HOLD + TO_BECOME_LEFT;
				}
				
			}
			else if (vx > 0)
			{


				if (holding_something == NULL)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else 
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else
					aniId = MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT;


			}
			else // vx < 0
			{
				if (holding_something == NULL)
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else 
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
				else
					aniId = MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;

			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	if (is_kick == true)
	{
		if (nx == 1)
			aniId = MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT;
		else
			aniId = MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
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

		if(holding_something != NULL)
			if (nx >= 0)
				aniId = MARIO_ANI_BIG_BRING_JUMP_RIGHT;
			else
				aniId = MARIO_ANI_BIG_BRING_JUMP_RIGHT + TO_BECOME_LEFT;
			
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
				if (holding_something == NULL)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = MARIO_ANI_BIG_STAND_HOLD;
					else  aniId = MARIO_ANI_BIG_STAND_HOLD +TO_BECOME_LEFT;
				}
			}
			else if (vx > 0)
			{
				
				if (holding_something == NULL)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (vx == MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				else
					aniId = MARIO_ANI_BRING_KOOMPASHELL_RIGHT;
			}
			else // vx < 0
			{
				if (holding_something == NULL)
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (vx == -MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
				else
					aniId = MARIO_ANI_BRING_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	if (is_kick == true)
	{
		if(nx==1)
			aniId = MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT;
		else
			aniId = MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
	}

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			
		}
		else
		{
			if (nx >= 0)
				aniId = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
			else
				aniId = MARIO_ANI_TAIL_JUMP_UP_RIGHT + TO_BECOME_LEFT;
		}


		if (holding_something != NULL)
			if (nx >= 0)
				aniId = MARIO_ANI_TAIL_BRING_JUMP_RIGHT;
			else
				aniId = MARIO_ANI_TAIL_BRING_JUMP_RIGHT + TO_BECOME_LEFT;
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = MARIO_ANI_TAIL_SITDOWN_RIGHT;
		else
			aniId = MARIO_ANI_TAIL_SITDOWN_RIGHT+TO_BECOME_LEFT;
	}
	else
		if (vx == 0)
		{
			if (holding_something == NULL)
			{
				if (nx > 0) aniId = MARIO_ANI_TAIL_IDLE_RIGHT;
				else aniId = MARIO_ANI_TAIL_IDLE_RIGHT + TO_BECOME_LEFT;
			}
			else
			{
				if (nx > 0) aniId = MARIO_ANI_TAIL_STAND_HOLD;
				else  aniId = MARIO_ANI_TAIL_STAND_HOLD + TO_BECOME_LEFT;
			}



		}
		else if (vx > 0)
		{
			// chỗ này lần milestone1
			if (holding_something == NULL)
			{
				if (ax < 0)
					aniId = MARIO_ANI_TAIL_SKID_LEFT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = MARIO_ANI_TAIL_RUN_RIGHT;
				else
					aniId = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
			else
				aniId = MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT;

		}
		else // vx < 0
		{
			if (holding_something == NULL)
			{
				if (ax > 0)
					aniId = MARIO_ANI_TAIL_SKID_LEFT + TO_BECOME_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = MARIO_ANI_TAIL_RUN_RIGHT + TO_BECOME_LEFT;
				else
					aniId = MARIO_ANI_TAIL_WALKING_RIGHT + TO_BECOME_LEFT;
			}
			else
				aniId = MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
		}

	if (state == MARIO_STATE_SPIN)
		if(nx==1)
			aniId = MARIO_ANI_TAIL_SPIN_TAIL_RIGHT;
		else
			aniId = MARIO_ANI_TAIL_SPIN_TAIL_RIGHT + TO_BECOME_LEFT;

	if(state== MARIO_STATE_FLY_LANDING)
		if(nx==1)
			aniId = MARIO_ANI_ORANGE_FLY_DOWN;
		else
			aniId = MARIO_ANI_ORANGE_FLY_DOWN + TO_BECOME_LEFT;

	if (state == MARIO_STATE_FLY_HIGH)
	{
		if (nx >= 0)
			aniId = MARIO_ANI_TAIL_FLY_HIGH;
		else
			aniId = MARIO_ANI_TAIL_FLY_HIGH + TO_BECOME_LEFT;
	}

	if (is_kick == true)
	{
		if (nx == 1)
			aniId = MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT;
		else
			aniId = MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
	}
	

	if (aniId == -1) aniId = MARIO_ANI_ORANGE_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = MARIO_ANI_ORANGE_FLYING;
			else
				aniId = MARIO_ANI_ORANGE_FLYING +TO_BECOME_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = MARIO_ANI_ORANGE_JUMP_UP_RIGHT;
			else
				aniId = MARIO_ANI_ORANGE_JUMP_UP_RIGHT + TO_BECOME_LEFT;
		}

		if (holding_something != NULL)
			if (nx >= 0)
				aniId = MARIO_ANI_ORANGE_BRING_JUMP_RIGHT;
			else
				aniId = MARIO_ANI_ORANGE_BRING_JUMP_RIGHT + TO_BECOME_LEFT;
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = MARIO_ANI_ORANGE_SITDOWN_RIGHT;
		else
			aniId = MARIO_ANI_ORANGE_SITDOWN_RIGHT  + TO_BECOME_LEFT;
	}
	else
		if (vx == 0)
		{
			if (holding_something == NULL)
			{
				if (nx > 0) aniId = MARIO_ANI_ORANGE_IDLE_RIGHT;
				else aniId = MARIO_ANI_ORANGE_IDLE_RIGHT  +  TO_BECOME_LEFT;
			}
			else
			{
				if (nx > 0) aniId = MARIO_ANI_ORANGE_STAND_HOLD;
				else  aniId = MARIO_ANI_ORANGE_STAND_HOLD + TO_BECOME_LEFT;
			}





		}
		else if (vx > 0)
		{
			// chỗ này lần milestone1
			if (holding_something == NULL)
			{
				if (ax < 0)
					aniId = MARIO_ANI_ORANGE_SKID_LEFT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = MARIO_ANI_ORANGE_RUN_RIGHT;
				else
					aniId = MARIO_ANI_ORANGE_WALKING_RIGHT;
			}
			else
				aniId = MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT;


		}
		else // vx < 0
		{
			if (holding_something == NULL)
			{
				if (ax > 0)
					aniId = MARIO_ANI_ORANGE_SKID_LEFT + TO_BECOME_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = MARIO_ANI_ORANGE_RUN_RIGHT + TO_BECOME_LEFT;
				else
					aniId = MARIO_ANI_ORANGE_WALKING_RIGHT + TO_BECOME_LEFT;
			}
			else
				aniId = MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
		}

	if (state == MARIO_STATE_STAND_SHOOT)
		if(nx==1)
			aniId = MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT;
		else
			aniId = MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT + TO_BECOME_LEFT;

	if (state == MARIO_STATE_JUMP_SHOOT_BULLET)
	{
		if (nx >= 0)
			aniId = MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT;
		else
			aniId = MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT + TO_BECOME_LEFT;
	}

	if (is_kick == true)
	{
		if (nx == 1)
			aniId = MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT;
		else
			aniId = MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT + TO_BECOME_LEFT;
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
	

	if (is_auto == true)
	{
		if (level == MARIO_LEVEL_SMALL)
			aniId = MARIO_ANI_SMALL_WALKING_RIGHT;
		else if (level == MARIO_LEVEL_BIG)
			aniId = MARIO_ANI_BIG_WALKING_RIGHT;
		else if (level == MARIO_LEVEL_BIG_TAIL)
			aniId = MARIO_ANI_TAIL_WALKING_RIGHT;
		else if (level == MARIO_LEVEL_BIG_ORANGE)
			aniId = MARIO_ANI_ORANGE_WALKING_RIGHT;
		nx = 1;
	}

	if(is_set_position==true)
	{
		if (level == MARIO_LEVEL_SMALL)
			aniId = MARIO_ANI_SMALL_GO_DOWN;
		else if (level == MARIO_LEVEL_BIG)
			aniId = MARIO_ANI_BIG_GO_DOWN;
		else if (level == MARIO_LEVEL_BIG_TAIL)
			aniId = MARIO_ANI_TAIL_GO_DOWN;
		else if (level == MARIO_LEVEL_BIG_ORANGE)
			aniId = MARIO_ANI_ORANGE_GO_DOWN;
		nx = 1;
	}

	if (is_moving_in_world_map)
	{
		if (level == MARIO_LEVEL_SMALL)
			aniId = MARIO_ANI_SMALL_IN_MAP;
		else if (level == MARIO_LEVEL_BIG)
			aniId = MARIO_ANI_BIG_IN_MAP;
		else if (level == MARIO_LEVEL_BIG_TAIL)
			aniId = MARIO_ANI_TAIL_IN_MAP;
		else if (level == MARIO_LEVEL_BIG_ORANGE)
			aniId = MARIO_ANI_ORANGE_IN_MAP;
		nx = 1;

	}
	/*int count = 402;
	GameTime* game_time = GameTime::GetInstance();

	if (game_time->gameTime % 4 == 1)
	{
		DebugOut(L"lin da xin chào cả nhà ố là la %d\n", count);
	}*/
	
	//for(int i=0;i<4;i++)
	//	animations->Get(552 +i)->Render(x +i*40, y);

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	

	for (int i = 0; i < listWeapons.size(); i++)
		listWeapons[i]->Render();
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
				vx = nx==1 ? MARIO_VX_JUMP : -MARIO_VX_JUMP;
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
		time_to_switch_scene = GetTickCount64();
		break;

	case MARIO_STATE_KICK:
		kick_start = GetTickCount64();
		is_kick = true;
		break;

	case MARIO_STATE_STAND_SHOOT:
		throw_start = GetTickCount64();
		this->attack();
		break;
	case MARIO_STATE_JUMP_SHOOT_BULLET:
		jump_fire_throw_start = GetTickCount64();
		this->attack();
		break;

	case MARIO_STATE_SPIN:
		spin_start = GetTickCount64();
		break;
	case MARIO_STATE_FLY_LANDING:
		fly_start = GetTickCount64();
		vy = MARIO_VY_FLY_LANDING;
		break;
	case MARIO_STATE_FLY_HIGH:
		fly_high_start = GetTickCount64();
		vy = -MARIO_VY_FLY_HIGH;
		break;
	
		
	}

	CGameObject::SetState(state);
}

void CMario::attack()
{
	if (listWeapons.size() == MARIO_SIZE_WEAPON)
		return;

	MarioBullet* temp = new MarioBullet(this->x, this->y);

	if (this->GetNX() > 0)
	{
		temp->SetState(MARIO_BULLET_STATE_WALKING_RIGHT);
		temp->SetPosition(this->GetX() + MARIO_GAP_BULLET_RIGHT, this->GetY());
	}
	else
	{
		temp->SetState(MARIO_BULLET_STATE_WALKING_LEFT);
		temp->SetPosition(this->GetX() - MARIO_GAP_BULLET_LEFT, this->GetY());
	}

	listWeapons.push_back(temp);
	//DebugOut(L"[INFO] weapon: %d\n", listWeapons.size());

}

void CMario::CollideWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat)
{
	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(ml, mt, mr, mb);

	for (UINT i = 0; i < itemsMarioCanEat->size(); i++)
	{
		LPGAMEOBJECT item = itemsMarioCanEat->at(i);

		item->GetBoundingBox(il, it, ir, ib);

		if (this->CheckOverLap(ml, mt, mr, mb, il, it, ir, ib))
		{
			if (dynamic_cast<Mushroom*>(item) && dynamic_cast<Mushroom*>(item)->type==RED)
			{
				//GREEN
				//&& dynamic_cast<Mushroom*>(item)->is_read_mushroom == true
				
				//SetState(MARIO_STATE_TRANSFORM);
				//score += 1000;
				this->SetLevel(2);
			}
			else if (dynamic_cast<SuperLeaf*>(item))
			{
				//SetState(MARIO_STATE_APPEAR_TAIL);
				//score += 1000;
				this->SetLevel(3);
			}
			//else if (dynamic_cast<Coin*>(item))
			//{
				//score += 10;
			//}

			//item->used = true;
			item->Delete();
		}
	}
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
	{ 

		if (isSitting)
		{
			left = x - MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH;
			bottom = top + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT;
		}
		else
		{
			if (this->GetState() == MARIO_STATE_SPIN)
			{
				//chỗ này nè
				/*left = x - MARIO_TAIL_BBOX_WIDTH / 2-90;
				top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
				right = left + MARIO_TAIL_BBOX_WIDTH;
				bottom = top + MARIO_TAIL_BBOX_HEIGHT;*/

				left = x - MARIO_TAIL_BBOX_WIDTH / 2 - MARIO_WIDTH_SPIN;
				//top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
				top = y - MARIO_HEIGHT_SPIN;

				right = x + MARIO_TAIL_BBOX_WIDTH / 2 + MARIO_WIDTH_SPIN;
				bottom = y + MARIO_TAIL_BBOX_HEIGHT / 2;
			}
			else
			{
				left = x - MARIO_BIG_TAIL_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_TAIL_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_TAIL_BBOX_WIDTH;
				bottom = top + MARIO_BIG_TAIL_BBOX_HEIGHT;
			}
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

