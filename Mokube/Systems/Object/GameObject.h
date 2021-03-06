#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
	using VertexType = VertexColor;
public:
	GameObject(string name = "None");
	GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~GameObject();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//카메라에 관한 최초업데이트 - 사용 안해두됨
	virtual void PreUpdate();
	//메인 루틴
	virtual void Update(float tick);
	//이동관련 계산
	virtual void PostUpdate();

	//이미지 렌더링 - direct2D
	virtual void Render(bool isRelative = true);
	//후처리 렌더링 -direct3D
	virtual void PostRender();
	//imgui debugUI render
	virtual void ImguiRender() {}



	const string& Name() { return name; }
	void SetName(const string& s) { name = s; }

	void SetObjectType(ObjectType t) { objectType = t; }
	ObjectType GetObjectType() { return objectType; }

	Matrix2D& Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	void SetSize(const D3DXVECTOR2& s) 
	{
		//수정해야됨
		size = s;
	}
	const D3DXVECTOR2& GetSize() { return size; }


	virtual UINT GetFrameX() { return frameX;}
	virtual UINT GetFrameY() { return frameY; }





protected:
	string name;
	ObjectType objectType;
	Matrix2D transform;
	D3DXVECTOR2 size;
	bool bActive;

	float alpha;
	float lifeTiem;
	float frameTime;

	



	//렌더링 레이어
	//충돌렉트or원
	//데이터 저장 - 할까? 말고 다른곳에서 한번에 할까?

	UINT frameX;
	UINT frameY;
	float frequency;


private:
	string shaderKey;
	WorldBuffer* worldBuffer;

};

