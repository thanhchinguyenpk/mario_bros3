#include "Map.h"
#include <iostream>
#include <fstream>
#include "debug.h"
#include "Textures.h"
#include "Game.h"

void Map::LoadTileSet()
{
	//DebugOut(L"day nefff: %d", a);
	int a,b;
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
	textures->Add(100, L"textures\\Final1.png", D3DCOLOR_XRGB(255, 255, 255));

	int id = 0;
	CSprites* sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 titleset = textures->Get(100);



	for (int i = 0; i < height_tile_set; i++)
	{
		for (int j = 0; j < width_tile_set; j++)
		{
			sprites->Add(id++, j*48, i*48, j*48+48 , i*48+48, titleset); // can chinh cho nay
		}
	}
	
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();

	int w = 48;
	int h = 48;

	int  SCREEN_WIDTH = 520;
	int  SCREEN_HEIGHT = 340;

	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	int begin_row = cam_y / w ;//
	int end_row =( cam_y + SCREEN_HEIGHT) / w -1;//

	if (begin_row < 0)
		begin_row = 0;


	int begin_column = cam_x / h ; //cọng 1 để nó trồi lên 1 tiled, để quan sát
	int end_column = (cam_x  + SCREEN_WIDTH)/h;//

	if (begin_column < 0)
		begin_column = 0;

	DebugOut(L"end row %d \n", end_row);
	DebugOut(L"end column %d \n", end_column);

	for (int  i=begin_row; i < end_row ; i++)
	{
		for (int j = begin_column; j < end_column; j++)
		{
			if (map[i][j] <= 0)
				continue;
			sprites->Get(map[i][j] - 1)->Draw(j * w, i * h);// trừ một vì số thứ tự của tile đánh số từ 0 
		}

	}
}

Map::Map() {}

Map::~Map() {}