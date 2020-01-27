#include "Bullet.h"


Bullet::Bullet()
{
	type = "bullet";
}


Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	//convert angle in degress to radians so we can do trigonometry
	float angleInRadians = angle / 180 * M_PI;

	//convert radian and speed into vector values
	velocity.x = movementSpeed*cos(angleInRadians);
	velocity.y = movementSpeed*sin(angleInRadians);

	updateMovement(dt);
}

void Bullet::draw()
{
	float drawX = pos.x - Globals::camera.x;
	float drawY = pos.y - Globals::camera.y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);//yellow
	SDL_Rect bulletRect = { drawX - 10, drawY - 10, 20, 20 }; //x,y,w,h
	SDL_RenderFillRect(renderer, &bulletRect);
}

void Bullet::updateCollisionBox()
{
	collisionBox.w = 20;
	collisionBox.h = 20;
	collisionBox.x = pos.x - (collisionBox.w / 2);
	collisionBox.y = pos.y - (collisionBox.h / 2);

}

void Bullet::updateCollision(float dt)
{
	//leave it to chaser to see if they are being hit
	//note: marbe check to see if we are colliding with walls or something

}