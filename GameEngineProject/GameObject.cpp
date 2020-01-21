#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setPosition(Vector pos)
{
	this->pos = pos;
}

void GameObject::setVelocity(Vector pos)
{
	this->velocity = velocity;
}

void GameObject::update(float dt)
{
	//let sub classes fill these in if appropriate
}

void GameObject::updateMovement(float dt)
{
	//accelaration changes velocity
	velocity.x = velocity.x + (acceleration.x*dt);
	velocity.y = velocity.y + (acceleration.y*dt);

	//velocity changes position
	pos.x = pos.x + velocity.x * dt;
	pos.y = pos.y + velocity.y * dt;

	//re-aligns the collisionbox
	updateCollisionBox();
}

void GameObject::updateCollisionBox()
{
	//reposition collision box to where pos.x and pos.y are
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
	//note: override this function if you need something different to happen
}

void GameObject::updateCollision(float dt)
{
	//override if need to deal with collisions
}

void GameObject::draw()
{
}

//initialising static variable on start of program
list<GameObject*> *GameObject::gameObjects = NULL;

bool GameObject::AABBcheck(SDL_Rect b1, SDL_Rect b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

void GameObject::deleteInactiveGameObjects()
{
	for (list<GameObject*>::iterator gObj = gameObjects->begin();
		gObj != gameObjects->end(); /*gObj++*/)
	{
		//if gameobject is not active
		if (!(*gObj)->active)
		{
			//deleting from RAM
			delete (*gObj);
			//remove reference from list
			gObj = gameObjects->erase(gObj);
		}
		else
		{
			//if active then move to next in the list
			gObj++;
		}
	}
}