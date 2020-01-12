#include "stdafx.h"
#include "Tank.h"






Tank::Tank(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p)
	:Unit(name, pos, size, type, p)
{
	tex = _ImageManager->FindTexture("Unit");
}

Tank::~Tank()
{
}

void Tank::Init()
{
}

void Tank::Release()
{
}

void Tank::PreUpdate()
{
}

void Tank::Update(float tick)
{
	Unit::Update(tick);

}

void Tank::PostUpdate()
{
}

void Tank::Render(bool isRelative)
{
	Unit::Render();
	tex->FrameRender(frameX, frameY, size, 1, Pivot::CENTER);

}

void Tank::PostRender()
{
}
