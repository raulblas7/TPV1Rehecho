#pragma once

#include "SDLApplication.h"
#include "EventHandler.h"
#include "Vector2D.h"
#include "SDLGameObject.h"

using CallBackOnClick = void(SDLApplication* game);
//callbacks para el menu principal
void PlayCallback(SDLApplication* game);
void LoadCallback(SDLApplication* game);
void ExitCallback(SDLApplication* game);
//callback para el juego
void PauseCallback(SDLApplication* game);
//callbacks para el menu pausa
void ContinuePlayingCallback(SDLApplication* game);
void SaveCallback(SDLApplication* game);
void MenuCallback(SDLApplication* game);


class MenuButton : public SDLGameObject, public EventHandler
{
private:
	CallBackOnClick* callbackbutton;
public:
	MenuButton(Point2D pos, uint w, uint h, Texture* texture, GameState* state, CallBackOnClick* call);
	virtual void render();
	virtual void handleEvent(SDL_Event& event);
};

