#pragma once
#include "GameObject.h"
 



#define MARIO_BULLET_GRAVITY 0.002f
#define MARIO_BULLET_WALKING_SPEED 0.1f


#define MARIO_BULLET_BBOX_WIDTH 8*3
#define MARIO_BULLET_BBOX_HEIGHT 8*3
#define MARIO_BULLET_BBOX_HEIGHT_DIE 7

#define MARIO_BULLET_DIE_TIMEOUT 500

#define MARIO_BULLET_STATE_WALKING_RIGHT 100
#define MARIO_BULLET_STATE_WALKING_LEFT 200
#define MARIO_BULLET_STATE_DIE 300

#define ID_ANI_MARIO_BULLET_WALKING 5000
#define ID_ANI_MARIO_BULLET_DIE 5001

class MarioBullet : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	MarioBullet(float x, float y);
	virtual void SetState(int state);
};

