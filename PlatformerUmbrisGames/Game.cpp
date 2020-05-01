#include "stdafx.h"
#include "Game.hpp"

//Static Functions

//Inititalize functions
void Game::initVariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->deltaTime = 0.f;
}


void Game::initWindow()
{
    /*Create a window with settings from a window.ini file*/
    //ifstream  is in file stream
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    windowSettings.antialiasingLevel = antialiasing_level;

    if(this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, 
            sf::Style::Titlebar | sf::Style::Close, windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    
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

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Constructors/Destructors
Game::Game()
{
    this->initWindow();
    this->initKeys();
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
