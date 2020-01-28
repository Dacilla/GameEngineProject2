#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Bullet.h"
#include "SoundManager.h"

class Player :
	public GameObject
{
public:
	Animation* animation;
	bool faceRight;

	int health;
	int ammo;

	Player();
	~Player();

	//override update
	void update(float dt);
	void draw();

	void shoot();
};

