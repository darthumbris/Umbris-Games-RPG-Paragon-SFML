#pragma once

#include "MainMenuState.hpp"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	
	sf::Clock dtClock;
	float deltaTime;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();
	
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update functions
	void updateDt();
	void handleEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

