#pragma once
#include <string>
#include "Globals.h"

using namespace std;

//abstract class to build other gamestates
class GameState
{
public:
	bool done = false;

	GameState();
	~GameState();

	virtual void update(float dt) = 0; // abstract function
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual string getStateID() = 0;
};

