#include "Balloon.h"
//Balloon::Balloon() :pos(), vel(), w(), velocidad(), globo(), explotado(), instPinchazo(), game() {}

Balloon::Balloon(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* balloon_, Game* game_): pos(pos_), vel(vel_), width(width_), height(height_), balloon(balloon_), game(game_)
{
}

Balloon::~Balloon()
{
}

void Balloon::render() const
{
	if (!pinchado) {
		//balloon->renderFrame(SDL_Rect{ pos.getX(), pos.getY(), width, height }, SDL_FLIP_NONE);
	}
}

bool Balloon::update() const
{
	return false;
}
