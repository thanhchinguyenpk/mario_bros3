﻿#include "RandomBonus.h"
#include "TextAndNumber.h"

RandomBonus::RandomBonus(float x, float y, CMario* mario) : CGameObject(x, y)
{
	start_ani = GetTickCount64();
	SetState(STATE_RANDOM_BONUS_FIRE_FLOWER);
	this->player = mario;
	
}



void RandomBonus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (got_bonus == false)
	{
		float mt, ml, mb, mr, l, t, r, b;
		player->GetBoundingBox(ml, mt, mr, mb);
		this->GetBoundingBox(l, t, r, b);
		if (this->CheckOverLap(ml, mt, mr, mb, l, t, r, b))
		{
			//DebugOut(L"va chạm rùi hihi object type: %d\n");
			got_bonus = true;
			time_order_to_render_text = GetTickCount64();
			
			player->is_hit_bonus = true;
			

		}
	}

	if (GetTickCount64() - start_ani >= TIME_TO_CHANGE_ITEM && got_bonus == false)
	{
		switch (state) {
		case STATE_RANDOM_BONUS_MUSHROOM:
			SetState(STATE_RANDOM_BONUS_STAR);
			break;
		case STATE_RANDOM_BONUS_STAR:
			SetState(STATE_RANDOM_BONUS_FIRE_FLOWER);
			break;
		case STATE_RANDOM_BONUS_FIRE_FLOWER:
			SetState(STATE_RANDOM_BONUS_MUSHROOM);
			break;
		}
		start_ani = GetTickCount64();
	}

	if (got_bonus == true)
	{
		switch (state) {
		case STATE_RANDOM_BONUS_MUSHROOM:
			SetState(STATE_GOT_BONUS_MUSHROOM);
			//cart_after_text = 1;
			player->card_end_scene = CARD_MUSHROOM;
			//scene->mario_end_bonus = MUSHROOM_CARD;
			break;
		case STATE_RANDOM_BONUS_FIRE_FLOWER:
			SetState(STATE_GOT_BONUS_FIRE_FLOWER);
			//cart_after_text = 2;
			player->card_end_scene = CARD_FIRE_FLOWER;
			//scene->mario_end_bonus = FIRE_FLOWER_CARD;
			break;
		case STATE_RANDOM_BONUS_STAR:
			SetState(STATE_GOT_BONUS_STAR);
			//cart_after_text = 3;
			player->card_end_scene = CARD_BONUS_STAR;
			//scene->mario_end_bonus = STAR_MAN_CARD;
			break;
		}

		x += vx * dt;
		y += vy * dt;
	}
}

void RandomBonus::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int ani = 0;

	if (state == STATE_RANDOM_BONUS_MUSHROOM)
		ani = ANI_BONUS_MUSHROOM;
	else if (state == STATE_RANDOM_BONUS_STAR)
		ani = ANI_BONUS_STAR;
	else if (state == STATE_RANDOM_BONUS_FIRE_FLOWER)
		ani = ANI_BONUS_FIRE_FLOWER;
	else if (state == STATE_GOT_BONUS_MUSHROOM)
		ani = ANI_GOT_BONUS_MUSHROOM;
	else if (state == STATE_GOT_BONUS_STAR)
		ani = ANI_GOT_BONUS_STAR;
	else if (state == STATE_GOT_BONUS_FIRE_FLOWER)
		ani = ANI_GOT_BONUS_FIRE_FLOWER;

	
	CSprites::GetInstance()->Get(ANI_RANDOM_BONUS_BOUNDARY)->Draw(RANDOM_BONUS_BOUNDARY_POS_X, RANDOM_BONUS_BOUNDARY_POS_Y);

	animations->Get(ani)->Render(x, y);
	
	if (got_bonus == true)
	{
		float x = CGame::GetInstance()->GetCamX();
		float y = CGame::GetInstance()->GetCamY();

		if (GetTickCount64() - time_order_to_render_text > TIME_TO_RENDER_COURSE_CLEAR)
			text.Render(x + FIX_COURSE_CLEAR_X, y + FIX_COURSE_CLEAR_Y, COURSE_CLEAR);

		if (GetTickCount64() - time_order_to_render_text > TIME_TO_RENDER_YOU_GOT_A_CARD)
			text.Render(x + FIX_YOU_GOT_A_CARD_X, y + FIX_YOU_GOT_A_CARD_Y, YOU_GOT_A_CARD);

		if (GetTickCount64() - time_order_to_render_text > TIME_TO_RENDER_CARD)
			CSprites::GetInstance()->Get(WHICH_CARD + player->card_end_scene)->Draw(x + FIX_CARD_X, y + FIX_CARD_Y);
				//CSprites::GetInstance()->Get(40040 + mario->which_card)->DrawFlipX(x + 550, y + 155, 0, 255, 1, 1);CSprites::GetInstance()->Get(40040 + mario->which_card)->DrawFlipX(x + 550, y + 155, 0, 255, 1, 1);
			

		//TextAndNumber text;
		//CSprites::GetInstance()->Get(40040 )->DrawFlipX(x + 100, y + 155, 0, 255, 1, 1);
	}
	
	RenderBoundingBox();
}


void RandomBonus::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {
	case STATE_GOT_BONUS_MUSHROOM:
	case STATE_GOT_BONUS_STAR:
	case STATE_GOT_BONUS_FIRE_FLOWER:
		vy = -RANDOM_BONUS_FLY_VY;
		break;
	}
}

void RandomBonus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - RANDOMBONUS_BBOX_WIDTH / 2;
	t = y - RANDOMBONUS_BBOX_HEIGHT / 2;
	r = l + RANDOMBONUS_BBOX_WIDTH;
	b = t + RANDOMBONUS_BBOX_HEIGHT;
}

