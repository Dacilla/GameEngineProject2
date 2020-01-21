#pragma once
#include <SDL.h>
class Globals
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	//screen and camera
	static int screenWidth;
	static int screenHeight;
	static SDL_Rect camera;

	//current game state (main menu = 0, playing = 1, how to play = 2 etc)
	static int currentState;
};

