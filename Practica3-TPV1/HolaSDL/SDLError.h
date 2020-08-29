#pragma once

#include "ArrowsError.h";
#include "Game.h";
#include <string>

class SDLError :public ArrowsError
{
public:
	SDLError() : ArrowsError(SDL_GetError()) {};
};

