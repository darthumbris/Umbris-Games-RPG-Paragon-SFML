#include "PauseMenu.hpp"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) /4.f,
			static_cast<float>(window.getSize().y) - 50.f
		));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition((
		static_cast<float>(window.getSize().x) /2.f) - (this->container.getSize().x / 2.f),
		25.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + (this->container.getSize().x / 2.f ) - 
		(this->menuText.getGlobalBounds().width / 2.f), 
		this->container.getPosition().y + 10.f);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void PauseMenu::update()
{

}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(this->menuText);
}

