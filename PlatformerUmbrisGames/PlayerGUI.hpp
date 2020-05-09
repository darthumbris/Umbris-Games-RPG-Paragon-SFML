#pragma once

#include "Player.hpp"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInside;

	//initializers
	void initFont();
	void initHpBar();

public:
	//Constructor/Destructor
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Functions
	void updateHpBar();
	void update(const float& deltaTime);

	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

