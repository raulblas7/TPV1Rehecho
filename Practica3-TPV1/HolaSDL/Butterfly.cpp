#include "Butterfly.h"

Butterfly::Butterfly(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* butterfly_, Game* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, butterfly_, game_), row(row_)
{
}

void Butterfly::render()
{
}

void Butterfly::update()
{
}
