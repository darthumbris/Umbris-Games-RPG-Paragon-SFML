#pragma once

#include "State.hpp"

class BattleState :
    public State
{
private:


	//void initDeferredRender();
	//void initView();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initShaders();
	void initBattleGUI();

public:
    BattleState(StateData* state_data);
    virtual ~BattleState();

	//Functions
	void updateInput(const float& deltaTime);
	void updateBattleGUI(const float& deltaTime);

	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

