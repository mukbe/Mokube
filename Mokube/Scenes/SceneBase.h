#pragma once
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init();
	virtual void Release();
	
	virtual void PreUpdate();
	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void PostRender();
	virtual void ImguiRender();


	class MessageManager* GetMessagePool() { return messageManager; }
	class ObjectManager* GetObjectPool() { return objectManager; }
	class TileMap* GetTileMap() { return tileMap; }
	class PathFinder* GetPathFinder() { return pathFinder; }


protected:
	class ObjectManager* objectManager;
	class MessageManager* messageManager;
	class TileMap* tileMap;
	class PathFinder* pathFinder;

};

