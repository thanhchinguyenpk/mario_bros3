

#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include <math.h> 
#include "Mario.h"

#define PI 3.14159265

#define ID_ANI_COIN 11000

#define	CIRCAL_WIDTH 10
#define CIRCAL_BBOX_WIDTH 48
#define CIRCAL_BBOX_HEIGHT 48

#define ANI_CIRCULAR_MOVING 6070

#define ORIGINAL_POS_X 2400
#define ORIGINAL_POS_Y 900

#define CIRCULAR_MOVING_SPEED 0.15

#define CIRCULAR_MOVING_RADIUS 150

#define FULL_CIRCLE_DEGREE 360
#define HALF_CIRCLE_DEGREE 180

class CircularMoving : public CGameObject {
public:
	CMario* player;

	float origin_pos_x;
	float origin_pos_y;

	int count = 0;
	CircularMoving(float x, float y, CMario* mario) : CGameObject(x, y) { origin_pos_x = x; origin_pos_y = y; player = mario; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};
