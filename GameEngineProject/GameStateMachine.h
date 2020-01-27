#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	vector<GameState*> gameStates;

	GameStateMachine();
	~GameStateMachine();

	//state management
	void push(GameState* state);
	void pop();
	void replace(GameState* state);
	void clearAll();

	void update(float dt);
	void render();
};

