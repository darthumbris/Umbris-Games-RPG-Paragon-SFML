#pragma once

#include "State.hpp"
#include "PauseMenu.hpp"

class GameState :
	public State
{
private:
	PauseMenu* pmenu;
	sf::Font font;
	
	Player* player;

	//Initializer Functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();

public:
	//Constructor/destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~GameState();

	//functions
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

