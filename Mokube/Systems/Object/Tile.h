#pragma once



class Tile : public GameObject
{
public:
	template<size_t N>
	struct Bit
	{
		static constexpr int Value = 31 < N ? 0 : 1 << N;
	};


	enum TileBitAttribute : int
	{
		Immovable = Bit<1>::Value,
		
	};


	Tile(string name = "Tile");
	Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~Tile();

	void CopyTile(Tile* other);


	void InitFrame(int frameX, int frameY);
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
	int GetAttribute() { return attribute; }
	void SetAttribute(int val);
	void SetIndex(POINT pt) { tileIndex = pt; }
	void SetIndex(int x, int y) { tileIndex = { x,y }; }
	void SetFrameIndex(int x, int y)
	{
		frameX = x;
		frameY = y;
	}
private:
	POINT tileIndex;
	shared_ptr<Texture> tileMapImage;
	int attribute;
	bool bPicked;
	bool bOnMouse;
	FloatRect pickedRect;


};

