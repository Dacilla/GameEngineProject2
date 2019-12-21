#pragma once
#include "InputHandler.h"
class MouseHandler :
	public InputHandler
{
public:
	SDL_Rect* exitTextLoc;
	bool leftMousePressedDown;
	MouseHandler();
	~MouseHandler();

	//overrides
	virtual void update(SDL_Event* event);
};

