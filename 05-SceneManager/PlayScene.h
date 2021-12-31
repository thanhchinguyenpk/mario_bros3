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
#include "Grid.h"

//#include "Koopas.h"


class CPlayScene: public CScene
{
//protected: 
public:

	CGrid* grid;
	// A play scene has to have player, right? 
	GameTime* game_time=new GameTime();
	UI* game_ui=new UI();

	Map* map;

	//LPGAMEOBJECT player;
	CMario* player;
	TextAndNumber temp;
	//GameTime* game_time ;

	vector<LPGAMEOBJECT> enemies;//dr
	vector<LPGAMEOBJECT> list_bricklink;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;
	
	//vector<LPGAMEOBJECT> items;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);

	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);
	void _ParseSection_OBJECTS_GRID(string line);

	void LoadAssets(LPCWSTR assetFile);
	
//public: 

	void DropItem(int itemType, float x, float y);
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load(); //load file scene 02, 01
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	//void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) { enemies.clear(); enemies = listEnemy; }
	 void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) {  }
	//void SetItems(vector<LPGAMEOBJECT> listItem) { items.clear(); items = listItem; }
	// void SetBrickBlink(vector<LPGAMEOBJECT> ListBrickBlink) { list_bricklink.clear(); list_bricklink = ListBrickBlink; }
	void SetBrickBlink(vector<LPGAMEOBJECT> ListBrickBlink) { }
	

};

typedef CPlayScene* LPPLAYSCENE;

