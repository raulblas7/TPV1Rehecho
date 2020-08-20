#include "Arrow.h"

Arrow::Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_) : pos(pos_), vel(vel_), width(width_), height(height_), arrow(arrow_)
{
}

Arrow::~Arrow()
{

}

void Arrow::render() const
{
	arrow->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}

bool Arrow::update() const
{
	return false;
}
