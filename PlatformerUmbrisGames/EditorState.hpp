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
	sf::View view;
	sf::Vector2i centreScreen;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu; // The pausemenu to quit the selector (and load and save later)

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap; //The grid of tiles where tiles can be added and removed

	sf::RectangleShape sideBar; // The bar on the left side of the screen where buttons get put in.

	sf::IntRect textureRect; //Determines which part of the tilesheet gets selected.
	sf::RectangleShape selectorRect; //The selection box according to a grid of where to place or remove a tile

	gui::TextureSelector* textureSelector; //The gui element to display and handle the selection of textures

	std::map<std::string, gui::DropDownList*> dropDownLists;

	std::vector<std::string> mapTypes;

	bool collision;
	short type;
	float cameraSpeed;
	int layer;

	bool hide; // a boolean to determine if the maptype list should be shown or not.

	//Functions
	void initVariables();
	void intitView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//functions
	void updateInput(const float& deltaTime);
	void updateEditorInput(const float& deltaTime);
	void updateButtons();
	void updateGui(const float& deltaTime);
	void updatePauseMenuButtons();
	void update(const float& deltaTime);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

