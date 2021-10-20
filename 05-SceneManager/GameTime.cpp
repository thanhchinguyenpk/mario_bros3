#include "GameTime.h"

void GameTime::Update(DWORD dt)
{
	if (currentTotalTime + dt > ONE_SECOND_UNIT)
	{
		//Lay phan thua` cua dt ra
		currentTotalTime = (currentTotalTime + dt) % ONE_SECOND_UNIT;
		gameTime++;
	}
	else
		currentTotalTime += dt;
}

GameTime::GameTime()
{
	currentTotalTime = 0;
	gameTime = 0;
	
}

GameTime::~GameTime()
{
}