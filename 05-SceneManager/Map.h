#pragma once
#include "Textures.h"
#include "Sprites.h"

#define WIDTH 48
#define HEIGHT 48

#define MAX_ROW 200
#define MAX_COLUMN 200

#define SCREEN_WIDTH  760
#define SCREEN_HEIGHT  730

#define MIN_ROW 0
#define MIN_COLUMN 0

#define IS_NOT_COLOURED_TILE 0

#define ID_MAP_TILE_SET 100
class Map
{
	int width_tile = WIDTH;
	int height_tile = HEIGHT;

	int number_tile_set_width;
	int number_tile_set_height;

	//int width_map = 20;
	//int height_map = 20;
	LPCWSTR tileSetFilePath;// L"textures\\Final1.png"

	int width_map;// = 176;
	int height_map;//; = 41;


	LPCWSTR mapTextFilePath;// = L"textures\\map_thanh.txt";
	int map[MAX_ROW][MAX_COLUMN];
public:
	Map(LPCWSTR maptext, LPCWSTR tileset, int width_map, int height_map,
		int number_tile_set_width,int number_tile_set_height);
	~Map();
	void LoadTileSet();
	void Draw();
};

