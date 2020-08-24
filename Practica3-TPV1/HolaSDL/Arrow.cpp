#include "Arrow.h"

Arrow::Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, Game* game_)
	: ArrowsGameObject(pos_, vel_,width_, height_,arrow_, game_)
{
}

Arrow::~Arrow()
{
	
}

void Arrow::render() 
{
	arrow->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}

void Arrow::update()
{
	pos = pos + vel;
	//return pos.getX() >= 800;
}
