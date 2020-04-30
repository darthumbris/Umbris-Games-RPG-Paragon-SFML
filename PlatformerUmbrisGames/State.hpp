#pragma once

#include "Player.hpp"

class State
{
private:
	

protected:
	//Variables
	std::stack<State*>* states;//A pointer to a stack of State pointers
	sf::RenderWindow* window; //Waarin er iets wordt gerendered
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float inputTime;
	float inputTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	//Constructors/Destructors
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
		std::stack<State*>* states);
	virtual ~State();

	//Accessor
	const bool& getQuit() const;
	const bool getInputTime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateInputTime(const float& deltaTime);
	virtual void updateInput(const float& deltaTime) = 0;
	//pure virtual (door de = 0) daarom moet elke class die inherit hiervan een update en render etc hebben
	virtual void update(const float& deltaTime) = 0; 
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

