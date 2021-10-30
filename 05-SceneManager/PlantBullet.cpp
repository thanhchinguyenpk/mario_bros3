﻿#include "PlantBullet.h"

PlantBullet::PlantBullet(float x, float y, LPGAMEOBJECT player) :CGameObject(x, y)
{
	//if (direction == 1)
	//	SetState(PLANT_BULLET_STATE_TOP_RIGHT);
	//else if(direction == 2)
	//	SetState(PLANT_BULLET_STATE_BOT_RIGHT);
	//else if (direction == 3)
	//	SetState(PLANT_BULLET_STATE_BOT_LEFT);
	//else if (direction == 4)
	//	SetState(PLANT_BULLET_STATE_TOP_LEFT);

	this->player = player;
}

void PlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	float l, t, r, b;
	player->GetBoundingBox(l, t, r, b);

	float lb, tb, rb, bb;
	this->GetBoundingBox(lb, tb, rb, bb);

	if (this->CheckOverLap(lb, tb, rb, bb, l, t, r, b) == true && is_hit_mario==false)
	{
		dynamic_cast<CMario*>(player)->SetLevel(1);
		is_hit_mario = true;
	}
}

void PlantBullet::Render()
{
	int ani = 0;


	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(704)->Render(x, y);

	RenderBoundingBox();


}

void PlantBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
		l = x - PLANT_BULLET_BBOX_WIDTH / 2;
		t = y - PLANT_BULLET_BBOX_HEIGHT / 2;
		r = x + PLANT_BULLET_BBOX_WIDTH / 2;
		b = y + PLANT_BULLET_BBOX_HEIGHT / 2;

}



void PlantBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case PLANT_BULLET_STATE_TOP_RIGHT:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_BOT_RIGHT:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_BOT_LEFT:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_TOP_LEFT:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	}

}