#include "stdafx.h"
#include "MainMenuState.hpp"
using namespace gui;

//Initializers
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x), 
		static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->mainMenuFont.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::MAINMENUSTATE::Could not load font");
	}
}

void MainMenuState::initKeybinds()
{

	//Hier bind ie de keys aan de acties dus bv W op UP etc.
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["GAME_STATE"] = new Button(
		gui::p2pX(7.8f, vm), gui::p2pY(13.9f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->mainMenuFont, "New Game", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new Button(
		gui::p2pX(7.8f, vm), gui::p2pY(27.8f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->mainMenuFont, "Settings", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new Button(
		gui::p2pX(7.8f, vm), gui::p2pY(41.7f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->mainMenuFont, "Editor", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(
		gui::p2pX(7.8f, vm), gui::p2pY(55.5f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->mainMenuFont, "Exit Game", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::resetGui()
{
	//clears the gui elements and reinitializes the gui
	this->buttons.clear();
	this->initGui();
}

//Constructor/destructors
MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void MainMenuState::updateInput(const float& deltaTime)
{
	
}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the state and handles the functionality

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//NEW game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}


}

void MainMenuState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//Remove later for seeing where the mouse is
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->mainMenuFont);
	mouseText.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
