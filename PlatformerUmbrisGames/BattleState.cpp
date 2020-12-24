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
	can be done using either giving the map type to the state or checking it here.
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
	
	probably using a switch case for where to load the enemy data from
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
	//maybe move this function to the battleplayer gui?
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//init background bar for buttons
	this->battleGUI.setSize(sf::Vector2f(
		gui::p2pX(35.f, vm),
		gui::p2pY(25.f, vm)));

	this->battleGUI.setFillColor(sf::Color(100, 100, 100, 255));
	this->battleGUI.setOutlineThickness(gui::p2pX(0.3f, vm));
	this->battleGUI.setOutlineColor(sf::Color(200,200,200,255));
	this->battleGUI.setPosition(sf::Vector2f(gui::p2pX(7.5f, vm), gui::p2pY(70.f, vm)));

	//init buttons
	//id = 0 for centre alignment, 1 for left alignment and 2 for right alignment

	this->buttons["FIGHT"] = new Button(
		gui::p2pX(12.f, vm), gui::p2pY(72.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Fight", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);

	this->buttons["MAGIC"] = new Button(
		gui::p2pX(12.f, vm), gui::p2pY(79.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Magic", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);

	this->buttons["MISC"] = new Button(
		gui::p2pX(12.f, vm), gui::p2pY(86.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Miscellany", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);

	this->buttons["DEFEND"] = new Button(
		gui::p2pX(32.0f, vm), gui::p2pY(72.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Defend", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);

	this->buttons["ITEM"] = new Button(
		gui::p2pX(32.f, vm), gui::p2pY(79.0f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Items", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);

	this->buttons["RUN"] = new Button(
		gui::p2pX(32.f, vm), gui::p2pY(86.0f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Run", gui::calcCharSize(vm, 50),
		sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 1);


	//init Player and enemy position for battlestate
	this->playerTempX = gui::p2pX(90.f, vm);
	this->playerTempY = gui::p2pY(50.f, vm);

	this->playerProtagonist->setPosition(this->playerTempX, this->playerTempY);
}

void BattleState::initBattlePlayerGUI()
{
	//for player 1 for now, need to add functionality to add multiple players
	//this->battlePlayerGUI = new BattlePlayerGUI(this->playerProtagonist, this->stateData->gfxSettings->resolution);
	this->battlePlayerGUI = new BattlePlayerGUI(this->playerProtagonist, this->stateData->gfxSettings->resolution, 0);
	this->battlePlayerGUI1 = new BattlePlayerGUI(this->playerProtagonist, this->stateData->gfxSettings->resolution, 1);
	this->battlePlayerGUI2 = new BattlePlayerGUI(this->playerProtagonist, this->stateData->gfxSettings->resolution, 2);
	this->battlePlayerGUI3 = new BattlePlayerGUI(this->playerProtagonist, this->stateData->gfxSettings->resolution, 3);
}

BattleState::BattleState(Player* player, StateData* state_data)
	:	State (state_data)
{
	this->playerProtagonist = player;
	this->worldX = player->getPosition().x;
	this->worldY = player->getPosition().y;
	this->fightButtonStatus = false;
	this->itemButtonStatus = false;
	this->magicButtonStatus = false;
	this->activePlayer = 0;

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
	delete this->battlePlayerGUI1;
	delete this->battlePlayerGUI2;
	delete this->battlePlayerGUI3;

	//Alleen voor de protagonist nodig niet voor de companions (want die hebben geen representatie op
	//de map alleen in combat en in de interface.
	this->playerProtagonist->setPosition(worldX, worldY);
}

//Accessors
const bool BattleState::checkRunPossibility()
{
	/*
	check for the possibilit of running from the battle
	determined by maybe certain attributes of player and enemies
	if boss, running impossible
	*/
	return true;
}

const bool BattleState::checkFightActive()
{
	if (this->buttons["FIGHT"]->isPressed())
	{
		return true;
	}
	else
		return false;
}

const bool BattleState::checkItemActive()
{
	if (this->buttons["ITEM"]->isPressed())
	{
		return true;
	}
	else
		return false;
}

const bool BattleState::checkMagicActive()
{
	if (this->buttons["MAGIC"]->isPressed())
	{
		return true;
	}
	else
		return false;
}

const int BattleState::checkEnemySelected()
{
	/*if ()
	{
		return 1;
	}
	else 
		return 0;
	*/
	return 0;
}

const unsigned BattleState::checkActivePlayer()
{
	return this->activePlayer;
}

//Functions
void BattleState::updateInput(const float& deltaTime)
{
	if (this->checkFightActive())
	{
		this->fightButtonStatus = true;
		this->itemButtonStatus = false;
		this->magicButtonStatus = false;
	}

	if (this->checkItemActive())
	{
		this->fightButtonStatus = false;
		this->itemButtonStatus = true;
		this->magicButtonStatus = false;
	}

	if (this->checkMagicActive())
	{
		this->fightButtonStatus = false;
		this->itemButtonStatus = false;
		this->magicButtonStatus = true;
	}
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
		this->checkRunPossibility();
		this->endState();
	}

	if (this->fightButtonStatus)
	{
		std::cout << "Fight pressed" << "\n";
		std::cout << "Showing possible targets" << "\n";

		//if target pressed ->
		this->fightButtonStatus = false;
	}
	

	this->playerProtagonist->setPosition(this->playerTempX, this->playerTempY);
}

void BattleState::updateBattlePlayerGUI(const float& deltaTime)
{
	this->battlePlayerGUI->update(deltaTime);
	this->battlePlayerGUI1->update(deltaTime);
	this->battlePlayerGUI2->update(deltaTime);
	this->battlePlayerGUI3->update(deltaTime);
}

void BattleState::calculateBattle()
{
	/*
	update player and enemy health
	update player exp after all enemies dead

	after all enemies dead enter Reward state or do that here?
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
	this->playerProtagonist->render(*target);
	this->battlePlayerGUI->render(*target);
	this->battlePlayerGUI1->render(*target);
	this->battlePlayerGUI2->render(*target);
	this->battlePlayerGUI3->render(*target);
	this->renderBattleGUI(*target);
}

