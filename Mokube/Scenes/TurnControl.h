#pragma once
#include <queue>

class Unit;
class TurnControl
{
public:
	TurnControl();
	~TurnControl();

	void Update(float tick);
	void Register(Unit* unit);
	void Next();
private:
	queue<Unit*> units;
	Unit* current;

};

