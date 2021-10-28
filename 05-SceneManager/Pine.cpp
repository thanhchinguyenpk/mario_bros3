﻿#include "Pine.h"

void Pine::Render()
{
	int ani = 0;
	if (state == PINE_STATE_TALL)
		ani = ANI_PINE_TALL;
	else if (state == PINE_STATE_SHORT)
		ani = ANI_PINE_SHORT;
	else if (state == PINE_STATE_BLACK)
		ani = ANI_PINE_BLACK;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani)->Render(x, y);

	RenderBoundingBox();


}

void Pine::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == PINE_STATE_TALL)
	{
		l = x - PINE_TALL_BBOX_WIDTH / 2;
		t = y - PINE_TALL_BBOX_HEIGHT / 2;
		r = x + PINE_TALL_BBOX_WIDTH / 2;
		b = y + PINE_TALL_BBOX_HEIGHT / 2;
	}
	else if (state == PINE_STATE_SHORT || state == PINE_STATE_BLACK)
	{
		l = x - PINE_SHORT_BBOX_WIDTH / 2;
		t = y - PINE_SHORT_BBOX_HEIGHT / 2;
		r = x + PINE_SHORT_BBOX_WIDTH / 2;
		b = y + PINE_SHORT_BBOX_HEIGHT / 2;
	}
}

void Pine::SetState(int state)
{
	CGameObject::SetState(state);
}