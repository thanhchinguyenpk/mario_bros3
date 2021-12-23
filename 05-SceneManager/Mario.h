#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "TimerCustom.h"
#include "debug.h"
#include "MarioBullet.h"

//#define MARIO_WALKING_SPEED		0.1f
#define MARIO_WALKING_SPEED		0.3f
#define MARIO_RUNNING_SPEED		0.7f

#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0007f

//#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_SPEED_Y		0.8f
#define MARIO_JUMP_RUN_SPEED_Y	0.95f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  1.0f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_STAND_SHOOT			700

#define MARIO_STATE_SPIN		800

#define MARIO_STATE_FLY_LANDING		820
#define MARIO_STATE_FLY_HIGH		840

#define MARIO_STATE_KICK		900

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 50002
#define ID_ANI_MARIO_IDLE_LEFT 50003

#define ID_ANI_MARIO_WALKING_RIGHT 50000
#define ID_ANI_MARIO_WALKING_LEFT 50001

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_BIG_FIRE_IDLE_RIGHT 1700

#define ID_ANI_MARIO_BIG_FIRE_SHOOT_BULLET_RIGHT 1720

#define ID_ANI_MARIO_BIG_FIRE_FLY_SHOOT_BULLET_RIGHT 1750
//===spin
#define ID_ANI_MARIO_BIG_TAIL_STAND_RIGHT 1900
#define ID_ANI_MARIO_BIG_TAIL_SPIN_RIGHT 1901
#define ID_ANI_MARIO_BIG_TAIL_JUMP_RIGHT 1915

#define ID_ANI_MARIO_BIG_TAIL_FLY_DOWN_RIGHT 1920

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_BIG_TAIL		3
#define	MARIO_LEVEL_BIG_ORANGE		4


#define MARIO_BIG_BBOX_WIDTH  14*3
#define MARIO_BIG_BBOX_HEIGHT 28*3
#define MARIO_BIG_SITTING_BBOX_WIDTH  14*3
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16*3

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13*3
#define MARIO_SMALL_BBOX_HEIGHT 12*3

#define MARIO_TAIL_BBOX_WIDTH  21*3
#define MARIO_TAIL_BBOX_HEIGHT 28*3


#define MARIO_UNTOUCHABLE_TIME 2500



#pragma region ANIMATION_ID_NEW
#define MARIO_ANI_BIG_IDLE_RIGHT			400
#define MARIO_ANI_SMALL_IDLE_RIGHT			401
#define MARIO_ANI_TAIL_IDLE_RIGHT			402 
#define MARIO_ANI_ORANGE_IDLE_RIGHT			403 


#define MARIO_ANI_BIG_WALKING_RIGHT			404
#define	MARIO_ANI_SMALL_WALKING_RIGHT		405
#define MARIO_ANI_TAIL_WALKING_RIGHT		406
#define MARIO_ANI_ORANGE_WALKING_RIGHT		407


#define MARIO_ANI_DIE				408

#define MARIO_ANI_BIG_JUMP_UP_RIGHT				409
#define MARIO_ANI_SMALL_JUMP_RIGHT				410
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT			411
#define MARIO_ANI_ORANGE_JUMP_UP_RIGHT			412

#define MARIO_ANI_BIG_SITDOWN_RIGT			413
#define MARIO_ANI_TAIL_SITDOWN_RIGHT		414
#define MARIO_ANI_ORANGE_SITDOWN_RIGHT		415



#define MARIO_ANI_SMALL_JUMP_DOWN_RIGHT				416
#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT				417
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT				418
#define MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT			419


#define	MARIO_ANI_SMALL_RUN_RIGHT			        420
#define	MARIO_ANI_BIG_RUN							421
#define	MARIO_ANI_TAIL_RUN_RIGHT					422
#define MARIO_ANI_ORANGE_RUN_RIGHT					423

#define  MARIO_ANI_TAIL_SPIN_TAIL_RIGHT			424


#define  MARIO_ANI_BIG_SKID				425
#define  MARIO_ANI_TAIL_SKID_LEFT		426
#define  MARIO_ANI_SMALL_SKID_LEFT		427
#define  MARIO_ANI_ORANGE_SKID_LEFT		428

#define MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT			429

#define MARIO_ANI_SMALL_FLYING								430
#define MARIO_ANI_BIG_FLYING								431
#define MARIO_ANI_TAIL_FLY_HIGH									432
#define MARIO_ANI_ORANGE_FLYING								433
#define MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT			434


#define MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT	 		435
#define MARIO_ANI_BRING_KOOMPASHELL_RIGHT				436
#define MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT			437
#define MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT		438

#define	MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT		439
#define MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT			440
#define MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT		441
#define MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT	442

#define MARIO_ANI_SMALL_STAND_HOLD  443
#define MARIO_ANI_BIG_STAND_HOLD    444
#define MARIO_ANI_TAIL_STAND_HOLD   445
#define MARIO_ANI_ORANGE_STAND_HOLD 446

#define MARIO_ANI_SMALL_GO_DOWN		447
#define MARIO_ANI_BIG_GO_DOWN		448
#define MARIO_ANI_TAIL_GO_DOWN		449
#define MARIO_ANI_ORANGE_GO_DOWN	450

#define MARIO_ANI_ORANGE_FLY_DOWN	451

#define MARIO_ANI_SMALL_IN_MAP			763
#define MARIO_ANI_BIG_IN_MAP			764
#define MARIO_ANI_TAIL_IN_MAP			765
#define MARIO_ANI_ORANGE_IN_MAP			766


#define TO_BECOME_LEFT 100
#pragma endregion

#define MARIO_BIG_TAIL_BBOX_WIDTH  21*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22*3
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 16*3

class CMario : public CGameObject
{
public:

	bool is_holding = false;

	CGameObject* holding_something = NULL;

	DWORD fly_high_start = 0;
	bool IsOnTheFlatForm() { return isOnPlatform; }
	DWORD fly_start = 0;

	DWORD spin_start = 0;
	vector<LPGAMEOBJECT> listWeapons;
	ULONGLONG throw_start = 0;

	TimerCustom* untouchtable_timer = new TimerCustom(2500);

	bool is_moving_in_world_map;

	ULONGLONG time_to_go_down =0;
	bool is_set_position = false;
	bool go_down = false;
	 
	bool is_hit_bonus = false;
	bool is_auto = false;

	int card_end_scene = 0;
	void CollideWithEnemy();

	ULONGLONG kick_start = 0;
	bool is_kick = false;

	float vy_store = 0;
	bool jump_down_to_up = false;

	int GetLevel() { return level; }
	ULONGLONG change_ani = GetTickCount64();
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithPine(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickBlink(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoompas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickCoin(LPCOLLISIONEVENT e);

	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);

	void OnCollisionWithVirtalBox(LPCOLLISIONEVENT e);

	void OnCollisionWithFlatForm(LPCOLLISIONEVENT e);

	void OnCollisionWithStoneKoompas(LPCOLLISIONEVENT e);

	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	

	
	int GetAniIdSmall();
	int GetAniIdBig();
	int GetAniIdTail();
	int GetAniIdFire();

	void attack();

	void CollideWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat);

public:
	CMario(float x, float y,bool is_in_world_map) : CGameObject(x, y)
	{
		is_moving_in_world_map = is_in_world_map;
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};