#include "stdafx.h"
#include "Sword.hpp"

Sword::Sword()
{
	//Visual weapon
	this->weaponTexture.loadFromFile("Resources/Images/Sprites/Player/sword.png");
	this->weaponSprite.setTexture(weaponTexture);

	this->weaponSprite.setOrigin
	(
		this->weaponSprite.getGlobalBounds().width / 2.f,
		this->weaponSprite.getGlobalBounds().height
	);
}

Sword::~Sword()
{
	
}

void Sword::update(const sf::Vector2f mouse_pos_view, const sf::Vector2f center)
{
	//Update visual weapon
	this->weaponSprite.setPosition(center);

	float dx = mouse_pos_view.x - this->weaponSprite.getPosition().x;
	float dy = mouse_pos_view.y - this->weaponSprite.getPosition().y;

	const float PI = 3.14159265;
	float deg = atan2(dy, dx) * 180 / PI;

	this->weaponSprite.setRotation(deg + 90.f);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->weaponSprite, shader);
	else
		target.draw(this->weaponSprite);
}

