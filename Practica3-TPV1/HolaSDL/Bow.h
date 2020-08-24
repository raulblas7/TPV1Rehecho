#pragma once
#include "Arrow.h"
#include "ArrowsGameObject.h"

class Game;
class Bow:public ArrowsGameObject
{
private:
	Texture* bowC;
	bool cargado = false;
	bool mov = false;


public:
	Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_ ,Texture* bowC_, Game* game_);
	~Bow();
	void render();
	void update();
	void handleEvents(SDL_Event& event);
};

