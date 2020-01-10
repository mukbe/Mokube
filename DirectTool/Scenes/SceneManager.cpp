#include "stdafx.h"
#include "SceneManager.h"

SingletonCpp(SceneManager)

SceneManager::SceneManager()
	:nowScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	for (size_t i = 0; i < scenes.size(); i++)
	{
		SceneBase* node = scenes.top();
		node->Release();
		SafeDelete(node);
		scenes.pop();
	}
}

void SceneManager::PreUpdate()
{
	if (nowScene != nullptr)
		nowScene->PreUpdate();
}

void SceneManager::Update(float tick)
{
	if (nowScene != nullptr)
		nowScene->Update(tick);

}

void SceneManager::PostUpdate()
{
	if (nowScene != nullptr)
		nowScene->PostUpdate();
}

void SceneManager::Render()
{
	if (nowScene != nullptr)
		nowScene->Render();
}

void SceneManager::ImguiRender()
{
	if (nowScene != nullptr)
		nowScene->ImguiRender();
}

void SceneManager::AddScene(SceneBase * node)
{
	nowScene = node;

	node->Init();
	scenes.push(node);

}

void SceneManager::PopScene()
{
	SceneBase* node = scenes.top();
	node->Release();
	SafeDelete(node);
	scenes.pop();

	nowScene = scenes.top();
}

void SceneManager::ChangeScene(SceneBase * node)
{
	SceneBase* scene = scenes.top();
	scene->Release();
	SafeDelete(scene);
	scenes.pop();

	AddScene(node);
}

SceneBase * SceneManager::GetNowScene()
{
	Log_ErrorAssert(nowScene != nullptr);
	return nowScene;
}
