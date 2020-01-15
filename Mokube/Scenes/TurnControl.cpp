#include "stdafx.h"
#include "TurnControl.h"
#include "./Systems/Object/Unit.h"


TurnControl::TurnControl()
{
	current = nullptr;
}


TurnControl::~TurnControl()
{
}

void TurnControl::Update(float tick)
{
	if (current->IsMoving() == false && current->IsMyTurn() == false)
	{
		Next();
	}
}

void TurnControl::Register(Unit * unit)
{
	if (units.size() == 0)
	{
		current = unit;
		current->SetTurn(true);
	}
	units.push(unit);
	
}

void TurnControl::Next()
{
	units.push(units.front());
	units.pop();
	current = units.front();
	current->SetTurn(true);
}
