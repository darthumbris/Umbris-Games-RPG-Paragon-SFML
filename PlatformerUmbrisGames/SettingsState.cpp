#include "stdafx.h"
#include "SettingsState.hpp"
using namespace gui;

//Initializers
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::MAINMENUSTATE::Could not load font");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	//init background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//init buttons
	this->buttons["EXIT_STATE_SETTINGS"] = new Button(
		gui::p2pX(20.7f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(19.5f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Return to Title", gui::calcCharSize(vm, 50),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 170), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new Button(
		gui::p2pX(62.1f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(19.5f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Apply settings", gui::calcCharSize(vm, 50),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 170), sf::Color(20, 20, 20, 0));

	//init modes
	std::vector<std::string> modes_str;

	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	//init dropdownlist
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(42.2f, vm), gui::p2pY(27.8f, vm),
		gui::p2pX(15.6f, vm), gui::p2pY(6.9f, vm),
		gui::calcCharSize(vm, 80),
		font, modes_str.data(), modes_str.size(), 0);

	//init Text
	this->settingsText.setFont(font);
	this->settingsText.setPosition(sf::Vector2f(gui::p2pX(7.8f, vm), gui::p2pY(27.8f, vm)));
	this->settingsText.setCharacterSize(gui::calcCharSize(vm, 60));
	this->settingsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->settingsText.setString(
		"Resolution \n\nFullscreen \nVsync \nAntia-Aliasing \n");
}

void SettingsState::resetGui()
{
	//clears the gui elements and reinitializes the gui
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	for (auto it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}


//Constructor/ Destructor
SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions

void SettingsState::updateInput(const float& deltaTime)
{

}

void SettingsState::updateGui(const float& deltaTime)
{
	//Updates all the gui elements in the state and handles the functionality
	
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	//Buttons functionality========
	//quit the game
	if (this->buttons["EXIT_STATE_SETTINGS"]->isPressed() && this->getInputTime())
	{
		this->endState();
	}

	//Apply settings
	if (this->buttons["APPLY"]->isPressed() && this->getInputTime())
	{
		
		std::cout << "Applied Settings" << "\n";
		//Test remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];


		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		this->resetGui();
	}

	//Dropdownlists======
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->update(this->mousePosWindow, deltaTime);
	}


	//dropdownlists functionality
	
}

void SettingsState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
	this->updateInputTime(deltaTime);
	this->updateGui(deltaTime);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	//Render Buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	//Render DropDownLists
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->settingsText);

	//Remove later for seeing where the mouse is
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}