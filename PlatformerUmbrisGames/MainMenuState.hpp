#pragma once


#include "GameState.hpp"
#include "Button.hpp"
#include "EditorState.hpp"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::Font mainMenuFont;
	sf::RectangleShape background;

	std::map<std::string, Button*> buttons;
	
	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
		std::stack<State*>* states);
	virtual ~MainMenuState();

	//functions
	void updateInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

