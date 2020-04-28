#pragma once

#include "Entity.hpp"

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
	virtual void update(const float& deltaTime);

};

