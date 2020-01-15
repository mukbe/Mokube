#pragma once
#include "SceneBase.h"

class Player;
class Unit;
class Tank;
class TurnControl;
class AStarScene : public SceneBase
{
public:
	AStarScene();
	virtual ~AStarScene();

	virtual void Init();
	virtual void Update(float tick);





private:
	Player* player;
	TurnControl* control;
};

