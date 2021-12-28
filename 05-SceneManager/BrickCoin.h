#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"

#define ID_ANI_BRICK_COIN 10000
#define ID_ANI_BRICKBLINK 746
#define BRICK_COIN_WIDTH 48
#define BRICK_COIN_BBOX_WIDTH 48
#define BRICK_COIN_BBOX_HEIGHT 48

//#define BRICK_COIN_STATE_CHUA_DAP	100
#define BRICK_COIN_STATE_DA_DAP 	200
#define BRICK_COIN_STATE_HORIZONTALLY_BOUCING 	300


#define ID_ANI_BRICK_QUESION 7000
#define ID_ANI_BRICK_QUESION_IS_HIT 7001

#define NORMAL_BRICKCOIN 0
#define BRICKCOIN_CONTAINS_EATABLE_ITEM 1
#define BRICKCOIN_CONTAINS_PBUTTON 2
#define BRICKCOIN_CONTAINS_GREEN_MUSHROOM 3
#define BRICKCOIN_CONTAINS_FIRE_FLOWER 4

class BrickCoin : public CGameObject {
public:
	CMario* player;

	float originalX = x;

	int has_item = NORMAL_BRICKCOIN;

	bool dropped = false;
	bool is_hit = false;
	//bool flag = false;
	float originalY = y;
	BrickCoin(float x, float y, int hasItem, CMario* mario) : CGameObject(x, y) { has_item = hasItem; player = mario; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};