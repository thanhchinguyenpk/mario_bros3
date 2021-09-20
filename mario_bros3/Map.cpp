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

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			f >> map[i][j];
			
			//DebugOut(L"day nefff: %d \n", map[i][j]);
		}
	}
	
	DebugOut(L"day nefff: %d \n", map[0][0]);
	DebugOut(L"day nefff: %d \n", map[0][1]);
	
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
			sprites->Add(id++, j*48, i*48, j*48+48 , i*48+48, titleset);
		}
	}
	
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();
	//CSprite *temp = sprites->Get(0);
	//temp->Draw(0, 0);
	float cam_x=0, cam_y=0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	//DebugOut(L"day nefff: %f \n", cam_x);
	//DebugOut(L"day nefff: %f \n", cam_y);
	
	int i = cam_y / 48 + 1;
	int tamp = i;
	if (i < 0)
		i = 0;
	

	for ( i ; i < tamp+5; i++)
	{
		int truc_ngang = cam_x / 48 +1; //cọng 1 để nó trồi lên 1 tiled, để quan sát
		//DebugOut(L"truc ngang: %d \n", truc_ngang);
		int tem = truc_ngang;
		if (truc_ngang < 0)
			truc_ngang=0;

		for (truc_ngang ; truc_ngang < tem+7; truc_ngang++)
		{
			if (map[i][truc_ngang] <= 0)
				continue;
			sprites->Get(map[i][truc_ngang]-1)->Draw(truc_ngang *48,i*48);
		}

		DebugOut(L"cuuuu: %d \n", map[99][0]);
	}

	/*temp = sprites->Get(1);
	temp->Draw(48, 0);

	temp = sprites->Get(2);
	temp->Draw(96, 0);


	temp = sprites->Get(29);
	temp->Draw(0, 48);
	temp = sprites->Get(30);
	temp->Draw(48, 48);
	temp = sprites->Get(31);
	temp->Draw(96, 48);

	temp = sprites->Get(58);
	temp->Draw(0, 96);
	temp = sprites->Get(59);
	temp->Draw(48, 96);
	temp = sprites->Get(60);
	temp->Draw(96, 96);


	temp = sprites->Get(61);
	temp->Draw(0, 144);
	temp = sprites->Get(62);
	temp->Draw(48, 144);
	temp = sprites->Get(63);
	temp->Draw(96, 144);*/
}

Map::Map() {}

Map::~Map() {}