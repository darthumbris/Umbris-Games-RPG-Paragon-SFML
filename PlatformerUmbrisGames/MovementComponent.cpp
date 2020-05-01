#include "stdafx.h"
#include "MovementComponent.hpp"


//Constructor/Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}


const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

//Accessors
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;

	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;

	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& deltaTime)
{
	/*Accelerating a sprite until it reaches max velocity*/

	//Acceleration
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& deltaTime)
{
	/*Decelerates the sprite and controls the maximum velocity
	and then moves the sprite*/
	
	//check for x direction
	if (this->velocity.x > 0.f) //check for positive x direction
	{
		//Max velocity check x positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
		
		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //check for negative x direction
	{
		//negative Max velocity check x
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	//check for y direction
	if (this->velocity.y > 0.f) //check for positive y direction
	{
		//Max velocity check y positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //check for negative y direction
	{
		//negative Max velocity check y
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * deltaTime); //uses velocity
}
