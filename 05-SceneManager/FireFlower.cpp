#include "FireFlower.h"


void FireFlower::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ANI_FIRE_FLOWE)->Render(x, y);

	RenderBoundingBox();
}

void FireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void FireFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIRE_FLOWE_BBOX_WIDTH / 2;
	t = y - FIRE_FLOWE_BBOX_HEIGHT / 2;
	r = l + FIRE_FLOWE_BBOX_WIDTH;
	b = t + FIRE_FLOWE_BBOX_HEIGHT;
}