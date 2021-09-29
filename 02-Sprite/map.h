#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	LPCWSTR mapFilePath = L"textures\\map20x20.txt";
	int map[200][200];
public:
	Map();
	~Map();
	void LoadTileSet();
};

