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
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponent->getPosition().x) / gridSizeU, 
			static_cast<unsigned>(this->hitboxComponent->getPosition().y) / gridSizeU
		);

	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& delatTime) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * delatTime);
	}
	return sf::FloatRect();
}

//Modifiers
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
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

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget& target)
{

}
