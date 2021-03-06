#include "Reward.h"
#include "PlayState.h"
Reward::Reward(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* reward_, Texture* bubble_, int timePower,GameState* game_)
	: ArrowsGameObject(pos_, vel_, width_, height_, reward_, game_), row(row_), bubble(bubble_),timePower(timePower)
{
}

void Reward::render()
{
	if (!tocado) {
		int pin = SDL_GetTicks() - time;
		frameAnimation = pin / TIME_PER_FRAME % 8;

		if (frameAnimation >= 8)
		{
			time = SDL_GetTicks();
		}


		texture->renderFrame(SDL_Rect{ (int)pos.getX() + width / 4, (int)pos.getY() + height / 4, width / 2, height / 2 },row, frameAnimation, 0, SDL_FLIP_NONE);

		if (burbuja) bubble->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);

	}
}

void Reward::update()
{
	ArrowsGameObject::update();
	if (dynamic_cast<PlayState*>(state)->OnCollision(it) && burbuja )
	{		burbuja = false;
	}
	
	if (  pos.getY() >= 600 || (tocado && timeP + timePower <= SDL_GetTicks() ))
	{
		if (timePower>0)
		{
			accion(false);

		}
		dynamic_cast<PlayState*>(state)->killObject(it);
	}

	
	
}

void Reward::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && !burbuja && !tocado)
	{
		int errorX = abs(event.button.x - pos.getX());
		int errorY = abs(event.button.y - pos.getY());
		if (errorX < 50 && errorY < 50)
		{
			tocado = true;
			accion(true);
			timeP = SDL_GetTicks();
		}
	}
}
void Reward::saveToFile(ofstream& output) {
	output << "Premio" << endl;
	output << row << endl;
	ArrowsGameObject::saveToFile(output);
	if (burbuja) output << "burbuja" << endl;
	else output << "noburbuja" << endl;
}

void Reward::loadFromFile(ifstream& input) {
	ArrowsGameObject::loadFromFile(input);
	string line;
	input >> line;
	if (line == "burbuja") burbuja = true;
	else burbuja = false;
}

