#include "StateTwo.h"
#include "Knife.h"
#include "Axe.h"

StateTwo::StateTwo()
{

}

StateTwo::~StateTwo()
{

}

void StateTwo::InitState(LPDIRECT3DDEVICE9 dv, LPDIRECT3DSURFACE9 bb)
{
	tilemap = new TileMap(L"textures\\map1A.png");
	tilemap->ViewPort();
	tilemap->LoadMapCSV(NULL);
}

void StateTwo::LoadState(int AS)
{
	CGameState::LoadState(AS);

	pointdoor.clear();
	D3DXVECTOR2 pos(3164.0f, 415.0f);
	D3DXVECTOR2 pos1(3805.0f, 415.0f);
	pointdoor.push_back(pos);
	pointdoor.push_back(pos1);

	//Simon
	//simon = new CMario();
	//simon->LoadResource();
	//simon->SetPosition(50.0f, 0);
	//simon->SetState(SM_STAND_STATIC);
	//objects.push_back(simon);

	//RECT enemy
	r1.left = 125;
	r1.top = 100;
	r1.right = 1662;
	r1.bottom = 480;

	r2.left = 2045;
	r2.top = 100;
	r2.right = 2942;
	r2.bottom = 480;

	r3.left = 4222;
	r3.top = 100;
	r3.right = 5435;
	r3.bottom = 480;

	//simon->SetPosition(3325, 0);

	//set position simon undoor
	if (AS >= 0)
	{
		simon->SetPosition(pointdoor[AS].x, pointdoor[AS].y - 80);
	}

	//Box Map
	BoxMap *map1 = new BoxMap();
	map1->LoadResource();
	map1->SetPosition(pointdoor[0].x, pointdoor[0].y);
	map1->SetASDoor(AS1);
	map1->SetAniBoxMap(BOX_CHANGE_MAP2);
	objecttsStatic.push_back(map1);

	BoxMap *map2 = new BoxMap();
	map2->LoadResource();
	map2->SetPosition(pointdoor[1].x, pointdoor[1].y);
	map2->SetASDoor(AS2);
	map2->SetAniBoxMap(BOX_CHANGE_MAP2);
	objecttsStatic.push_back(map2);

	//Boss
	boss = new BossBat();
	boss->LoadResource();
	boss->SetPosition(500.0f, 150.0f);//5119.0f, 150.0f
	boss->SetState(BOSSBAT_STATIC);
	objectsEnemy.push_back(boss);
	objectsEnemy.push_back(boss->GetItem());

	//Groud
	BOXStair *box_dl = new BOXStair();
	box_dl->LoadResource();
	box_dl->SetPosition(2972.0f, 150);
	box_dl->SetState(BOX_LEFT);
	objecttsStatic.push_back(box_dl);

	BOXStair *box_dr = new BOXStair();
	box_dr->LoadResource();
	box_dr->SetPosition(3200.0f, 150);
	box_dr->SetState(BOX_RIGHT);
	objecttsStatic.push_back(box_dr);

	//Candle small H1
	for (int i = 1; i <= 4; i++)
	{
		CandleSmall *can = new CandleSmall();
		can->LoadResource();
		can->SetPosition(i * 255.0f, 280.0f);
		can->SetState(CANDLESMALL_STATE_NO);
		objects.push_back(can->GetItem());
		objecttsStatic.push_back(can);

	}

	//Candle small H2
	CandleSmall *can = new CandleSmall();
	can->LoadResource();
	can->SetPosition(345.0f, 350.0f);
	can->SetState(CANDLESMALL_STATE_NO);
	objects.push_back(can->GetItem());
	objecttsStatic.push_back(can);

	//CandleSmall *test = new CandleSmall();
	//test->LoadResource();
	//test->SetPosition(200.0f, 350.0f);
	//test->SetState(CANDLESMALL_STATE_NO);
	//objects.push_back(test->GetItem());
	//objecttsStatic.push_back(test);

	for (int i = 1; i <= 4; i++)
	{
		CandleSmall *can = new CandleSmall();
		can->LoadResource();
		can->SetPosition(i * 258.0f + 345.0f, 350.0f);
		can->SetState(CANDLESMALL_STATE_NO);
		objects.push_back(can->GetItem());
		objecttsStatic.push_back(can);

	}

	//Limit map
	CLimit *lim = new CLimit();
	lim->SetPosition(0.0f, 0.0f);
	lim->SetState(LIMIT_CAMERA);
	objects.push_back(lim);

	CLimit *lim1 = new CLimit();
	lim1->SetPosition(5600, 0.0f);
	lim->SetState(LIMIT_CAMERA);
	objects.push_back(lim1);

	//G31
	CLimit *limG3 = new CLimit();
	limG3->SetPosition(1500, 228.0f);
	limG3->SetwidthBBox(0.64f);
	limG3->SetState(LIMIT_GROUND);
	objects.push_back(limG3);

	//G21
	CLimit *limG2 = new CLimit();
	limG2->SetPosition(1373, 292.0f);
	limG2->SetwidthBBox(0.192f);
	limG2->SetState(LIMIT_GROUND);
	objects.push_back(limG2);

	//G22
	CLimit *limG22 = new CLimit();
	limG22->SetPosition(1856, 292.0f);
	limG22->SetwidthBBox(0.384f);
	limG22->SetState(LIMIT_GROUND);
	objects.push_back(limG22);

	//G32
	CLimit *limG32 = new CLimit();
	limG32->SetPosition(2780, 230.0f);
	limG32->SetwidthBBox(1.088f);
	limG32->SetState(LIMIT_GROUND);
	objects.push_back(limG32);

	//G23
	CLimit *limG23 = new CLimit();
	limG23->SetPosition(3328, 292.0f);
	limG23->SetwidthBBox(0.192f);
	limG23->SetState(LIMIT_GROUND);
	objects.push_back(limG23);

	//Ground
	CLimit *limG1 = new CLimit();
	limG1->SetwidthBBox(11.264f);//6.176f
	limG1->SetPosition(0.0f, 420.0f);
	limG1->SetState(LIMIT_GROUND);
	objects.push_back(limG1);

	//G12
	CLimit *limG12 = new CLimit();
	limG12->SetwidthBBox(1.024f);
	limG12->SetPosition(3072.0f, 420.0f);
	limG12->SetState(LIMIT_GROUND);
	objects.push_back(limG12);
	
	//Ground map3
	CLimit *limM3G21 = new CLimit();
	limM3G21->SetPosition(3583, 264.0f);
	limM3G21->SetwidthBBox(0.384f);
	limM3G21->SetState(LIMIT_GROUND);
	objects.push_back(limM3G21);

	CLimit *limM3G22 = new CLimit();
	limM3G22->SetPosition(3774, 296.0f);
	limM3G22->SetwidthBBox(0.192f);
	limM3G22->SetState(LIMIT_GROUND);
	objects.push_back(limM3G22);

	CLimit *limM3G23 = new CLimit();
	limM3G23->SetPosition(4352, 296.0f);
	limM3G23->SetwidthBBox(0.704f);
	limM3G23->SetState(LIMIT_GROUND);
	objects.push_back(limM3G23);

	CLimit *limM3G31 = new CLimit();
	limM3G31->SetPosition(3904, 232.0f);
	limM3G31->SetwidthBBox(0.832f);
	limM3G31->SetState(LIMIT_GROUND);
	objects.push_back(limM3G31);

	//Box stair
	//left - right

	//stair1
	BOXStair *box11 = new BOXStair();
	box11->LoadResource();
	box11->SetcurrentBox(1);
	box11->SetState(BOX_STAIR_BOTTOM);
	box11->SetPosition(1248, 413);
	objecttsStatic.push_back(box11);

	BOXStair *box12 = new BOXStair();
	box12->LoadResource();
	box12->SetcurrentBox(1);
	box12->SetState(BOX_STAIR_TOP);
	box12->SetPosition(1376, 195.0f);
	objecttsStatic.push_back(box12);

	//stair2
	BOXStair *box13 = new BOXStair();
	box13->LoadResource();
	box13->SetcurrentBox(1);
	box13->SetState(BOX_STAIR_BOTTOM);
	box13->SetPosition(1440, 289.0f);
	objecttsStatic.push_back(box13);

	BOXStair *box14 = new BOXStair();
	box14->LoadResource();
	box14->SetcurrentBox(1);
	box14->SetState(BOX_STAIR_TOP);
	box14->SetPosition(1505, 130.0f);
	objecttsStatic.push_back(box14);


	//stair4
	BOXStair *box15 = new BOXStair();
	box15->LoadResource();
	box15->SetcurrentBox(1);
	box15->SetState(BOX_STAIR_BOTTOM);
	box15->SetPosition(2594.0f, 413.0f);
	objecttsStatic.push_back(box15);

	BOXStair *box16 = new BOXStair();
	box16->LoadResource();
	box16->SetcurrentBox(1);
	box16->SetState(BOX_STAIR_TOP);
	box16->SetPosition(2785.0f, 132.0f);
	objecttsStatic.push_back(box16);

	//right -left

	//stair3
	BOXStair *box21 = new BOXStair();
	box21->LoadResource();
	box21->SetcurrentBox(-1);
	box21->SetState(BOX_STAIR_BOTTOM);
	box21->SetPosition(1857.0f, 285.0f);
	objecttsStatic.push_back(box21);

	BOXStair *box23 = new BOXStair();
	box23->LoadResource();
	box23->SetcurrentBox(-1);
	box23->SetState(BOX_STAIR_TOP);
	box23->SetPosition(1792, 130.0f);
	objecttsStatic.push_back(box23);

	//stair5
	BOXStair *box51 = new BOXStair();
	box51->LoadResource();
	box51->SetcurrentBox(-1);
	box51->SetState(BOX_STAIR_BOTTOM);
	box51->SetPosition(3516.0f, 414.0f);
	objecttsStatic.push_back(box51);

	BOXStair *box52 = new BOXStair();
	box52->LoadResource();
	box52->SetcurrentBox(-1);
	box52->SetState(BOX_STAIR_TOP);
	box52->SetPosition(3390.0f, 195.0f);
	objecttsStatic.push_back(box52);

	//stair6
	BOXStair *box61 = new BOXStair();
	box61->LoadResource();
	box61->SetcurrentBox(-1);
	box61->SetState(BOX_STAIR_BOTTOM);
	box61->SetPosition(3968.0f, 414.0f);
	objecttsStatic.push_back(box61);

	BOXStair *box62 = new BOXStair();
	box62->LoadResource();
	box62->SetcurrentBox(-1);
	box62->SetState(BOX_STAIR_TOP);
	box62->SetPosition(3838.0f, 198.0f);
	objecttsStatic.push_back(box62);

	//stair7
	BOXStair *box71 = new BOXStair();
	box71->LoadResource();
	box71->SetcurrentBox(-1);
	box71->SetState(BOX_STAIR_BOTTOM);
	box71->SetPosition(4351.0f, 285.0f);
	objecttsStatic.push_back(box71);

	BOXStair *box72 = new BOXStair();
	box72->LoadResource();
	box72->SetcurrentBox(-1);
	box72->SetState(BOX_STAIR_TOP);
	box72->SetPosition(4286, 134.0f);
	objecttsStatic.push_back(box72);

	//stair8
	BOXStair *box81 = new BOXStair();
	box81->LoadResource();
	box81->SetcurrentBox(-1);
	box81->SetState(BOX_STAIR_BOTTOM);
	box81->SetPosition(4797.0f, 414.0f);
	objecttsStatic.push_back(box81);

	BOXStair *box82 = new BOXStair();
	box82->LoadResource();
	box82->SetcurrentBox(-1);
	box82->SetState(BOX_STAIR_TOP);
	box82->SetPosition(4669.0f, 198.0f);
	objecttsStatic.push_back(box82);

	//Zombie R3
	Zombie *zom8 = new Zombie();
	zom8->SetPosition(r3.right - 100, 345.0f);
	zom8->LoadResource();
	zom8->SetSpeed(0.05f, 1.0f);
	zom8->SetState(ZOMBIE_MOVE_LEFT);
	zom8->SetRectLim(r3);
	objectsEnemy.push_back(zom8);

	Zombie *zom9 = new Zombie();
	zom9->SetPosition(r3.right - 150, 345.0f);
	zom9->LoadResource();
	zom9->SetSpeed(0.05f, 1.0f);
	zom9->SetState(ZOMBIE_MOVE_LEFT);
	zom9->SetRectLim(r3);
	objectsEnemy.push_back(zom9);

	Zombie *zom10 = new Zombie();
	zom10->SetPosition(r3.right - 300, 345.0f);
	zom10->LoadResource();
	zom10->SetSpeed(0.05f, 1.0f);
	zom10->SetState(ZOMBIE_MOVE_LEFT);
	zom10->SetRectLim(r3);
	objectsEnemy.push_back(zom10);

	//Zombie R2
	Zombie *zom5 = new Zombie();
	zom5->SetPosition(r2.right - 100, 345.0f);
	zom5->LoadResource();
	zom5->SetSpeed(0.05f, 1.0f);
	zom5->SetState(ZOMBIE_MOVE_LEFT);
	zom5->SetRectLim(r2);
	objectsEnemy.push_back(zom5);

	Zombie *zom6 = new Zombie();
	zom6->SetPosition(r2.right - 150, 345.0f);
	zom6->LoadResource();
	zom6->SetSpeed(0.05f, 1.0f);
	zom6->SetState(ZOMBIE_MOVE_LEFT);
	zom6->SetRectLim(r2);
	objectsEnemy.push_back(zom6);

	Zombie *zom7 = new Zombie();
	zom7->SetPosition(r2.right - 300, 345.0f);
	zom7->LoadResource();
	zom7->SetSpeed(0.05f, 1.0f);
	zom7->SetState(ZOMBIE_MOVE_LEFT);
	zom7->SetRectLim(r2);
	objectsEnemy.push_back(zom7);

	//Zombie R1
	Zombie *zom1 = new Zombie();
	zom1->SetPosition(r1.right - 50, 345.0f);
	zom1->LoadResource();
	zom1->SetSpeed(0.05f, 1.0f);
	zom1->SetState(ZOMBIE_MOVE_LEFT);
	zom1->SetRectLim(r1);
	objects.push_back(zom1->GetItem());
	objectsEnemy.push_back(zom1);

	Zombie *zom3 = new Zombie();
	zom3->SetPosition(r1.right - 80, 345.0f);
	zom3->LoadResource();
	zom3->SetSpeed(0.05f, 1.0f);
	zom3->SetState(ZOMBIE_MOVE_LEFT);
	zom3->SetRectLim(r1);
	objects.push_back(zom3->GetItem());
	objectsEnemy.push_back(zom3);

	Zombie *zom2 = new Zombie();
	zom2->SetPosition(r1.right - 150, 345.0f);
	zom2->LoadResource();
	zom2->SetSpeed(0.05f, 1.0f);
	zom2->SetState(ZOMBIE_MOVE_LEFT);
	zom2->SetRectLim(r1);
	objects.push_back(zom2->GetItem());
	objectsEnemy.push_back(zom2);

	//Panther
	Panther *pan1 = new Panther();
	pan1->LoadResource();
	pan1->SetPosition(1390, 100);//1390
	pan1->SetNX(-1);
	pan1->SetState(PANTHER_STATIC);
	objects.push_back(pan1->GetItem());
	objectsEnemy.push_back(pan1);

	Panther *pan2 = new Panther();
	pan2->LoadResource();
	pan2->SetPosition(1760, 100);
	pan2->SetNX(-1);
	pan2->SetState(PANTHER_STATIC);
	objectsEnemy.push_back(pan2);

	//Bat red
	BatRed *bat1 = new BatRed();
	bat1->LoadResource();
	bat1->SetPosition(3609.0f, 190.0f);//3609.0f, 190.0f
	bat1->SetNX(-1);
	bat1->SetState(BAT_RED_STATIC);
	objectsEnemy.push_back(bat1);
}

void StateTwo::UpdateState(DWORD dt)
{
	boss->UpdatePosSimon(simon->x, simon->y);
	CGameState::UpdateState(dt);
}

void StateTwo::RenderState(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 bb, LPD3DXSPRITE spriteHandler)
{
	//Update viewport
	tilemap->UpdateScrollPosition();
	CGameState::RenderState(d3ddv, bb, spriteHandler);
}