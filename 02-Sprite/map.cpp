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

			DebugOut(L"day nefff: %d \n", _map[i][j]);
		}
	}

	DebugOut(L"day nefff: %d \n", _map[0][0]);
	DebugOut(L"day nefff: %d \n", _map[0][1]);

	f.close();

	CTextures* textures = CTextures::GetInstance();
	textures->Add(100, L"textures\\Final1.png", D3DCOLOR_XRGB(255, 255, 255));

	int id = 0;
	CSprites* sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 titleset = textures->Get(100);



	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			sprites->Add(id++, j * 48, i * 48, j * 48 + 48, i * 48 + 48, titleset);
		}
	}

}
