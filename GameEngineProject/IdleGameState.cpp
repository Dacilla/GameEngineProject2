#include "IdleGameState.h"


IdleGameState::IdleGameState()
{
}


IdleGameState::~IdleGameState()
{
}

void IdleGameState::update(float dt)
{
	idleTimer -= dt;
	if (idleTimer <= 0){
		done = true;
	}
}

void IdleGameState::render()
{
	if (gameObject != NULL)
	{
		//draw rectangle at game objects position
		SDL_SetRenderDrawColor(Globals::renderer, 0, 255, 0, 255);
		SDL_Rect idleStateRect = { gameObject->pos.x - 10, gameObject->pos.y - 10, 20, 20 };
		SDL_RenderFillRect(Globals::renderer, &idleStateRect);
	}
}

bool IdleGameState::onEnter()
{
	idleTimer = rand() % 2 + 1; // 1 - 3 seconds of waiting around
	done = false;

	return true;
}

bool IdleGameState::onExit()
{
	return true;
}

string IdleGameState::getStateID()
{
	return "idleGameState";
}
