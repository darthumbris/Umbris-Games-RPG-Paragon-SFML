#pragma once

#include "State.hpp"
#include "Button.hpp"

class GameState :
	public State
{
private:
	Player* player;

	//Initializer Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

public:
	//Constructor/destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~GameState();

	//functions
	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

