#include "MouseHandler.h"


MouseHandler::MouseHandler()
{
	leftMousePressedDown = false;
}


MouseHandler::~MouseHandler()
{
}

void MouseHandler::update(SDL_Event* event)
{
	//Check if user has clicked on exit button
	/*if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		if (event->button.x >= exitTextLoc.x)
	}*/

	//check if user has clicked on exit
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		if (event->button.x >= exit)
	}
}