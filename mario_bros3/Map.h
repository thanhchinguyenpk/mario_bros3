#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	CSprites* sprites = CSprites::GetInstance();
	
	LPCWSTR mapFilePath=L"textures\\map10x10.txt";
	int map[200][200];

public:
	Map();
	~Map();
	void LoadTileSet();
	void Draw();

};

