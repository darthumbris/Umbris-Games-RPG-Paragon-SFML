#pragma once

#include "Player.hpp"

class Player;

class PlayerGUI
{
private:
	Player* player;

public:
	//Constructor/Destructor
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget& target);
};

