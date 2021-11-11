#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	int width_tileset = 16*3;
	int height_tileset = 16*3;

	int number_tile_set_width;
	int number_tile_set_height;

	//int width_map = 20;
	//int height_map = 20;
	LPCWSTR tileSetFilePath;// L"textures\\Final1.png"

	int width_map;// = 176;
	int height_map;//; = 41;


	LPCWSTR mapTextFilePath;// = L"textures\\map_thanh.txt";
	int map[200][200];
public:
	Map(LPCWSTR maptext, LPCWSTR tileset, int width_map, int height_map,
		int number_tile_set_width,int number_tile_set_height);
	~Map();
	void LoadTileSet();
	void Draw();
};

