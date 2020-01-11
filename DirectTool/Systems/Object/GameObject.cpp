#include "stdafx.h"
#include "GameObject.h"
#include "./Utilities/Matrix2D.h"

GameObject::GameObject(string name)
	: name(name), bActive(true), worldBuffer(nullptr), shader(nullptr), transform(nullptr)
	, alpha(1.f), lifeTiem(0.f), frameTime(0.f)

{
}

GameObject::GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type ,Pivot p)
	: name(name), bActive(true), worldBuffer(nullptr), shader(nullptr), transform(nullptr)
	, alpha(1.f), size(size),  lifeTiem(0.f), frameTime(0.f), objectType(type)
{
	//worldBuffer = new WorldBuffer;
	//shader = new Shader(L"./Shaders/Color.hlsl");
	shader = Shaders->CreateShader("Color", L"Color.hlsl");
	transform = new Matrix2D(pos, size, p);

	bActive = true;

	frameX = frameY = 0;

	frequency = 0.07f;
}


GameObject::~GameObject()
{
	Release();
	SafeDelete(transform);
	SafeDelete(worldBuffer);
}

void GameObject::Init()
{
	
}

void GameObject::Release()
{
}

void GameObject::PreUpdate()
{

}

void GameObject::Update(float tick)
{

	if (Keyboard::Get()->Down(VK_F5))
		bActive = !bActive;

	if (bActive == false) return;


	lifeTiem += tick;
	frameTime += tick;

	////�ִϸ��̼����� �ٲ�ߵ�
	//if (sprites.size() != 0)
	//{
	//	if (frameTime >= frequency)
	//	{
	//		frameX++;
	//		frameTime -= frequency;
	//		if (frameX >= sprites[state]->GetMaxFrame().x)
	//		{
	//			frameY++;
	//			frameX = 0;


	//			if (frameY >= sprites[state]->GetMaxFrame().y)
	//			{
	//				frameY = 0;
	//			}
	//		}
	//	}

	//}

}

void GameObject::PostUpdate()
{
}

//����� ����� �ϸ� TRUE
void GameObject::Render(bool isRelative)
{
	if (bActive == false)return;

	Matrix2D world = *transform;

	if (isRelative)
	{
		world = world * CAMERA->GetView();
	}

	world.Bind();

	transform->Render();

	
}

void GameObject::PostRender()
{

	CAMERA->CameraDataBind();
	worldBuffer->Setting(transform->GetResult());
	worldBuffer->SetPSBuffer(1);
	shader->Render();

	UINT stride = sizeof(VertexColor);
	UINT offset = 0;

	DeviceContext->IASetInputLayout(nullptr);
	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	pRenderer->TurnOnAlphaBlend();
	DeviceContext->Draw(4, 0);
	pRenderer->TurnOffAlphaBlend();

}
