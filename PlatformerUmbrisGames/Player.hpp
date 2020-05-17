#pragma once

#include "Entity.hpp"

#include "Sword.hpp"

class Entity;

class Player :
	public Entity
{
private:
	//Variables
	bool attacking;
	Sword sword;

	//Initializer functions
	void initVariables();
	void initComponents();
public:
	//Constructor/Destructor
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessors
	AttributeComponent* getAttributeComponent();

	//Functions
	void loseHp(const int hp);
	void loseExp(const int exp);
	void gainHp(const int hp);
	void gainExp(const int exp);
	void updateAttack();
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false);

};

