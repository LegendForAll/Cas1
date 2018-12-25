#include "StateTwo.h"
#include "Knife.h"
#include "Axe.h"
#include "tinyxml.h"

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

	//UI
	uigame = new UI();
	uigame->LoadResource();
	uigame->SetPosition(0.0f, 20.0f);
	objects.push_back(uigame);

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

	//------------------------------------------------------
	//init XML
	TiXmlDocument doc("ResourceXML\\map1A.xml");
	if (!doc.LoadFile())
	{
		printf("%s", doc.ErrorDesc());
	}
	int id;
	int id_obj;
	int posX, posY;

	//load XML ground
	TiXmlElement* rootG = doc.RootElement();
	TiXmlElement* ground = nullptr;
	float multiplier;
	ground = rootG->FirstChildElement("ground");
	for (TiXmlElement* obj = ground->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);
		obj->QueryFloatAttribute("multiplier", &multiplier);

		//init ground
		CLimit *limG = new CLimit();
		limG->SetwidthBBox(multiplier);
		limG->SetPosition(posX, posY);
		limG->SetState(LIMIT_GROUND);
		objects.push_back(limG);
	}

	//load XML limit
	TiXmlElement* rootlim = doc.RootElement();
	TiXmlElement* limit = nullptr;
	limit = rootlim->FirstChildElement("limit");
	for (TiXmlElement* obj = limit->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);

		//init limit
		CLimit *lim = new CLimit();
		lim->SetPosition(posX, posY);
		lim->SetState(LIMIT_CAMERA);
		//objects.push_back(lim);
	}

	//load XML candle
	TiXmlElement* rootcan = doc.RootElement();
	TiXmlElement* candle = nullptr;
	candle = rootcan->FirstChildElement("candlemi");
	for (TiXmlElement* obj = candle->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);

		//init candle
		CandleSmall *can = new CandleSmall();
		can->LoadResource();
		can->SetPosition(posX, posY);
		can->SetState(CANDLESMALL_STATE_NO);
		objects.push_back(can->GetItem());
		objecttsStatic.push_back(can);
	}

	//load XML boss
	TiXmlElement* rootbos = doc.RootElement();
	TiXmlElement* bos = nullptr;
	bos = rootbos->FirstChildElement("boss");
	for (TiXmlElement* obj = bos->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);

		//init boss
		boss = new BossBat();
		boss->LoadResource();
		boss->SetPosition(posX, posY);
		boss->SetState(BOSSBAT_STATIC);
		objectsEnemy.push_back(boss);
		objectsEnemy.push_back(boss->GetItem());
	}

	//load XML panther
	TiXmlElement* rootpan = doc.RootElement();
	TiXmlElement* panther = nullptr;
	panther = rootpan->FirstChildElement("panther");
	for (TiXmlElement* obj = panther->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);

		//init panther
		Panther *pan1 = new Panther();
		pan1->LoadResource();
		pan1->SetPosition(posX, posY);
		pan1->SetNX(-1);
		pan1->SetState(PANTHER_STATIC);
		objects.push_back(pan1->GetItem());
		objectsEnemy.push_back(pan1);
	}

	//load XML bat red
	TiXmlElement* rootbat = doc.RootElement();
	TiXmlElement* bat = nullptr;
	bat = rootbat->FirstChildElement("batmi");
	for (TiXmlElement* obj = bat->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);

		//init bat red
		BatRed *bat1 = new BatRed();
		bat1->LoadResource();
		bat1->SetPosition(posX, posY);
		bat1->SetNX(-1);
		bat1->SetState(BAT_RED_STATIC);
		objectsEnemy.push_back(bat1);
	}

	//load XML stair
	TiXmlElement* rootstair = doc.RootElement();
	TiXmlElement* stair = nullptr;
	int isLeft, boxState;
	stair = rootstair->FirstChildElement("boxstair");
	for (TiXmlElement* obj = stair->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement())
	{
		obj->QueryIntAttribute("id", &id_obj);
		obj->QueryIntAttribute("x", &posX);
		obj->QueryIntAttribute("y", &posY);
		obj->QueryIntAttribute("left", &isLeft);
		obj->QueryIntAttribute("state", &boxState);

		//init boss
		BOXStair *box11 = new BOXStair();
		box11->LoadResource();
		box11->SetcurrentBox(isLeft);
		box11->SetState(boxState);
		box11->SetPosition(posX, posY);
		objecttsStatic.push_back(box11);
	}
	//------------------------------------------------------

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

}

void StateTwo::UpdateState(DWORD dt)
{
	boss->UpdatePosSimon(simon->x, simon->y);
	CGameState::UpdateState(dt);
	this->uigame->UpdateItem(simon);
}

void StateTwo::RenderState(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 bb, LPD3DXSPRITE spriteHandler)
{
	//Update viewport
	tilemap->UpdateScrollPosition();
	CGameState::RenderState(d3ddv, bb, spriteHandler);
}