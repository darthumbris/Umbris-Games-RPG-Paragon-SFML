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

	Player* playerProtagonist;
	Player* playerComp1;
	Player* playerComp2;
	Player* playerComp3;

	BattlePlayerGUI* battlePlayerGUI;

	float worldX;
	float worldY;
	float playerTempX;
	float playerTempY;

	bool fightButtonStatus;
	bool itemButtonStatus;
	bool magicButtonStatus;

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

	//Accessor
	const bool checkRunPossibility();
	const bool checkFightActive();
	const bool checkItemActive();
	const bool checkMagicActive();
	const int checkEnemySelected();

	//Functions
	void updateInput(const float& deltaTime);
	void updateBattleGUI(const float& deltaTime);
	void updateBattlePlayerGUI(const float& deltaTime);
	void calculateBattle();
	

	void update(const float& deltaTime);

	void renderBattleGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

