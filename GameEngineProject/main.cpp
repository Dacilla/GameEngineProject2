#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>

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

	//params:
	//	window title, x and y pos, width, height, flags for creation
	SDL_Window* window = SDL_CreateWindow("My Awesome Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN); // |SDL_WINDOW_FULLSCREEN

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

	//ASSETS
	//FONT
	TTF_Font* titleFont = TTF_OpenFont("Assets/vermin_vibes_1989.ttf", 32);
	SDL_Color textColour = { 123, 0, 34, 0 };
	list<SDL_Texture*> textTextures; // create a list of all textures
	list<SDL_Rect> textRects;

	//TODO: Find a way to do all of this is a function
	//Create Title Text
	SDL_Surface* textSurface = TTF_RenderText_Blended(titleFont, "Game Title", textColour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textTextures.push_back(textTexture);
	//Text dest
	SDL_Rect titleTextDest;
	titleTextDest.x = 570;
	titleTextDest.y = 50;
	textRects.push_back(titleTextDest);

	//Create New Game Text
	SDL_Surface* newGametextSurface = TTF_RenderText_Blended(titleFont, "New Game", textColour);
	SDL_Texture* newGameTextTexture = SDL_CreateTextureFromSurface(renderer, newGametextSurface);
	SDL_FreeSurface(newGametextSurface);
	SDL_Rect newGameTextDest;
	newGameTextDest.x = 570;
	newGameTextDest.y = 100;
	textTextures.push_back(newGameTextTexture);
	textRects.push_back(newGameTextDest);

	//Create Leaderboards Text
	SDL_Surface* leaderboardsTextSurface = TTF_RenderText_Blended(titleFont, "Leaderboards", textColour);
	SDL_Texture* leaderboardsTextTexture = SDL_CreateTextureFromSurface(renderer, leaderboardsTextSurface);
	SDL_FreeSurface(leaderboardsTextSurface);
	SDL_Rect leaderboardsTextDest;
	leaderboardsTextDest.x = 570;
	leaderboardsTextDest.y = 150;
	textTextures.push_back(leaderboardsTextTexture);
	textRects.push_back(leaderboardsTextDest);

	//Create How To Play Text
	SDL_Surface* howToPlayTextSurface = TTF_RenderText_Blended(titleFont, "How To Play", textColour);
	SDL_Texture* howToPlayTextTexture = SDL_CreateTextureFromSurface(renderer, howToPlayTextSurface);
	SDL_FreeSurface(howToPlayTextSurface);
	SDL_Rect howToPlayTextDest;
	howToPlayTextDest.x = 570;
	howToPlayTextDest.y = 200;

	//Create Exit Text
	SDL_Surface* exitTextSurface = TTF_RenderText_Blended(titleFont, "Exit", textColour);
	SDL_Texture* exitTextTexture = SDL_CreateTextureFromSurface(renderer, exitTextSurface);
	SDL_FreeSurface(exitTextSurface);
	SDL_Rect exitTextDest;
	exitTextDest.x = 570;
	exitTextDest.y = 250;

	//query for width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &titleTextDest.w, &titleTextDest.h);
	SDL_QueryTexture(newGameTextTexture, NULL, NULL, &newGameTextDest.w, &newGameTextDest.h);
	SDL_QueryTexture(leaderboardsTextTexture, NULL, NULL, &leaderboardsTextDest.w, &leaderboardsTextDest.h);
	SDL_QueryTexture(howToPlayTextTexture, NULL, NULL, &howToPlayTextDest.w, &howToPlayTextDest.h);
	SDL_QueryTexture(exitTextTexture, NULL, NULL, &exitTextDest.w, &exitTextDest.h);

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
			}
		}

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
	SDL_Quit();

	system("pause");
	return 0;

}