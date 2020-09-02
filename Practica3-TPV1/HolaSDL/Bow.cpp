#include "Bow.h"
#include "PlayState.h"


Bow::Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_,Texture* bowC_, GameState* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, bow_, game_), bowC(bowC_)
{
	aux = bow_;
}
void Bow::render()
{
	if (!cargado)
	{
		texture = bowC;
	}
	else
	{
		texture = aux;
	}
	ArrowsGameObject::render();

}

void Bow::update()
{
	if (mov)
	{
		ArrowsGameObject::update();
		if (pos.getY() + height >= 600|| pos.getY() <= 0)
		{
			pos = pos - vel;

		}
		mov = false;
	}
	
}
void Bow::handleEvent(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {

		if (event.key.keysym.sym == SDLK_DOWN) {
			mov = true;
			vel = Vector2D(vel.getX(), abs(vel.getY()));
		}
		else  if (event.key.keysym.sym == SDLK_UP) {
			mov = true;
			vel = Vector2D(vel.getX(), abs(vel.getY())*-1);

		}
		else if (event.key.keysym.sym == SDLK_LEFT && !cargado )
		{
			cargado = true;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && cargado)
		{
			dynamic_cast<PlayState*>(state)->ThrowArrow(pos+ Vector2D(0,height/2));
			cargado = false;
		}
	}

}

void Bow::saveToFile(ofstream& output) {
	output << "Arco" << endl;
	ArrowsGameObject::saveToFile(output);
	if (cargado) output << "cargado" << endl;
	else output << "nocargado" << endl;
}

void Bow::loadFromFile(ifstream& input) {
	ArrowsGameObject::loadFromFile(input);
	string line;
	input >> line;
	if (line == "cargado") {
		cargado = true;
	}
	else cargado = false;
}
