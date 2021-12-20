
#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "FlatForm.h"

#define GOOMBA_GRAVITY 0.002f
#define KOOMPAS_WALKING_SPEED 0.06f
#define KOOMPAS_FLYING_SPEED_Y 0.5f

#define KOOMPAS_BBOX_WIDTH 16*3
#define KOOMPAS_BBOX_HEIGHT 27*3

#define GOOMBA_BBOX_WIDTH_INDENT_IN 16*3
#define GOOMBA_BBOX_HEIGHT_INDENT_IN 16*3

#define STONE_KOOMPAS_BBOX_WIDTH_DIE 23*3
#define STONE_KOOMPAS_BBOX_HEIGHT_DIE 11*3

#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500


#define STONE_KOOMPAS_STATE_DIE 100
#define STONE_KOOMPAS_STATE_WALKING_LEFT 200
#define STONE_KOOMPAS_STATE_WALKING_RIGHT 300
#define STONE_KOOMPAS_STATE_HEAD_MOVING 400


#define  ANI_STONE_KOOMPAS_WALKING_LEFT 6000
#define  ANI_STONE_KOOMPAS_FALLING_DOWN_LEFT 6001
#define  ANI_STONE_KOOMPAS_DIE_LEFT 6002
#define  ANI_STONE_KOOMPAS_HEAD_MOVING_LEFT 6003

#define  ANI_STONE_KOOMPAS_WALKING_RIGHT 6010
#define  ANI_STONE_KOOMPAS_FALLING_DOWN_RIGHT 6011
#define  ANI_STONE_KOOMPAS_DIE_RIGHT 6012
#define  ANI_STONE_KOOMPAS_HEAD_MOVING_RIGHT 6013


//stone koompas 
class StoneKoompas : public CGameObject
{
public:
	ULONGLONG time_to_rescure;
	bool is_block = 1;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	//	virtual int IsBlocking() { return 1; };
	int IsBlocking() { return is_block; };

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	StoneKoompas(float x, float y);
	void SetState(int state);
};

