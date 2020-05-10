#pragma once

#include "State.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"
#include "PlayerGUI.hpp"

class PauseMenu;
class Player;
class PlayerGUI;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture; //Canvas that gets rendered to the screen
	sf::Sprite renderSprite;
	
	PauseMenu* pmenu;
	sf::Font font;
	
	sf::Shader coreShader;

	Player* player;
	PlayerGUI* playerGUI;

	TileMap* tileMap;

	//Initializer Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();

public:
	//Constructor/destructor
	GameState(StateData* state_data);
	virtual ~GameState();

	//functions
	void updateView(const float& deltaTime);
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void updatePlayerGUI(const float& deltaTime);
	void updatePauseMenuButtons();
	void updateTileMap(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

