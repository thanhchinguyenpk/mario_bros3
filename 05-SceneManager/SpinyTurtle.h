
#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "FlatForm.h"

#define SPINY_TURTLE_GRAVITY 0.002f
#define SPINY_TURTLE_WALKING_SPEED 0.06f

#define SPINY_TURTLE_FLYING_SPEED_Y 0.5f

#define SPINY_TURTLE_BBOX_WIDTH 32*3
#define SPINY_TURTLE_BBOX_HEIGHT 22*3

#define SPINY_TURTLE_BBOX_WIDTH_INDENT_IN 16*3
#define SPINY_TURTLE_BBOX_HEIGHT_INDENT_IN 16*3

#define SPINY_TURTLE_BBOX_WIDTH_DIE 23*3
#define SPINY_TURTLE_BBOX_HEIGHT_DIE 11*3

//#define SPINY_TURTLE_BBOX_HEIGHT_DIE 7

#define SPINY_TURTLE_DIE_TIMEOUT 500



#define SPINY_TURTLE_STATE_STILL 0

#define SPINY_TURTLE_STATE_JUMP 100
#define SPINY_TURTLE_STATE_WALKING 500
#define SPINY_TURTLE_STATE_SPINE 600
#define SPINY_TURTLE_STATE_INJURY 700



#define SPINY_TURTLE_STATE_HEAD_MOVING 1000

#define  ANI_SPINE_TURTLE	6080
#define  ANI_SPINELESS_TURTLE 6081
#define  ANI_SPINE_TURTLE_STANDING 6082
#define  ANI_SPINE_TURTLE_HAND_UP_AND_DOWN_HIGH 6083
#define  ANI_SPINE_TURTLE_HAND_UP_AND_DOWN_LOW 6084
#define  ANI_SPINE_TURTLE_BEING_JUMPED 6085
#define  ANI_SPINE_TURTLE_DIE 6086

#define AY_SPINE_TURTLE 0.002f

#define DISTANCE_TO_ACTIVE_SPINY_TURTLE 200
#define DISTANCE_TO_FOLLOW_MARIO 300
#define TIME_TO_SPINE 300
#define TIME_TO_RESCUE 3000
#define AX_WHEN_SPINE 0.0001f
#define VX_FROM_SPINY_STATE_BECOME_JUMPING_STATE 0.02
#define VY_STADING 0.1f
#define VX_SPINY_TURTLE_JUMPING 0.15f
#define VY_SPINY_TURTLE_JUMPING 0.7f

#define FIRST_STAGE 1
#define SECOND_STAGE 2
#define THIRD_STAGE 3


//stone koompas 
class SpinyTurtle : public CGameObject
{
public:
	int heart = 3;

	ULONGLONG time_to_rescue = 0;
	float ax = 0;

	ULONGLONG time_to_spine=0;
	ULONGLONG time_to_jump = 0;

	int stage = 1;

	LPGAMEOBJECT player;
	
	bool is_block = 1;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	//	virtual int IsBlocking() { return 1; };
	int IsBlocking() { return 0; };

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	SpinyTurtle(float x, float y, LPGAMEOBJECT mario);
	void SetState(int state);
};