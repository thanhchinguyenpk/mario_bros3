﻿#include "Grid.h"
#include "Goomba.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <fstream>
#include "debug.h"
#include "PlayScene.h"

#include "Utils.h"

void CGrid::Classify(LPGAMEOBJECT obj)
{
	//type 1 moving flatform, 2 la gach blink
	if (obj->type == 1)
		items.push_back(obj);
	else if (obj->type == 2)
		bricks.push_back(obj);
	else
		enemies.push_back(obj);
}

void CGrid::GetListObjInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();

	enemies.clear();
	//items.clear();
	//bricks.clear();

	int top = (int)((cam_y) / CELL_HEIGHT);
	int bottom = (int)((cam_y + 730) / CELL_HEIGHT);

	int left = (int)((cam_x) / CELL_WIDTH);
	int right = (int)((cam_x + 760) / CELL_WIDTH);



	for (int i = top - 1; i <= bottom + 1; i++)
		for (int j = left; j <= right; j++) { // trừ bớt 2  để test


			if (j < 0) j = 0;
			if (i < 0) i = 0;
			/*DebugOut(L"i %d\n", i);
			DebugOut(L"j %d\n", j);
			DebugOut(L"size %d\n", cells[i][j].size());*/

			for (int k = 0; k < cells[i][j].size(); k++) {
				//DebugOut(L"id %d\n", cells[i][j].at(k)->id);
				//if (cells[i][j].at(k)->GetHealth()) {
				if (cells[i][j].at(k)->is_appeared == false && cells[i][j].at(k)->isDeleted == false) // nếu chưa xuất hiện và chưa chết
					//{//  && // is_appeared: giả sử nó có mặt trong 4 ô thì chỉ lấy 1 ô
					//if (j >= left && j <= right)

					//&& cells[i][j].at(k)->used == false không cần thiết
				{
					Classify(cells[i][j].at(k));
					cells[i][j].at(k)->is_appeared = true; // tại sao trong playscene lại phục hồi lại biến này dị tarr
				}
				//}
					//if (!cells[i][j].at(k)->is_in_grid && cells[i][j].at(k)->is_appeared) {

					//	cells[i][j].at(k)->is_in_grid = true;
				//	}

				//}
			}
		}


	//giữ
	//game->GetCurrentScene()->SetEnemiesInScene(enemies);
	
	//game->GetCurrentScene()->SetItemsInScene(items);
	//game->GetCurrentScene()->SetBrickInScene(bricks);

	//dynamic_cast<ParaGoompa*>(e->obj);
	//dynamic_cast<PlayScene*>(game->GetCurrentScene());
	
	//if (dynamic_cast<CPlayScene*>(game->GetCurrentScene()))
	//{
		dynamic_cast<CPlayScene*>(game->GetCurrentScene())->SetEnemiesInScene(enemies);
	//}
}

void CGrid::UpdatePositionInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();
	int top_cell = (int)((cam_y) / CELL_HEIGHT);
	int bottom_cell = (int)((cam_y + SCREEN_HEIGHT) / CELL_HEIGHT) - 1;

	int left_cell = (int)((cam_x) / CELL_WIDTH);
	int right_cell = (int)((cam_x + SCREEN_WIDTH) / CELL_WIDTH);




	if (dynamic_cast<CPlayScene*>(game->GetCurrentScene()))
	{
		enemies.clear();

		CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
		enemies = scene->enemies;
		//items = scene->items;
		// update  vị trí của enemy trong cam từ cell này qua cell khác
		for (int m = 0; m < enemies.size(); m++) {
			LPGAMEOBJECT enemy = enemies[m];

			for (int i = top_cell - 1; i <= bottom_cell + 1; i++)
				for (int j = left_cell - 2; j <= right_cell + 2; j++) {
					if (j < 0) j = 0;
					if (i < 0) i = 0;
					for (int k = 0; k < cells[i][j].size(); k++) {
						if (cells[i][j].at(k)->id_grid == enemy->id_grid) {
							cells[i][j].erase(cells[i][j].begin() + k);
						}
					}
				}

			int top = (int)(enemy->GetY() / CELL_HEIGHT);
			int bottom = (int)((enemy->GetY() + enemy->h) / CELL_HEIGHT);
			int left = (int)(enemy->GetX() / CELL_WIDTH);
			int right = (int)((enemy->GetX() + enemy->w) / CELL_WIDTH);
			/*DebugOut(L"***********\n");
			DebugOut(L"left %d\n", left);
			DebugOut(L"right %d\n", right);*/

			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++) {
					cells[i][j].push_back(enemy);
				}
		}



	}
	






}

LPGAMEOBJECT CGrid::CreateNewObj(int obj_type, float x, float y, float w, float h, int ani_id, int type, int extra0, int extra1, int extra2, int id_grid)
{
	///CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (obj_type)
	{

		case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, player); break;
		/*case 7:
		{
			int lv = type;
			obj = new VenusFireTrap(player, lv);
			//obj->SetState(VENUS_STATE_GOING_UP);
			break;
		}
		case 8:
		{
			//int lv = atof(tokens[4].c_str());
			obj = new PiranhaPlant(player);
			//obj->SetState(PIRANHA_PLANT_STATE_GOING_UP);
			break;
		}

		case 4:

		{
			obj = new CConCo(player, y);
			dynamic_cast<CConCo*>(obj)->type = type; //loại cò
			break;
		}
		case 5:
		{
			obj = new ParaGoomba(player);
			//obj->SetState(PARA_GROOMBA_STATE_JUMP_BIG);
			break;
		}

		case 15:
		{
			//int state = atof(tokens[4].c_str());
			obj = new MovingFlatform(player);

			break;
		}
		case 11:
		{
			//int lv = atof(tokens[4].c_str());
			obj = new BrickBlink(player);
			//obj->SetState(BRICK_COIN_STATE_CHUA_DAP);
			break;
		}*/

	}


	obj->SetPosition(x, y);
	obj->w = w;
	obj->h = h;
	obj->id_grid = id_grid;

	//LPANIMATION_SET ani_set = animation_sets->Get(ani_id);
	// nhớ thêm đoạn code animation set mà null chẳng hạn 0:32:38
	//obj->SetAnimationSet(ani_set);

	return obj;
	//return NULL;
}

void CGrid::ReadFileObj()
{
	ifstream f;
	f.open(objFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 8) continue;
		int id_grid = atoi(tokens[0].c_str());
		int object_type = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());

		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());

		int ani_id = atoi(tokens[6].c_str());


		int type = atoi(tokens[7].c_str());
		int extra = 0;
		if (object_type == 2 || object_type == 3 ||
			object_type == 6 || object_type == 11 ||
			object_type == 1)
			extra = atoi(tokens[8].c_str());

		//AddObjectIntoGrid(object_type, x, y, w, h, ani_id, type, extra);
		LPGAMEOBJECT obj = CreateNewObj(object_type, x, y, w, h, ani_id, type, extra, 1, 1, id_grid);
		total_obj.push_back(obj);											//extra0, extra1,extra2

	}

	DebugOut(L"total obj la---------------] DINPUT::GetDeviceData failed. Error: %d\n", total_obj.size());
	f.close();

	//LPGAMEOBJECT obj = CreateNewObj(2, 672,1152, 48, 48, 0, 0, 0, 1, 1, 9);
	//total_obj.push_back(obj);
	//9	2	672	1152	48	48	5	2	100
}

void CGrid::ReadFileGrid()
{
	//objs.clear();
	ifstream f;
	f.open(gridFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 3) continue;
		int i = atoi(tokens[0].c_str());
		int j = atoi(tokens[1].c_str());

		//bốc id tìm trong số object
		for (int k = 2; k < tokens.size(); k++) {
			int id = atoi(tokens[k].c_str());
			for (LPGAMEOBJECT obj : total_obj) // chaỵ trong list object để tìm id match
				if (id == obj->id_grid) {
					cells[i][j].push_back(obj);
				}

		}
	}

	f.close();

	//DebugOut(L"[EEEEEEEEEEEEEEE] DINPUT::GetDeviceData failed. Error: %d\n", cells[6][14].size());
}

CGrid::CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath, CMario* mario)
{
	//DebugOut(L"new\n");
	this->objFilePath = objFilePath;
	this->gridFilePath = gridFilePath;

	player = mario;
}
