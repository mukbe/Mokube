#pragma once
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void PreUpdate();
	void Update(float tick);
	void PostUpdate();

	void Render();

	void PostRender();
	void ImguiRender();


	//template <typename T>
	//GameObject* CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	GameObject* FindObjectByName(ObjectType type, string inputName);
	GameObject* FindObjectByName(string inputName);
	vector<GameObject*>* FindObjectsArrByType(ObjectType type);
	//¾² Áö ¸¶ 
	void AddObject(class GameObject* inputObject);
	void DeleteObjects(ObjectType type);

private:
	bool isValidCreate(string name, ObjectType type);

	typedef vector<class GameObject*>::iterator ArrIter;
	typedef unordered_map<ObjectType, vector<class GameObject*>>::iterator MapIter;

	unordered_map<ObjectType, vector<class GameObject*>> mapObjects;
};

