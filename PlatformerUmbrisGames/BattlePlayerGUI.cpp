#include "stdafx.h"
#include "BattlePlayerGUI.hpp"

//initializers
void BattlePlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/slkscr.ttf");
}

void BattlePlayerGUI::initHpBar()
{

	float width = gui::p2pX(10.f, this->vm);
	float height = gui::p2pY(2.f, this->vm);
	float x = gui::p2pX(45.f, this->vm);
	float y = gui::p2pY(75.f, this->vm);
	
	this->hpBarConvex.setPointCount(4);
	this->hpBarConvex.setPoint(0, sf::Vector2f(0.f, height - gui::p2pY(1.f, this->vm)));
	this->hpBarConvex.setPoint(1, sf::Vector2f(width, height - gui::p2pY(1.f, this->vm)));
	this->hpBarConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->hpBarConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->hpBarConvex.setFillColor(sf::Color(250, 10, 10, 250));
	this->hpBarConvex.setOutlineThickness(1.5f);
	this->hpBarConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->hpBarConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(.5f, this->vm));

	this->hpBarBackConvex.setPointCount(4);
	this->hpBarBackConvex.setPoint(0, sf::Vector2f(0.3f, height - gui::p2pY(1.2f, this->vm)));
	this->hpBarBackConvex.setPoint(1, sf::Vector2f(width + gui::p2pX(.3f, this->vm), height - gui::p2pY(1.2f, this->vm)));
	this->hpBarBackConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->hpBarBackConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->hpBarBackConvex.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBackConvex.setOutlineThickness(1.5f);
	this->hpBarBackConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->hpBarBackConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(1.f, this->vm));

	//the actual value of the hp
	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(
		x + gui::p2pX(8.5f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.2f, this->vm)
	);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 140));
	this->hpBarText.setOutlineColor(sf::Color(50,50,50,200));
	this->hpBarText.setOutlineThickness(1.f);

	//the letters to clarify it's the hp bar
	this->hpText.setFont(this->font);
	this->hpText.setPosition(
		x + gui::p2pX(1.f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.f, this->vm)
	);
	this->hpText.setCharacterSize(gui::calcCharSize(this->vm, 160));
	this->hpText.setFillColor(sf::Color(85, 170, 223, 255));
	this->hpText.setOutlineColor(sf::Color(25, 50, 70, 255));
	this->hpText.setOutlineThickness(1.f);
	this->hpText.setString(sf::String("HP"));
}

void BattlePlayerGUI::initExpBar()
{
	float width = gui::p2pX(10.f, this->vm);
	float height = gui::p2pY(2.f, this->vm);
	float x = gui::p2pX(45.f, this->vm);
	float y = gui::p2pY(83.f, this->vm);

	this->expBarConvex.setPointCount(4);
	this->expBarConvex.setPoint(0, sf::Vector2f(0.f, height - gui::p2pY(1.f, this->vm)));
	this->expBarConvex.setPoint(1, sf::Vector2f(width, height - gui::p2pY(1.f, this->vm)));
	this->expBarConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->expBarConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->expBarConvex.setFillColor(sf::Color(10, 250, 10, 250));
	this->expBarConvex.setOutlineThickness(1.5f);
	this->expBarConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->expBarConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(.5f, this->vm));

	this->expBarBackConvex.setPointCount(4);
	this->expBarBackConvex.setPoint(0, sf::Vector2f(0.3f, height - gui::p2pY(1.2f, this->vm)));
	this->expBarBackConvex.setPoint(1, sf::Vector2f(width + gui::p2pX(.3f, this->vm), height - gui::p2pY(1.2f, this->vm)));
	this->expBarBackConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->expBarBackConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->expBarBackConvex.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBackConvex.setOutlineThickness(1.5f);
	this->expBarBackConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->expBarBackConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(1.f, this->vm));

	//the actual value of the exp
	this->expBarText.setFont(this->font);
	this->expBarText.setPosition(
		x + gui::p2pX(8.5f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.2f, this->vm)
	);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 140));
	this->expBarText.setOutlineColor(sf::Color(50, 50, 50, 200));
	this->expBarText.setOutlineThickness(1.f);

	//the letters to clarify it's the hp bar
	this->expText.setFont(this->font);
	this->expText.setPosition(
		x + gui::p2pX(1.f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.f, this->vm)
	);
	this->expText.setCharacterSize(gui::calcCharSize(this->vm, 160));
	this->expText.setFillColor(sf::Color(85, 170, 223, 255));
	this->expText.setOutlineColor(sf::Color(25, 50, 70, 255));
	this->expText.setOutlineThickness(1.f);
	this->expText.setString(sf::String("XP"));
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
	float width = gui::p2pX(10.f, this->vm);
	float height = gui::p2pY(2.f, this->vm);
	float x = gui::p2pX(45.f, this->vm);
	float y = gui::p2pY(79.f, this->vm);

	this->manaBarConvex.setPointCount(4);
	this->manaBarConvex.setPoint(0, sf::Vector2f(0.f, height - gui::p2pY(1.f, this->vm)));
	this->manaBarConvex.setPoint(1, sf::Vector2f(width, height - gui::p2pY(1.f, this->vm)));
	this->manaBarConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->manaBarConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->manaBarConvex.setFillColor(sf::Color(10, 10, 250, 250));
	this->manaBarConvex.setOutlineThickness(1.5f);
	this->manaBarConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->manaBarConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(.5f, this->vm));

	this->manaBarBackConvex.setPointCount(4);
	this->manaBarBackConvex.setPoint(0, sf::Vector2f(0.3f, height - gui::p2pY(1.2f, this->vm)));
	this->manaBarBackConvex.setPoint(1, sf::Vector2f(width + gui::p2pX(.3f, this->vm), height - gui::p2pY(1.2f, this->vm)));
	this->manaBarBackConvex.setPoint(2, sf::Vector2f(gui::p2pX(1.f, this->vm) + width, 0.f));
	this->manaBarBackConvex.setPoint(3, sf::Vector2f(gui::p2pX(1.f, this->vm), 0.f));
	this->manaBarBackConvex.setFillColor(sf::Color(50, 50, 50, 200));
	this->manaBarBackConvex.setOutlineThickness(1.5f);
	this->manaBarBackConvex.setOutlineColor(sf::Color(0, 0, 50, 255));
	this->manaBarBackConvex.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y + gui::p2pY(1.f, this->vm));

	//the actual value of the mana
	this->manaBarText.setFont(this->font);
	this->manaBarText.setPosition(
		x + gui::p2pX(8.5f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.2f, this->vm)
	);
	this->manaBarText.setCharacterSize(gui::calcCharSize(this->vm, 140));
	this->manaBarText.setOutlineColor(sf::Color(50, 50, 50, 200));
	this->manaBarText.setOutlineThickness(1.f);

	//the letters to clarify it's the mana bar
	this->manaText.setFont(this->font);
	this->manaText.setPosition(
		x + gui::p2pX(1.f, this->vm) + this->position * gui::p2pX(12.f, this->vm),
		y - gui::p2pY(1.f, this->vm)
	);
	this->manaText.setCharacterSize(gui::calcCharSize(this->vm, 160));
	this->manaText.setFillColor(sf::Color(85, 170, 223, 255));
	this->manaText.setOutlineColor(sf::Color(25, 50, 70, 255));
	this->manaText.setOutlineThickness(1.f);
	this->manaText.setString(sf::String("MP"));
}

void BattlePlayerGUI::initName()
{
	//here the name gets called and set a size and position etc and if it's active or not
	float width = gui::p2pX(4.6f, this->vm);
	float height = gui::p2pY(3.f, this->vm);
	float x = gui::p2pX(45.f, this->vm);
	float y = gui::p2pY(72.f, this->vm);

	this->nameRect.setSize(sf::Vector2f(width, height));
	this->nameRect.setFillColor(sf::Color(100, 100, 100, 100));
	this->nameRect.setPosition(x + this->position * gui::p2pX(12.f, this->vm), y);

	this->nameString = this->player->getName();
	this->nameText.setFont(this->font);
	this->nameText.setPosition(this->nameRect.getPosition().x + gui::p2pX(0.5f, this->vm),
								this->nameRect.getPosition().y
	);
	this->nameText.setCharacterSize(gui::calcCharSize(this->vm, 160));
	this->nameText.setOutlineColor(sf::Color(0, 0, 0, 255));
	this->nameText.setOutlineThickness(1.f);
	this->nameText.setString(this->nameString);
}

//Constructor/Destructor
BattlePlayerGUI::BattlePlayerGUI(Player* player, sf::VideoMode& vm, unsigned position)
	: vm(vm)
{
	this->player = player;
	this->position = position;

	this->initFont();
	this->initHpBar();
	this->initExpBar();
	this->initManaBar();
	this->initName();
	//this->initLevelDisplay();
}

BattlePlayerGUI::~BattlePlayerGUI()
{

}

//Functions
void BattlePlayerGUI::updateHpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) /
		static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarConvex.setScale(sf::Vector2f(percent , 1.f));

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) ;
	this->hpBarText.setString(this->hpBarString);
}

void BattlePlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) /
		static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarConvex.setScale(sf::Vector2f(percent, 1.f));

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp);
	this->expBarText.setString(this->expBarString);
}

void BattlePlayerGUI::updateManaBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->mana) /
		static_cast<float>(this->player->getAttributeComponent()->manaMax);

	this->manaBarConvex.setScale(sf::Vector2f(percent, 1.f));

	this->manaBarString = std::to_string(this->player->getAttributeComponent()->mana);
	this->manaBarText.setString(this->manaBarString);
}

void BattlePlayerGUI::updateLevelDisplay()
{
	this->levelDisplayString = "L " + std::to_string(this->player->getAttributeComponent()->level);
	this->levelDisplayText.setString(this->levelDisplayString);
}

void BattlePlayerGUI::updateName()
{
	//here the name gets updated if it's active or not
}

void BattlePlayerGUI::update(const float& deltaTime)
{
	this->updateHpBar();
	
	// exp only needs to be updated at the end of the battle
	this->updateExpBar();

	this->updateManaBar();
	this->updateName();
	//this->updateLevelDisplay();
}

void BattlePlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBackConvex);
	target.draw(this->hpBarConvex);
	target.draw(this->hpBarText);
	target.draw(this->hpText);
	
	
}

void BattlePlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBackConvex);
	target.draw(this->expBarConvex);
	target.draw(this->expBarText);
	target.draw(this->expText);
}

void BattlePlayerGUI::renderManaBar(sf::RenderTarget& target)
{
	target.draw(this->manaBarBackConvex);
	target.draw(this->manaBarConvex);
	target.draw(this->manaBarText);
	target.draw(this->manaText);
}

void BattlePlayerGUI::renderLevelDisplay(sf::RenderTarget& target)
{
	target.draw(this->levelDisplayBack);
	target.draw(this->levelDisplayText);
}

void BattlePlayerGUI::renderName(sf::RenderTarget& target)
{
	//here the name gets drawn
	//target.draw(this->nameRect);
	target.draw(this->nameText);
}

void BattlePlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderExpBar(target);
	this->renderManaBar(target);
	this->renderName(target);
	//this->renderLevelDisplay(target);
}