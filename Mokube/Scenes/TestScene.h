#pragma once
#include "./Scenes/SceneBase.h"


class TileMap;
class TestScene : public SceneBase
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init();
	virtual void Release();

	virtual void PreUpdate();
	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void PostRender();
	virtual void ImguiRender();

private:
};

