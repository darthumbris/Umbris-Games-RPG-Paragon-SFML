#pragma once

#include "State.hpp"
#include "Button.hpp"

class EditorState :
	public State
{
private:
	//Variables
	sf::Font mainMenuFont;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~EditorState();

	//functions
	void updateInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

