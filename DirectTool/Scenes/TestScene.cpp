#include "stdafx.h"
#include "TestScene.h"

#include "./Systems/Object/ObjectManager.h"
#include "./Systems/Object/TileMap.h"

TestScene::TestScene()
	:SceneBase()
{
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{
	SceneBase::Init();

	map = new TileMap;
	TileMap::tileMaxIndex = { 20,20 };
	map->Init();
	map->LoadFrame();

}

void TestScene::Release()
{
}

void TestScene::PreUpdate()
{
	SceneBase::PreUpdate();
}

void TestScene::Update(float tick)
{
	SceneBase::Update(tick);

	if(TileMap::bLoadFrame)
		map->Update(tick);
}

void TestScene::PostUpdate()
{
	SceneBase::PostUpdate();
}

void TestScene::Render()
{
	SceneBase::Render();
}

void TestScene::PostRender()
{
	SceneBase::PostRender();
}


void TestScene::ImguiRender()
{
	SceneBase::ImguiRender();

	map->ImguiRender();
}
