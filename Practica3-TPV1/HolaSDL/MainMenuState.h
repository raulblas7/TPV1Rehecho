#pragma once
#include "GameState.h"
class MenuButton;

class MainMenuState:public GameState
{

private:
	MenuButton* playButton;
	MenuButton* loadButton;
	MenuButton* exitButton;
public:
	MainMenuState(SDLApplication* game);

};

