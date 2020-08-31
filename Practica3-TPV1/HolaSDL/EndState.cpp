#include "EndState.h"
#include <iostream>
#include "checkML.h"
#include "MenuButton.h"

EndState::EndState(SDLApplication* game) : GameState(game) {
	exitButton = new MenuButton(Point2D(300, 400), 100, 100, game->GetTexture(14), this, ExitCallback);
	menuButton = new MenuButton(Point2D(300, 250), 100, 100, game->GetTexture(12), this, MenuCallback);
	objects.push_back(exitButton);
	events.push_back(exitButton);
	objects.push_back(menuButton);
	events.push_back(menuButton);
}
