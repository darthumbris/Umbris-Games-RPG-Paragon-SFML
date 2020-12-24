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
	Companion* playerComp1;
	Companion* playerComp2;
	Companion* playerComp3;

	BattlePlayerGUI* battlePlayerGUI;
	BattlePlayerGUI* battlePlayerGUI1;
	BattlePlayerGUI* battlePlayerGUI2;
	BattlePlayerGUI* battlePlayerGUI3;

	float worldX;
	float worldY;
	float playerTempX;
	float playerTempY;

	bool fightButtonStatus;
	bool itemButtonStatus;
	bool magicButtonStatus;

	//to set who is the active player at the moment (0 for player, 1 for comp 1 etc)
	unsigned activePlayer;

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
	const unsigned checkActivePlayer();

	//Functions
	void updateInput(const float& deltaTime);
	void updateBattleGUI(const float& deltaTime);
	void updateBattlePlayerGUI(const float& deltaTime);
	void calculateBattle();
	

	void update(const float& deltaTime);

	void renderBattleGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

