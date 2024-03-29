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
	std::string name;

	//Initializer functions
	void initVariables();
	void initComponents();
public:
	//Constructor/Destructor
	//constructor for the main player with a texture
	Player(float x, float y, sf::Texture& texture_sheet, std::string name);
	Player(sf::Texture& texture_sheet, std::string name);
	virtual ~Player();

	//Accessors
	AttributeComponent* getAttributeComponent();
	const std::string getName() const;

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

