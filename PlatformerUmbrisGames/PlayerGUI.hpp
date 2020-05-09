#pragma once

#include "Player.hpp"
#include "Gui.hpp"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;

	//level display
	std::string levelDisplayString;
	sf::Text levelDisplayText;
	//float levelDisplayMaxWidth;
	sf::RectangleShape levelDisplayBack;
	//sf::RectangleShape levelDisplayInside;

	//Exp bar
	std::string expBarString;
	sf::Text expBarText;
	float expBarMaxWidth;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInside;

	//Hp Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInside;

	//initializers
	void initFont();
	void initHpBar();
	void initExpBar();
	void initLevelDisplay();

public:
	//Constructor/Destructor
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Functions
	void updateHpBar();
	void updateExpBar();
	void updateLevelDisplay();
	void update(const float& deltaTime);

	void renderHpBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderLevelDisplay(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

