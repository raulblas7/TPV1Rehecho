#include "Reward.h"

Reward::Reward(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* reward_, Texture* bubble_, Game* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, reward_, game_), row(row_), bubble(bubble_)
{
}

void Reward::render()
{
}

void Reward::update()
{
}

void Reward::handleEvents(SDL_Event& event)
{
}
