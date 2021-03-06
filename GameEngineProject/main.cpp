#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "Globals.h"
#include "InputHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "gameControllerHandler.h"
#include "Animation.h"
#include "GameObject.h"
#include "Vector.h"
#include "Bullet.h"
#include "Player.h"
#include "SoundManager.h"
#include "Wall.h"

using namespace std;

int main(int argc, char **argv)
{
	//initialise SDL and its subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		return -1; //exit program early
	}
	else
	{
		cout << "SDL Initialised" << endl;
	}
	//Initialise SDL Image
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		//if didn't work, report error
		cout << "SDL IMAGE ERROR: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -2;
	}

	if (TTF_Init() != 0)
	{
		//failed
		cout << "TTF FAILED: " << TTF_GetError() << endl;
		SDL_Quit();
		return -3;
	}

	//mixer init
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "mixer error: " << Mix_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -4;
	}

	//params:
	//	window title, x and y pos, width, height, flags for creation
	SDL_Window* window = SDL_CreateWindow("Zombie Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN); // |SDL_WINDOW_FULLSCREEN

	if (window != NULL){
		cout << "Window created" << endl;
	}
	else{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -4;
	}

	//create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -5;
	}

	Globals::window = window;
	Globals::renderer = renderer;

	//setup game objects list
	list<GameObject*> gameObjects;
	//give list reference to game objects static variable
	GameObject::gameObjects = &gameObjects;

	//ASSETS
	

	//walls
	Wall* topWall = new Wall();
	topWall->renderer = Globals::renderer;
	topWall->pos.x = 0; 
	topWall->pos.y = 0;
	topWall->w = 1000;
	topWall->h = 32;
	gameObjects.push_back(topWall);

	Wall* leftWall = new Wall();
	leftWall->renderer = Globals::renderer;
	leftWall->pos.x = 0;
	leftWall->pos.y = 0;
	leftWall->w = 32;
	leftWall->h = 1000;
	gameObjects.push_back(leftWall);

	Wall* rightWall = new Wall();
	rightWall->renderer = Globals::renderer;
	rightWall->pos.x = 1000;
	rightWall->pos.y = 0;
	rightWall->w = 32;
	rightWall->h = 1000;
	gameObjects.push_back(rightWall);

	Wall* bottomWall = new Wall();
	rightWall->renderer = Globals::renderer;
	rightWall->pos.x = 0;
	rightWall->pos.y = 1000;
	rightWall->w = 1000;
	rightWall->h = 32;
	gameObjects.push_back(bottomWall);

	//FONT
	TTF_Font* titleFont = TTF_OpenFont("Assets/ConcertOne-Regular.ttf", 42);
	TTF_Font* menuTextFont = TTF_OpenFont("Assets/Comfortaa-VariableFont_wght.ttf", 24);
	SDL_Color textColour = { 200, 200, 200, 0 };
	list<SDL_Texture*> textTextures; // create a list of all textures, not in use now, but planning ahead
	list<SDL_Rect> textRects;

	//TODO: Find a way to do all of this in a function
	//Create Title Text
	SDL_Surface* textSurface = TTF_RenderText_Blended(titleFont, "Zombie Hunter", textColour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textTextures.push_back(textTexture);
	//Text dest
	SDL_Rect titleTextDest;
	titleTextDest.x = 570;
	titleTextDest.y = 50;
	textRects.push_back(titleTextDest);

	//Create New Game Text
	SDL_Surface* newGametextSurface = TTF_RenderText_Blended(menuTextFont, "New Game", textColour);
	SDL_Texture* newGameTextTexture = SDL_CreateTextureFromSurface(renderer, newGametextSurface);
	SDL_FreeSurface(newGametextSurface);
	SDL_Rect newGameTextDest;
	newGameTextDest.x = 570;
	newGameTextDest.y = 130;
	textTextures.push_back(newGameTextTexture);
	textRects.push_back(newGameTextDest);

	//Create Leaderboards Text
	SDL_Surface* leaderboardsTextSurface = TTF_RenderText_Blended(menuTextFont, "Leaderboards", textColour);
	SDL_Texture* leaderboardsTextTexture = SDL_CreateTextureFromSurface(renderer, leaderboardsTextSurface);
	SDL_FreeSurface(leaderboardsTextSurface);
	SDL_Rect leaderboardsTextDest;
	leaderboardsTextDest.x = 570;
	leaderboardsTextDest.y = 180;
	textTextures.push_back(leaderboardsTextTexture);
	textRects.push_back(leaderboardsTextDest);

	//Create How To Play Text
	SDL_Surface* howToPlayTextSurface = TTF_RenderText_Blended(menuTextFont, "How To Play", textColour);
	SDL_Texture* howToPlayTextTexture = SDL_CreateTextureFromSurface(renderer, howToPlayTextSurface);
	SDL_FreeSurface(howToPlayTextSurface);
	SDL_Rect howToPlayTextDest;
	howToPlayTextDest.x = 570;
	howToPlayTextDest.y = 230;

	//Create Exit Text
	SDL_Surface* exitTextSurface = TTF_RenderText_Blended(menuTextFont, "Exit", textColour);
	SDL_Texture* exitTextTexture = SDL_CreateTextureFromSurface(renderer, exitTextSurface);
	SDL_FreeSurface(exitTextSurface);
	SDL_Rect exitTextDest;
	exitTextDest.x = 570;
	exitTextDest.y = 280;

	//query for width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &titleTextDest.w, &titleTextDest.h);
	SDL_QueryTexture(newGameTextTexture, NULL, NULL, &newGameTextDest.w, &newGameTextDest.h);
	SDL_QueryTexture(leaderboardsTextTexture, NULL, NULL, &leaderboardsTextDest.w, &leaderboardsTextDest.h);
	SDL_QueryTexture(howToPlayTextTexture, NULL, NULL, &howToPlayTextDest.w, &howToPlayTextDest.h);
	SDL_QueryTexture(exitTextTexture, NULL, NULL, &exitTextDest.w, &exitTextDest.h);

	//Create background
	SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "Assets/background.png");
	SDL_Rect backgroundRect;
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
	backgroundRect.x = 0;
	backgroundRect.y = 0;

	//Create selector
	//SDL_Surface* selectorSurface = IMG_LoadTexture(renderer, "Assets/)

	//INPUT HANDLERS
	KeyboardHandler keyboardHandler;

	MouseHandler mouseHandler;

	GameControllerHandler gameControllerHandler;

	//query for width and height
	/*for each (SDL_Texture* textTexture in textTextures)
	{
		SDL_QueryTexture(textTexture, NULL, NULL, &titleTextDest.w, &titleTextDest.h);
	}*/

	Uint32 lastUpdate = SDL_GetTicks();

	bool loop = true;
	while (loop)
	{
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float dt = timeDiff / 100.0;
		lastUpdate = SDL_GetTicks();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		//Input Handling
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			//check if window has been closed
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
			//check for key press
			if (e.type == SDL_KEYDOWN)
			{
				//check for esc
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					loop = false;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{

				}
			}
		}

		//draw background
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

		//FONT BACKGROUND - I want to make the text have outlines but can't find how to do that, so this is a cheap and easy workaround for now
		SDL_Rect textBack = { 535, 55, 350, 300 }; // rough estimate of pixel positions using paint
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &textBack);

		//draw text on top layer
		//TODO: Do this in a function using an array or smth
		SDL_RenderCopy(renderer, textTexture, NULL, &titleTextDest);
		SDL_RenderCopy(renderer, newGameTextTexture, NULL, &newGameTextDest);
		SDL_RenderCopy(renderer, leaderboardsTextTexture, NULL, &leaderboardsTextDest);
		SDL_RenderCopy(renderer, howToPlayTextTexture, NULL, &howToPlayTextDest);
		SDL_RenderCopy(renderer, exitTextTexture, NULL, &exitTextDest);

		SDL_RenderPresent(renderer);
	}

	//cleanup
	TTF_CloseFont(titleFont);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(newGameTextTexture);
	SDL_DestroyTexture(leaderboardsTextTexture);
	SDL_DestroyTexture(howToPlayTextTexture);
	SDL_DestroyTexture(exitTextTexture);
	SDL_DestroyTexture(backgroundTexture);
	SDL_Quit();

	system("pause");
	return 0;

}