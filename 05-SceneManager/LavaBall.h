
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_COIN 11000

#define	LAVA_BALL_WIDTH 10
#define LAVA_BALL_BBOX_WIDTH 10*3
#define LAVA_BALL_BBOX_HEIGHT 16*3

#define ANI_LAVA_BALL_UP 6050
#define ANI_LAVA_BALL_DOWN 6051

#define LAVA_BALL_STATE_STOP 0
#define LAVA_BALL_STATE_MOVING_UP 100
#define LAVA_BALL_STATE_MOVING_DOWN 200


class LavaBall : public CGameObject {
public:
	float original_pos_y = y;
	ULONGLONG time_to_stop=0;
	LavaBall(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	void SetState(int state);
};