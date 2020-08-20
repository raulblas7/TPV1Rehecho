#include "Bow.h"

Bow::Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_, Game* game_): pos(pos_), vel(vel_), width(width_), height(height_), bow(bow_), game(game_)
{

}

Bow::~Bow()
{
}

void Bow::render()
{
	bow->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
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
		vel = Vector2D(vel.getX(), abs(vel.getY()));
	}
	
}
void Bow::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {

		if (event.key.keysym.sym == SDLK_DOWN) {
			mov = true;

		}
		else  if (event.key.keysym.sym == SDLK_UP) {
			mov = true;
			vel = vel * -1;

		}
		else if (event.key.keysym.sym == SDLK_LEFT && !cargado)
		{
			/*juego->CargaFlecha();*/

			cargado = true;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && cargado)
		{
			/*juego->DisparaFlecha(esqIzq);*/
			cargado = false;
		}
	}

}