#include "stdafx.h"
#include "Entity.hpp"

//Initializers
void Entity::initVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

//Constructor/Destructor
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, 
	const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x ,offset_y, width, height);
}


//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite.getPosition();
}

//Modifiers
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


//Functions
void Entity::move(const float dir_x, const float dir_y, const float& deltaTime)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, deltaTime); //sets velocity
	}

}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
