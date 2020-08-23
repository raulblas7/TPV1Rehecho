#include "Arrow.h"

Arrow::Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_) : pos(pos_), vel(vel_), width(width_), height(height_), arrow(arrow_)
{
	
}

Arrow::~Arrow()
{
	/*delete rect;
	rect = nullptr;*/
}

void Arrow::render() 
{
	arrow->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}

bool Arrow::update()
{
	pos = pos + vel;
	return pos.getX() >= 800;
}
