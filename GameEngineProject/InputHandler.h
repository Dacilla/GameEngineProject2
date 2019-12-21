#pragma once
#include <SDL.h>

class InputHandler
{
public:

	InputHandler();
	~InputHandler();

	//abstract functions
	//Note: abstract function has no func body and makes class abstract
	virtual void update(SDL_Event* event) = 0;

	virtual void updateHeld()
	{
		//get sub classes to fill in if appropriate
	}
};

