#pragma once

#include "State.hpp"
#include "Gui.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"

class State;
class Gui;
class PauseMenu;
class Tilemap;

class EditorState :
	public State
{
private:
	//Variables
	sf::Font font;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap map;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initPauseMenu();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//functions
	void updateInput(const float& deltaTime);
	void updateButtons();
	void updatePauseMenuButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

