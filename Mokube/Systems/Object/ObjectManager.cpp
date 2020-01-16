#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	mapObjects.clear();
	vector<class GameObject*> arrTemp;
	arrTemp.clear();
}


ObjectManager::~ObjectManager()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;

		for (size_t t = 0; t < arrTemp.size();t++)
		{
			SafeDelete(arrTemp[t]);

		}
		arrTemp.clear();
	}

}

void ObjectManager::Init()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->Init();
		}
	}
}

void ObjectManager::PreUpdate()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->PreUpdate();
		}
	}
}

void ObjectManager::Update(float tick)
{

	//if (Math::IsAABBInAABB(objs[0]->Transform()->GetRect(), objs[1]->Transform()->GetRect()))
	//{
	//	objs[1]->SendCallbackMessage("Enter");
	//}
	//else
	//{
	//	objs[1]->SendCallbackMessage("Exit");

	//}
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->Update(tick);
		}	
	}

}

void ObjectManager::PostUpdate()
{
	MapIter mapIter = mapObjects.begin();
		
	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->PostUpdate();
		}
	}
}

void ObjectManager::Render()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->Render();
		}
	}
}

void ObjectManager::PostRender()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->PostRender();
		}
	}
}

void ObjectManager::ImguiRender()
{
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end(); ++mapIter)
	{
		vector<class GameObject*>  arrTemp = mapIter->second;
		ArrIter arrIter = arrTemp.begin();

		for (; arrIter != arrTemp.end(); ++arrIter)
		{
			(*arrIter)->ImguiRender();
		}
	}
}


//mapObjects에서 ObjectType에 맞는 arrObjects를 찾아서 매개변숙로 들어온 GameObject*를 넣어줌
void ObjectManager::AddObject(GameObject * inputObject)
{
	ObjectType tempType = inputObject->GetObjectType();
	mapObjects[tempType].emplace_back(inputObject);
}

void ObjectManager::DeleteObjects(ObjectType type)
{

	vector<GameObject*> vec = mapObjects[type];
	for (int i = 0; i < vec.size(); i++)
	{
		SafeDelete(vec[i]);
	}
	MapIter mapIter = mapObjects.begin();

	for (; mapIter != mapObjects.end();)
	{
		if (mapIter->first == type)
		{
			mapIter = mapObjects.erase(mapIter);
		}
		else
			mapIter++;
	}


}

//name 키 값이 중복되는지 검사함.
bool ObjectManager::isValidCreate(string name, ObjectType type)
{
	vector<GameObject*>* tempArr;
	tempArr = &(mapObjects[type]);

	ArrIter arrIter = tempArr->begin(), arrEnd = tempArr->end();

	for (; arrIter != arrEnd; ++arrIter) {
		if ((*arrIter)->Name() == name) {
			return false;
		}
	}
	return true;
}


GameObject * ObjectManager::FindObjectByName(ObjectType type, string inputName)
{
	vector<class GameObject*>* arrTemp = &(mapObjects[type]);
	ArrIter arrIter = arrTemp->begin(), arrEnd = arrTemp->end();
	for (; arrIter != arrEnd;)
	{
		string tempName = (*arrIter)->Name();

		if (inputName == tempName)
		{
			return (*arrIter);
		}
	}
	return (*arrIter);
}

GameObject * ObjectManager::FindObjectByName(string inputName)
{
	
	MapIter Iter = mapObjects.begin();
	for (; Iter != mapObjects.end(); ++Iter)
	{
		vector<GameObject*>  arrTemp = Iter->second;	
		for (size_t t = 0; t < arrTemp.size() ; t++)
		{
			if (inputName == arrTemp[t]->Name())
			{
				return arrTemp[t];
			}
		}
	}

	LOG->Print("No Exist Object");
	return nullptr;
	
}

//입력받은 type과 같은 GameObject*가 들어있는 arrObjects를 반환해줌
vector<GameObject*>* ObjectManager::FindObjectsArrByType(ObjectType type)
{
	vector<GameObject*>* tempArrAdress;
	tempArrAdress = &(mapObjects[type]);
	return tempArrAdress;
}
