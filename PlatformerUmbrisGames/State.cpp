#include "stdafx.h"
#include "State.hpp"

//Constructors/Destructors
State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->inputTime = 0.f;
	this->inputTimeMax = 10.f;
	this->gridSize = state_data->gridSize;
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

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = 
		sf::Vector2i(
			static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
		);

	this->window->setView(this->window->getDefaultView());
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
