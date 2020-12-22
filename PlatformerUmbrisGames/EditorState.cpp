#include "stdafx.h"
#include "EditorState.hpp"
using namespace gui;

//Initializers
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 0, 
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize));

	this->collision = false;
	this->type = TileTypes::DEFAULT;

	this->cameraSpeed = 64.f;
	this->layer = 0;
	this->hide = false;

	
	//sets the centre position of the render screen so that not the whole map gets rendered
	this->centreScreen.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->centreScreen.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void EditorState::intitView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f ,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void EditorState::initBackground()
{
	
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::EDITORSTATE::Could not load font");
	}
}

void EditorState::initText()
{
	//Remove later for seeing where the mouse is
	
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
}

void EditorState::initKeybinds()
{

	//Hier bind ie de keys aan de acties dus bv W op UP etc.
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("EXIT_STATE", gui::p2pY(83.3f, vm), gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm), gui::calcCharSize(vm, 50), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(41.7f, vm), gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm), gui::calcCharSize(vm, 50), "Save map");
	this->pmenu->addButton("LOAD", gui::p2pY(55.6f, vm), gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm), gui::calcCharSize(vm, 50), "Load map");
}

void EditorState::initButtons()
{
	sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	this->buttons["SET"] = new Button(
		gui::p2pX(0.56f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(3.125f, vm), gui::p2pY(5.55f, vm),
		&this->font, "Set", gui::calcCharSize(vm, 80),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 50));

	this->buttons["HIDE"] = new Button(
		gui::p2pX(0.56f, vm), gui::p2pY(50.f, vm),
		gui::p2pX(3.125f, vm), gui::p2pY(5.55f, vm),
		&this->font, "MT", gui::calcCharSize(vm, 80),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 50));
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet1.png", "OVERWORLD");
}

void EditorState::initGui()
{
	sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	//Sidebar
	this->sideBar.setSize(sf::Vector2f(
		gui::p2pX(3.9f, vm),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
		));
	this->sideBar.setFillColor(sf::Color(50,50,50,100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(1.f);
	
	//Selector rectangle
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	//Texture selector button in the sidebar
	this->textureSelector = new gui::TextureSelector(
		gui::p2pX(1.56f, vm), gui::p2pY(2.78f, vm), 400.f, 450.f, this->stateData->gridSize, 
		this->tileMap->getTileSheet(), this->font, "TS", this->stateData->gfxSettings->resolution);

	//MapType dropdownlist selector in the sidebar======================================
	

	//init modes
	std::vector<std::string> map_types;
	
	map_types.push_back("OVERWORLD");
	map_types.push_back("FOREST");
	map_types.push_back("MOUNTAIN");
	map_types.push_back("PLAINS");
	map_types.push_back("RIVER");
	map_types.push_back("SEA");
	map_types.push_back("DESERT");
	

	//init dropdownlist
	this->dropDownLists["MAPTYPES"] = new gui::DropDownList(
		gui::p2pX(3.8f, vm), gui::p2pY(50.f, vm),
		gui::p2pX(12.f, vm), gui::p2pY(5.55f, vm),
		gui::calcCharSize(vm, 70),
		font, map_types.data(), map_types.size(), 0);
	//=================================================================================
}

//Constructor/destructors
EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->intitView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pmenu;

	delete this->tileMap;

	delete this->textureSelector;

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Functions
void EditorState::updateInput(const float& deltaTime)
{
	//when pressing the "close" button it either opens or closes the pause menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getInputTime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& deltaTime)
{
	//Move map view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * deltaTime);
	}

	//move render view
	this->centreScreen.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->centreScreen.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
	
	//Adding and removing tiles
	if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		//Add a Tile to the Tilemap
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!this->textureSelector->getActive()) // if not in the selection for textures add a tile
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, 
					this->textureRect, this->collision, this->type);
			}
			else // else select the texture selected
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}

		//Remove a tile from the tilemap
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getInputTime())
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
	}

	//Toggle Collision

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getInputTime())
	{
		this->collision = !this->collision;
	}

	//Toggle Type
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TYPE_INC"))) && this->getInputTime())
	{
		//Make a limit here
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TYPE_DEC"))) && this->getInputTime())
	{
		if(this->type > 0)
			--this->type;
	}
}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state and handles the functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& deltaTime)
{
	this->textureSelector->update(this->mousePosWindow, deltaTime);
	
	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,
			this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << " mouseposview:  " <<this->mousePosView.x << "  ,  " << this->mousePosView.y << "\n" <<
		" mouseposgrid:  " << this->mousePosGrid.x << "  ,  " << this->mousePosGrid.y << "\n" <<
		" Sheet loc:  " << this->textureRect.left << "  ,  " << this->textureRect.top << "\n" <<
		"Collision: " << this->collision << "\n" <<
		"type: " << this->type << "\n" <<
		"# Tiles: " << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer);
	
	this->cursorText.setString(ss.str());

	//Hide maptype selector button
	if (this->buttons["HIDE"]->isPressed() && this->getInputTime())
	{
		this->hide = !this->hide;
	}

	//Apply maptype
	if (this->buttons["SET"]->isPressed() && this->getInputTime())
	{		
		switch (this->dropDownLists["MAPTYPES"]->getActiveElementId())
		{
		case 0:
			this->tileMap->setMapType("OVERWORLD");
			std::cout << "Set Map Type to overworld" << "\n";
			break;
		case 1:
			this->tileMap->setMapType("FOREST");
			std::cout << "Set Map Type to forest" << "\n";
			break;
		case 2:
			this->tileMap->setMapType("MOUNTAIN");
			std::cout << "Set Map Type to mountain" << "\n";
			break;
		case 3:
			this->tileMap->setMapType("PLAINS");
			std::cout << "Set Map Type to plains" << "\n";
			break;
		case 4:
			this->tileMap->setMapType("RIVER");
			std::cout << "Set Map Type to river" << "\n";
			break;
		case 5:
			this->tileMap->setMapType("SEA");
			std::cout << "Set Map Type to sea" << "\n";
			break;
		case 6:
			this->tileMap->setMapType("DESERT");
			std::cout << "Set Map Type to desert" << "\n";
			break;
		default:
			break;
		}
		
		this->tileMap->resetTileSheet();
	}

	if (!hide) //only update if not hidden
	{
		//Dropdownlists======
		for (auto& it2 : this->dropDownLists)
		{
			it2.second->update(this->mousePosWindow, deltaTime);
		}
	}
	//Still to add that the maptype gets altered
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT_STATE") && this->getInputTime())
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE") && this->getInputTime())
		this->tileMap->saveToFile("Map_Saves/map_data.map");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("Map_Saves/map_data.map");
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions(&this->view);
	this->updateInput(deltaTime);
	this->updateInputTime(deltaTime);

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui(deltaTime);
		this->updateEditorInput(deltaTime);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	target.setView(this->window->getDefaultView());
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	if (!hide) //only render if not hidden
	{
		//Render DropDownLists
		target.setView(this->window->getDefaultView());
		for (auto& it2 : this->dropDownLists)
		{
			it2.second->render(target);
		}
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sideBar);

	target.setView(this->view);
	target.draw(this->cursorText);

	//target.setView(this->window->getDefaultView());
	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	target->setView(this->view);

	this->tileMap->render(*target, this->centreScreen, nullptr, sf::Vector2f(), true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());

	if (this->paused) // Pause Menu render
	{
		this->pmenu->render(*target);
	}
	else
	{
		this->renderGui(*target);
		this->renderButtons(*target);
	}
}
