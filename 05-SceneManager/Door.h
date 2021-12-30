#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"


#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 48
#define COIN_BBOX_HEIGHT 96

#define ANI_COIN 777

#define POS_X_MARIO_UNDER_CASTLE 3600
#define POS_Y_MARIO_UNDER_CASTLE 2300

#define POS_X_MARIO_IN_CASTLE 5958
#define POS_Y_MARIO_IN_CASTLE 1083

#define DOOR_IN_CASTLE	1
#define DOOR_UNDER_CASTLE	2

class Door : public CGameObject {
public:

	CMario* player;
	int type = 1;
	Door(float x, float y, int type, CMario* mario) : CGameObject(x, y) { this->type = type; player = mario;}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};