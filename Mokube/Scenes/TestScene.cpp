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

	tileMap = new TileMap;
	TileMap::tileMaxIndex = { 20,20 };
	tileMap->Init();
	tileMap->LoadFrame();

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
		tileMap->Update(tick);
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

	tileMap->ImguiRender();
}
