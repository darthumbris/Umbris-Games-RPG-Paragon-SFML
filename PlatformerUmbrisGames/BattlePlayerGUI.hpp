#pragma once

#include "Gui.hpp"
#include "Player.hpp"

class BattlePlayerGUI
{
private:
	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	unsigned position; //position order of the player gui

	//Name
	std::string nameString;
	sf::Text nameText;
	sf::RectangleShape nameRect;

	//level display
	std::string levelDisplayString;
	sf::Text levelDisplayText;
	//float levelDisplayMaxWidth;
	sf::RectangleShape levelDisplayBack;
	//sf::RectangleShape levelDisplayInside;

	//Exp bar
	std::string expBarString;
	sf::Text expBarText;
	sf::Text expText;
	float expBarMaxWidth;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInside;

	//Hp Bar
	std::string hpBarString;
	sf::Text hpBarText;
	sf::Text hpText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInside;

	//Mana bar
	std::string manaBarString;
	sf::Text manaBarText;
	sf::Text manaText;
	float manaBarMaxWidth;
	sf::RectangleShape manaBarBack;
	sf::RectangleShape manaBarInside;

	//initializers
	void initFont();
	void initHpBar();
	void initExpBar();
	void initLevelDisplay();
	void initManaBar();
	void initName();

public:
	//Constructor/Destructor
	BattlePlayerGUI(Player* player, sf::VideoMode& vm, unsigned position = 0);
	virtual ~BattlePlayerGUI();

	//Functions
	void updateHpBar();
	void updateExpBar();
	void updateManaBar();
	void updateLevelDisplay();
	void updateName();
	void update(const float& deltaTime);

	void renderHpBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderManaBar(sf::RenderTarget& target);
	void renderLevelDisplay(sf::RenderTarget& target);
	void renderName(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

