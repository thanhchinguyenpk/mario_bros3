#pragma once
#pragma once
#include "Textures.h"
#include "Sprites.h"
class map
{
	CSprites* sprites = CSprites::GetInstance();

	LPCWSTR mapFilePath = L"textures\\map20x20.txt";
	int _map[200][200];

public:
	map();
	~map();
	void LoadTileSet();
	
};

