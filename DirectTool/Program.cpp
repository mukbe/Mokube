#include "stdafx.h"
#include "Program.h"

#include "./Scenes/TestScene.h"

Program::Program()
{
	//������������ json or sql
	//jsonRoot = new Json::Value();
	//JsonHelper::ReadData(L"LevelEditor.json", jsonRoot);

	SceneBase* scene = new TestScene;
	_SceneManager->AddScene(scene);


	//IMGUI FONT SETUP
	//�ؽ�Ʈ�� �� ���ڶ�� �ѱ��� �� ��� Imgui::Text(u8"�׽�Ʈ TEST"); 
	//�ؽ�Ʈ �տ� u8�� ���־���� �����ڵ� ���
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("..//_Resources//TTF//Maplestory Light.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
	}


}

Program::~Program()
{
}

void Program::PreUpdate()
{
	_GameWorld->PreUpdate();
}

void Program::Update(float tick)
{
	_GameWorld->Update(tick);
}

void Program::PostUpdate()
{
	_GameWorld->PostUpdate();
}

void Program::Render()
{
	_GameWorld->Render();





	CAMERA->GetView().Bind();
	p2DRenderer->DrawLine(D3DXVECTOR2(-10000, 0), D3DXVECTOR2(10000, 0));
	p2DRenderer->DrawLine(D3DXVECTOR2(0, -10000), D3DXVECTOR2(0, 10000));

	wstring str;
	str += L"pos.x : " + to_wstring(CAMERA->GetMousePos().x).substr(0, 6);
	str += L"pos.y : " + to_wstring(CAMERA->GetMousePos().y).substr(0, 6);
	p2DRenderer->DrawText2D(Mouse::Get()->GetPosition().x - 200, Mouse::Get()->GetPosition().y - 20, str, 20);
}

void Program::PostRender()
{
	_GameWorld->PostRender();
}

void Program::ImguiRender()
{
	static bool bLockFPS = true;
	static int fps = Time::Get()->GetLockFPS();
	ImGui::Begin("Info");
	{
		ImGui::Text("FPS : %f", Time::Get()->FPS()); ImGui::SameLine();

		if (ImGui::Checkbox("FPS Lock", &bLockFPS) || ImGui::InputInt("FPS Value", &fps))
		{
			if (bLockFPS)
				Time::Get()->SetLockFPS(fps);
			else
				Time::Get()->SetLockFPS(0.f);
		}
		ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", CAMERA->GetPos().x, CAMERA->GetPos().y);
	}
	ImGui::End();


	_GameWorld->ImguiRender();

}

void Program::ResizeScreen()
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
}
