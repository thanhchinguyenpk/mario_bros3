#include "BrickDebris.h"
#include "debug.h"

BrickDebris::BrickDebris(float brick_pos_x, float brick_pos_y, int nx, float height)
{
	vx = DEBRIS_BRICK_SPEED_X * nx; // 2 hòn hướng quá trái/phải
	vy = -DEBRIS_BRICK_SPEED_Y * height; // 2 hòn cao hơn 
	x = brick_pos_x;
	y = brick_pos_y;
}

void BrickDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	//DebugOut(L"[INFO]vô trong debirck update ko\n");
	vy += DEBRIS_BRICK_GRAVITY * dt;
	x += vx * dt;
	y += vy * dt;

	//if (y > 1400)
	//	delete this;

	this->DeleteWhenOutOfCam();
}

void BrickDebris::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	RenderBoundingBox();
}
