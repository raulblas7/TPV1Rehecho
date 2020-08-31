#include "MainMenuState.h"
#include "MenuButton.h"

MainMenuState::MainMenuState(SDLApplication* game):GameState(game)
{
	playButton = new MenuButton(Point2D(300, 100), 100, 100, game->GetTexture(9), this, PlayCallback);
	loadButton = new MenuButton(Point2D(300, 250), 100, 100, game->GetTexture(11), this, LoadCallback);
	exitButton = new MenuButton(Point2D(300, 400), 100, 100, game->GetTexture(14), this, ExitCallback);
	objects.push_back(playButton);
	objects.push_back(loadButton);
	objects.push_back(exitButton);
	events.push_back(playButton);
	events.push_back(loadButton);
	events.push_back(exitButton);
}


