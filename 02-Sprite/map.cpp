#include "map.h"
#include <iostream>
#include <fstream>

map::map()
{
}

map::~map()
{
}

void map::LoadTileSet()
{
	//DebugOut(L"day nefff: %d", a);
	int a, b;
	ifstream f;
	f.open(mapFilePath);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> _map[i][j];

			//DebugOut(L"day nefff: %d \n", map[i][j]);
		}
	}

	//DebugOut(L"day nefff: %d \n", map[0][0]);
	//DebugOut(L"day nefff: %d \n", map[0][1]);

	f.close();


}
