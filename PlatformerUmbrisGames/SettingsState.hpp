#pragma once

#include "State.hpp"
#include "Gui.hpp"

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;

	gui::DropDownList* ddl;

	//Initializers
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();


public:
	//Constructor/ Destructor
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~SettingsState();

	//Accessors
	
	//Functions
	void updateInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

