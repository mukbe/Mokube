#include "stdafx.h"
#include "AStarScene.h"
#include "./Systems/Object/Player.h"
#include "./Systems/Object/TileMap.h"
#include "./Systems/Object/ObjectManager.h"
#include "./Systems/Object/Tank.h"
#include "./Scenes/TurnControl.h"

AStarScene::AStarScene()
{
}


AStarScene::~AStarScene()
{
	SafeDelete(control);
	SafeDelete(tileMap);
}

void AStarScene::Init()
{
	control = new TurnControl;

	TileMap::tileMaxIndex = { 20,20 };
	tileMap = new TileMap;
	tileMap->Init(ResourcePath + L"Test.json");

	_ImageManager->AddFrameTexture("Player", ResourcePath + L"player_idle.png", 4, 1);
	_ImageManager->AddFrameTexture("Unit", ResourcePath + L"monster04_idle.png", 4, 6);

	D3DXVECTOR2 pos = tileMap->GetTilePos({ 0,0 }) + TileMap::tileSize * 0.5f;
	player = new Player("Player", pos, D3DXVECTOR2(32, 32), ObjectType::Character);
	_ObjectPool->AddObject(player);

	pos = tileMap->GetTilePos({ 18,18 }) + TileMap::tileSize * 0.5f;
	Tank* tank = new Tank("Tank", pos, D3DXVECTOR2(32, 32), ObjectType::Monster);
	_ObjectPool->AddObject(tank);


	control->Register(player);
	control->Register(tank);
}

void AStarScene::Update(float tick)
{
	SceneBase::Update(tick);


	control->Update(tick);
}
