#pragma once

#include "MainMenuState.hpp"

class Game
{
private:
	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = false;
			this->verticalSync = false;
			this->framerateLimit = 60;
			this->contextSettings.antialiasingLevel = 0;
			this->videoModes = sf::VideoMode::getFullscreenModes();
			this->title = "DEFAULT";
		}

		//Variables
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned framerateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoModes;

		//Functions
		void saveToFile(const std::string path)
		{
			std::ofstream ofs(path);

			if (ofs.is_open())
			{
				ofs << this->title;
				ofs << this->resolution.width << " " << this->resolution.height;
				ofs << this->fullscreen;
				ofs << this->framerateLimit;
				ofs << this->verticalSync;
				ofs << this->contextSettings.antialiasingLevel;
			}

			ofs.close();

			std::cout << "saving graphics settings" << "\n";
		}

		void loadFromFile(const std::string path)
		{
			std::ifstream ifs(path);

			if (ifs.is_open())
			{
				std::getline(ifs, this->title);
				ifs >> this->resolution.width >> this->resolution.height;
				ifs >> this->fullscreen;
				ifs >> this->framerateLimit;
				ifs >> this->verticalSync;
				ifs >> this->contextSettings.antialiasingLevel;
			}

			ifs.close();

			std::cout << "loading graphics settings" << "\n";
		}
	};

	//Variables
	GraphicsSettings gfxSettings;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	
	sf::Clock dtClock;
	float deltaTime;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();
	
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update functions
	void updateDt();
	void handleEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

