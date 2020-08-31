#pragma once
#include "GameState.h"
//#include "WinGameOver.h"
class MenuButton;
class EndState : public GameState
{
private:
	MenuButton* exitButton;
	MenuButton* menuButton;
public:
	EndState(SDLApplication* game);
};