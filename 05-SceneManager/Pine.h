
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define	 PINE_TALL_BBOX_WIDTH 32*3
#define	 PINE_TALL_BBOX_HEIGHT 48*3

#define	 PINE_SHORT_BBOX_WIDTH 30*3
#define	 PINE_SHORT_BBOX_HEIGHT 32*3


#define  PINE_STATE_TALL				100
#define  PINE_STATE_SHORT				200
#define  PINE_STATE_BLACK				300

#define  ANI_PINE_TALL				740
#define  ANI_PINE_SHORT				741
#define  ANI_PINE_BLACK				742


#define  PINE_TALL				1
#define  PINE_SHORT				2
#define  PINE_BLACK				3
class Pine : public CGameObject
{
public:

	bool is_pine_can_go = false;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render();

	virtual int IsCollidable() { return 1; }; //hàm cha trả về 0
	//virtual int IsBlocking() { return 0; } // hàm cha trả về 1
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Pine(float x, float y, int type,int is_pine_can_go);
	virtual void SetState(int state);
};
