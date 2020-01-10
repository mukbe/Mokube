#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
public:
	GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~GameObject();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//ī�޶� ���� ���ʾ�����Ʈ - ��� ���صε�
	virtual void PreUpdate();
	//���� ��ƾ
	virtual void Update(float tick);
	//�̵����� ���
	virtual void PostUpdate();

	//�̹��� ������ - direct2D
	virtual void Render(bool isRelative = true);
	//��ó�� ������ -direct3D
	virtual void PostRender();
	//imgui debugUI render
	virtual void ImguiRender() {}



	const string& Name() { return name; }
	void SetName(const string& s) { name = s; }

	void SetObjectType(ObjectType t) { objectType = t; }
	ObjectType GetObjectType() { return objectType; }

	Matrix2D* Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	void SetSize(const D3DXVECTOR2& s) 
	{
		//�����ؾߵ�
		size = s;
	}
	const D3DXVECTOR2& GetSize() { return size; }


	int GetDir() { return 1; }






protected:
	string name;
	ObjectType objectType;
	Matrix2D* transform;
	D3DXVECTOR2 size;
	bool bActive;

	float alpha;
	float lifeTiem;
	float frameTime;

	



	//������ ���̾�
	//�浹��Ʈor��
	//������ ���� - �ұ�? ���� �ٸ������� �ѹ��� �ұ�?

	UINT frameX;
	UINT frameY;
	float frequency;


private:
	WorldBuffer * worldBuffer;
	Shader* shader;
};
