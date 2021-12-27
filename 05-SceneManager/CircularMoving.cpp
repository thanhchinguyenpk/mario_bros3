#include "CircularMoving.h"


void CircularMoving::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ANI_CIRCULAR_MOVING)->Render(x, y);

	RenderBoundingBox();
}

void CircularMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	count += CIRCULAR_MOVING_SPEED * dt;
	count %= FULL_CIRCLE_DEGREE;

	x = ORIGINAL_POS_X + CIRCULAR_MOVING_RADIUS * sin(count * PI / HALF_CIRCLE_DEGREE);
	y = ORIGINAL_POS_Y + CIRCULAR_MOVING_RADIUS * cos(count * PI / HALF_CIRCLE_DEGREE);
}

void CircularMoving::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CIRCAL_BBOX_WIDTH / 2;
	t = y - CIRCAL_BBOX_HEIGHT / 2;
	r = l + CIRCAL_BBOX_WIDTH;
	b = t + CIRCAL_BBOX_HEIGHT;
}