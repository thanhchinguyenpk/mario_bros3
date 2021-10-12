
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16*3
#define GOOMBA_BBOX_HEIGHT 14*3
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_PARA_GOOMBA_WALKING 7000
#define ID_ANI_GOOMBA_DIE 5001

class ParaGoompa : public CGameObject
{
protected:



	float ax;
	float ay;
	CMario* player;
	ULONGLONG die_start;

	ULONGLONG walking_start;


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	ParaGoompa(float x, float y, CMario* mario);
	virtual void SetState(int state);
};
