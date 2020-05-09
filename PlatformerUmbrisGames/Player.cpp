#include "stdafx.h"
#include "Player.hpp"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

//Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	

	this->setPosition(x, y);

	this->createMovementComponent(350.f, 1500.f, 600.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 32.f, 10.f, 35.f, 90.f);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE_DOWN", 8.f, 0, 0, 0, 0, 100, 100);
	this->animationComponent->addAnimation("IDLE_LEFT", 8.f, 0, 3, 0, 3, 100, 100);
	this->animationComponent->addAnimation("IDLE_UP", 8.f, 0, 1, 0, 1, 100, 100);
	this->animationComponent->addAnimation("IDLE_RIGHT", 8.f, 0, 3, 0, 2, 100, 100);
	this->animationComponent->addAnimation("RUN_DOWN", 8.f, 0, 0, 6, 0, 100, 100);
	this->animationComponent->addAnimation("RUN_LEFT", 8.f, 0, 3, 6, 3, 100, 100);
	this->animationComponent->addAnimation("RUN_UP", 8.f, 0, 1, 6, 1, 100, 100);
	this->animationComponent->addAnimation("RUN_RIGHT", 8.f, 0, 2, 6, 2, 100, 100);
	//Voor nu is de attack animatie de run_right animatie, puur voor testen
	this->animationComponent->addAnimation("ATTACK", 8.f, 0, 2, 6, 2, 100, 100);
}

Player::~Player()
{

}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

void Player::loseHp(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::loseExp(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainHp(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainXp(exp);
}

//Functions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
	
}

void Player::updateAnimation(const float& deltaTime)
{
	if (this->attacking)
	{
		//Voor Attack
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) // Facing left
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		else // Facing right
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", deltaTime, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) // Facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else // Facing right
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE_DOWN", deltaTime);
	}
	else if (this->movementComponent->getState(MOVING))
	{
		if (this->movementComponent->getState(MOVING_LEFT))
		{
			this->animationComponent->play("RUN_LEFT", deltaTime,
				this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		}
		else if (this->movementComponent->getState(MOVING_RIGHT))
		{
			this->animationComponent->play("RUN_RIGHT", deltaTime,
				this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		}
		else if (this->movementComponent->getState(MOVING_DOWN))
		{
			this->animationComponent->play("RUN_DOWN", deltaTime,
				this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
		else if (this->movementComponent->getState(MOVING_UP))
		{
			this->animationComponent->play("RUN_UP", deltaTime,
				this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
	}

	/*for flipping the sprite
	this->sprite.setScale(-1.f, 1.f); for flipping horizontal
	this->sprite.setScale(1.f, 1.f); for setting to normal
	this->sprite.setScale(1.f, -1.f); for flipping vertical
	but it flips it around the origin, thus it probably needs to be moved
	for moving do this first:
	this->sprite.setOrigin(number.f, 0.f) for when flipping horizontal
	then
	this->sprite.setOrigin(0.f, 0.f) for setting it to normal

	en kan misschien beter ook eerst nog een check inzetten zodat
	niet hele tijd wordt aangepast en alleen als nodig is.:
	
	//Voor links
	if(this->sprite.getScale().x < 0.f)
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
	}

	//Voor rechts
	if(this->sprite.getScale().x > 0.f)
	{
		this->sprite.setOrigin(number.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
	}
	etc.
	*/

	

}

void Player::update(const float& deltaTime)
{	
	this->movementComponent->update(deltaTime);

	this->updateAttack();

	this->updateAnimation(deltaTime);	

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}

