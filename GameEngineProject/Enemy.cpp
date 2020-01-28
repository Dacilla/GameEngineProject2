#include "Enemy.h"


Enemy::Enemy()
{
	//build idle game states for our defauly state for enemy
	IdleGameState* idle = new IdleGameState();
	idle->gameObject = this;
	type = "enemy";
	gsm.push(idle);
}


Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	gsm.update(dt);
	GameState* currentState = gsm.gameStates.back();
	if (currentState->done)
	{
		//if idle finished, add chase state on top of stack
		if (currentState->getStateID() == "idleGameState")
		{
			ChaseGameState* newState = new ChaseGameState();
			newState->gameObject = this;
			newState->target = target;

			gsm.push(newState);
		}
		else
		{
			//probably the chase state, then kill it and we should fall back onto idle
			gsm.pop();
		}
	}

	updateMovement(dt);

	animation->update(dt);
}


void Enemy::draw()
{
	gsm.render();
	if (animation != NULL){
		float drawX = pos.x - Globals::camera.x;
		float drawY = pos.y - Globals::camera.y;
		animation->draw(drawX, drawY);
	}
}

void Enemy::updateCollisionBox()
{
	collisionBox.w = 32;
	collisionBox.h = 32;
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
}

void Enemy::updateCollision(float dt)
{
	//see if any bullets have hit us
	for (list<GameObject*>::iterator gObj = GameObject::gameObjects->begin();
		gObj != GameObject::gameObjects->end(); gObj++)
	{
		if ((*gObj)->type == "bullet" && GameObject::AABBcheck(collisionBox, (*gObj)->collisionBox))
		{
			health -= 20;
			//deactivate bullet
			(*gObj)->active = false;

			//if enemy died
			if (health <= 0)
				active = false;
		}
	}
}