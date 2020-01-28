#pragma once
#include "GameObject.h"
#include "GameStateMachine.h"
#include "IdleGameState.h"
#include "ChaseGameState.h"
#include "Animation.h"

class Enemy :
	public GameObject
{
public:
	GameStateMachine gsm;
	GameObject* target = NULL;
	Animation* animation;

	int health = 100;

	Enemy();
	~Enemy();

	//overrides
	virtual void update(float dt);
	virtual void draw();

	void updateCollisionBox();
	void updateCollision(float dt);
};

