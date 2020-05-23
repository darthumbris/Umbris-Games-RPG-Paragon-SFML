#pragma once

#include "State.hpp"
#include "Gui.hpp"
#include "BattlePlayerGUI.hpp"

class BattleState :
    public State
{
private:
	//variables
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::RectangleShape background;
	sf::RectangleShape battleGUI;

	std::map<std::string, gui::Button*> buttons;

	sf::Shader coreShader;

	Player* player;
	BattlePlayerGUI* battlePlayerGUI;

	//Functions
	
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initEnemies();
	void initEnemyData();
	void initTextures();
	void initShaders();
	void initBattleGUI();
	void initBattlePlayerGUI();

	//Maybe make a battle player gui class lile im gamestate?

public:
    BattleState(Player* player, StateData* state_data);
    virtual ~BattleState();

	//Functions
	void updateInput(const float& deltaTime);
	void updateBattleGUI(const float& deltaTime);
	void updateBattlePlayerGUI(const float& deltaTime);
	void calculateBattle();
	void chechRunPossibility();

	void update(const float& deltaTime);

	void renderBattleGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

