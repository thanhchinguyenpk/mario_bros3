#include "CircularMoving.h"




void CircularMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	count += (int)CIRCULAR_MOVING_SPEED * dt;
	count %= FULL_CIRCLE_DEGREE;

	x = origin_pos_x + CIRCULAR_MOVING_RADIUS * sin(count * PI / HALF_CIRCLE_DEGREE);
	y = origin_pos_y + CIRCULAR_MOVING_RADIUS * cos(count * PI / HALF_CIRCLE_DEGREE);



	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{
		player->CollideWithEnemy();
	}

}

void CircularMoving::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ANI_CIRCULAR_MOVING)->Render(x, y);

	//RenderBoundingBox();
}

void CircularMoving::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CIRCAL_BBOX_WIDTH / 2;
	t = y - CIRCAL_BBOX_HEIGHT / 2;
	r = l + CIRCAL_BBOX_WIDTH;
	b = t + CIRCAL_BBOX_HEIGHT;
}