#include "VirtalBox.h"


void VirtalBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(777)->Render(x, y);

	RenderBoundingBox();
}

void VirtalBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.002 * dt;

	CGameObject::Update(dt, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void VirtalBox::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	//y += vy * dt;
};
void VirtalBox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		vx = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
		
	}
}

void VirtalBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}