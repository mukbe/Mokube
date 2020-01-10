#pragma once



class Tile : public GameObject
{
public:
	enum Attribute : int
	{
		Move = 0,
		Slow = 1 << 0,
		Damge = 1 << 1

	};

	Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~Tile();

	void Init(int tileIndexX, int tileIndexY);
	void SetTexture(string key);
	virtual void Init();
	virtual void Release();

	virtual void PreUpdate();
	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render(bool isRelative = true);
	virtual void PostRender() {}
	virtual void ImguiRender() {}

	void AddCallBackFunc();
	POINT GetTileIndex() { return tileIndex; }

private:
	POINT tileIndex;
	shared_ptr<Texture> tileMapImage;
	int attribute;
	bool bPicked;
	bool bOnMouse;
	FloatRect pickedRect;
	void SetAttribute(int val);


};

