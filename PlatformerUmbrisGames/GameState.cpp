#include "stdafx.h"
#include "GameState.hpp"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
		0, 
		0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2.f),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2.f)
		)
	);
}

//Initializers
void GameState::initKeybinds()
{
	
	//Hier bind ie de keys aan de acties dus bv W op UP etc.
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("Error::MAINMENUSTATE::Could not load font");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player_spritesheet.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("EXIT_STATE", gui::p2pY(83.3f, vm), gui::p2pX(12.9f, vm), gui::p2pY(6.3f, vm), gui::calcCharSize(vm, 50), "Quit" );
}

void GameState::initShaders()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers()
{
	//Initialize the main player, initalize companions when certain conditions are met 
	//and then recall this?
	this->player = new Player(400, 200, this->textures["PLAYER_SHEET"], "Jacen");
}

void GameState::initPlayerGUI()
{
	//Shows the current level, hp etc just for debug for now, maybe nice to have or 
	//just put into the menu screen?
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("Map_Saves/map_data.map");
}


//Constructors/destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();

	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
}

//Functions
void GameState::updateView(const float& deltaTime)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width /2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f));

	if (this->tileMap->getMaxSizeGridF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeGridF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeGridF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	if (this->tileMap->getMaxSizeGridF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeGridF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeGridF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getInputTime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}


void GameState::updatePlayerInput(const float& deltaTime)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0.f, deltaTime);
		//Debug test for exp
		if (this->getInputTime())
			this->player->loseExp(10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0.f, deltaTime);
		//Debug test for exp
		if (this->getInputTime())
			this->player->gainExp(10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, deltaTime);
		//Debug test for health
		if (this->getInputTime())
			this->player->gainHp(1);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, deltaTime);
		//Debug test for health
		if(this->getInputTime())
			this->player->loseHp(1);
	}

	//Enter Battle debug key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BATTLE"))))
	{
		this->states->push(new BattleState(this->player, this->stateData));
		std::cout << "Entering Battle" << "\n";
	}
}

void GameState::updatePlayerGUI(const float& deltaTime)
{
	this->playerGUI->update(deltaTime);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT_STATE") && this->getInputTime())
		this->endState();
}

void GameState::updateTileMap(const float& deltaTime)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, deltaTime);
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions(&this->view); //Needs to work in paused
	this->updateInput(deltaTime);
	this->updateInputTime(deltaTime);


	if (!this->paused) //Unpaused Update
	{
		this->updateView(deltaTime);
		
		this->updatePlayerInput(deltaTime); //Needs to work in paused

		this->updateTileMap(deltaTime);

		this->player->update(deltaTime, this->mousePosView);
		
		this->updatePlayerGUI(deltaTime);
	}
	else //Paused Update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	//Map rendering (needs to be optimized so that it only renders the viewscreen and
	// not the whole map
	this->renderTexture.setView(this->view);
	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition, 
		&this->coreShader, 
		this->player->getCenter(),
		false);

	this->player->render(this->renderTexture, &this->coreShader, false);

	this->tileMap->renderDeferred(this->renderTexture, &this->coreShader, this->player->getCenter());
	
	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) // Pause Menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Final Render!
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
