#pragma once

#include "State.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"

class PauseMenu;
class Player;
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
	
	Player* player;

	TileMap* tileMap;

	//Initializer Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	//Constructor/destructor
	GameState(StateData* state_data);
	virtual ~GameState();

	//functions
	void updateView(const float& deltaTime);
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void updatePauseMenuButtons();
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

