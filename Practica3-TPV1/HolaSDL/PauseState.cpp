#include "PauseState.h"
#include "checkML.h"
#include  "MenuButton.h"

PauseState::PauseState(SDLApplication* game) :GameState(game) {
	
    insertObject(new MenuButton(Point2D(300, 100), 100, 100, game->GetTexture(13), this, SaveCallback));
	insertObject(new MenuButton(Point2D(300, 250), 100, 100, game->GetTexture(12), this, MenuCallback));
	insertObject(new MenuButton(Point2D(300, 400), 100, 100, game->GetTexture(9), this, ContinuePlayingCallback));

}



