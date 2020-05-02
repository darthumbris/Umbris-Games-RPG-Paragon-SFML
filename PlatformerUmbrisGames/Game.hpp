#pragma once

#include "MainMenuState.hpp"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	
	sf::Clock dtClock;
	float deltaTime;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStataData();
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

