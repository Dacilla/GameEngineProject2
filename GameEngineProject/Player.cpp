#include "Player.h"


Player::Player()
{
	animation = NULL;
	faceRight = true;
	type = "player";
	health = 10;
	ammo = 30;
}


Player::~Player()
{
}

void Player::update(float dt)
{
	//basic game object vector movement
	updateMovement(dt);

	//update facing direction based on velocity
	if (velocity.x > 0)
		faceRight = true;
	if (velocity.x < 0)
		faceRight = false;

	//update our animation
	if (velocity.x != 0 || velocity.y != 0)
		animation->update(dt);
}

void Player::draw()
{
	if (animation != NULL)
	{
		float drawX = pos.x - Globals::camera.x;
		float drawY = pos.y - Globals::camera.y;
		if (faceRight)
			animation->draw(drawX, drawY);
		else
			animation->draw(drawX, drawY, true);
	}
}

void Player::shoot()
{
	//TODO: ADD AMMO FUNCTIONALITY
	if (ammo > 0)
	{
		SoundManager::soundManager.playSound("explode");

		Bullet* bullet = new Bullet();
		bullet->renderer = renderer;
		bullet->setPosition(pos);
		bullet->angle = rand() % 360;//rand gives random int between min and max int value, modulus it into 360 degree value
		bullet->movementSpeed = 200;

		//add to gameObjects list
		GameObject::gameObjects->push_back(bullet);
		ammo--;
	}
	else
	{
		
	}

}
