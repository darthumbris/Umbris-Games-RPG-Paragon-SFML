#pragma once

#include "State.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"

class GameState :
	public State
{
private:
	PauseMenu* pmenu;
	sf::Font font;
	
	Player* player;

	TileMap map;

	//Initializer Functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();

public:
	//Constructor/destructor
	GameState(StateData* state_data);
	virtual ~GameState();

	//functions
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void updatePauseMenuButtons();
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

