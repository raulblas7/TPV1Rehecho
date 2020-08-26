#include "ArrowsGameObject.h"

void ArrowsGameObject::render()
{
	texture->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}

void ArrowsGameObject::update()
{
	pos = pos + vel;
}

void ArrowsGameObject::setItList(list<GameObject*>::iterator i)
{
	it = i;
}
