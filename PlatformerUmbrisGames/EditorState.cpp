#include "stdafx.h"
#include "EditorState.hpp"

//Initializers
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 0, 
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize));
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
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("EXIT_STATE", 600.f, "Quit");
}

void EditorState::initButtons()
{

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 26, 15);
}

void EditorState::initGui()
{
	this->sideBar.setSize(sf::Vector2f(
		40.f,
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
		20.f, 20.f, 200.f, 150.f, this->stateData->gridSize, 
		this->tileMap->getTileSheet(), this->font, "TS");
}

//Constructor/destructors
EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
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
	if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		//Add a Tile to the Tilemap
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getInputTime())
		{
			if (!this->textureSelector->getActive()) // if not in the selection for textures add a tile
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
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
}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state and handles the functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
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
		" Texture sheet loc:  " << this->textureRect.left << "  ,  " << this->textureRect.top << "\n";
	this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT_STATE") && this->getInputTime())
		this->endState();
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions();
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
		this->pmenu->update(this->mousePosView);
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
	if(!this->textureSelector->getActive())
		target.draw(this->selectorRect);

	this->textureSelector->render(target);

	target.draw(this->cursorText);
	target.draw(this->sideBar);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->tileMap->render(*target);

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
