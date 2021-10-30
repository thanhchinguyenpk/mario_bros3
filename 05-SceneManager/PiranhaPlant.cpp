﻿#include "PiranhaPlant.h"

#include "Goomba.h"
#include "Mario.h"

//extern  CMario* mario;
PiranhaPlant::PiranhaPlant(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{

	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(VENUS_STATE_GOING_UP);

	player = mario;

	min_y = y - VENUS_BBOX_HEIGHT+15;
	max_y = y;



	l_safe = x - 90;
	t_safe = 0;
	r_safe = x + 90;
	b_safe = y + 90;
}

void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = x + VENUS_BBOX_WIDTH / 2;
	bottom = y + VENUS_BBOX_HEIGHT / 2;
}




void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < min_y && state == VENUS_STATE_GOING_UP) //trừ cống/2 nữa
	{
		vy = 0;
	}

	if (y > max_y && state == VENUS_STATE_GOING_DOWN)
	{
		vy = 0;
	}

	if (state == VENUS_STATE_GOING_UP && GetTickCount64() - time_interval > 2000)
	{
		SetState(VENUS_STATE_GOING_DOWN);
	}

	else if (state == VENUS_STATE_GOING_DOWN && GetTickCount64() - time_interval > 5000)
	{
		
		float l, t, r, b;
		player->GetBoundingBox(l, t, r, b);

		if (this->CheckOverLap(l_safe, t_safe, r_safe, b_safe, l, t, r, b) == false)
		{
			SetState(VENUS_STATE_GOING_UP);
		}

	}

}


void PiranhaPlant::Render()
{



	CAnimations::GetInstance()->Get(744)->Render(x, y);

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

}


void PiranhaPlant::SetState(int state)
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





