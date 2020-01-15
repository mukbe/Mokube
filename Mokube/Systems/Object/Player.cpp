#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "./Systems/PathFinder/PathFinder.h"
#include "./Systems/Message/MessageManager.h"

Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p)
	:Unit(name, pos, size, type, p)
{
	tex = _ImageManager->FindTexture("Player");
	path = new PathFinder;
}


Player::~Player()
{
	SafeDelete(path);
}

void Player::Init()
{
}

void Player::Release()
{
}

void Player::PreUpdate()
{
}

void Player::Update(float tick)
{
	Unit::Update(tick);


	
}

void Player::PostUpdate()
{
}

void Player::Render(bool isRelative)
{
	Unit::Render();

	tex->FrameRender(frameX, frameY, size, 1, Pivot::CENTER);
}

void Player::PostRender()
{
}

void Player::ImguiRender()
{
}
