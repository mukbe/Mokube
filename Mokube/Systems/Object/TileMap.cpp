#include "stdafx.h"
#include "TileMap.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "./Systems/Message/MessageManager.h"


POINT TileMap::tileMaxIndex;
D3DXVECTOR2 TileMap::tileSize = { 32.f,32.f };
bool TileMap::bLoadFrame = false;
bool TileMap::bImmovable = false;
TileMap::TileMap()
{
	jsonRoot = make_unique<Json::Value>();
}


TileMap::~TileMap()
{

}
//json파일 path를 넣어주라고
void TileMap::Init(wstring file)
{
	if (file.size() == 0)
	{
		wstring path = ResourcePath + L"DefaultTileMap.png";
		frameTextureKey = String::WStringToString(Path::GetFileNameWithoutExtension(path));
		if (_ImageManager->AddFrameTexture(frameTextureKey, path, DefaultTileImageFrame.x, DefaultTileImageFrame.y))
			frameTexture = _ImageManager->FindTexture(frameTextureKey);

		LoadStage();
	}
	else
	{
		Load(file);
	}

}

void TileMap::Update(float tick)
{
	D3DXVECTOR2 pos = CAMERA->GetMousePos();
	FloatRect mapRect, frameRect;
	mapRect = FloatRect(D3DXVECTOR2(0, 0), tileSize.x * tileMaxIndex.x, Pivot::LEFT_TOP);
	frameRect = FloatRect(frameStart, frameSize.x * frameMaxIndex.x, frameSize.y * frameMaxIndex.y, Pivot::LEFT_TOP);
	
	if (Math::IsPointInAABB(mapRect, pos))
	{
		pos.x = Math::Clamp(pos.x, 0, tileSize.x * tileMaxIndex.x);
		pos.y = Math::Clamp(pos.y, 0, tileSize.y * tileMaxIndex.y);
		currentIndex.x = (LONG)(pos.x / tileSize.x);
		currentIndex.y = (LONG)(pos.y / tileSize.y);

		currentIndex.x = Math::Clamp(currentIndex.x, 0, tileMaxIndex.x - 1);
		currentIndex.y = Math::Clamp(currentIndex.y, 0, tileMaxIndex.y - 1);

		if (currentIndex.x == oldIndex.x && currentIndex.y == oldIndex.y)
		{

		}
		else
		{
			tiles[tileMaxIndex.x * oldIndex.y + oldIndex.x]->SendCallbackMessage("OutMouse");
			tiles[tileMaxIndex.x * currentIndex.y + currentIndex.x]->SendCallbackMessage("InMouse");
			oldIndex = currentIndex;
		}

		if (Mouse::Get()->Press(1))
		{
			POINT index = tiles[tileMaxIndex.x * currentIndex.y + currentIndex.x]->GetTileIndex();
			if (pickedframes.size() != 0)
			{
				POINT frameIndex = {pickedframes[0]->GetFrameX(), pickedframes[0]->GetFrameY()};
				if (index.x != frameIndex.x || index.y != frameIndex.y)
				{
					_GameWorld->GetMessagePool()->ReserveMessage(tiles[tileMaxIndex.x * currentIndex.y + currentIndex.x], "SetFrameIndex", 0, frameIndex);
					_MessagePool->ReserveMessage(tiles[tileMaxIndex.x * currentIndex.y + currentIndex.x], "SetTileAttribute", 0, (int)Tile::TileBitAttribute::Immovable);
				}
			}
		}
	}
	

	if (Math::IsPointInAABB(frameRect, pos))
	{
		currentFrameIndex.x = (LONG)((pos.x - frameStart.x) / frameSize.x);
		currentFrameIndex.y = (LONG)((pos.y - frameStart.y) / frameSize.y);


		currentFrameIndex.x = Math::Clamp(currentFrameIndex.x, 0, frameMaxIndex.x - 1);
		currentFrameIndex.y = Math::Clamp(currentFrameIndex.y, 0, frameMaxIndex.y - 1);

		if (currentFrameIndex.x == oldFrameIndex.x && currentFrameIndex.y == oldFrameIndex.y)
		{

		}
		else
		{
			frames[frameMaxIndex.x * oldFrameIndex.y + oldFrameIndex.x]->SendCallbackMessage("OutMouse");
			frames[frameMaxIndex.x * currentFrameIndex.y + currentFrameIndex.x]->SendCallbackMessage("InMouse");
			oldFrameIndex = currentFrameIndex;
		}



		if (Mouse::Get()->Down(0))
		{
			for (int i = 0;i < pickedframes.size(); i++)
			{
				pickedframes[i]->SendCallbackMessage("Drop");

			}
			pickedframes.clear();

			pickedframes.push_back(frames[frameMaxIndex.x * currentFrameIndex.y + currentFrameIndex.x]);
			pickedframes[0]->SendCallbackMessage("Pick");

			pickIndex = currentFrameIndex;
		}

	}

}

void TileMap::ImguiRender()
{
	ImGui::Begin(u8"타일맵");
	{

		ImVec2 uv0, uv1;
		uv0.x = (float)currentFrameIndex.x / (float)frameMaxIndex.x;
		uv0.y = (float)currentFrameIndex.y / (float)frameMaxIndex.y;
		uv1.x = (float)(currentFrameIndex.x+1) / (float)frameMaxIndex.x;
		uv1.y = (float)(currentFrameIndex.y+1) / (float)frameMaxIndex.y;
		ImGui::Image(_ImageManager->FindTexture("DefaultTileMap")->GetSRV(), ImVec2(100, 100), uv0, uv1);


		uv0.x = (float)pickIndex.x / (float)frameMaxIndex.x;
		uv0.y = (float)pickIndex.y / (float)frameMaxIndex.y;
		uv1.x = (float)(pickIndex.x + 1) / (float)frameMaxIndex.x;
		uv1.y = (float)(pickIndex.y + 1) / (float)frameMaxIndex.y;
		ImGui::SameLine();
		ImGui::Image(_ImageManager->FindTexture("DefaultTileMap")->GetSRV(), ImVec2(100, 100), uv0, uv1);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(u8"선택된 타일");
			ImGui::EndTooltip();

		}
		ImGui::Checkbox(u8"못 움직여 속성", &bImmovable);


		if (ImGui::Button(u8"저장"))
		{
			D3DDesc desc;
			DxRenderer::GetDesc(&desc);
			Path::SaveFileDialog(L"TileMap", Path::JsonFilter, ResourcePath, bind(&TileMap::Save, this, placeholders::_1), desc.Handle);
		}ImGui::SameLine();

		
		if (ImGui::Button(u8"로드"))
		{
			D3DDesc desc;
			DxRenderer::GetDesc(&desc);
			Path::OpenFileDialog(L"map", Path::JsonFilter, ResourcePath, bind(&TileMap::Load, this, placeholders::_1), desc.Handle);
		}

	}
	ImGui::End();
}

//TileMap의 Path를 넣어
void TileMap::LoadStage()
{
	oldIndex = currentIndex = { 0,0 };

	for (int y = 0; y < tileMaxIndex.y; y++)
	{
		for (int x = 0; x < tileMaxIndex.x; x++)
		{
			Tile* tile = new Tile("Tile", D3DXVECTOR2(tileSize.x * x, tileSize.y * y), tileSize, ObjectType::Tiles, Pivot::LEFT_TOP);
			tile->SetTexture(frameTextureKey);
			tiles.push_back(tile);
			
			_GameWorld->GetObjectPool()->AddObject(tile);
		}
	}

}

//툴 쓰려면 콜 해줘야됨
void TileMap::LoadFrame(string key)
{
	bLoadFrame = true;
	string defaultKey = "";
	if (key.size() == 0)
		defaultKey = "DefaultTileMap";
	else
		defaultKey = key;

	oldFrameIndex = currentFrameIndex = { 0,0 };
	frameMaxIndex.x = _ImageManager->FindTexture(defaultKey)->GetMaxFrame().x;
	frameMaxIndex.y = _ImageManager->FindTexture(defaultKey)->GetMaxFrame().y;
	frameStart = { WinSizeX * 0.6f, 100.f };
	frameSize = { 28.f,28.f };
	pickIndex = { 0,0 };

	for (int y = 0; y < (int)frameMaxIndex.y; y++)
	{
		for (int x = 0; x < (int)frameMaxIndex.x; x++)
		{
			Tile* tile = new Tile("Tile", D3DXVECTOR2(frameStart.x + frameSize.x * x, frameStart.y + frameSize.y * y), frameSize, ObjectType::Tiles, Pivot::LEFT_TOP);
			tile->SetFrameIndex(x, y);
			tile->SetTexture(defaultKey);
			frames.push_back(tile);
			_GameWorld->GetObjectPool()->AddObject(tile);
		}
	}

	pickedTiles.clear();


}

D3DXVECTOR2 TileMap::GetTilePos(POINT index)
{
	return tiles[tileMaxIndex.x * index.y + index.x]->Transform().GetPos();
}

Tile * TileMap::GetTile(POINT pt)
{
	if (pt.x < 0 || pt.y < 0 ||
		pt.x >= tileMaxIndex.x || pt.y >= tileMaxIndex.y)
		return nullptr;


	return tiles[tileMaxIndex.x * pt.y + pt.x];
}

Tile * TileMap::GetTile(int x, int y)
{
	if (x < 0 || y < 0 ||
		x >= tileMaxIndex.x || y >= tileMaxIndex.y)
		return nullptr;

	return tiles[tileMaxIndex.x * y + x];
}

Tile * TileMap::GetTile(D3DXVECTOR2 pos)
{
	int x = (int)(pos.x / tileSize.x);
	int y = (int)(pos.y / tileSize.y);

	return GetTile(x, y);
}

void TileMap::Save(wstring file)
{
	Json::Value imageData, tileData, tileLUT;
	string str = String::WStringToString(frameTexture->GetFilePath());

	JsonHelper::SetValue(imageData, "ImagePath", str);

	D3DXVECTOR2 mapMaxFrame = frameTexture->GetMaxFrame();
	JsonHelper::SetValue(imageData, "FrameMaxIndex", mapMaxFrame);

	wstring tiledataPath = L"../_Resources/TileIndex.index";
	str = String::WStringToString(tiledataPath);
	JsonHelper::SetValue(tileData, "TileData", str);

	vector<Tile> lut;
	BinaryWriter* w = new BinaryWriter();
	w->Open(tiledataPath);
	{
		//타일갯수 저장
		w->UInt(tileMaxIndex.x);
		w->UInt(tileMaxIndex.y);

		for (int y = 0; y < tileMaxIndex.y; y++)
		{
			for (int x = 0; x < tileMaxIndex.x; x++)
			{
				bool bCheck = true;
				Tile* tile = tiles[tileMaxIndex.x * y + x];
				for (int i = 0; i < lut.size(); i++)
				{
					//lut에 있는지 확인하고 있으면 lut번호로 추가
					if (lut[i].GetFrameX() == tile->GetFrameX() &&
						lut[i].GetFrameY() == tile->GetFrameY() && 
						lut[i].GetAttribute() == tile->GetAttribute())
					{
						//바이너리로 LUT인덱스 저장
						w->Int(i);
						bCheck = false;
					}
				}
				//lut에 없으면 인덱스 추가
				if (bCheck)
				{
					Tile temp;
					temp.CopyTile(tile);
					lut.push_back(temp);
					int index = lut.size() - 1;
					w->Int(index);

				}
			}
		}
	}
	w->Close();


	wstring tileLUTDataPath = L"../_Resources/TileLUT.lut";
	str = String::WStringToString(tileLUTDataPath);
	BinaryWriter* wLUT = new BinaryWriter();

	wLUT->Open(tileLUTDataPath);
	{
		wLUT->UInt(lut.size());

		for (int i = 0; i < lut.size(); i++)
		{
			D3DXVECTOR2 index;
			index.x = lut[i].GetFrameX();
			index.y = lut[i].GetFrameY();
			wLUT->Vector2(index);

			int attribute;
			attribute = lut[i].GetAttribute();
			wLUT->Int(attribute);
		}
	}
	wLUT->Close();

	JsonHelper::SetValue(tileLUT, "TileLUTData", str);


	(*jsonRoot)["ImageData"] = imageData;
	(*jsonRoot)["TileData"] = tileData;
	(*jsonRoot)["TileLUT"] = tileLUT;

	JsonHelper::WriteData(file, jsonRoot.get());

}

void TileMap::Load(wstring file)
{
	_GameWorld->GetObjectPool()->DeleteObjects(ObjectType::Tiles);
	tiles.clear();

	JsonHelper::ReadData(file, jsonRoot.get());
	Json::Value imageData, tileData, tileLUT;

	imageData = (*jsonRoot)["ImageData"];
	tileData = (*jsonRoot)["TileData"];
	tileLUT = (*jsonRoot)["TileLUT"];

	string loadImageKey;
	if (imageData.isNull() == false)
	{
		string imagePath;
		wstring wImagePath;
		D3DXVECTOR2 frameIndex;
		JsonHelper::GetValue(imageData, "ImagePath", imagePath);
		JsonHelper::GetValue(imageData, "FrameMaxIndex", frameIndex);

		wImagePath = String::StringToWString(imagePath);
		loadImageKey = String::WStringToString(Path::GetFileNameWithoutExtension(wImagePath));

		if (_ImageManager->AddFrameTexture(loadImageKey
			, String::StringToWString(imagePath)
			, (UINT)frameIndex.x, (UINT)frameIndex.y))
		{
			frameTextureKey = loadImageKey;
			frameTexture = _ImageManager->FindTexture(loadImageKey);
		}
	}

	vector<int> tileLUTIndex;
	if (tileData.isNull() == false)
	{
		string tileDataPath;
		JsonHelper::GetValue(tileData, "TileData", tileDataPath);
		BinaryReader* r = new BinaryReader;

		r->Open(String::StringToWString(tileDataPath));
		{
			tileMaxIndex.x = r->UInt();
			tileMaxIndex.y = r->UInt();

			for (int y = 0; y < tileMaxIndex.y; y++)
			{
				for (int x = 0; x < tileMaxIndex.x; x++)
				{
					tileLUTIndex.push_back(r->Int());
				}
			}
		}
		r->Close();


		for (int y = 0; y < tileMaxIndex.y; y++)
		{
			for (int x = 0; x < tileMaxIndex.x; x++)
			{
				Tile* tile = new Tile("Tile", D3DXVECTOR2(tileSize.x * x, tileSize.y * y), tileSize, ObjectType::Tiles, Pivot::LEFT_TOP);
				tile->SetIndex(x, y);
				tiles.push_back(tile);
				_GameWorld->GetObjectPool()->AddObject(tile);
			}
		}

	}

	vector<Tile> lut;
	if (tileLUT.isNull() == false)
	{
		string tileLUTPath;
		JsonHelper::GetValue(tileLUT, "TileLUTData", tileLUTPath);

		BinaryReader* r = new BinaryReader;
		r->Open(String::StringToWString(tileLUTPath));
		{
			UINT lutSize;
			lutSize = r->UInt();

			for (int i = 0; i < lutSize; i++)
			{
				Tile tile;
				D3DXVECTOR2 index;
				index = r->Vector2();
				tile.InitFrame(index.x, index.y);
				
				int mask;
				mask = r->Int();
				tile.SetAttribute(mask);

				//이미지도 추가해줌
				tile.SetTexture(loadImageKey);

				lut.push_back(tile);
			}
		}
		r->Close();
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->CopyTile(&lut[tileLUTIndex[i]]);

	}
}

