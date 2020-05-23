#include "stdafx.h"
#include "BattleState.hpp"
using namespace gui;

//Initializers
void BattleState::initBackground()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;


	//Init background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)));

	/*Check for what area it is to change which background is loaded
	!!!!!
	!!!!!
	Check for what area it is to change which background is loaded
	*/

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg_forest1.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void BattleState::initKeybinds()
{
	
}

void BattleState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::MAINMENUSTATE::Could not load font");
	}
}

void BattleState::initEnemies()
{
	/*
	* Here check which area it is.
	Load a file with the enemies of that area
	then pick an amount of enemies 1-5
	then pick for that amount enemies out of that list
	*/
}

void BattleState::initEnemyData()
{
	/*
	Load in the data for the enemies determined in the previous function
	and scale them with a random level between certain value set in the file
	for that area.
	*/
}

void BattleState::initTextures()
{
	/*
	Load the textures of the enemies previous determined and the players
	*/
}

void BattleState::initShaders()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void BattleState::initBattleGUI()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//init background bar for buttons
	this->battleGUI.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height) / 4));

	this->battleGUI.setFillColor(sf::Color(100, 100, 100, 250));
	this->battleGUI.setPosition(sf::Vector2f(0, gui::p2pY(75.f, vm)));

	//init buttons
	this->buttons["RUN"] = new Button(
		gui::p2pX(31.7f, vm), gui::p2pY(90.0f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Run", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ATTACK"] = new Button(
		gui::p2pX(8.3f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Fight", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ITEM"] = new Button(
		gui::p2pX(8.3f, vm), gui::p2pY(90.0f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Items", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["DEFEND"] = new Button(
		gui::p2pX(20.0f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Defend", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["MAGIC"] = new Button(
		gui::p2pX(31.7f, vm), gui::p2pY(83.3f, vm),
		gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm),
		&this->font, "Magic", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void BattleState::initBattlePlayerGUI()
{
	this->battlePlayerGUI = new BattlePlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

BattleState::BattleState(Player* player, StateData* state_data)
	:	State (state_data)
{
	this->player = player;
	
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initEnemies();
	this->initEnemyData();
	this->initTextures();
	this->initShaders();
	this->initBattleGUI();
	this->initBattlePlayerGUI();
}

BattleState::~BattleState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->battlePlayerGUI;
}

//Functions
void BattleState::updateInput(const float& deltaTime)
{
}

void BattleState::updateBattleGUI(const float& deltaTime)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	
	//quit the battlestate
	if (this->buttons["RUN"]->isPressed())
	{
		this->endState();
	}
}

void BattleState::updateBattlePlayerGUI(const float& deltaTime)
{
	this->battlePlayerGUI->update(deltaTime);
}

void BattleState::calculateBattle()
{
	/*
	update player and enemy health
	update player exp after all enemies dead

	after all enemies dead enter Reward state or do that here?
	*/
}

void BattleState::chechRunPossibility()
{
	/*
	check for the possibilit of running from the battle
	determined by maybe certain attributes
	if boss, running impossible
	*/
}

void BattleState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
	this->updateBattleGUI(deltaTime);
	this->updateBattlePlayerGUI(deltaTime);
}

void BattleState::renderBattleGUI(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void BattleState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->battleGUI);
	this->battlePlayerGUI->render(*target);
	this->renderBattleGUI(*target);
}

