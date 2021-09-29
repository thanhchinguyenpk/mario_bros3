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

	for (int i = 0; i < height_map; i++)
	{
		for (int j = 0; j < width_map; j++)
		{
			f >> map[i][j];

			//DebugOut(L"day nefff: %d \n", map[i][j]);
		}
	}

	//DebugOut(L"day nefff: %d \n", map[0][0]);
	//DebugOut(L"day nefff: %d \n", map[0][1]);

	f.close();

	CTextures* textures = CTextures::GetInstance();


	textures->Add(100, L"textures\\Final1.png");

	int id = 0;
	CSprites* sprites = CSprites::GetInstance();


	LPTEXTURE titleset = textures->Get(100);



	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			sprites->Add(id++, j * width_tileset, i * height_tileset,
				j * width_tileset + width_tileset, i * height_tileset + height_tileset, titleset);
		}
	}
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();

	for (int i = 15; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] <= 0)
				continue;
			sprites->Get(map[i][j] - 1)->Draw(j * width_tileset, (i - 15) * height_tileset);
		}

	}

}
