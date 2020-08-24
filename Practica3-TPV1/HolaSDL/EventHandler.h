#pragma once
#include "checkML.h"
#include "Game.h"

class EventHandler
{
public:
	EventHandler() {};
	~EventHandler() {};
	virtual void handleEvent(SDL_Event& event) = 0;
};

