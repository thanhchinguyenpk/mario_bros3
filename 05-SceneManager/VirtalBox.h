#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 58
#define BRICK_BBOX_HEIGHT 58

#define VIRTUAL_BOX_ADJUST_HEIGHT 100
#define GAP 5

#define AY_VIRTUAL_BOX 0.002

class VirtalBox : public CGameObject {
public:
	LPGAMEOBJECT player;

	VirtalBox(float x, float y, LPGAMEOBJECT mario) : CGameObject(x, y) { player = mario;  }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	 void OnNoCollision(DWORD dt);

	 void SetState(int state);

	 void OnCollisionWith(LPCOLLISIONEVENT e);
};