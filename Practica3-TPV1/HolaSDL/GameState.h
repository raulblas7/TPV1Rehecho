#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "SDLGameObject.h"

class SDLApplication;
class MenuButton;

class GameState
{
protected:
	list<GameObject*>  objects;
	list<EventHandler*> events;
	SDLApplication* game;
public:
	GameState(SDLApplication* game);
	~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event& event);
	virtual SDLApplication* giveMeGame() { return game; };
	void insertObject(MenuButton* ob);
};

