#include "stdafx.h"
#include "BattlePlayerGUI.hpp"

//initializers
void BattlePlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/slkscr.ttf");
}

void BattlePlayerGUI::initHpBar()
{

	float width = gui::p2pX(23.4f, this->vm);
	float height = gui::p2pY(3.5f, this->vm);
	float x = gui::p2pX(60.f, this->vm);
	float y = gui::p2pY(83.3f, this->vm);
	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInside.setSize(sf::Vector2f(width, height));
	this->hpBarInside.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInside.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(
		this->hpBarInside.getPosition().x + gui::p2pX(0.8f, this->vm),
		this->hpBarInside.getPosition().y + gui::p2pY(0.7f, this->vm)
	);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 160));
}

void BattlePlayerGUI::initExpBar()
{
	float width = gui::p2pX(15.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(60.f, this->vm);
	float y = gui::p2pY(90.9f, this->vm);
	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInside.setSize(sf::Vector2f(width, height));
	this->expBarInside.setFillColor(sf::Color(20, 250, 20, 200));
	this->expBarInside.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setPosition(
		this->expBarInside.getPosition().x + gui::p2pX(0.8f, this->vm),
		this->expBarInside.getPosition().y + gui::p2pY(0.7f, this->vm)
	);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 160));
}

void BattlePlayerGUI::initLevelDisplay()
{
	float width = gui::p2pX(4.7f, this->vm);
	float height = gui::p2pY(6.9f, this->vm);
	float x = gui::p2pX(55.f, this->vm);
	float y = gui::p2pY(83.3f, this->vm);
	//this->levelDisplayMaxWidth = width;

	this->levelDisplayBack.setSize(sf::Vector2f(width, height));
	this->levelDisplayBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelDisplayBack.setPosition(x, y);

	/*this->levelDisplayInside.setSize(sf::Vector2f(width, height));
	this->levelDisplayInside.setFillColor(sf::Color(20, 250, 20, 200));
	this->levelDisplayInside.setPosition(this->levelDisplayBack.getPosition());*/

	this->levelDisplayText.setFont(this->font);
	this->levelDisplayText.setPosition(
		this->levelDisplayBack.getPosition().x + gui::p2pX(0.8f, this->vm),
		this->levelDisplayBack.getPosition().y + gui::p2pY(0.7f, this->vm)
	);
	this->levelDisplayText.setCharacterSize(gui::calcCharSize(this->vm, 120));
}

void BattlePlayerGUI::initManaBar()
{
	float width = gui::p2pX(23.4f, this->vm);
	float height = gui::p2pY(3.5f, this->vm);
	float x = gui::p2pX(60.f, this->vm);
	float y = gui::p2pY(87.1f, this->vm);
	this->manaBarMaxWidth = width;

	this->manaBarBack.setSize(sf::Vector2f(width, height));
	this->manaBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->manaBarBack.setPosition(x, y);

	this->manaBarInside.setSize(sf::Vector2f(width, height));
	this->manaBarInside.setFillColor(sf::Color(20, 20, 250, 200));
	this->manaBarInside.setPosition(this->manaBarBack.getPosition());

	this->manaBarText.setFont(this->font);
	this->manaBarText.setPosition(
		this->manaBarInside.getPosition().x + gui::p2pX(0.8f, this->vm),
		this->manaBarInside.getPosition().y + gui::p2pY(0.7f, this->vm)
	);
	this->manaBarText.setCharacterSize(gui::calcCharSize(this->vm, 160));
}

//Constructor/Destructor
BattlePlayerGUI::BattlePlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initHpBar();
	this->initExpBar();
	this->initManaBar();
	this->initLevelDisplay();
}

BattlePlayerGUI::~BattlePlayerGUI()
{

}

//Functions
void BattlePlayerGUI::updateHpBar()
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

void BattlePlayerGUI::updateExpBar()
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

void BattlePlayerGUI::updateManaBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->mana) /
		static_cast<float>(this->player->getAttributeComponent()->manaMax);

	this->manaBarInside.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->manaBarMaxWidth * percent)),
			this->manaBarInside.getSize().y
		)
	);

	this->manaBarString = std::to_string(this->player->getAttributeComponent()->mana) + "/" + std::to_string(this->player->getAttributeComponent()->manaMax);
	this->manaBarText.setString(this->manaBarString);
}

void BattlePlayerGUI::updateLevelDisplay()
{
	this->levelDisplayString = "L " + std::to_string(this->player->getAttributeComponent()->level);
	this->levelDisplayText.setString(this->levelDisplayString);
}

void BattlePlayerGUI::update(const float& deltaTime)
{
	this->updateHpBar();
	this->updateExpBar();
	this->updateManaBar();
	this->updateLevelDisplay();
}

void BattlePlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInside);
	target.draw(this->hpBarText);
}

void BattlePlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInside);
	target.draw(this->expBarText);
}

void BattlePlayerGUI::renderManaBar(sf::RenderTarget& target)
{
	target.draw(this->manaBarBack);
	target.draw(this->manaBarInside);
	target.draw(this->manaBarText);
}

void BattlePlayerGUI::renderLevelDisplay(sf::RenderTarget& target)
{
	target.draw(this->levelDisplayBack);
	target.draw(this->levelDisplayText);
}

void BattlePlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderExpBar(target);
	this->renderManaBar(target);
	this->renderLevelDisplay(target);
}