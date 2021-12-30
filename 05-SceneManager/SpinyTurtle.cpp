#include "SpinyTurtle.h"
#include "FlatForm.h"

SpinyTurtle::SpinyTurtle(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->SetState(SPINY_TURTLE_STATE_STILL);
	player = mario;
}

void SpinyTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	//if (state == SPINY_TURTLE_STATE_INJURY)
	//	return;

	if ( state == SPINY_TURTLE_STATE_HEAD_MOVING)
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

	vx += ax * dt;

	if (stage == 1)
	{
		if (this->x - player->x < 200 && state == SPINY_TURTLE_STATE_STILL)
			this->SetState(SPINY_TURTLE_STATE_JUMP);


		if (abs(this->x - player->x) > 300 && state== SPINY_TURTLE_STATE_WALKING)
		{
			if (this->x > player->x)
				vx = -abs(vx);
			else if (this->x < player->x)
				vx = abs(vx);

			time_to_spine = GetTickCount64();

		}

		if (GetState() == SPINY_TURTLE_STATE_WALKING && GetTickCount64() - time_to_spine >= 300 && time_to_spine)
		{
			SetState(SPINY_TURTLE_STATE_SPINE);

			if (vx > 0)
				ax = -0.0001;
			else if (vx < 0)
				ax = 0.0001;

			time_to_spine = 0;
			
			DebugOut(L"[INFO] vo day hoai sao------------------------------??\n");
		}

		if (abs(vx) < 0.02 && state == SPINY_TURTLE_STATE_SPINE)
		{
			this->SetState(SPINY_TURTLE_STATE_JUMP);
			ax = 0;
		}
	}
	else if (stage == 2)
	{

	}



	//DebugOut(L"[INFO] con turle:  %d\n", state);

	


	

	CCollision::GetInstance()->Process(this, dt, coObjects);



	if (GetState() == SPINY_TURTLE_STATE_INJURY && GetTickCount64() - time_to_rescue >= 3000 && time_to_rescue)
	{
		heart -= 1;

		if (heart == 0)
			CGame::GetInstance()->InitiateSwitchScene(MAP_SCENE);
		else
			this->SetState(SPINY_TURTLE_STATE_JUMP);

	}

	
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

	if (stage == 1)
	{
		if(state== SPINY_TURTLE_STATE_STILL)
			idAni = ANI_SPINE_TURTLE;

		if(vy<0)
			idAni = ANI_SPINELESS_TURTLE;
		else if(vy>0 && vy< 0.1)
			idAni = ANI_SPINE_TURTLE_STANDING;
		else if (vy > 0.1)
			idAni = ANI_SPINE_TURTLE_HAND_UP_AND_DOWN_HIGH;

		if(state== SPINY_TURTLE_STATE_WALKING)
			idAni = ANI_SPINE_TURTLE_HAND_UP_AND_DOWN_HIGH;

		if (state == SPINY_TURTLE_STATE_SPINE)
			idAni = ANI_SPINE_TURTLE;
	}

	

	if (state == SPINY_TURTLE_STATE_INJURY)
		idAni = ANI_SPINE_TURTLE_BEING_JUMPED;

	CAnimations::GetInstance()->Get(idAni)->Render(x, y);


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
		vx = -vx;

	}

	if (dynamic_cast<FlatForm*>(e->obj))
	{
		if (stage == 1)
		{
			if (state == SPINY_TURTLE_STATE_JUMP)
			{
				this->SetState(SPINY_TURTLE_STATE_WALKING);
			}
		}
	}
}



void SpinyTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPINY_TURTLE_STATE_JUMP:

		vx =  this->x> player->x ?-0.15 : 0.15;
		vy = -0.7;
	
		break;
	
	

	case SPINY_TURTLE_STATE_STILL:
		vx = 0;
		vy = 0;
		nx = 1;
		break;
	case SPINY_TURTLE_STATE_WALKING:
		//tý chỉnh tốc độ lại sau
		break;

	case SPINY_TURTLE_STATE_SPINE:
		//tý chỉnh tốc độ lại sau
		break;

	case SPINY_TURTLE_STATE_INJURY:
		vx = 0;
		vy = 0;
		ax = 0;
		time_to_rescue = GetTickCount64();
		
		
		break;

		
		
	}
}
