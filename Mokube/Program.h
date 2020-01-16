#pragma once


class TestScene;
class Program
{
	using VertexType = VertexTexture;
public:
	Program();
	~Program();

	void PreUpdate();
	void Update(float tick);
	void PostUpdate();

	void Render();

	void PostRender();
	void ImguiRender();

	void ResizeScreen();

	void GameUIRender();


	void Print(char str[], ...);

private:


};