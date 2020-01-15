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

	void TestFunc();

private:
	Shader* testShader;


	class UIBuffer : public ShaderBuffer
	{
	private:
		struct Struct
		{

			D3DXVECTOR2 Pos;
			D3DXVECTOR2 Size;
			D3DXVECTOR4 TEST;
		}data;

	public:
		UIBuffer()
			:ShaderBuffer(&data, sizeof Struct)
		{}

		void Setting()
		{
			data.Size = D3DXVECTOR2(300, 300);
			data.Pos = D3DXVECTOR2((- data.Size.x), (data.Size.y)) * 0.5f;
			data.TEST = D3DXVECTOR4(-1, 1, 0, 0);
		}
	};

	unique_ptr<UIBuffer> buffer;

};