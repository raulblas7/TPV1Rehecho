#include "GameState.h"
#include "MenuButton.h"
#include "checkML.h"

GameState::GameState(SDLApplication* _game) : game(_game) {};

GameState::~GameState() {
	for (auto ob: objects)
	{
		delete ob;
	}
	objects.clear();
	events.clear();
}

void GameState::update() {
	for (auto ob : objects)
	{
		ob->update();
	}
}

void GameState::render() {
	for (auto ob : objects)
	{
		ob->render();
	}
}

void GameState::handleEvent(SDL_Event& event) {
	for (auto ob : events)
	{
		ob->handleEvent(event);
	}
}

void GameState::insertObject(MenuButton* ob)
{
	auto it = objects.insert(objects.end(), ob);
	events.push_back(ob);
	ob->setItList(it);
}
