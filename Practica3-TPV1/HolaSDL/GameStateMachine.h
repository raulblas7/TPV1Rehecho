#pragma once
#include <stack>
#include "GameState.h"
#include "SDLApplication.h"

using namespace std;

class GameStateMachine
{
private:
	stack<GameState*> states;
	SDLApplication* game;
public:
	GameStateMachine(SDLApplication* game);
	GameState* currentState();
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();
	void handleEvent(SDL_Event event);
};

