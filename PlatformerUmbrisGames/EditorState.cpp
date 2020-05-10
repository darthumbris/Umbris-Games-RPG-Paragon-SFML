#include "stdafx.h"
#include "EditorState.hpp"

//Initializers
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 0, 
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize));

	this->collision = false;
	this->type = TileTypes::DEFAULT;

	this->cameraSpeed = 100.f;
	this->layer = 0;
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

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 780, 450, "Resources/Images/Tiles/tilesheet1.png");
}

void EditorState::initGui()
{
	this->sideBar.setSize(sf::Vector2f(
		50.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
		));
	this->sideBar.setFillColor(sf::Color(50,50,50,100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(1.f);
	
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 400.f, 450.f, this->stateData->gridSize, 
		this->tileMap->getTileSheet(), this->font, "TS");
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
	//Move view
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
	
	//Adding and removing tiles
	if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		//Add a Tile to the Tilemap
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getInputTime())
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

	this->tileMap->render(*target, this->mousePosGrid, nullptr, sf::Vector2f(), true);
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
