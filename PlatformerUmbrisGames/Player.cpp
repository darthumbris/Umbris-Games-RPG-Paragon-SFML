#include "Player.hpp"

//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{
	
}

//Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 8.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 32.f, 10.f, 35.f, 90.f);

	this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 0, 0, 100, 100);
	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 3, 0, 3, 100, 100);
	this->animationComponent->addAnimation("IDLE_UP", 10.f, 0, 1, 0, 1, 100, 100);
	this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 3, 0, 2, 100, 100);
	this->animationComponent->addAnimation("RUN_DOWN", 10.f, 0, 0, 6, 0, 100, 100);
	this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 3, 6, 3, 100, 100);
	this->animationComponent->addAnimation("RUN_UP", 10.f, 0, 1, 6, 1, 100, 100);
	this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 2, 6, 2, 100, 100);
}

Player::~Player()
{

}

//Functions
void Player::update(const float& deltaTime)
{
	this->movementComponent->update(deltaTime);

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE_DOWN", deltaTime);
	}
	else if(this->movementComponent->getState(MOVING))
	{
		if (this->movementComponent->getState(MOVING_LEFT))
			this->animationComponent->play("RUN_LEFT", deltaTime);
		else if (this->movementComponent->getState(MOVING_RIGHT))
			this->animationComponent->play("RUN_RIGHT", deltaTime);
		else if (this->movementComponent->getState(MOVING_DOWN))
			this->animationComponent->play("RUN_DOWN", deltaTime);
		else if (this->movementComponent->getState(MOVING_UP))
			this->animationComponent->play("RUN_UP", deltaTime);
	}

	this->hitboxComponent->update();
}

