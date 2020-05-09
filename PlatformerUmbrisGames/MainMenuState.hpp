#pragma once


#include "GameState.hpp"
#include "Gui.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::Font mainMenuFont;
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;
	
	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	//Constructor/Destructor
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//functions
	void updateInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

