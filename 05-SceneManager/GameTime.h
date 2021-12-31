#pragma once
#include "Game.h"

#define ONE_SECOND_UNIT			1000



class GameTime
{

	static GameTime* __instance;

public:

	static GameTime* GetInstance();

	int gameTime;
	DWORD currentTotalTime;

	void Update(DWORD dt);
	void Reset() { gameTime = 0; }
	int GetTime() { return gameTime; }

	GameTime();
	~GameTime();
};

