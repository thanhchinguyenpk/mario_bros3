
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

#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500


class StoneKoompas : public CGameObject
{


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	 void Render();

	int IsCollidable() { return 1; };
	//	virtual int IsBlocking() { return 1; };
	int IsBlocking() { return 1; };

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	StoneKoompas(float x, float y);
};

