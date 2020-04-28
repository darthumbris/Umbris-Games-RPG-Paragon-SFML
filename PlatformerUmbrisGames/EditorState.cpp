#include "EditorState.hpp"

//Initializers
void EditorState::initVariables()
{

}

void EditorState::initBackground()
{
	
}

void EditorState::initFonts()
{
	if (!this->mainMenuFont.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::EDITORSTATE::Could not load font");
	}
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

void EditorState::initButtons()
{

}

//Constructor/destructors
EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void EditorState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state and handles the functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);

	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderButtons(target);

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
