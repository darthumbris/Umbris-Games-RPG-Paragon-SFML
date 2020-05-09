#include "stdafx.h"
#include "PlayerGUI.hpp"

//initializers
void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/slkscr.ttf");
}

void PlayerGUI::initHpBar()
{
	float width = 300.f;
	float height = 25.f;
	float x = 20.f;
	float y = 20.f;
	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInside.setSize(sf::Vector2f(width, height));
	this->hpBarInside.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInside.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBarInside.getPosition().x + 10.f, this->hpBarInside.getPosition().y + 5.f);
	this->hpBarText.setCharacterSize(12);
}

//Constructor/Destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();
	this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{

}

void PlayerGUI::updateHpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / 
		static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarInside.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), 
			this->hpBarInside.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& deltaTime)
{
	this->updateHpBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInside);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
}

//Functions