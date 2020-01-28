#include "ChaseGameState.h"


ChaseGameState::ChaseGameState()
{
}


ChaseGameState::~ChaseGameState()
{
}

void ChaseGameState::update(float dt)
{
	if (gameObject != NULL && target != NULL)
	{
		//distance between gameObject and target in pixels
		float distance = abs(sqrt(pow(gameObject->pos.x - target->pos.x, 2) + pow(gameObject->pos.y - target->pos.y, 2)));

		if (distance > 10)
		{
			//chase target
			//get angle between gameObject and target in RADIANS
			float angleBetween = atan2(target->pos.y - gameObject->pos.y, target->pos.x - gameObject->pos.x);

			float moveSpeed = 50; //pixels per second
			gameObject->velocity.x = cos(angleBetween) * moveSpeed;
			gameObject->velocity.y = sin(angleBetween) * moveSpeed;
		}
		else
		{
			//stop chasing
			gameObject->velocity.x = 0;
			gameObject->velocity.y = 0;
			done = true;
		}
	}
}

void ChaseGameState::render()
{
	if (gameObject != NULL)
	{
		//draw rectangle at game objects position
		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, 255);
		SDL_Rect idleStateRect = { gameObject->pos.x - 10, gameObject->pos.y - 10, 20, 20 };
		SDL_RenderFillRect(Globals::renderer, &idleStateRect);
	}
}

bool ChaseGameState::onEnter()
{
	return true;
}

bool ChaseGameState::onExit()
{
	return true;
}

string ChaseGameState::getStateID()
{
	return "chaseGameState";
}