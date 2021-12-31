﻿
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PLANT_BULLET_WALKING_SPEED 0.04f;

#define PLANT_BULLET_BBOX_WIDTH 9*3
#define PLANT_BULLET_BBOX_HEIGHT 9*3
#define PLANT_BULLET_BBOX_HEIGHT_DIE 9

#define PLANT_BULLET_STATE_TOP_RIGHT 100 //bắt đầu từ chiều kim đồng hồ 12h, góc 1 2 3 4
#define PLANT_BULLET_STATE_BOT_RIGHT 200
#define PLANT_BULLET_STATE_BOT_LEFT 300
#define PLANT_BULLET_STATE_TOP_LEFT 400

#define ANI_PLANT_BULLET 704

class PlantBullet : public CGameObject
{
protected:

	bool is_hit_mario = false;
	LPGAMEOBJECT player;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) ;
	virtual void Render();

	//virtual int IsCollidable() { return 1; }; //hàm cha trả về 0
	//virtual int IsBlocking() { return 0; } // hàm cha trả về 1
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	PlantBullet(float x, float y, LPGAMEOBJECT player) ;
	virtual void SetState(int state);

	//PlantBullet(LPGAMEOBJECT player) { this->player = player; };
};
