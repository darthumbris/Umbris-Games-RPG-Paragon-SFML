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
	float y = 70.f;
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

void PlayerGUI::initExpBar()
{
	float width = 200.f;
	float height = 20.f;
	float x = 20.f;
	float y = 100.f;
	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInside.setSize(sf::Vector2f(width, height));
	this->expBarInside.setFillColor(sf::Color(20, 250, 20, 200));
	this->expBarInside.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setPosition(this->expBarInside.getPosition().x + 10.f, this->expBarInside.getPosition().y + 5.f);
	this->expBarText.setCharacterSize(12);
}

void PlayerGUI::initLevelDisplay()
{
	float width = 60.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;
	//this->levelDisplayMaxWidth = width;

	this->levelDisplayBack.setSize(sf::Vector2f(width, height));
	this->levelDisplayBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelDisplayBack.setPosition(x, y);

	/*this->levelDisplayInside.setSize(sf::Vector2f(width, height));
	this->levelDisplayInside.setFillColor(sf::Color(20, 250, 20, 200));
	this->levelDisplayInside.setPosition(this->levelDisplayBack.getPosition());*/

	this->levelDisplayText.setFont(this->font);
	this->levelDisplayText.setPosition(this->levelDisplayBack.getPosition().x + 10.f, this->levelDisplayBack.getPosition().y + 10.f);
	this->levelDisplayText.setCharacterSize(14);
}

//Constructor/Destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();
	this->initHpBar();
	this->initExpBar();
	this->initLevelDisplay();
}

PlayerGUI::~PlayerGUI()
{

}

//Functions
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

void PlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) /
		static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInside.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInside.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateLevelDisplay()
{
	this->levelDisplayString = "L " + std::to_string(this->player->getAttributeComponent()->level);
	this->levelDisplayText.setString(this->levelDisplayString);
}

void PlayerGUI::update(const float& deltaTime)
{
	this->updateHpBar();
	this->updateExpBar();
	this->updateLevelDisplay();
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInside);
	target.draw(this->hpBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInside);
	target.draw(this->expBarText);
}

void PlayerGUI::renderLevelDisplay(sf::RenderTarget& target)
{
	target.draw(this->levelDisplayBack);
	target.draw(this->levelDisplayText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderExpBar(target);
	this->renderLevelDisplay(target);
}