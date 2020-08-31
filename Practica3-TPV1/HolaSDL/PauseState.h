#pragma once
#include "GameState.h"
class MenuButton;

class PauseState :public GameState
{
public:
	PauseState(SDLApplication* game);
	~PauseState() {};
};

