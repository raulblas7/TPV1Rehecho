#pragma once
#include "ArrowsGameObject.h"

class Butterfly:public ArrowsGameObject
{
private:
	bool muerta = false;
	bool pinchado = false;
	uint pinchazoTime;
	int frameAnimation = 0;
	uint time;
public:
	Butterfly(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* balloon_, Game* game_);
	~Butterfly() {};
	void render();
	void update();
	SDL_Rect getRect() { return SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }; };
};

