#include "SDLGameObject.h"

void SDLGameObject::render()
{
	texture->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}
