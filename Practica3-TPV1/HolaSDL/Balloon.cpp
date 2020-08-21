#include "Balloon.h"
//Balloon::Balloon() :pos(), vel(), w(), velocidad(), globo(), explotado(), instPinchazo(), game() {}

Balloon::Balloon(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* balloon_, Game* game_): pos(pos_), vel(vel_), width(width_), height(height_), row(row_), balloon(balloon_), game(game_)
{
}

Balloon::~Balloon()
{
}

void Balloon::render() 
{
	/*if (pinchado) {
	
		frameAnimation = textFrameW * int(((SDL_GetTicks() / TIME_PER_FRAME) % 6));
	}*/
	balloon->renderFrame(SDL_Rect{(int) pos.getX(), (int)pos.getY(), width, height }, row, frameAnimation,0 , SDL_FLIP_NONE);

}

bool Balloon::update() 
{
	if (pos.getY()> -50)
	{
		pos = pos - vel;
	}
	else
	{
		return false;
	}
}
