
#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "TextAndNumber.h"
#include "GameTime.h"
#include "ParaGoompa.h"
#include "Map.h"
#include "PiranhaPlant.h"
#include "UI.h"
#include "CoinEffect.h"

#define CAM_MIN_X_UNDER_CASTLE 3550
#define CAM_WIDTH_UNDER_CASTLE 74
#define CAM_Y_UNDER_CASTLE 2100


#define CAM_MIN_X_IN_CASTLE 7680-760+15
#define CAM_WIDTH_IN_CASTLE 24
#define CAM_Y_IN_CASTLE 700

#define Y_STUCK_WITH_BOSS 7320

#define CAM_X_END_CASTLE 7680 - 760 + 15 - 24
#define CAM_Y_END_CASTLE 700

#define OBJECT_BLOCK_MARIO_END_CASTLE_POS_X 6886
#define OBJECT_BLOCK_MARIO_END_CASTLE_POS_Y 760
#define OBJECT_BLOCK_MARIO_END_CASTLE_WIDTH 48
#define OBJECT_BLOCK_MARIO_END_CASTLE_HEIGHT 432


class CastleScene : public CScene
{
	//protected: 
public:

	//bool is_mario_in_end_castle;
	// A play scene has to have player, right? 
	
	GameTime* game_time= new GameTime();
	UI* game_ui=new UI();

	Map* map;

	//LPGAMEOBJECT player;
	CMario* player;
	TextAndNumber temp;
	//GameTime* game_time ;

	vector<LPGAMEOBJECT> enemies;
	void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) { enemies.clear(); enemies = listEnemy; }


	vector<LPGAMEOBJECT> list_bricklink;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);

	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);

	void LoadAssets(LPCWSTR assetFile);

	//public: 

	void DropItem(int itemType, float x, float y);
	CastleScene(int id, LPCWSTR filePath);

	virtual void Load(); //load file scene 02, 01
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	//bool is_mario_in_end_castle = false;
};

typedef CastleScene* LPCASTLESCENE;

