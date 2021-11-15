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
#include "MapPortal.h"

#define POS_CAM_X -20
#define POS_CAM_Y -20

class MapScene : public CScene
{
public:

	vector<LPGAMEOBJECT> map_portals;
	MapPortal* current_portal;

	Map* map;

	CMario* player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);

	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP_SELECTION(string line);

	void LoadAssets(LPCWSTR assetFile);

//public: 
	MapScene(int id, LPCWSTR filePath);

	virtual void Load(); //load file scene 02, 01
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef MapScene* LPMAPSCENE;
