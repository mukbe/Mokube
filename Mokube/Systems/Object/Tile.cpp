#include "stdafx.h"
#include "Tile.h"
#include "ObjectManager.h"



Tile::Tile(string name)
{
	tileIndex = { 0,0 };
	attribute = 0;
}

Tile::Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p)
	:GameObject(name, pos, size, type, p)
{
	tileMapImage = _ImageManager->FindTexture("DefaultTileMap");

	tileIndex = { 0,0 };
	bPicked = false;
	bOnMouse = false;
	attribute = 0;
	pickedRect = FloatRect(D3DXVECTOR2(0, 0), size, Pivot::LEFT_TOP);

	AddCallBackFunc();

}

Tile::~Tile()
{
}

void Tile::CopyTile(Tile* other)
{
	tileMapImage = other->tileMapImage;
	frameX = other->frameX;
	frameY = other->frameY;
	attribute = other->attribute;
}

void Tile::InitFrame(int frameX, int frameY)
{
	this->frameX = frameX;
	this->frameY = frameY;

}

void Tile::SetTexture(string key)
{
	tileMapImage = _ImageManager->FindTexture(key);
}

void Tile::Init()
{
}

void Tile::Release()
{
}

void Tile::PreUpdate()
{
}

void Tile::Update(float tick)
{
}

void Tile::PostUpdate()
{
}

void Tile::Render(bool isRelative)
{
	if (bActive == false)return;

	Matrix2D world = transform;

	if (isRelative)
	{
		world = world * CAMERA->GetView();
	}
	world.Bind();

	if (tileMapImage)
	{
		tileMapImage->FrameRender(frameX, frameY, size);
	}
	else
	{
		assert(tileMapImage != nullptr);
	}

	if (bOnMouse)
		p2DRenderer->DrawRectangle(pickedRect, DefaultBrush::yello);

	if (bPicked)
		p2DRenderer->DrawRectangle(pickedRect, DefaultBrush::red);


}

void Tile::AddCallBackFunc()
{
	AddCallback("SetFrameIndex", [&](TagMessage msg) {
		POINT index = msg.Data->GetValue<POINT>();
		frameX = index.x;
		frameY = index.y;
	});
	AddCallback("SetTileAttribute", [&](TagMessage msg) {
		int mask = msg.Data->GetValue<int>();

		SetAttribute(mask);

	});
	AddCallback("InMouse", [&](TagMessage msg) {
		bOnMouse = true;
	});
	AddCallback("OutMouse", [&](TagMessage msg) {
		bOnMouse = false;
	});
	AddCallback("Pick", [&](TagMessage msg) {
		bPicked = true;
	});
	AddCallback("Drop", [&](TagMessage msg) {
		bPicked = false;
	});


}

void Tile::SetAttribute(int val)
{
	attribute |= val;

}


