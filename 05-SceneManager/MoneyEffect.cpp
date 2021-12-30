#include "MoneyEffect.h"

MoneyEffect::MoneyEffect(float pos_x, float pos_y, int moneyAni)
{
	this->x = pos_x;
	this->y = pos_y;

	vy = -VY_MONEY_EFFECT;
	effectTime = MONEY_EFFECT_TIME;

	//this->SetAnimationSet(CAnimationSets::GetInstance()->Get(23));
}

void MoneyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Effect::Update(dt, coObjects);
	y += vy*dt;
}

void MoneyEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ANI_MONEY_EFFECT)->Render(x, y);
}

MoneyEffect::~MoneyEffect()
{
}
