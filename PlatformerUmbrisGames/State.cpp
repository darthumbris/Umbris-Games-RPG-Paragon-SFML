#include "stdafx.h"
#include "State.hpp"

//Constructors/Destructors
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
	std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
	this->inputTime = 0.f;
	this->inputTimeMax = 10.f;
}

State::~State()
{

}

//Accessor
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getInputTime()
{
	if (this->inputTime >= this->inputTimeMax)
	{
		this->inputTime = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateInputTime(const float& deltaTime)
{
	if (this->inputTime < this->inputTimeMax)
		this->inputTime += 50.f * deltaTime;
}

void State::updateInput(const float& deltaTime)
{

}

void State::update(const float &deltaTime)
{

}

void State::render(sf::RenderTarget* target)
{

}
