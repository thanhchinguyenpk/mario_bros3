
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_COIN 11000

//#define	COIN_WIDTH 10
#define FIRE_FLOWE_BBOX_WIDTH 16*3
#define FIRE_FLOWE_BBOX_HEIGHT 16*3

#define ANI_FIRE_FLOWE 6095

class FireFlower : public CGameObject {
public:
	int count = 0;
	FireFlower(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};