﻿#include "BrickBlink.h"
#include "debug.h"
#include "BrickDebris.h"

#define HIGH_DEBRIS 1.5
#define LOW_DEBRIS 1

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1

void BrickBlink::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int ani = ID_ANI_BRICKBLINK;

	if (state == BRICKBLINK_STATE_IS_HIT)
		//animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	{
		for (int i = 0; i < vec_debris.size(); i++)
		{
			vec_debris[i]->Render();
		}
		return;
	}
	if (state == BRICKBLINK_STATE_COIN)
		ani = ID_ANI_BRICKBLINK_COIN_STAND_STILL;

	animations->Get(ani)->Render(x, y);

//	DebugOut(L"[INFO] state cua brick %d\n", state);

	RenderBoundingBox();
}

void BrickBlink::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < vec_debris.size(); i++)
	{
		vec_debris[i]->Update(dt);
	}


	for (LPGAMEOBJECT debris : vec_debris)
	{
		debris->Update(dt, coObjects);
		//DebugOut(L"[INFO]update hihi %d\n", vec_debris.size());

	}
	//DebugOut(L"[INFO]vô trong update brick khum? %d\n", vec_debris.size());
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (is_hit == true)
	{
		//l = t = r = b = 0;
		return;
	}
		
	l = x - BRICKBLINK_BBOX_WIDTH / 2;
	t = y - BRICKBLINK_BBOX_HEIGHT / 2;
	r = l + BRICKBLINK_BBOX_WIDTH;
	b = t + BRICKBLINK_BBOX_HEIGHT;
}

void BrickBlink::SetState(int state)
{
	BrickDebris* debrick_brick = NULL;

	switch (state)
	{
		//MARIO_STATE_FLY
	case BRICKBLINK_STATE_IS_HIT:
		
		

		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, RIGHT_DIRECTION, HIGH_DEBRIS); // trên phải cùng
		vec_debris.push_back(debrick_brick);


		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, RIGHT_DIRECTION, LOW_DEBRIS);//dưới phải cùng
		vec_debris.push_back(debrick_brick);


		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, LEFT_DIRECTION, LOW_DEBRIS);//dưới phải cùng
		vec_debris.push_back(debrick_brick);

		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, LEFT_DIRECTION, HIGH_DEBRIS);
		vec_debris.push_back(debrick_brick);

		is_hit = true;
		
		break;

	case BRICKBLINK_STATE_COIN:
		is_block = false;
		break;

	case BRICKBLINK_STATE_BRICK:
		is_block = true;
		break;

	}

	CGameObject::SetState(state);
}
