#include "stdafx.h"
#include "GraphicsSettings.hpp"

//Constructor
GraphicsSettings::GraphicsSettings()
{
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->framerateLimit = 60;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
	this->title = "DEFAULT";
}


//Functions
void GraphicsSettings::saveToFile(const std::string path)
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

void GraphicsSettings::loadFromFile(const std::string path)
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
