#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <math.h>

class ChaseGameState :
	public GameState
{
public:
	GameObject* gameObject = NULL;
	GameObject* target = NULL; // who to chase

	ChaseGameState();
	~ChaseGameState();

	virtual void update(float dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID();
};

