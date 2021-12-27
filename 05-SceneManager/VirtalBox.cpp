#include "VirtalBox.h"
#include "Mario.h"


void VirtalBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(777)->Render(x, y);

	RenderBoundingBox();
}

void VirtalBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += AY_VIRTUAL_BOX * dt;

	CGameObject::Update(dt, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void VirtalBox::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	//y += vy * dt;
}
void VirtalBox::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VIRTUAL_BOX_ADJUST_HEIGHT:
		y -= GAP;
		break;
	}
}
;
void VirtalBox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	//if (dynamic_cast<CMario*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		vx = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
		
	}

	/*if (dynamic_cast<CMario*>(e->obj))
	{
		if (e->ny > 0)
		{
			DebugOut(L"da dap len virtalbox %d \n");
			this->SetState(VIRTUAL_BOX_ADJUST_HEIGHT);
		}
	}*/
}

void VirtalBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}