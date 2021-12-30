#include "Door.h"

void Door::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(ANI_COIN)->Render(x, y);

	RenderBoundingBox();
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (player->is_up_press == true)
	{
		
		
		float ml, mt, mr, mb;
		float il, it, ir, ib;

		this->GetBoundingBox(il, it, ir, ib);
		player->GetBoundingBox(ml, mt, mr, mb);

		if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
		{
			if (this->type == 1)
			{
				player->SetPosition(3600, 2300);
				player->is_on_the_ground = true;
			}
			else if (this->type == 2)
			{
				player->SetPosition(5958, 1083);
				player->is_on_the_ground = false;
			}
		}

	}
}

void Door::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}