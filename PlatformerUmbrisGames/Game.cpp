#include "stdafx.h"
#include "Game.hpp"

//Static Functions

//Inititalize functions
void Game::initVariables()
{
    this->window = nullptr;
    this->deltaTime = 0.f;
    this->gridSize = 50.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
    /*Create a SFML window*/
   
    if(this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Fullscreen, 
            this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
    //voor welke int een key is check definition sf::Keyboard
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
    
    //debug remve later
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStataData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}


void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}

//Constructors/Destructors
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStataData();
    this->initStates();
    
}

Game::~Game()
{
	delete this->window;

    //hier wordt alle states leeggemaakt en verwijdert
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
     
}

//Functions
void Game::endApplication()
{
    std::cout << "ending application" << "\n";
}

void Game::updateDt()
{
   /*hier wordt de deltatime geupdate met de tijd die duurt voor
   een update en render van 1 frame*/
    this->deltaTime = this->dtClock.restart().asSeconds();
}

void Game::handleEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->handleEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->deltaTime);

        //Hier checkt ie of je wil quitten, zo ja dan gaat ie uit die state
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Application end
    else 
    {
        this->endApplication();
        this->window->close();
    }
    

}

void Game::render()
{
    this->window->clear();

    //Render Items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
