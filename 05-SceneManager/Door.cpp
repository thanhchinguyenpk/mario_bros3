#include "Door.h"

void Door::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(ANI_COIN)->Render(x, y);

	RenderBoundingBox();
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Door::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}