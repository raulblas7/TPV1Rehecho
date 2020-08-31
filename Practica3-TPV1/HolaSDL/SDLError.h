#pragma once

#include "ArrowsError.h";
#include "PlayState.h";
#include <string>

class SDLError :public ArrowsError
{
public:
	SDLError() : ArrowsError(SDL_GetError()) {};
};

