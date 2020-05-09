#pragma once

#include "Player.hpp"
#include "GraphicsSettings.hpp"

class Player;
class GraphicsSettings;
class State;

class StateData 
{
public:
	//Constructor of statedata
	StateData() {};

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map < std::string,	int >* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:
	

protected:
	//Variables
	StateData* stateData;
	std::stack<State*>* states;//A pointer to a stack of State pointers
	sf::RenderWindow* window; //Waarin er iets wordt gerendered
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float inputTime;
	float inputTimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	//function to initialize the keybindings
	virtual void initKeybinds() = 0;

public:
	//Constructor
	State(StateData* state_data);
	//Destructor
	virtual ~State();

	//Accessor

	//function to see if the state needs to quit
	const bool& getQuit() const;
	//function that handles the input time so that a key doesn't get pressed 100s of times per second
	const bool getInputTime();

	//Functions

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = nullptr);
	virtual void updateInputTime(const float& deltaTime);
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0; 

	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	//pure virtual (door de = 0) daarom moet elke class die inherit hiervan een update en render etc hebben
};

