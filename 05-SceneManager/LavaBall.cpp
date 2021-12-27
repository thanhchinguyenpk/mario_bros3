#include "LavaBall.h"


LavaBall::LavaBall(float x, float y) :CGameObject(x, y)
{
	//original_pos_y = y;
	this->SetState(LAVA_BALL_STATE_MOVING_UP);
}

void LavaBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(state!= LAVA_BALL_STATE_STOP)
		vy += AY_LAVA * dt;

	
	y += vy * dt;

	if (this->y > original_pos_y + LAVA_DISTANCE && time_to_stop==0)
	{
		this->SetState(LAVA_BALL_STATE_STOP);
		this->SetPosition(this->x, original_pos_y + LAVA_DISTANCE);
	}

	if (state == LAVA_BALL_STATE_STOP && GetTickCount64() - time_to_stop > LAVA_TIME_TO_MOVE_UP)
	{
		this->SetState(LAVA_BALL_STATE_MOVING_UP);
		time_to_stop = 0;
	}

}

void LavaBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LAVA_BALL_BBOX_WIDTH / 2;
	t = y - LAVA_BALL_BBOX_HEIGHT / 2;
	r = l + LAVA_BALL_BBOX_WIDTH;
	b = t + LAVA_BALL_BBOX_HEIGHT;
}



void LavaBall::Render()
{
	int IdAni = ANI_LAVA_BALL_UP;

	if(vy<0)
		IdAni = ANI_LAVA_BALL_UP;
	else
		IdAni = ANI_LAVA_BALL_DOWN;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(IdAni)->Render(x, y);

	RenderBoundingBox();
}



void LavaBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LAVA_BALL_STATE_MOVING_UP:
		//die_start = GetTickCount64();
		//y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;


		vx = 0;
		vy = -VY_LAVA;
		
		//ay = 0;
		break;

	case LAVA_BALL_STATE_STOP:
		vx = 0;
		vy = 0;
		time_to_stop = GetTickCount64();
		break;
	
	}

}
