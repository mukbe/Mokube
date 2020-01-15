#pragma once
#include "./Utilities/BinaryFile.h"


class Tile;
class TileMap
{
private:
	//디폴트로 생성할 타일 이미지의 프레임 수 
	const POINT DefaultTileImageFrame = { 2,2 };

public:
	static POINT tileMaxIndex;
	static D3DXVECTOR2 tileSize;
	static bool bLoadFrame;

public:
	TileMap();
	~TileMap();

	void Init(wstring file = L"");
	void Update(float tick);
	void ImguiRender();

	void LoadStage();
	void LoadFrame(string key = "");

	vector< Tile*> GetTiles() { return tiles; }
	D3DXVECTOR2 GetTilePos(POINT index); 
	Tile* GetTile(POINT pt);
	Tile* GetTile(int x, int y);

	Tile* GetTile(D3DXVECTOR2 pos);
private:
	void Save(wstring file);
	void Load(wstring file = L"");

	static bool bImmovable;


	vector<Tile*> tiles;
	vector<Tile*> pickedTiles;

	POINT currentIndex;
	POINT oldIndex;




	POINT frameMaxIndex;
	D3DXVECTOR2 frameSize;
	D3DXVECTOR2 frameStart;
	POINT currentFrameIndex;
	POINT oldFrameIndex;
	POINT pickIndex;

	vector<Tile*> frames;
	vector<Tile*> pickedframes;

	unique_ptr<class Json::Value> jsonRoot;
	shared_ptr<Texture> frameTexture;
	string frameTextureKey;

};

