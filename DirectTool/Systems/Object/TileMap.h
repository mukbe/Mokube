#pragma once
#include "./Utilities/BinaryFile.h"


class TileMap
{
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
	
private:
	void Save(wstring file);
	void Load(wstring file = L"");
	void ChangeFrameImage(wstring file);

	//POINT tileMaxIndex;
	//D3DXVECTOR2 tileSize;

	vector<class Tile*> tiles;
	vector<class Tile*> pickedTiles;

	POINT currentIndex;
	POINT oldIndex;




	POINT frameMaxIndex;
	D3DXVECTOR2 frameSize;
	D3DXVECTOR2 frameStart;
	POINT currentFrameIndex;
	POINT oldFrameIndex;
	POINT pickIndex;

	vector<class Tile*> frames;
	vector<class Tile*> pickedframes;

	unique_ptr<class Json::Value> jsonRoot;
	shared_ptr<Texture> frameTexture;
	string frameTextureKey;

private:
	//디폴트로 생성할 타일 이미지의 프레임 수 
	const POINT DefaultTileImageFrame = { 16,9 };
};

