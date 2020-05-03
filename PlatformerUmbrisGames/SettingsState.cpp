#include "stdafx.h"
#include "SettingsState.hpp"
using namespace gui;

//Initializers
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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
	float x_button = this->background.getSize().x / 2.f - 250 / 2.f;
	float x_dropdown = this->background.getSize().x / 2.f - 200 / 2.f;
	this->buttons["EXIT_STATE_SETTINGS"] = new Button(
		x_button - 250, 600.f, 250.f, 45.f,
		&this->font, "Return to Title", 40,
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 170), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new Button(
		x_button + 250, 600.f, 250.f, 45.f,
		&this->font, "Apply settings", 40,
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 170), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;

	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(x_dropdown, 200, 200, 50, 
		font, modes_str.data(), modes_str.size(), 0);
}

void SettingsState::initText()
{
	this->settingsText.setFont(font);
	this->settingsText.setPosition(sf::Vector2f(100.f, 200.f));
	this->settingsText.setCharacterSize(30);
	this->settingsText.setFillColor(sf::Color(255, 255, 255, 200));
	
	this->settingsText.setString(
		"Resolution \n\nFullscreen \nVsync \nAntia-Aliasing \n");
}

//Constructor/ Destructor
SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
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
		it.second->update(this->mousePosView);
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
	}

	//Dropdownlists======
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->update(this->mousePosView, deltaTime);
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