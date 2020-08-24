#include "Bow.h"
#include "Game.h"


Bow::Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_,Texture* bowC_, Game* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, bow_, game_), bowC(bowC_)
{

}

Bow::~Bow()
{
}

void Bow::render()
{
	if (cargado)
	{
		bow->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);

	}
	else
	{
		bowC->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);

	}
}

void Bow::update()
{
	if (mov)
	{
		pos = pos + vel;
		if (pos.getY() + height >= 600|| pos.getY() <= 0)
		{
			pos = pos - vel;

		}
		mov = false;
	}
	
}
void Bow::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {

		if (event.key.keysym.sym == SDLK_DOWN) {
			mov = true;
			vel = Vector2D(vel.getX(), abs(vel.getY()));
		}
		else  if (event.key.keysym.sym == SDLK_UP) {
			mov = true;
			vel = Vector2D(vel.getX(), abs(vel.getY())*-1);

		}
		else if (event.key.keysym.sym == SDLK_LEFT && !cargado && game->GetNumberArrows() > 0)
		{
			cargado = true;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && cargado)
		{
			game->ThrowArrow(pos+ Vector2D(0,height/2));
			cargado = false;
		}
	}

}