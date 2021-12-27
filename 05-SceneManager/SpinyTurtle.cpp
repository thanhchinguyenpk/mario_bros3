#include "SpinyTurtle.h"


SpinyTurtle::SpinyTurtle(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->SetState(SPINY_TURTLE_STATE_WALKING_LEFT);
	player = mario;
}

void SpinyTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SPINY_TURTLE_STATE_DIE || state == SPINY_TURTLE_STATE_HEAD_MOVING)
	{
		left = x - SPINY_TURTLE_BBOX_WIDTH_DIE / 2;
		top = y - SPINY_TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + SPINY_TURTLE_BBOX_WIDTH_DIE;
		bottom = top + SPINY_TURTLE_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SPINY_TURTLE_BBOX_WIDTH / 2;
		top = y - SPINY_TURTLE_BBOX_HEIGHT / 2;
		right = left + SPINY_TURTLE_BBOX_WIDTH;
		bottom = top + SPINY_TURTLE_BBOX_HEIGHT;
	}

}


void SpinyTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += AY_SPINE_TURTLE * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	/*if (state == SPINY_TURTLE_STATE_DIE && GetTickCount64() - time_to_rescure > 5000)
	{

		this->SetState(SPINY_TURTLE_STATE_HEAD_MOVING);

	}
	if (state == SPINY_TURTLE_STATE_HEAD_MOVING && GetTickCount64() - time_to_rescure > 9000)
	{
		SetPosition(this->x, this->y - 50);

		if (nx <= 0)
			this->SetState(SPINY_TURTLE_STATE_WALKING_LEFT);
		else
			this->SetState(SPINY_TURTLE_STATE_WALKING_RIGHT);
	}
	*/
	//DebugOut(L"nx cua sto %d\n", nx);
}

void SpinyTurtle::Render()
{
	/*CAnimations::GetInstance()->Get(6000)->Render(x, y);
	CAnimations::GetInstance()->Get(6001)->Render(x+50, y); // xà xuống lúc đội đầu
	CAnimations::GetInstance()->Get(6002)->Render(x + 100, y);
	CAnimations::GetInstance()->Get(6003)->Render(x + 200, y);
	*/

	/*CAnimations::GetInstance()->Get(6010)->Render(x, y);
	CAnimations::GetInstance()->Get(6011)->Render(x + 50, y);
	CAnimations::GetInstance()->Get(6012)->Render(x + 100, y);
	CAnimations::GetInstance()->Get(6013)->Render(x + 200, y);*/

	int idAni = ANI_SPINE_TURTLE;

	


	CAnimations::GetInstance()->Get(ANI_SPINE_TURTLE)->Render(x, y);


	RenderBoundingBox();
}

void SpinyTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void SpinyTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		//vx = -vx;
		if (state == SPINY_TURTLE_STATE_WALKING_LEFT)
			this->SetState(SPINY_TURTLE_STATE_WALKING_RIGHT);
		else
			this->SetState(SPINY_TURTLE_STATE_WALKING_LEFT);
	}
}



void SpinyTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPINY_TURTLE_STATE_DIE:
		//die_start = GetTickCount64();
		//y += (SPINY_TURTLE_BBOX_HEIGHT - SPINY_TURTLE_BBOX_HEIGHT_DIE) / 2;


		vx = 0;
		vy = 0;
		//is_block = 0;
		//time_to_rescure = GetTickCount64();
		//ay = 0;
		break;
	case SPINY_TURTLE_STATE_HEAD_MOVING:
		vx = 0;
		vy = 0;
		break;
	case SPINY_TURTLE_STATE_WALKING_LEFT:
		nx = -1;
		//vx = -0.06;
		vx = 0;
		vy = 0;
		break;
	case SPINY_TURTLE_STATE_WALKING_RIGHT:
		vx = SPINY_TURTLE_WALKING_SPEED;
		nx = 1;
		break;

	}
}
