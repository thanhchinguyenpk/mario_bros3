#include "Map.h"

#include <iostream>
#include <fstream>
#include "debug.h"
#include "Textures.h"
#include "Game.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadTileSet()
{
	//DebugOut(L"day nefff: %d", a);
	int a, b;
	ifstream f;
	f.open(mapFilePath);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> map[i][j];

			//DebugOut(L"day nefff: %d \n", map[i][j]);
		}
	}

	DebugOut(L"day nefff: %d \n", map[0][0]);
	DebugOut(L"day nefff: %d \n", map[0][1]);

	f.close();
}
