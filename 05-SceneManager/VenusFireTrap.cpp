﻿#include "VenusFireTrap.h"

#include "Goomba.h"
#include "Mario.h"

//extern  CMario* mario;
VenusFireTrap::VenusFireTrap(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(VENUS_STATE_GOING_UP);

	player = mario;
}

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = x + VENUS_BBOX_WIDTH / 2;
	bottom = y + VENUS_BBOX_HEIGHT / 2;
}




void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < origin_y - VENUS_BBOX_HEIGHT-48/2 && state == VENUS_STATE_GOING_UP) //trừ cống/2 nữa
	{
		vy = 0;
	}

	if (y > origin_y && state== VENUS_STATE_GOING_DOWN)
	{
		vy = 0;
	}

	if (state == VENUS_STATE_GOING_UP && GetTickCount64() - time_interval > 2000)
	{
		SetState(VENUS_STATE_SEEING);
	}
	else if (state == VENUS_STATE_SEEING && GetTickCount64() - time_interval > 4000)
	{
		PlantBullet* venus_bullet;
		venus_bullet = new PlantBullet(x,y-35);
		venus_bullet->SetPosition(x, y-35);

		if (player->GetX() < x)
		{
			if (player->GetY() < y)
				venus_bullet->SetState(PLANT_BULLET_STATE_TOP_LEFT);
			else if (player->GetY() >= y)
				venus_bullet->SetState(PLANT_BULLET_STATE_BOT_LEFT);		
				
		}
		else if (player->GetX() >= x)
		{
			if (player->GetY() < y)
				venus_bullet->SetState(PLANT_BULLET_STATE_TOP_RIGHT);
			else if (player->GetY() >= y)
				venus_bullet->SetState(PLANT_BULLET_STATE_BOT_RIGHT);
		}

		listFireball.push_back(venus_bullet);

		SetState(VENUS_STATE_GOING_DOWN);
		
	}
	else if (state == VENUS_STATE_GOING_DOWN && GetTickCount64() - time_interval > 9000)
	{
		SetState(VENUS_STATE_GOING_UP);

	}

	for (LPGAMEOBJECT fireball : listFireball)
		fireball->Update(dt, coObjects);
}


void VenusFireTrap::Render()
{
	int aniId = VENUS_ANI_SCORPION_DOWN_LEFT;
	if (state == GOOMBA_STATE_DIE)
	{
		//aniId = ID_ANI_GOOMBA_DIE;
	}
	if (player->GetX() <= x)
	{
		if (state == VENUS_STATE_SEEING)
		{
			aniId = VENUS_ANI_SHOOTING_DOWN_LEFT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SHOOTING_UP_LEFT;
			
		}
		else if(state== VENUS_STATE_GOING_UP||state== VENUS_STATE_GOING_DOWN)
		{

			aniId = VENUS_ANI_SCORPION_DOWN_LEFT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SCORPION_UP_LEFT;
		}


	}else if (player->GetX() > x)
	{
		if (state == VENUS_STATE_SEEING)
		{
			aniId = VENUS_ANI_SHOOTING_DOWN_RIGHT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SHOOTING_UP_RIGHT;

		}
		else if (state == VENUS_STATE_GOING_UP || state == VENUS_STATE_GOING_DOWN)
		{

			aniId = VENUS_ANI_SCORPION_DOWN_RIGHT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SCORPION_UP_RIGHT;
		}
	}
		

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();


	for (LPGAMEOBJECT fireball : listFireball)
		fireball->Render();
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case VENUS_STATE_GOING_UP:
		vy = -VENUS_WALKING_SPEED;
		time_interval = GetTickCount64();
		break;

	case VENUS_STATE_SEEING:
		vy = 0;
		break;
	case VENUS_STATE_GOING_DOWN:
		vy = VENUS_WALKING_SPEED;
		break;
	}


}

	

