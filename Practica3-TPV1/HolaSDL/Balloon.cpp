#include "Balloon.h"
#include "Game.h"
//Balloon::Balloon() :pos(), vel(), w(), velocidad(), globo(), explotado(), instPinchazo(), game() {}

Balloon::Balloon(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* balloon_, Game* game_)
	: ArrowsGameObject(pos_, vel_,width_, height_, balloon_,game_), row(row_)
{
}



void Balloon::render() 
{
	if (pinchado) {
	
		int pin = SDL_GetTicks() - pinchazoTime;
		frameAnimation =  pin/ TIME_PER_FRAME % 6;
	}
	texture->renderFrame(SDL_Rect{(int) pos.getX(), (int)pos.getY(), width, height }, row, frameAnimation,0 , SDL_FLIP_NONE);

}

void Balloon::update() 
{
	if (!pinchado)
	{
		ArrowsGameObject::update();
		if (game->OnCollision(it))
		{
			pinchado = true;
			pinchazoTime = SDL_GetTicks();
		}
	}
	if (pos.getY() <= -50 || frameAnimation > 4) {
		game->killObject(it);
	}
}

void Balloon::loadFromFile(ifstream& input)
{
}

void Balloon::saveToFile(ofstream& outuput)
{
}
