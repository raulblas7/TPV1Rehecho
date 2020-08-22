#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"

class Game;
class Bow
{
private:
	Point2D pos;
	Vector2D vel;
	Texture* bow;
	Texture* bowC;
	bool cargado = false;
	int width = 0;
	int height = 0;
	Game* game=nullptr;
	bool mov = false;


public:
	Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_ ,Texture* bowC_, Game* game_);
	~Bow();
	void render();
	void update();
	void handleEvents(SDL_Event& event);
};

