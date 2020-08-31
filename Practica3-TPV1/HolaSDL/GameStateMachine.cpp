#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(SDLApplication* game): game(game)
{

}

GameState* GameStateMachine::currentState()
{
    return states.top();
}

void GameStateMachine::pushState(GameState* pState)
{
    states.push(pState);
}

void GameStateMachine::popState()
{
	if (!states.empty())
	{
		states.pop();

	}
}

void GameStateMachine::changeState(GameState* pState)
{
	if (!states.empty())
	{
		states.pop();
	}
	states.push(pState);
}


void GameStateMachine::update()
{
	if (!states.empty())
	{
		states.top()->update();
	}
}

void GameStateMachine::render()
{
	if (!states.empty())
	{
		states.top()->render();
	}
}

void GameStateMachine::handleEvent(SDL_Event event)
{
	if (!states.empty())
	{
		states.top()->handleEvent(event);
	}
}
