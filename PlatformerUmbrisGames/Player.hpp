#pragma once

#include "Entity.hpp"

class Entity;

class Player :
	public Entity
{
private:
	//Variables
	bool attacking;

	//Initializer functions
	void initVariables();
	void initComponents();
public:
	//Constructor/Destructor
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	void updateAttack();
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

	void render(sf::RenderTarget& target);

};

