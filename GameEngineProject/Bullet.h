#pragma once
#include "GameObject.h"
#include <cmath> //trig stuff
class Bullet :
	public GameObject
{
public:
	Bullet();
	~Bullet();

	float angle;
	float movementSpeed;

	void update(float dt);
	void draw();

	//overriding
	void updateCollisionBox();
	void updateCollision(float dt);
};

