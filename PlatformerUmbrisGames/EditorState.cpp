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
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->tileMap->getTileSheet());
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
	//Add a Tile to the Tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getInputTime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}

	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getInputTime())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//Change texture selected on the tilesheet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getInputTime())
	{
		if (this->textureRect.left <= 50)
		{
			this->textureRect.left += 50;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->getInputTime())
	{
		if (this->textureRect.left >= 50)
		{
			this->textureRect.left -= 50;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->getInputTime())
	{
		if (this->textureRect.top <= 50)
		{
			this->textureRect.top += 50;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->getInputTime())
	{
		if (this->textureRect.top >= 50)
		{
			this->textureRect.top -= 50;
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

void EditorState::updateGui()
{
	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize , 
		this->mousePosGrid.y * this->stateData->gridSize);

	
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << " mouseposview:  " <<this->mousePosView.x << "  ,  " << this->mousePosView.y << "\n" <<
		" mouseposgrid:  " << this->mousePosGrid.x << "  ,  " << this->mousePosGrid.y << "\n" <<
		" Texture sheet loc:  " << this->textureRect.left << "  ,  " << this->textureRect.top << "\n";
	this->cursorText.setString(ss.str());

	this->textureSelector->update();
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
		this->updateGui();
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
	this->textureSelector->render(target);

	target.draw(this->selectorRect);
	target.draw(this->cursorText);
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
