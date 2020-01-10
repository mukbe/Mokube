#pragma once

class SceneManager
{
	SingletonHeader(SceneManager)
public:

	void Release();
	void PreUpdate();
	void Update(float tick);
	void PostUpdate();
	void Render();
	void ImguiRender();


	void AddScene(SceneBase* node);
	void PopScene();
	void ChangeScene(SceneBase* node);
	SceneBase* GetNowScene() ;
private:
	stack<SceneBase*> scenes;

	SceneBase* nowScene;
};

#define _SceneManager SceneManager::Get()
#define _GameWorld SceneManager::Get()->GetNowScene()
#define _MessagePool SceneManager::Get()->GetNowScene()->GetMessagePool()
#define _ObjectPool SceneManager::Get()->GetNowScene()->GetObjectPool()