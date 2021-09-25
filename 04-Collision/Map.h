#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	int width_map = 20;
	int height_map = 20;

	int width_tile_set =29 ;
	int height_tile_set =30 ;

	int width_tile = 48;
	int height_tile = 48;

	CSprites* sprites = CSprites::GetInstance();
	
	LPCWSTR mapFilePath=L"textures\\map20x20.txt";
	int map[200][200];

public:
	Map();
	~Map();
	void LoadTileSet();
	void Draw();

};

