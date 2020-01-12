#include "stdafx.h"
#include "Unit.h"
#include "./Systems/PathFinder/PathFinder.h"
#include "./Systems/Object/TileMap.h"
#include "./Systems/Object/Tile.h"
#include "./Systems/Object/ObjectManager.h"

Unit::Unit(string name)
{
}

Unit::Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p)
	:GameObject(name, pos, size, type, p)
{
	currentState = nullptr;
	states.insert(make_pair("Step", new StateOneStep(this)));
	states.insert(make_pair("Idle", new StateIdle(this)));

	ChangeState("Idle");
	bMoving = false;
	bMyTurn = false;
}

Unit::~Unit()
{
}

void Unit::Init()
{
}

void Unit::Release()
{
}

void Unit::PreUpdate()
{
}

void Unit::Update(float tick)
{

	if(currentState)
		currentState->Update();
}

void Unit::PostUpdate()
{
}

void Unit::Render(bool isRelative)
{
	GameObject::Render(isRelative);
	
}

void Unit::PostRender()
{
}

void Unit::ChangeState(string key)
{
	StateBase* state = states[key];
	state->Enter();
	currentState = state;
}

void StateOneStep::Enter()
{
	if (me->path.size() <= 0)
		me->ChangeState("Idle");
	time = 0.f;
}

void StateOneStep::Update()
{
	if (time > 1.f)
	{
		me->path.pop_front();
		me->ChangeState("Idle");
		if (me->path.size() == 1) me->bMyTurn = false;

		return;
	}
	D3DXVECTOR2 tilePos = me->path[0]->Transform().GetPos() + TileMap::tileSize * 0.5f;
	D3DXVECTOR2 pos = me->transform.GetPos();
	pos = Math::Lerp(pos, tilePos, time );
	me->transform.SetPos(pos);

	time += Time::Tick();
}

void StateIdle::Enter()
{
}

void StateIdle::Update()
{

	if (me->path.size() != 0)
	{
		me->ChangeState("Step");
		return;
	}
	else
	{
		me->bMoving = false;
	}

	if (!me->bMyTurn) return;
	
	if (Mouse::Get()->Down(1))
	{
		Tile* start, *end;
		start = _TileMap->GetTile(me->transform.GetPos());
		end = _TileMap->GetTile(CAMERA->GetMousePos());
		if ((Math::Abs(start->GetTileIndex().x - end->GetTileIndex().x) + Math::Abs(start->GetTileIndex().y - end->GetTileIndex().y)) < 3)
		{
			me->path = _PathFinder->GetPath(start, end);
			me->bMoving = true;
			me->ChangeState("Step");
		}
	}
	else if (me->name == "Tank")
	{
		Tile* start, *end;
		start = _TileMap->GetTile(me->transform.GetPos());
		end = _TileMap->GetTile(_ObjectPool->FindObjectByName("Player")->Transform().GetPos());

		deque<Tile*> path = _PathFinder->GetPath(start, end);
		for (int i = 0;i < 2; i++)
		{
			if (path.size() == 1 && i == 1) break;
			me->path.push_back(path[i]);
		}

		me->bMoving = true;
		me->ChangeState("Step");
	}
}
