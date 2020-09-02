#include "MenuButton.h"
#include "SDLGameObject.h"

MenuButton::MenuButton(Point2D pos, uint w, uint h, Texture* texture, GameState* state, CallBackOnClick* call)
:SDLGameObject(pos,w,h,texture,state),callbackbutton(call)
{

}

void PlayCallback(SDLApplication* game)
{
	game->Play();
}

void LoadCallback(SDLApplication* game)
{
	game->Load();
}

void ExitCallback(SDLApplication* game)
{
	game->Exit();
}

void PauseCallback(SDLApplication* game)
{
	game->Pause();
}

void ContinuePlayingCallback(SDLApplication* game)
{
	game->ContinuePlaying();
}

void SaveCallback(SDLApplication* game)
{
	game->Save();
}

void MenuCallback(SDLApplication* game)
{
	game->MainMenu();
}


void MenuButton::render()
{
	SDLGameObject::render();
}

void MenuButton::handleEvent(SDL_Event& event)
{
	if ((event.type == SDL_MOUSEBUTTONUP) && (event.button.button == SDL_BUTTON_LEFT)) {
		SDL_Point mousePoint = { event.button.x, event.button.y };
		SDL_Rect punto = { (int)pos.getX(), (int)pos.getY(), width, height };
	
		if (SDL_PointInRect(&mousePoint, &punto)) {
			callbackbutton(state->giveMeGame());
		}
	}
}
