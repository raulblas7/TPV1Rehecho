#include "Butterfly.h"
#include "Game.h"
Butterfly::Butterfly(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* butterfly_, Game* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, butterfly_, game_)
{
	time = SDL_GetTicks();
}

void Butterfly::render()
{
	if (!pinchado) {
		int pin = SDL_GetTicks() - time;
		frameAnimation = pin / TIME_PER_FRAME % 10;

		if (frameAnimation>=10)
		{
			time = SDL_GetTicks();
		}
	}
	texture->renderFrame(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, 0, frameAnimation, 0, SDL_FLIP_NONE);
}

void Butterfly::update()
{
	ArrowsGameObject::update();
	if (!pinchado)
	{
		if (pos.getX() <= 0 || pos.getX() >= 750) {
			vel = Vector2D(-vel.getX(), vel.getY());
		}
		else if (pos.getY() <= 0 || pos.getY() >= 550) {
			vel = Vector2D(vel.getX(), -vel.getY());
		}

		if (game->OnCollision(it))
		{
			pinchado = true;
			pinchazoTime = SDL_GetTicks();
			vel = Vector2D(0, 2);
		}
	}
	else if(SDL_GetTicks()>=pinchazoTime+3000){ game->killObject(it); }
}

void Butterfly::saveToFile(ofstream& output) {
	output << "Mariposa" << endl;
	ArrowsGameObject::saveToFile(output);
}

void Butterfly::loadFromFile(ifstream& input) {
	ArrowsGameObject::loadFromFile(input);
}
