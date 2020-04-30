#include "SettingsState.hpp"
using namespace gui;

//Initializers
void SettingsState::initVariables()
{

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

void SettingsState::initButtons()
{
	float x = this->background.getPosition().x + this->background.getSize().x / 2.f - 150 / 2.f;
	this->buttons["EXIT_STATE_SETTINGS"] = new Button(
		x, 600.f, 250.f, 50.f,
		&this->font, "Return to Title", 40,
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 170), sf::Color(20, 20, 20, 0));
}

//Constructor/ Destructor
SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Accessors

//Functions

void SettingsState::updateInput(const float& deltaTime)
{

}

void SettingsState::updateButtons()
{
	//Updates all the buttons in the state and handles the functionality

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//quit the game
	if (this->buttons["EXIT_STATE_SETTINGS"]->isPressed() && this->getInputTime())
	{
		this->endState();
	}


}

void SettingsState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
	this->updateInputTime(deltaTime);

	this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
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