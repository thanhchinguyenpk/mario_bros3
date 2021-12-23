
// Koompas


#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "FlatForm.h"
#include "VirtalBox.h"

#define GOOMBA_GRAVITY 0.002f
#define KOOMPAS_WALKING_SPEED 0.06f
#define KOOMPAS_FLYING_SPEED_Y 0.5f

#define KOOMPAS_BBOX_WIDTH 16*3
#define KOOMPAS_BBOX_HEIGHT 27*3

#define GOOMBA_BBOX_WIDTH_INDENT_IN 15*3
#define GOOMBA_BBOX_HEIGHT_INDENT_IN 15*3

#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500


#define CONCO_STATE_WALKING_LEFT	100
#define CONCO_STATE_DIE				200
#define CONCO_STATE_WALKING_RIGHT	300
#define GOOMBA_STATE_INDENT_IN		400
#define GOOMBA_STATE_SHELL_RUNNING	500
#define CONCO_STATE_MAI_RUA_CHAY_TRAI	501
#define CONCO_STATE_FLY_LEFT	    600
#define CONCO_STATE_FLY_RIGHT	    700
#define CONCO_STATE_WAS_BROUGHT	    800
#define CONCO_STATE_WAS_SHOOTED		900
#define CONCO_STATE_INDENT_OUT		1000
#define CONCO_STATE_SHELL_MOVING		1100
#define CONCO_STATE_RED_FLY_Y		1200

#define CONCO_STATE_BEING_HOLDING		1300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_ANI_KOOMPAS_WALKING_LEFT 6000
#define ID_ANI_KOOMPAS_INDENT_IN 6100



#define CONCO_ANI_RED_WALKING_LEFT	 708
#define CONCO_ANI_RED_THUT_VAO		 709
#define CONCO_ANI_RED_MAI_RUA_CHAY	 710
#define CONCO_ANI_RED_FLY_LEFT		 711

#define CONCO_ANI_RED_FLY_RIGHT			 712
#define CONCO_ANI_RED_WALKING_RIGHT	     713
#define CONCO_ANI_RED_SHELL_MOVING		 714
#define CONCO_ANI_RED_INDENT_OUT		 715
#define CONCO_ANI_RED_WAS_SHOOTED 5402

//=========================================

#define CONCO_ANI_GREEN_WALKING_LEFT	 716
#define CONCO_ANI_GREEN_THUT_VAO		 717
#define CONCO_ANI_GREEN_MAI_RUA_CHAY	 718
#define CONCO_ANI_GREEN_FLY_LEFT		 719

#define CONCO_ANI_GREEN_FLY_RIGHT			 720
#define CONCO_ANI_GREEN_WALKING_RIGHT	     721
#define CONCO_ANI_GREEN_SHELL_MOVING		 722
#define CONCO_ANI_GREEN_INDENT_OUT		 723
#define CONCO_ANI_GREEN_WAS_SHOOTED 5410



#define KOOMPAS_GREEN		 0
#define KOOMPAS_RED		 1



class Koompas : public CGameObject
{
public:

	VirtalBox* virtalbox = NULL;

	int type = KOOMPAS_GREEN;

	bool is_blocking = 1;

	bool is_minus_vx = false;
	bool is_colliable = 1;
	ULONGLONG time_to_indent_out;

	float ax=0;
	float ay=0;
	LPGAMEOBJECT player;
	ULONGLONG die_start;


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return is_colliable; };
//	virtual int IsBlocking() { return 1; };
	virtual int IsBlocking() {return is_blocking ; };

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithFlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithKoompas(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickCoin(LPCOLLISIONEVENT e);

	void OnCollisionWithBrickBlink(LPCOLLISIONEVENT e);


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Koompas(float x, float y, LPGAMEOBJECT mario, int koompas_type, int koompas_state);
	virtual void SetState(int state);
};